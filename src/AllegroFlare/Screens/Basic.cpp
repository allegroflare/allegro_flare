

#include <AllegroFlare/Screens/Basic.hpp>

#include <iostream>
#include <allegro5/allegro_color.h>
#include <AllegroFlare/ConsoleColor.hpp>
#include <AllegroFlare/Display.hpp>



namespace AllegroFlare
{
namespace Screens
{




//void Screen::create_and_use_backbuffer_sub_bitmap_of(ALLEGRO_BITMAP *new_target)
//{
   //// calling al_get_parent_bitmap on a nullptr causes a crash
   //if (backbuffer_sub_bitmap != nullptr && new_target == al_get_parent_bitmap(backbuffer_sub_bitmap)) return;

   //if (backbuffer_sub_bitmap == nullptr) al_destroy_bitmap(backbuffer_sub_bitmap);

   //backbuffer_sub_bitmap = al_create_sub_bitmap(new_target,
         //0, 0, al_get_bitmap_width(new_target), al_get_bitmap_height(new_target));

   //if (!backbuffer_sub_bitmap) std::cout << "[Screen::Screen()] there was an error creating the backbuffer_sub_bitmap" << std::endl;
//}


Basic::Basic(std::string type)
   : AllegroFlare::ElementID(nullptr)
   , type(type)
   //, display(display)
   //, backbuffer_sub_bitmap(nullptr)
{
}


Basic::~Basic()
{
   //if (backbuffer_sub_bitmap) al_destroy_bitmap(backbuffer_sub_bitmap);
}


void Basic::set_type(std::string type)
{
   this->type = type;
}


std::string Basic::get_type()
{
   return type;
}


bool Basic::is_type(std::string possible_type)
{
   return type == possible_type;
}


//void Basic::prepare_drawing_state(bool prepare_3d)
//{
   //if (backbuffer_sub_bitmap) al_set_target_bitmap(backbuffer_sub_bitmap);
   //else al_set_target_bitmap(al_get_backbuffer(display->al_display));

   //if (prepare_3d)
   //{
      //al_set_render_state(ALLEGRO_DEPTH_TEST, 1);
      //al_set_render_state(ALLEGRO_WRITE_MASK, ALLEGRO_MASK_DEPTH | ALLEGRO_MASK_RGBA);
      //al_clear_depth_buffer(1);
   //}
   //else
   //{
      //al_set_render_state(ALLEGRO_DEPTH_TEST, 0);
   //}
//}


//void Basic::set_on_display(Display *display)
//{
   //this->display = display;
//}


void Basic::on_event(ALLEGRO_EVENT *ev) {}
void Basic::primary_timer_func() {}
void Basic::timer_func() {}
void Basic::mouse_axes_func() {}
void Basic::mouse_warp_func() {}
void Basic::display_switch_in_func() {}
void Basic::display_switch_out_func() {}
void Basic::mouse_down_func() {}
void Basic::mouse_up_func() {}
void Basic::key_down_func(ALLEGRO_EVENT *ev) {}
void Basic::key_up_func(ALLEGRO_EVENT *ev) {}
void Basic::key_char_func(ALLEGRO_EVENT *ev) {}
void Basic::joy_button_down_func(ALLEGRO_EVENT *ev) {}
void Basic::joy_button_up_func(ALLEGRO_EVENT *ev) {}
void Basic::joy_axis_func(ALLEGRO_EVENT *ev) {}
void Basic::joy_config_func(ALLEGRO_EVENT *ev) {}
void Basic::user_event_func(ALLEGRO_EVENT *ev) {}
void Basic::event_emitter_event_func(ALLEGRO_EVENT *ev) {}
void Basic::virtual_control_button_up_func(ALLEGRO_EVENT *ev) {};
void Basic::virtual_control_button_down_func(ALLEGRO_EVENT *ev) {};
void Basic::virtual_control_axis_change_func(ALLEGRO_EVENT *ev) {};
void Basic::native_menu_click_func() {}
void Basic::receive_signal(int signal, void *data) {}
void Basic::receive_signal(std::string const signal, void *data) {}






} // namespace Screens
} // namespace AllegroFlare


