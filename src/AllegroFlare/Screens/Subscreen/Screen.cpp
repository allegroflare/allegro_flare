

#include <AllegroFlare/Screens/Subscreen/Screen.hpp>

#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Screens
{
namespace Subscreen
{


Screen::Screen(AllegroFlare::EventEmitter* event_emitter, AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, AllegroFlare::Screens::Subscreen::Element* subscreen_element)
   : AllegroFlare::Screens::Base("AllegroFlare/Screens/Subscreen/Screen")
   , event_emitter(event_emitter)
   , bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , subscreen_element(subscreen_element)
   , on_exit_callback_func()
   , on_exit_callback_func_user_data(nullptr)
   , initialized(false)
{
}


Screen::~Screen()
{
}


void Screen::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   if (get_initialized()) throw std::runtime_error("[Screen::set_event_emitter]: error: guard \"get_initialized()\" not met.");
   this->event_emitter = event_emitter;
}


void Screen::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   if (get_initialized()) throw std::runtime_error("[Screen::set_bitmap_bin]: error: guard \"get_initialized()\" not met.");
   this->bitmap_bin = bitmap_bin;
}


void Screen::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   if (get_initialized()) throw std::runtime_error("[Screen::set_font_bin]: error: guard \"get_initialized()\" not met.");
   this->font_bin = font_bin;
}


void Screen::set_subscreen_element(AllegroFlare::Screens::Subscreen::Element* subscreen_element)
{
   if (get_initialized()) throw std::runtime_error("[Screen::set_subscreen_element]: error: guard \"get_initialized()\" not met.");
   this->subscreen_element = subscreen_element;
}


void Screen::set_on_exit_callback_func(std::function<void(AllegroFlare::Screens::Subscreen::Screen*, void*)> on_exit_callback_func)
{
   this->on_exit_callback_func = on_exit_callback_func;
}


void Screen::set_on_exit_callback_func_user_data(void* on_exit_callback_func_user_data)
{
   this->on_exit_callback_func_user_data = on_exit_callback_func_user_data;
}


AllegroFlare::EventEmitter* Screen::get_event_emitter() const
{
   return event_emitter;
}


AllegroFlare::BitmapBin* Screen::get_bitmap_bin() const
{
   return bitmap_bin;
}


AllegroFlare::FontBin* Screen::get_font_bin() const
{
   return font_bin;
}


AllegroFlare::Screens::Subscreen::Element* Screen::get_subscreen_element() const
{
   return subscreen_element;
}


std::function<void(AllegroFlare::Screens::Subscreen::Screen*, void*)> Screen::get_on_exit_callback_func() const
{
   return on_exit_callback_func;
}


void* Screen::get_on_exit_callback_func_user_data() const
{
   return on_exit_callback_func_user_data;
}


bool Screen::get_initialized() const
{
   return initialized;
}


void Screen::initialize()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::Subscreen::Screen::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Subscreen::Screen::initialize]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::Subscreen::Screen::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Subscreen::Screen::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::Subscreen::Screen::initialize]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Subscreen::Screen::initialize]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::Subscreen::Screen::initialize]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Subscreen::Screen::initialize]: error: guard \"event_emitter\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::Subscreen::Screen::initialize]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Subscreen::Screen::initialize]: error: guard \"bitmap_bin\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::Subscreen::Screen::initialize]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Subscreen::Screen::initialize]: error: guard \"font_bin\" not met");
   }
   if (!(subscreen_element))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::Subscreen::Screen::initialize]: error: guard \"subscreen_element\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Subscreen::Screen::initialize]: error: guard \"subscreen_element\" not met");
   }
   set_update_strategy(AllegroFlare::Screens::Base::UpdateStrategy::SEPARATE_UPDATE_AND_RENDER_FUNCS);
   initialized = true;
   return;
}

void Screen::refresh()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::Subscreen::Screen::refresh]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Subscreen::Screen::refresh]: error: guard \"initialized\" not met");
   }
   subscreen_element->refresh();
   return;
}

void Screen::on_activate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::Subscreen::Screen::on_activate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Subscreen::Screen::on_activate]: error: guard \"initialized\" not met");
   }
   emit_event_to_update_input_hints_bar();
   emit_show_and_size_input_hints_bar_event();
   return;
}

void Screen::on_deactivate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::Subscreen::Screen::on_deactivate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Subscreen::Screen::on_deactivate]: error: guard \"initialized\" not met");
   }
   // TODO: this should be a push/pop style to restore the previous input hints bar state, rather than
   // turning it off. This might be an option to add to the framework
   emit_hide_and_restore_size_input_hints_bar_event();
   return;
}

