
#include <gtest/gtest.h>

#include <AllegroFlare/FrameAnimation/Animation.hpp>
#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Camera3D.hpp>
#include <AllegroFlare/Camera2D.hpp>
#include <AllegroFlare/Placement3D.hpp>
#include <AllegroFlare/Rulers.hpp>

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
   }
   virtual void TearDown() override
   {
      if (sprite_sheet)
      {
         sprite_sheet->destroy();
         delete sprite_sheet;
         sprite_sheet = nullptr;
      }

      AllegroFlare::Testing::WithAllegroRenderingFixture::TearDown();
   }
   void setup_sprite_sheet(
         std::string sprite_sheet_bitmap_identifier="sprites_grid-x.png",
         int cell_width=48,
         int cell_height=48,
         int scale=5
      )
   {
      //std::string sprite_sheet_bitmap_identifier = "sprites_grid-x.png";
      ALLEGRO_BITMAP *sprite_sheet_bitmap = get_bitmap_bin_ref().auto_get(sprite_sheet_bitmap_identifier);
      sprite_sheet = new AllegroFlare::FrameAnimation::SpriteSheet(sprite_sheet_bitmap, cell_width, cell_height, scale);
      sprite_sheet->initialize();
      get_bitmap_bin_ref().destroy(sprite_sheet_bitmap_identifier);
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
   CAPTURE__draw_in_context__will_take_into_account_anchors__alignments___sprite_sheet_scales__and__any_\
current_transform__for_the_current_animation_and_frame)
{
   ALLEGRO_TRANSFORM camera_transform;
   al_identity_transform(&camera_transform);
   al_scale_transform(&camera_transform, 4.0, 4.0);
   al_translate_transform(&camera_transform, 1920/2, 1080/2);
   //al_scale_transform(&camera_transform, 1920/2, 1080/2);
   //al_use_transform(&camera_transform);

   ALLEGRO_TRANSFORM hud_transform;
   al_identity_transform(&hud_transform);

   ALLEGRO_FONT *font = get_any_font();

   setup_sprite_sheet();
   
   AllegroFlare::FrameAnimation::Animation *animation = create_animation(
      std::vector<Frame>{
         {
            1,
            0.2f, // duration
            0.5f, // align_x
            1.0f, // align_y
         },
         {
            2,
            0.1f, // duration
            0.5f, // align_x
            1.0f, // align_y
         },
         {
            3,
            0.2f, // duration
            0.5f, // align_x
            1.0f, // align_y
         }
      },
      Animation::PLAYMODE_FORWARD_PING_PONG
   );

   int frames = 120 * 3;
   int frame_width = 0;
   int frame_height = 0;
   int organic_frame_width = 0;
   int organic_frame_height = 0;
   int sprite_sheet_scale = animation->get_sprite_sheet()->get_scale();
   animation->start();
   for (int i=0; i<frames; i++)
   {
      //
      // Update
      //

      animation->update();
      ALLEGRO_BITMAP *this_frame_bitmap = animation->get_frame_bitmap_now();
      if (this_frame_bitmap)
      {
         frame_width = al_get_bitmap_width(this_frame_bitmap);
         frame_height = al_get_bitmap_height(this_frame_bitmap);
         organic_frame_width = frame_width / sprite_sheet_scale;
         organic_frame_height = frame_height / sprite_sheet_scale;
      }

      //
      // Draw
      //

      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 1});
      al_use_transform(&hud_transform);
      draw_rulers();

      al_use_transform(&camera_transform);
      //draw_horizontal_crosshair(0, 0);

      animation->draw_in_context(false, false, true);

      draw_crosshair_blue(0, 0);

      // draw info text
      al_use_transform(&hud_transform);
      int sprite_sheet_cell_index_num = animation->get_sprite_sheet_cell_index_num_now();
      int frame_num_now = animation->get_frame_num_now();

      int l = 0; // l for line
      al_draw_textf(font, ALLEGRO_COLOR{1, 1, 1, 1}, 200, 200+50*l++, 0, "frame %d", sprite_sheet_cell_index_num);
      al_draw_textf(font, ALLEGRO_COLOR{1, 1, 1, 1}, 200, 200+50*l++, 0, "frame_num %d", frame_num_now);
      al_draw_textf(font, ALLEGRO_COLOR{1, 1, 1, 1}, 200, 200+50*l++, 0, "frame_bitmap_width %d", frame_width);
      al_draw_textf(font, ALLEGRO_COLOR{1, 1, 1, 1}, 200, 200+50*l++, 0, "frame_bitmap_height %d", frame_height);
      al_draw_textf(font, ALLEGRO_COLOR{1, 1, 1, 1}, 200, 200+50*l++, 0, "organic_frame_width %d", organic_frame_width);
      al_draw_textf(font, ALLEGRO_COLOR{1, 1, 1, 1}, 200, 200+50*l++, 0, "organic_frame_height %d", organic_frame_height);
      al_draw_textf(font, ALLEGRO_COLOR{1, 1, 1, 1}, 200, 200+50*l++, 0, "sprite_sheet_scale %d", sprite_sheet_scale);

      al_flip_display();
   }
}


