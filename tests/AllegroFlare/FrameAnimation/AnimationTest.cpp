
#include <gtest/gtest.h>

#include <AllegroFlare/FrameAnimation/Animation.hpp>
#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>

#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>


using AllegroFlare::FrameAnimation::Animation;
using AllegroFlare::FrameAnimation::Frame;
using AllegroFlare::FrameAnimation::SpriteSheet;


class AllegroFlare_FrameAnimation_AnimationTest : public testing::Test {};
class AllegroFlare_FrameAnimation_AnimationTestWithSetup : public testing::Test
{
public:
   ALLEGRO_DISPLAY *display;
   ALLEGRO_FONT *font;
   ALLEGRO_BITMAP *sprite_sheet_bitmap;
   Animation *animation;
   AllegroFlare::FrameAnimation::SpriteSheet *sprite_sheet;

   AllegroFlare_FrameAnimation_AnimationTestWithSetup()
      : display(nullptr)
      , font(nullptr)
      , sprite_sheet_bitmap(nullptr)
      , animation(nullptr)
   {}
   virtual void SetUp() override
   {
      al_init();
      al_init_image_addon();
      al_init_font_addon();
      al_init_ttf_addon();

      display = al_create_display(1920, 1080);
      font = al_load_font("./bin/data/fonts/ChronoTrigger.ttf", -50, 0);
      sprite_sheet_bitmap = al_load_bitmap("./bin/data/bitmaps/sprites_grid-x.png");

      EXPECT_NE(nullptr, sprite_sheet_bitmap);

      sprite_sheet = new AllegroFlare::FrameAnimation::SpriteSheet(sprite_sheet_bitmap, 48, 48, 5);
      sprite_sheet->initialize();

      al_destroy_bitmap(sprite_sheet_bitmap);
   }
   void setup_animation(std::vector<Frame> frames, Animation::Playmode playmode)
   {
      animation = new Animation(sprite_sheet, "my_animation", frames, playmode);
      animation->initialize();
   }
   void display_subject()
   {
      int frames = 120;
      animation->start();
      for (int i=0; i<frames; i++)
      {
         al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 1});

         // update and draw
         animation->update();
         animation->draw_raw();

         // draw info text
         int sprite_sheet_cell_index_num = animation->get_sprite_sheet_cell_index_num_at(0.21);
         al_draw_textf(font, ALLEGRO_COLOR{1, 1, 1, 1}, 10, 10, 0, "frame %d", sprite_sheet_cell_index_num);

         al_flip_display(); // assumes a rest of 1/60.0f
      }
   }
   virtual void TearDown() override
   {
      sprite_sheet->destroy();
      al_destroy_font(font);
      al_destroy_display(display);
      al_shutdown_font_addon();
      al_shutdown_ttf_addon();
      al_shutdown_image_addon();
      al_uninstall_system();
   }
};
class AllegroFlare_FrameAnimation_AnimationTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{
public:
   AllegroFlare::FrameAnimation::SpriteSheet *sprite_sheet;

   AllegroFlare_FrameAnimation_AnimationTestWithAllegroRenderingFixture()
      : sprite_sheet(nullptr)
   {
   }
   virtual void SetUp() override
   {
      AllegroFlare::Testing::WithAllegroRenderingFixture::SetUp();

      std::string sprite_sheet_bitmap_identifier = "sprites_grid-x.png";
      ALLEGRO_BITMAP *sprite_sheet_bitmap = get_bitmap_bin_ref().auto_get(sprite_sheet_bitmap_identifier);
      sprite_sheet = new AllegroFlare::FrameAnimation::SpriteSheet(sprite_sheet_bitmap, 48, 48, 5);
      sprite_sheet->initialize();
      get_bitmap_bin_ref().destroy(sprite_sheet_bitmap_identifier);
   }
   virtual void TearDown() override
   {
      sprite_sheet->destroy();
      delete sprite_sheet;
      sprite_sheet = nullptr;

      AllegroFlare::Testing::WithAllegroRenderingFixture::TearDown();
   }
   AllegroFlare::FrameAnimation::Animation *create_animation(std::vector<Frame> frames, Animation::Playmode playmode)
   {
      AllegroFlare::FrameAnimation::Animation *animation =
         new Animation(sprite_sheet, "my_animation", frames, playmode);
      animation->initialize();
      return animation;
   }
};