void Screen::set_background_bitmap(ALLEGRO_BITMAP* background_bitmap)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::Subscreen::Screen::set_background_bitmap]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Subscreen::Screen::set_background_bitmap]: error: guard \"initialized\" not met");
   }
   subscreen_element->set_background_bitmap(background_bitmap); // Not sure what this method is needed for, I might
                                                                // assume the background is controlled as a part of
                                                                // this screen. However, the element may want to
                                                                // control the background so I'm not sure how that
                                                                // might work out.
   return;
}

void Screen::exit_screen()
{
   // TODO: Test this callback
   if (!on_exit_callback_func)
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::Screens::Subscreen::Screen::exit_screen",
         "Expecting an \"on_exit_callback_func\" to be present, but it is not."
      );
   }
   on_exit_callback_func(this, on_exit_callback_func_user_data);
   return;
}

void Screen::emit_event_to_update_input_hints_bar()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::Subscreen::Screen::emit_event_to_update_input_hints_bar]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Subscreen::Screen::emit_event_to_update_input_hints_bar]: error: guard \"initialized\" not met");
   }
   // TODO: Figure out how to handle subscreen-related control hints here.

   // NOTE: Some examples of how hints were previously handled:

   //if (subscreen_element.infer_currently_active_pane_is_rap_sheets_pane())
   //{
      //event_emitter->emit_set_input_hints_bar_event({{
           //"SHIFT", "%SPACE", "%PLUS", "%SPACE", "RIGHT", "%SPACE", "%SLASH", "%SPACE", "LEFT",
              //"%SPACER", "LABEL>>", "Next / Previous tab",
           //"%SEPARATOR",
           //"UP", "%SPACE", "DOWN", "%SPACE", "LEFT", "%SPACE", "RIGHT", "%SPACER", "LABEL>>", "Move cursor",
           //"%SEPARATOR",
           //"X", "%SPACER", "LABEL>>", "Close Chronicle",
      //}});
   //}
   //else if (subscreen_element.infer_currently_active_pane_is_crime_summary_pane())
   //{
      // TODO: add case where crime summary is empty state
      //event_emitter->emit_set_input_hints_bar_event({{
           //"SHIFT", "%SPACE", "%PLUS", "%SPACE", "RIGHT", "%SPACE", "%SLASH", "%SPACE", "LEFT",
              //"%SPACER", "LABEL>>", "Next / Previous tab",
           //"%SEPARATOR",
           //"UP", "%SPACE", "DOWN", "%SPACE", "LEFT", "%SPACE", "RIGHT", "%SPACER", "LABEL>>", "Move camera",
           //"%SEPARATOR",
           //"+", "%SPACE", "%SLASH", "%SPACE", "-", "%SPACER", "LABEL>>", "Zoom",
           //"%SEPARATOR",
           //"N", "%SPACE", "%SLASH", "%SPACE", "P", "%SPACER", "LABEL>>", "Next / Previous page",
           //"%SEPARATOR",
           //"R", "%SPACER", "LABEL>>", "Reset camera",
           //"%SEPARATOR",
           //"X", "%SPACER", "LABEL>>", "Close Chronicle",
      //}});
   //}
   //else if (subscreen_element.infer_currently_active_pane_is_evidence_sheet_pane())
   //{
      //event_emitter->emit_set_input_hints_bar_event({{
           //"SHIFT", "%SPACE", "%PLUS", "%SPACE", "RIGHT", "%SPACE", "%SLASH", "%SPACE", "LEFT",
              //"%SPACER", "LABEL>>", "Next / Previous tab",
           //"%SEPARATOR",
           //"UP", "%SPACE", "DOWN", "%SPACER", "LABEL>>", "Move cursor",
           //"%SEPARATOR",
           //"X", "%SPACER", "LABEL>>", "Close Chronicle",
      //}});
   //}

   return;
}

void Screen::emit_show_and_size_input_hints_bar_event()
{
   event_emitter->emit_show_input_hints_bar_event();
   event_emitter->emit_set_input_hints_bar_backfill_opacity_event(0.0f);
   //event_emitter->emit_set_input_hints_bar_height_event(CatDetective::Chronicle::Chronicle::BLACK_BARS_HEIGHT);
   return;
}

void Screen::emit_hide_and_restore_size_input_hints_bar_event()
{
   event_emitter->emit_hide_input_hints_bar_event();
   event_emitter->emit_set_input_hints_bar_backfill_opacity_event(); // default argument is the system default, 60.0f
   event_emitter->emit_set_input_hints_bar_height_event(); // default argument is the system default, 60.0f
   return;
}

void Screen::move_pane_left()
{
   bool move_pane_was_successful = subscreen_element->move_pane_left();
   if (move_pane_was_successful) emit_event_to_update_input_hints_bar();
   return;
}

void Screen::move_pane_right()
{
   bool move_pane_was_successful = subscreen_element->move_pane_right();
   if (move_pane_was_successful) emit_event_to_update_input_hints_bar();
   return;
}

void Screen::primary_update_func(double time_now, double delta_time)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::Subscreen::Screen::primary_update_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Subscreen::Screen::primary_update_func]: error: guard \"initialized\" not met");
   }
   // Update stuff here (take into account delta_time)
   subscreen_element->update();
   return;
}

