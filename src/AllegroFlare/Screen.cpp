

#include <AllegroFlare/Screen.hpp>

#include <iostream>
#include <allegro5/allegro_color.h>
#include <AllegroFlare/Framework.hpp>
#include <AllegroFlare/ConsoleColor.hpp>
#include <AllegroFlare/Display.hpp>




namespace AllegroFlare
{
   void Screen::create_and_use_backbuffer_sub_bitmap_of(ALLEGRO_BITMAP *new_target)
   {
      // calling al_get_parent_bitmap on a nullptr causes a crash
      if (backbuffer_sub_bitmap != nullptr && new_target == al_get_parent_bitmap(backbuffer_sub_bitmap)) return;

      if (backbuffer_sub_bitmap == nullptr) al_destroy_bitmap(backbuffer_sub_bitmap);

      backbuffer_sub_bitmap = al_create_sub_bitmap(new_target,
            0, 0, al_get_bitmap_width(new_target), al_get_bitmap_height(new_target));

      if (!backbuffer_sub_bitmap) std::cout << "[Screen::Screen()] there was an error creating the backbuffer_sub_bitmap" << std::endl;
   }


   Screen::Screen(Framework &framework, Screens &screens, Display *display)
      : backbuffer_sub_bitmap(nullptr)
      , framework(framework)
      , screens(screens)
      , display(display)
   {
      if (!framework.is_initialized())
      {
         std::cout << CONSOLE_COLOR_YELLOW << "[Screen::Screen()] auto-initializing with default config" << CONSOLE_COLOR_DEFAULT << std::endl;
         framework.initialize();
         if (!this->display)
         {
            std::cout << CONSOLE_COLOR_YELLOW << "[Screen::Screen()] auto-creating display" << CONSOLE_COLOR_DEFAULT << std::endl;
            int display_width = framework.get_config().get_or_default_int("", "screen_width", 1280);
            int display_height = framework.get_config().get_or_default_int("", "screen_height", 720);
            this->display = framework.create_display(display_width, display_height);
         }
      }

      if (!display)
      {
         std::cout << "[Screen::Screen()] display is NULL, cannot create backbuffer_sub_bitmap" << std::endl;
      }
      else
      {
         ALLEGRO_BITMAP *backbuffer = al_get_backbuffer(display->al_display);
         create_and_use_backbuffer_sub_bitmap_of(backbuffer);
      }

      screens.add(this);
   }


   Screen::~Screen()
   {
      screens.remove(this);
   }


   void Screen::prepare_drawing_state(bool prepare_3d)
   {
      if (backbuffer_sub_bitmap) al_set_target_bitmap(backbuffer_sub_bitmap);
      else al_set_target_bitmap(al_get_backbuffer(display->al_display));

      if (prepare_3d)
      {
         al_set_render_state(ALLEGRO_DEPTH_TEST, 1);
         al_set_render_state(ALLEGRO_WRITE_MASK, ALLEGRO_MASK_DEPTH | ALLEGRO_MASK_RGBA);
         al_clear_depth_buffer(1);
      }
      else
      {
         al_set_render_state(ALLEGRO_DEPTH_TEST, 0);
      }
   }


   void Screen::set_on_display(Display *display)
   {
      this->display = display;
   }


   void Screen::on_event(ALLEGRO_EVENT *ev) {}
   void Screen::primary_timer_func() {}
   void Screen::timer_func() {}
   void Screen::mouse_axes_func() {}
   void Screen::mouse_warp_func() {}
   void Screen::display_switch_in_func() {}
   void Screen::display_switch_out_func() {}
   void Screen::mouse_down_func() {}
   void Screen::mouse_up_func() {}
   void Screen::key_down_func() {}
   void Screen::key_up_func() {}
   void Screen::key_char_func() {}
   void Screen::joy_button_down_func() {}
   void Screen::joy_button_up_func() {}
   void Screen::joy_axis_func() {}
   void Screen::joy_config_func() {}
   void Screen::user_event_func() {}
   void Screen::native_menu_click_func() {}
   void Screen::receive_signal(int signal, void *data) {}
   void Screen::receive_signal(std::string const signal, void *data) {}
}