TEST_F(AllegroFlare_FrameAnimation_AnimationTestWithAllegroRenderingFixture,
   DISABLED__draw_in_context__will_take_into_account_anchors__alignments___sprite_sheet_scales__and__any_\
current_transform__for_the_current_animation_and_frame__in_a_3d_context)
{
   // TODO: This test
}


TEST_F(AllegroFlare_FrameAnimation_AnimationTestWithAllegroRenderingFixture,
   CAPTURE__draw_in_context__will_take_into_account_flip_x_and_flip_y_arguments)
{
   ALLEGRO_TRANSFORM camera_transform;
   al_identity_transform(&camera_transform);
   al_scale_transform(&camera_transform, 4.0, 4.0);
   al_translate_transform(&camera_transform, 1920/2, 1080/2);
   //al_scale_transform(&camera_transform, 1920/2, 1080/2);
   //al_use_transform(&camera_transform);

   ALLEGRO_TRANSFORM hud_transform;
   al_identity_transform(&hud_transform);

   ALLEGRO_FONT *font = get_any_font();

   setup_sprite_sheet("a_sprite_stip-01.png", 48, 48, 5);
   
   AllegroFlare::FrameAnimation::Animation *animation = create_animation(
      std::vector<Frame>{
         {
            0,
            0.2f, // duration
            0.5f, // align_x
            1.0f, // align_y
         },
         {
            1,
            0.2f, // duration
            0.5f, // align_x
            1.0f, // align_y
         },
         {
            2,
            0.2f, // duration
            0.5f, // align_x
            1.0f, // align_y
         },
         {
            3,
            0.2f, // duration
            0.5f, // align_x
            1.0f, // align_y
         },
         {
            4,
            0.2f, // duration
            0.5f, // align_x
            1.0f, // align_y
         },
         {
            5,
            0.2f, // duration
            0.5f, // align_x
            1.0f, // align_y
         }
      },
      Animation::PLAYMODE_FORWARD_LOOP
   );

   int frames = 120 * 3;
   int frame_width = 0;
   int frame_height = 0;
   int organic_frame_width = 0;
   int organic_frame_height = 0;
   int sprite_sheet_scale = animation->get_sprite_sheet()->get_scale();
   ALLEGRO_TRANSFORM subject_placement_transform;
   animation->start();
   for (int i=0; i<frames; i++)
   {
      //
      // Update
      //

      animation->update();
      ALLEGRO_BITMAP *this_frame_bitmap = animation->get_frame_bitmap_now();
      if (this_frame_bitmap)
      {
         frame_width = al_get_bitmap_width(this_frame_bitmap);
         frame_height = al_get_bitmap_height(this_frame_bitmap);
         organic_frame_width = frame_width / sprite_sheet_scale;
         organic_frame_height = frame_height / sprite_sheet_scale;
      }

      //
      // Draw
      //

      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 1});
      al_use_transform(&hud_transform);
      draw_rulers();

      al_use_transform(&camera_transform);
      //draw_horizontal_crosshair(0, 0);

      float spacing = 300;
      float h_spacing = spacing * 0.5;
      ALLEGRO_COLOR origin_crosshair_color = ALLEGRO_COLOR{1, 1, 0, 1};

      // Normal
      al_identity_transform(&subject_placement_transform);
      al_compose_transform(&subject_placement_transform, &camera_transform);
      al_translate_transform(&subject_placement_transform, -spacing - h_spacing, 0);
      al_use_transform(&subject_placement_transform);
      animation->draw_in_context(false, false, true);
      draw_crosshair(0, 0, origin_crosshair_color, 20.0);

      // Flip x
      al_identity_transform(&subject_placement_transform);
      al_compose_transform(&subject_placement_transform, &camera_transform);
      al_translate_transform(&subject_placement_transform, -h_spacing, 0);
      al_use_transform(&subject_placement_transform);
      animation->draw_in_context(true, false, true);
      draw_crosshair(0, 0, origin_crosshair_color, 20.0);

      // Flip y
      al_identity_transform(&subject_placement_transform);
      al_compose_transform(&subject_placement_transform, &camera_transform);
      al_translate_transform(&subject_placement_transform, h_spacing, 0);
      al_use_transform(&subject_placement_transform);
      animation->draw_in_context(false, true, true);
      draw_crosshair(0, 0, origin_crosshair_color, 20.0);

      // Flip x and y
      al_identity_transform(&subject_placement_transform);
      al_compose_transform(&subject_placement_transform, &camera_transform);
      al_translate_transform(&subject_placement_transform, spacing + h_spacing, 0);
      al_use_transform(&subject_placement_transform);
      animation->draw_in_context(true, true, true);
      draw_crosshair(0, 0, origin_crosshair_color, 20.0);

      // draw info text
      al_use_transform(&hud_transform);
      int sprite_sheet_cell_index_num = animation->get_sprite_sheet_cell_index_num_now();
      int frame_num_now = animation->get_frame_num_now();

      float x = 100;
      float y = 100;
      float lh = 40;
      int l = 0; // l for line
      al_draw_textf(font, ALLEGRO_COLOR{1, 1, 1, 1}, x, y+lh*l++, 0, "frame %d", sprite_sheet_cell_index_num);
      al_draw_textf(font, ALLEGRO_COLOR{1, 1, 1, 1}, x, y+lh*l++, 0, "frame_num %d", frame_num_now);
      al_draw_textf(font, ALLEGRO_COLOR{1, 1, 1, 1}, x, y+lh*l++, 0, "frame_bitmap_width %d", frame_width);
      al_draw_textf(font, ALLEGRO_COLOR{1, 1, 1, 1}, x, y+lh*l++, 0, "frame_bitmap_height %d", frame_height);
      al_draw_textf(font, ALLEGRO_COLOR{1, 1, 1, 1}, x, y+lh*l++, 0, "organic_frame_width %d", organic_frame_width);
      al_draw_textf(font, ALLEGRO_COLOR{1, 1, 1, 1}, x, y+lh*l++, 0, "organic_frame_height %d", organic_frame_height);
      al_draw_textf(font, ALLEGRO_COLOR{1, 1, 1, 1}, x, y+lh*l++, 0, "sprite_sheet_scale %d", sprite_sheet_scale);

      al_flip_display();
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