void Screen::primary_render_func()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::Subscreen::Screen::primary_render_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Subscreen::Screen::primary_render_func]: error: guard \"initialized\" not met");
   }
   // Render stuff here
   al_clear_to_color(al_color_html("16161d")); // TODO: Not sure if should clear here, probably rely on screen's
                                               // background
   //subscreen_element->update();
   subscreen_element->render();
   //render();
   return;
}

void Screen::key_up_func(ALLEGRO_EVENT* event)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::Subscreen::Screen::key_up_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Subscreen::Screen::key_up_func]: error: guard \"initialized\" not met");
   }
   if (!(event))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::Subscreen::Screen::key_up_func]: error: guard \"event\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Subscreen::Screen::key_up_func]: error: guard \"event\" not met");
   }
   bool shift = event->keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
   switch(event->keyboard.keycode)
   {
     case ALLEGRO_KEY_UP:
       //if (!shift) chronicle_element->cursor_up_unpressed();
       break;

     case ALLEGRO_KEY_DOWN:
       //if (!shift) chronicle_element.cursor_down_unpressed();
       break;

     case ALLEGRO_KEY_LEFT:
       //if (!shift) chronicle_element.cursor_left_unpressed();
       break;

     case ALLEGRO_KEY_RIGHT:
       //if (!shift) chronicle_element.cursor_right_unpressed();
       break;
   }
   return;
}

void Screen::key_down_func(ALLEGRO_EVENT* event)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::Subscreen::Screen::key_down_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Subscreen::Screen::key_down_func]: error: guard \"initialized\" not met");
   }
   if (!(event))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::Subscreen::Screen::key_down_func]: error: guard \"event\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Subscreen::Screen::key_down_func]: error: guard \"event\" not met");
   }
   bool shift = event->keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
   switch(event->keyboard.keycode)
   {
     case ALLEGRO_KEY_UP:
        //if (!shift) chronicle_element.cursor_up_pressed();
     break;

     case ALLEGRO_KEY_DOWN:
        //if (!shift) chronicle_element.cursor_down_pressed();
     break;

     case ALLEGRO_KEY_LEFT:
        //if (!shift) chronicle_element.cursor_left_pressed();
     break;

     case ALLEGRO_KEY_RIGHT:
        //if (!shift) chronicle_element.cursor_right_pressed();
     break;

     //case ALLEGRO_KEY_X:
        // TODO: assess if this is the correct location for emitting this event
        // TODO: ensure missing event_emitter throws error
        //event_emitter->emit_game_event(AllegroFlare::GameEvent("close_chronicle_screen"));
     //break;

     case ALLEGRO_KEY_ESCAPE:
         // TODO: Test this
         // TODO: Add option to disable this, or change the key used to exit
        exit_screen();
     break;
   }
   return;
}

void Screen::key_char_func(ALLEGRO_EVENT* event)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::Subscreen::Screen::key_char_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Subscreen::Screen::key_char_func]: error: guard \"initialized\" not met");
   }
   if (!(event))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::Subscreen::Screen::key_char_func]: error: guard \"event\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Subscreen::Screen::key_char_func]: error: guard \"event\" not met");
   }
   // TODO: Review these keyboard commands and/or map them to virtual controls, joysticks, etc
   bool shift = event->keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
   switch(event->keyboard.keycode)
   {
     case ALLEGRO_KEY_UP:
       //subscreen_element->move_cursor_up();
       break;

     case ALLEGRO_KEY_DOWN:
       //subscreen_element->move_cursor_down();
       break;

     case ALLEGRO_KEY_N:
       //chronicle_element.current_pane_page_next();
       break;

     case ALLEGRO_KEY_P:
       //chronicle_element.current_pane_page_previous();
       break;

     case ALLEGRO_KEY_R:
       //chronicle_element.reset_document_camera();
       break;

     case ALLEGRO_KEY_LEFT:
       //shift ? move_pane_left() : subscreen_element->move_cursor_left();
       break;

     case ALLEGRO_KEY_RIGHT:
       //suscreen_element.move_cursor_down();
       //shift ? move_pane_right() : subscreen_element->move_cursor_right();
       break;

     case ALLEGRO_KEY_PAD_MINUS:
       case ALLEGRO_KEY_MINUS: // (minus)
       //chronicle_element.pane_camera_zoom_out();
       break;

     case ALLEGRO_KEY_PAD_PLUS:
       case ALLEGRO_KEY_EQUALS: // (plus)
       //chronicle_element.pane_camera_zoom_in();
       break;

     // TODO: handle this case
     //case ALLEGRO_KEY_ESCAPE:
       //abort = true;
       //break;
   }
   return;
}


} // namespace Subscreen
} // namespace Screens
} // namespace AllegroFlare


