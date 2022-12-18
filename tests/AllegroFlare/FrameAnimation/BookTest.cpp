
#include <gtest/gtest.h>

#include <AllegroFlare/FrameAnimation/Book.hpp>

#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>


using AllegroFlare::FrameAnimation::Book;
using AllegroFlare::FrameAnimation::Animation;



TEST(AllegroFlare_FrameAnimation_BookTest, can_be_created_without_blowing_up)
{
   Book animation_book;
}


TEST(AllegroFlare_FrameAnimation_BookTest, VISUAL__will_load_an_animation)
{
   al_init();
   al_init_image_addon();
   al_init_font_addon();
   al_init_ttf_addon();
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   ALLEGRO_FONT *font = al_load_font("./bin/data/fonts/ChronoTrigger.ttf", -50, 0);

   Book animation_book;
   animation_book.initialize();

   Animation animation = animation_book.find_animation_by_name("blob");
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
      uint32_t frame_id = animation.get_frame_id_at(0.21);
      al_draw_textf(font, ALLEGRO_COLOR{1, 1, 1, 1}, 10, 10, 0, "frame %d", frame_id);

      al_flip_display(); // assumes a rest of 1/60.0f
   }


   al_destroy_font(font);
   al_destroy_display(display);
   al_shutdown_font_addon();
   al_shutdown_ttf_addon();
   al_shutdown_image_addon();
   al_uninstall_system();
}