TEST_F(AllegroFlare_FrameAnimation_AnimationTest, can_be_created_without_blowing_up)
{
   Animation animation;
}


TEST_F(AllegroFlare_FrameAnimation_AnimationTest, before_initialization__some_select_functions_will_throw_an_error)
{
   // Trying this fancy EXPECT_GUARD out here
   // TODO: Clean up the alignment
   EXPECT_THROW_GUARD_ERROR(Animation().start(), "AllegroFlare::FrameAnimation::Animation::start", "initialized");
   EXPECT_THROW_GUARD_ERROR(Animation().update(), "AllegroFlare::FrameAnimation::Animation::update", "initialized");
   EXPECT_THROW_GUARD_ERROR(Animation().draw(), "AllegroFlare::FrameAnimation::Animation::draw", "initialized");
   EXPECT_THROW_GUARD_ERROR(
         Animation().get_frame_bitmap_now(),
         "AllegroFlare::FrameAnimation::Animation::get_frame_bitmap_now",
         "initialized"
      );
   EXPECT_THROW_GUARD_ERROR(
         Animation().get_bitmap_at_frame_num(),
         "AllegroFlare::FrameAnimation::Animation::get_bitmap_at_frame_num",
         "initialized"
      );
   EXPECT_THROW_GUARD_ERROR(
         Animation().get_sprite_sheet_cell_index_num_now(),
         "AllegroFlare::FrameAnimation::Animation::get_sprite_sheet_cell_index_num_now",
         "initialized"
      );
   EXPECT_THROW_GUARD_ERROR(
         Animation().get_frame_bitmap_at_time(),
         "AllegroFlare::FrameAnimation::Animation::get_frame_bitmap_at_time",
         "initialized"
      );
   // TODO: Consider more checks here
}


TEST_F(AllegroFlare_FrameAnimation_AnimationTest,
   set_playspeed_multiplier__with_a_value_less_than_0__will_throw_an_error)
{
   AllegroFlare::FrameAnimation::Animation animation;
   EXPECT_THROW_GUARD_ERROR(
      animation.set_playspeed_multiplier(-0.0001),
      "AllegroFlare::FrameAnimation::Animation::set_playspeed_multiplier",
      "(playspeed_multiplier >= 0.0f)"
   );
}


TEST_F(AllegroFlare_FrameAnimation_AnimationTestWithSetup, test_fixture_will_work_as_expected)
{
   setup_animation(
      std::vector<Frame>{{ 1, 0.2f }, { 2, 0.1f }, { 3, 0.2f }},
      Animation::PLAYMODE_FORWARD_PING_PONG
   );
   display_subject();
}


TEST_F(AllegroFlare_FrameAnimation_AnimationTestWithAllegroRenderingFixture,
   FOCUS__draw__will_take_into_account_anchors_alignments_and_sprite_sheet_scales)
{
   //ALLEGRO_TRANSFORM camera;
   //al_identity_transform(&t);
   //al_translate_transform(&t, 1920/2, 1080/2);
   //al_use_transform(&t);
   ALLEGRO_FONT *font = get_any_font();
   
   AllegroFlare::FrameAnimation::Animation *animation = create_animation(
      std::vector<Frame>{{ 1, 0.2f }, { 2, 0.1f }, { 3, 0.2f }},
      Animation::PLAYMODE_FORWARD_PING_PONG
   );

   //setup_animation(
      //std::vector<Frame>{{ 1, 0.2f }, { 2, 0.1f }, { 3, 0.2f }},
      //Animation::PLAYMODE_FORWARD_PING_PONG
   //);

   int frames = 120;
   animation->start();
   for (int i=0; i<frames; i++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 1});

      // update and draw
      animation->update();
      animation->draw();

      // draw info text
      int sprite_sheet_cell_index_num = animation->get_sprite_sheet_cell_index_num_now();
      int frame_num_now = animation->get_frame_num_now();