TEST_F(AllegroFlare_FrameAnimation_AnimationTestWithSetup,
   CAPTURE__draw_in_context_3d_xzy__will_render_as_expected)
   // TODO: Convert this test fixture to derive from WithAllegroRenderingFixture because CAPTURE is not respected
   // otherwise
{
   al_init_primitives_addon();

   setup_animation(
      std::vector<Frame>{
         { 1, 0.2f, 0.5f, 0.0f },
         { 2, 0.1f, 0.5f, 0.0f },
         { 3, 0.2f, 0.5f, 0.0f }
      },
      Animation::PLAYMODE_FORWARD_PING_PONG
   );

   AllegroFlare::Camera3D camera;
   camera.stepout = { 0, 1, 10 };
   camera.spin = 0.125;
   camera.tilt = 0.25;
   AllegroFlare::Camera2D hud_camera;

   AllegroFlare::Placement3D placement;
   placement.position.x = 2;
   placement.position.z = 1;
   placement.rotation.y = 0.125;

   int frames = 240;
   animation->start();
   for (int i=0; i<frames; i++)
   {
      // Update
      animation->update();
      camera.spin -= 0.125/64.0f;
      camera.tilt -= 0.125/256.0f;

      // Render
      camera.setup_projection_on(al_get_backbuffer(al_get_current_display()));
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 1});
      al_clear_depth_buffer(1);
      AllegroFlare::Rulers::draw_3d_ground_plane_grid();

      // update and draw
      placement.start_transform();
      animation->draw_in_context_3d_xzy(false, false, 16, 16, true);
      placement.restore_transform();

      // draw info text
      //hud_camera.setup_dimensional_projection(al_get_backbuffer(al_get_current_display()));
      //int sprite_sheet_cell_index_num = animation->get_sprite_sheet_cell_index_num_at(0.21);
      //al_draw_textf(font, ALLEGRO_COLOR{1, 1, 1, 1}, 10, 10, 0, "frame %d", sprite_sheet_cell_index_num);

      al_flip_display(); // assumes a rest of 1/60.0f
   }
}


