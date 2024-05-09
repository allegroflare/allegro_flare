
#include <gtest/gtest.h>

#include <AllegroFlare/FrameAnimation/Animation.hpp>
#include <AllegroFlare/Testing/ErrorAssertions.hpp>

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

      //Animation animation(sprite_sheet, "my_animation", std::vector<Frame>{
            //{ 1, 0.200f },
            //{ 2, 0.100f },
            //{ 3, 0.200f },
         //},
         //Animation::PLAYMODE_FORWARD_PING_PONG
      //);

      //animation.initialize();
   }
   void setup_animation(std::vector<Frame> frames, Animation::Playmode playmode)
   {
      animation = new Animation(sprite_sheet, "my_animation", frames, playmode); //std::vector<Frame>{
            //{ 1, 0.200f },
            //{ 2, 0.100f },
            //{ 3, 0.200f },
         //},
         //playmode
      //);

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
         animation->draw();

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



TEST_F(AllegroFlare_FrameAnimation_AnimationTest, can_be_created_without_blowing_up)
{
   Animation animation;
}


TEST_F(AllegroFlare_FrameAnimation_AnimationTest,
   set_playspeed_multiplier__with_a_value_less_than_0__will_throw_an_error)
{
   AllegroFlare::FrameAnimation::Animation animation;
   EXPECT_THROW_WITH_MESSAGE(
      animation.set_playspeed_multiplier(-0.0001),
      std::runtime_error,
      "Animation::set_playspeed_multiplier: error: guard \"(playspeed_multiplier >= 0.0f)\" not met"
   );
}


TEST_F(AllegroFlare_FrameAnimation_AnimationTest, will_work_as_expected)
{
   al_init();
   al_init_image_addon();
   al_init_font_addon();
   al_init_ttf_addon();

   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   ALLEGRO_FONT *font = al_load_font("./bin/data/fonts/ChronoTrigger.ttf", -50, 0);
   ALLEGRO_BITMAP *sprite_sheet_bitmap = al_load_bitmap("./bin/data/bitmaps/sprites_grid-x.png");
   EXPECT_NE(nullptr, sprite_sheet_bitmap);
   AllegroFlare::FrameAnimation::SpriteSheet sprite_sheet(sprite_sheet_bitmap, 48, 48, 5);
   sprite_sheet.initialize();

   al_destroy_bitmap(sprite_sheet_bitmap);

   Animation animation(&sprite_sheet, "my_animation", std::vector<Frame>{
         { 1, 0.200f },
         { 2, 0.100f },
         { 3, 0.200f },
      },
      Animation::PLAYMODE_FORWARD_PING_PONG
   );

   animation.initialize();

   
   int frames = 120;
   animation.start();
   for (int i=0; i<frames; i++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 1});

      // update and draw
      animation.update();
      animation.draw();

      // draw info text
      int sprite_sheet_cell_index_num = animation.get_sprite_sheet_cell_index_num_at(0.21);
      al_draw_textf(font, ALLEGRO_COLOR{1, 1, 1, 1}, 10, 10, 0, "frame %d", sprite_sheet_cell_index_num);

      al_flip_display(); // assumes a rest of 1/60.0f
   }

   sprite_sheet.destroy();
   al_destroy_font(font);
   al_destroy_display(display);
   al_shutdown_font_addon();
   al_shutdown_ttf_addon();
   al_shutdown_image_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_FrameAnimation_AnimationTest, before_initialization__some_select_functions_will_throw_an_error)
{
   // Trying this fancy EXPECT_GUARD out here
   // TODO: Clean up the alignment
   EXPECT_THROW_GUARD_ERROR(Animation().start(), "Animation::start", "initialized");
   EXPECT_THROW_GUARD_ERROR(Animation().update(), "Animation::update", "initialized");
   EXPECT_THROW_GUARD_ERROR(Animation().draw(), "Animation::draw", "initialized");
   EXPECT_THROW_GUARD_ERROR(Animation().get_frame_bitmap_now(), "Animation::get_frame_bitmap_now", "initialized");
   EXPECT_THROW_GUARD_ERROR(Animation().get_bitmap_at_frame_num(), "Animation::get_bitmap_at_frame_num", "initialized");
   EXPECT_THROW_GUARD_ERROR(
         Animation().get_sprite_sheet_cell_index_num_now(),
         "Animation::get_sprite_sheet_cell_index_num_now",
         "initialized"
      );
   EXPECT_THROW_GUARD_ERROR(
         Animation().get_frame_bitmap_at_time(),
         "Animation::get_frame_bitmap_at_time",
         "initialized"
      );
   // TODO: Consider more checks here
}


TEST_F(AllegroFlare_FrameAnimation_AnimationTestWithSetup, FOCUS__test_fixture_will_work_as_expected)
{
   setup_animation(
      std::vector<Frame>{
         { 1, 0.200f },
         { 2, 0.100f },
         { 3, 0.200f },
      },
      Animation::PLAYMODE_FORWARD_PING_PONG
   );
   display_subject();
}