//get_sprite_sheet_cell_index_num_at(0.21);
//get_frame_num_now

      al_draw_textf(font, ALLEGRO_COLOR{1, 1, 1, 1}, 10, 10, 0, "frame %d", sprite_sheet_cell_index_num);
      al_draw_textf(font, ALLEGRO_COLOR{1, 1, 1, 1}, 10, 50, 0, "frame_num %d", frame_num_now);
//get_frame_num_now

      al_flip_display(); // assumes a rest of 1/60.0f
   }
}


TEST_F(AllegroFlare_FrameAnimation_AnimationTestWithSetup, 
   get_sprite_sheet_cell_index_num_at__on_a_PLAYMODE_FORWARD_ONCE__will_return_the_cell_index_num)
{
   setup_animation(
      std::vector<Frame>{{ 1, 0.2f }, { 2, 0.1f }, { 3, 0.2f }},
      Animation::PLAYMODE_FORWARD_ONCE
   );

   EXPECT_EQ(1, animation->get_sprite_sheet_cell_index_num_at(0.0));
   EXPECT_EQ(1, animation->get_sprite_sheet_cell_index_num_at(0.101));
   EXPECT_EQ(1, animation->get_sprite_sheet_cell_index_num_at(0.199));

   EXPECT_EQ(2, animation->get_sprite_sheet_cell_index_num_at(0.2));
   EXPECT_EQ(2, animation->get_sprite_sheet_cell_index_num_at(0.201));
   EXPECT_EQ(2, animation->get_sprite_sheet_cell_index_num_at(0.299));

   EXPECT_EQ(3, animation->get_sprite_sheet_cell_index_num_at(0.3));
   EXPECT_EQ(3, animation->get_sprite_sheet_cell_index_num_at(0.301));
   EXPECT_EQ(3, animation->get_sprite_sheet_cell_index_num_at(0.499));

   EXPECT_EQ(-1, animation->get_sprite_sheet_cell_index_num_at(0.5001f));
}


TEST_F(AllegroFlare_FrameAnimation_AnimationTestWithSetup, 
   get_sprite_sheet_cell_index_num_at__on_a_PLAYMODE_FORWARD_ONCE_AND_HOLD_LAST_FRAME__will_return_the_cell_index_num)
{
   setup_animation(
      std::vector<Frame>{{ 1, 0.2f }, { 2, 0.1f }, { 3, 0.2f }},
      Animation::PLAYMODE_FORWARD_ONCE_AND_HOLD_LAST_FRAME
   );

   EXPECT_EQ(1, animation->get_sprite_sheet_cell_index_num_at(0.0));
   EXPECT_EQ(1, animation->get_sprite_sheet_cell_index_num_at(0.101));
   EXPECT_EQ(1, animation->get_sprite_sheet_cell_index_num_at(0.199));

   EXPECT_EQ(2, animation->get_sprite_sheet_cell_index_num_at(0.2));
   EXPECT_EQ(2, animation->get_sprite_sheet_cell_index_num_at(0.201));
   EXPECT_EQ(2, animation->get_sprite_sheet_cell_index_num_at(0.299));

   EXPECT_EQ(3, animation->get_sprite_sheet_cell_index_num_at(0.3));
   EXPECT_EQ(3, animation->get_sprite_sheet_cell_index_num_at(0.301));
   EXPECT_EQ(3, animation->get_sprite_sheet_cell_index_num_at(0.499));

   EXPECT_EQ(3, animation->get_sprite_sheet_cell_index_num_at(0.5001f));
   EXPECT_EQ(3, animation->get_sprite_sheet_cell_index_num_at(0.9999f));
   EXPECT_EQ(3, animation->get_sprite_sheet_cell_index_num_at(9999.9999f));
}


