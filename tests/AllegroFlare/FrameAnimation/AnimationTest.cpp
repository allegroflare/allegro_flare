
#include <gtest/gtest.h>

#include <AllegroFlare/FrameAnimation/Animation.hpp>
#include <AllegroFlare/Testing/ErrorAssertions.hpp>

#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>


using AllegroFlare::FrameAnimation::Animation;
using AllegroFlare::FrameAnimation::Frame;
using AllegroFlare::FrameAnimation::SpriteSheet;



TEST(AllegroFlare_FrameAnimation_AnimationTest, can_be_created_without_blowing_up)
{
   Animation animation;
}


TEST(AllegroFlare_FrameAnimation_AnimationTest,
   set_playspeed_multiplier__with_a_value_less_than_0__will_throw_an_error)
{
   AllegroFlare::FrameAnimation::Animation animation;
   EXPECT_THROW_WITH_MESSAGE(
      animation.set_playspeed_multiplier(-0.0001),
      std::runtime_error,
      "Animation::set_playspeed_multiplier: error: guard \"(playspeed_multiplier >= 0.0f)\" not met"
   );
}


TEST(AllegroFlare_FrameAnimation_AnimationTest, DISABLED__dev_test)
{
   al_init();
   al_init_image_addon();
   al_init_font_addon();
   al_init_ttf_addon();


   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   ALLEGRO_BITMAP *sprite_sheet_bitmap = al_load_bitmap("./bin/data/bitmaps/sprites_grid-x.png");
   ALLEGRO_FONT *font = al_load_font("./bin/data/fonts/ChronoTrigger.ttf", -50, 0);
   SpriteSheet sprite_sheet(sprite_sheet_bitmap, 48, 48, 8); // auto-inits
   al_destroy_bitmap(sprite_sheet_bitmap);

   Animation animation(&sprite_sheet, "my_animation", std::vector<Frame>{
         { 1, 0.200f },
         { 2, 0.100f },
         { 3, 0.200f },
      },
      Animation::PLAYMODE_FORWARD_PING_PONG
   );

   
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


   al_destroy_font(font);
   sprite_sheet.destroy();
   al_destroy_display(display);
   al_shutdown_font_addon();
   al_shutdown_ttf_addon();
   al_shutdown_image_addon();
   al_uninstall_system();
}


#define EXPECT_GUARD EXPECT_THROW_GUARD_ERROR


TEST(AllegroFlare_FrameAnimation_AnimationTest, before_initialization__most_functions_will_throw_an_error)
{
   // Trying this out here
   EXPECT_GUARD(Animation().start(),                   "Animation::start",                   "initialized");
   EXPECT_GUARD(Animation().update(),                  "Animation::update",                  "initialized");
   EXPECT_GUARD(Animation().draw(),                    "Animation::draw",                    "initialized");
   //EXPECT_GUARD(Animation().get_num_frames(),        "Animation::get_num_frames",          "initialized");
   EXPECT_GUARD(Animation().get_frame_now(),           "Animation::get_frame_now",           "initialized");
   EXPECT_GUARD(Animation().get_bitmap_at_frame_num(), "Animation::get_bitmap_at_frame_num", "initialized");
   EXPECT_GUARD(Animation().get_sprite_sheet_cell_index_num_now(),        "Animation::get_sprite_sheet_cell_index_num_now",        "initialized");
   EXPECT_GUARD(Animation().get_frame_at(),            "Animation::get_frame_at",            "initialized");
   // TODO: add more checks here
}


TEST(AllegroFlare_FrameAnimation_AnimationTest, DISABLED__dev_test2)
{
   al_init();
   al_init_image_addon();
   al_init_font_addon();
   al_init_ttf_addon();

   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   ALLEGRO_BITMAP *sprite_sheet_bitmap = al_load_bitmap("./bin/data/bitmaps/sprites_grid-x.png");
   ALLEGRO_FONT *font = al_load_font("./bin/data/fonts/ChronoTrigger.ttf", -50, 0);
   SpriteSheet sprite_sheet(sprite_sheet_bitmap, 48, 48, 8); // auto-inits
   al_destroy_bitmap(sprite_sheet_bitmap);

   Animation animation(&sprite_sheet, "my_animation", std::vector<Frame>{});


   
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


   al_destroy_font(font);
   sprite_sheet.destroy();
   al_destroy_display(display);
   al_shutdown_font_addon();
   al_shutdown_ttf_addon();
   al_shutdown_image_addon();
   al_uninstall_system();
}