TEST_F(AllegroFlare_FrameAnimation_AnimationTestWithSetup, 
   get_sprite_sheet_cell_index_num_at__on_a_PLAYMODE_FORWARD_ONCE_AND_HOLD_LAST_FRAME__when_there_are_no_frames__will_\
return_the_expected_index_num)
{
   setup_animation(
      std::vector<Frame>{},
      Animation::PLAYMODE_FORWARD_ONCE_AND_HOLD_LAST_FRAME
   );

   EXPECT_EQ(-1, animation->get_sprite_sheet_cell_index_num_at(0.0f));
   EXPECT_EQ(-1, animation->get_sprite_sheet_cell_index_num_at(0.5f));
   EXPECT_EQ(-1, animation->get_sprite_sheet_cell_index_num_at(0.9999f));
   EXPECT_EQ(-1, animation->get_sprite_sheet_cell_index_num_at(9999.9999f));
}


TEST_F(AllegroFlare_FrameAnimation_AnimationTestWithSetup, 
   get_sprite_sheet_cell_index_num_at__on_a_PLAYMODE_FORWARD_PING_PONG__will_return_the_expected_cell_index_num)
{
   setup_animation(
      std::vector<Frame>{{ 1, 0.2f }, { 2, 0.1f }, { 3, 0.2f }},
      Animation::PLAYMODE_FORWARD_PING_PONG
   );

   EXPECT_EQ(1, animation->get_sprite_sheet_cell_index_num_at(0.0));
   EXPECT_EQ(1, animation->get_sprite_sheet_cell_index_num_at(0.101));
   EXPECT_EQ(1, animation->get_sprite_sheet_cell_index_num_at(0.199));

   EXPECT_EQ(2, animation->get_sprite_sheet_cell_index_num_at(0.2));
   EXPECT_EQ(2, animation->get_sprite_sheet_cell_index_num_at(0.201));
   EXPECT_EQ(2, animation->get_sprite_sheet_cell_index_num_at(0.299));

   EXPECT_EQ(3, animation->get_sprite_sheet_cell_index_num_at(0.3));
   EXPECT_EQ(3, animation->get_sprite_sheet_cell_index_num_at(0.301));
   EXPECT_EQ(3, animation->get_sprite_sheet_cell_index_num_at(0.499));

   // At the last timeframe
   EXPECT_EQ(3, animation->get_sprite_sheet_cell_index_num_at(0.5f));

   // In the "pong" part of the "ping-pong"
   EXPECT_EQ(3, animation->get_sprite_sheet_cell_index_num_at(0.5001f));
   EXPECT_EQ(3, animation->get_sprite_sheet_cell_index_num_at(0.6999f));

   EXPECT_EQ(3, animation->get_sprite_sheet_cell_index_num_at(0.7f)); // Should this be frame 3 though, technically?

   EXPECT_EQ(2, animation->get_sprite_sheet_cell_index_num_at(0.7001f));
   EXPECT_EQ(2, animation->get_sprite_sheet_cell_index_num_at(0.7999f));

   EXPECT_EQ(1, animation->get_sprite_sheet_cell_index_num_at(0.8f)); // Should this be frame 2?

   // Repeating on the ping
   EXPECT_EQ(1, animation->get_sprite_sheet_cell_index_num_at(0.999f));
   EXPECT_EQ(1, animation->get_sprite_sheet_cell_index_num_at(1.0f));
   EXPECT_EQ(1, animation->get_sprite_sheet_cell_index_num_at(1.199f));
   EXPECT_EQ(2, animation->get_sprite_sheet_cell_index_num_at(1.2f));
}


