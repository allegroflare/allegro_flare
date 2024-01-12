

#include <AllegroFlare/Screens/DisplaySettings.hpp>

#include <AllegroFlare/Elements/UI/IntSpinner.hpp>
#include <AllegroFlare/Elements/UI/SliderToggle.hpp>
#include <AllegroFlare/Logger.hpp>
#include <AllegroFlare/Screens/DisplaySettings.hpp>
#include <AllegroFlare/VirtualControllers/GenericController.hpp>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Screens
{


DisplaySettings::DisplaySettings(AllegroFlare::EventEmitter* event_emitter, AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, AllegroFlare::ModelBin* model_bin, AllegroFlare::DisplaySettingsInterfaces::Base* display_settings_interface, int base_font_size)
   : AllegroFlare::Screens::Base(AllegroFlare::Screens::DisplaySettings::TYPE)
   , event_emitter(event_emitter)
   , bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , model_bin(model_bin)
   , display_settings_interface(display_settings_interface)
   , on_exit_callback_func()
   , on_exit_callback_func_user_data(nullptr)
   , surface_width(1920)
   , surface_height(1080)
   , base_font_size(base_font_size)
   , cursor_y(0)
   , cursor_x(0)
   , up_pressed(false)
   , up_pressed_at(0)
   , down_pressed(false)
   , down_pressed_at(0)
   , initialized(false)
{
}


DisplaySettings::~DisplaySettings()
{
}


void DisplaySettings::set_on_exit_callback_func(std::function<void(AllegroFlare::Screens::DisplaySettings*, void*)> on_exit_callback_func)
{
   this->on_exit_callback_func = on_exit_callback_func;
}


void DisplaySettings::set_on_exit_callback_func_user_data(void* on_exit_callback_func_user_data)
{
   this->on_exit_callback_func_user_data = on_exit_callback_func_user_data;
}


void DisplaySettings::set_surface_height(int surface_height)
{
   this->surface_height = surface_height;
}


void DisplaySettings::set_base_font_size(int base_font_size)
{
   this->base_font_size = base_font_size;
}


AllegroFlare::DisplaySettingsInterfaces::Base* DisplaySettings::get_display_settings_interface() const
{
   return display_settings_interface;
}


std::function<void(AllegroFlare::Screens::DisplaySettings*, void*)> DisplaySettings::get_on_exit_callback_func() const
{
   return on_exit_callback_func;
}


void* DisplaySettings::get_on_exit_callback_func_user_data() const
{
   return on_exit_callback_func_user_data;
}


int DisplaySettings::get_surface_width() const
{
   return surface_width;
}


int DisplaySettings::get_surface_height() const
{
   return surface_height;
}


int DisplaySettings::get_base_font_size() const
{
   return base_font_size;
}


void DisplaySettings::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[DisplaySettings::set_event_emitter]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DisplaySettings::set_event_emitter: error: guard \"(!initialized)\" not met");
   }
   this->event_emitter = event_emitter;
   return;
}

void DisplaySettings::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[DisplaySettings::set_bitmap_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DisplaySettings::set_bitmap_bin: error: guard \"(!initialized)\" not met");
   }
   this->bitmap_bin = bitmap_bin;
   return;
}

void DisplaySettings::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[DisplaySettings::set_font_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DisplaySettings::set_font_bin: error: guard \"(!initialized)\" not met");
   }
   this->font_bin = font_bin;
   return;
}

void DisplaySettings::set_model_bin(AllegroFlare::ModelBin* model_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[DisplaySettings::set_model_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DisplaySettings::set_model_bin: error: guard \"(!initialized)\" not met");
   }
   this->model_bin = model_bin;
   return;
}

void DisplaySettings::set_display_settings_interface(AllegroFlare::DisplaySettingsInterfaces::Base* display_settings_interface)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[DisplaySettings::set_display_settings_interface]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DisplaySettings::set_display_settings_interface: error: guard \"(!initialized)\" not met");
   }
   this->display_settings_interface = display_settings_interface;
   return;
}

void DisplaySettings::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[DisplaySettings::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DisplaySettings::initialize: error: guard \"(!initialized)\" not met");
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[DisplaySettings::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DisplaySettings::initialize: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[DisplaySettings::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DisplaySettings::initialize: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[DisplaySettings::initialize]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DisplaySettings::initialize: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[DisplaySettings::initialize]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DisplaySettings::initialize: error: guard \"event_emitter\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[DisplaySettings::initialize]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DisplaySettings::initialize: error: guard \"bitmap_bin\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[DisplaySettings::initialize]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DisplaySettings::initialize: error: guard \"font_bin\" not met");
   }
   if (!(model_bin))
   {
      std::stringstream error_message;
      error_message << "[DisplaySettings::initialize]: error: guard \"model_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DisplaySettings::initialize: error: guard \"model_bin\" not met");
   }
   if (!(display_settings_interface))
   {
      std::stringstream error_message;
      error_message << "[DisplaySettings::initialize]: error: guard \"display_settings_interface\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DisplaySettings::initialize: error: guard \"display_settings_interface\" not met");
   }
   set_update_strategy(AllegroFlare::Screens::Base::UpdateStrategy::SEPARATE_UPDATE_AND_RENDER_FUNCS);
   initialized = true;
   return;
}

void DisplaySettings::exit_screen()
{
   if (on_exit_callback_func)
   {
      on_exit_callback_func(this, on_exit_callback_func_user_data);
   }
   else
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::Screens::DisplaySettings::exit_screen",
         "Expecting an \"on_exit_callback_func\" to be present, but it is not."
      );
   }

   return;
}

void DisplaySettings::on_activate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[DisplaySettings::on_activate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DisplaySettings::on_activate: error: guard \"initialized\" not met");
   }
   //emit_event_to_update_input_hints_bar();
   //emit_show_and_size_input_hints_bar_event();
   deactivate_up_down_keypress_repeat_tracking();
   return;
}

void DisplaySettings::on_deactivate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[DisplaySettings::on_deactivate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DisplaySettings::on_deactivate: error: guard \"initialized\" not met");
   }
   //emit_hide_and_restore_size_input_hints_bar_event();
   deactivate_up_down_keypress_repeat_tracking();
   return;
}

void DisplaySettings::deactivate_up_down_keypress_repeat_tracking()
{
   up_pressed = false;
   up_pressed_at = 0;
   down_pressed = false;
   down_pressed_at = 0;
   return;
}

void DisplaySettings::move_cursor_up()
{
   if (cursor_x == 0)
   {
      cursor_y--;
      if (cursor_y < 0) cursor_y = 0;
   }
   else
   {
      increment_current_option();
      // Move cursor within the current element
   }
   return;
}

void DisplaySettings::move_cursor_down()
{
   if (cursor_x == 0)
   {
      cursor_y++;
      if (cursor_y >= infer_num_elements()) cursor_y = (infer_num_elements() - 1);
   }
   else
   {
      decrement_current_option();
      // Move cursor within the current element
   }
   return;
}

void DisplaySettings::move_cursor_left()
{
   cursor_x--;
   if (cursor_x < 0) cursor_x = 0;
   return;
}

void DisplaySettings::move_cursor_right()
{
   cursor_x++;
   if (cursor_x >= infer_current_element_depth()) cursor_x = (infer_current_element_depth() - 1);
   return;
}

int DisplaySettings::infer_num_elements()
{
   return 6;
}

int DisplaySettings::infer_current_element_depth()
{
   if (cursor_y == 1)
   {
      bool is_disabled = obtain_fullscreen_status();
      if (is_disabled)
      {
         return 1;
      }
      else
      {
         return 3;
      }
   }
   return 1;
}

bool DisplaySettings::is_cursor_at(int x, int y)
{
   return (cursor_x == x && cursor_y == y);
}

void DisplaySettings::activate_current_option()
{
   if (cursor_y == 0) display_settings_interface->toggle_fullscreen();
   else if (cursor_y == 3) display_settings_interface->toggle_inhibit_screensaver();
   else if (cursor_y == 4) display_settings_interface->toggle_hide_mouse_cursor();
   else if (cursor_y == (infer_num_elements() - 1))
   {
      exit_screen();
   }
   return;
}

void DisplaySettings::increment_current_option()
{
   //std::cout << "-- increment" << std::endl;
   //if (cursor_y == 1) // Window size
   //{
      //bool is_disabled = obtain_fullscreen_status();

      //if (!is_disabled)
      //{
         if (is_cursor_at(1, 1))
         {
            // increment display width
            int display_width;
            int display_height;
            std::tie(display_width, display_height) = obtain_display_dimensions();
            // NOTE: For some reason, macos only supports increments of two here, otherwise there are glitches
            display_settings_interface->set_window_size(display_width+2, display_height);
         }
         else if (is_cursor_at(2, 1))
         {
            // increment display height
            int display_width;
            int display_height;
            std::tie(display_width, display_height) = obtain_display_dimensions();
            // NOTE: For some reason, macos only supports increments of two here, otherwise there are glitches
            display_settings_interface->set_window_size(display_width, display_height+2);
         }
      //}
   //}
   return;
}

void DisplaySettings::decrement_current_option()
{
   //std::cout << "-- decrement" << std::endl;

   if (is_cursor_at(1, 1))
   {
      // decrement display width
      int display_width;
      int display_height;
      std::tie(display_width, display_height) = obtain_display_dimensions();
      // NOTE: For some reason, macos only supports increments of two here, otherwise there are glitches
      display_settings_interface->set_window_size(display_width-2, display_height);
   }
   else if (is_cursor_at(2, 1))
   {
      // decrement display height
      int display_width;
      int display_height;
      std::tie(display_width, display_height) = obtain_display_dimensions();
      // NOTE: For some reason, macos only supports increments of two here, otherwise there are glitches
      display_settings_interface->set_window_size(display_width, display_height-2);
   }
   return;
}

void DisplaySettings::update()
{
   do_manual_key_repat_logic();
   return;
}

void DisplaySettings::render()
{
   ALLEGRO_FONT *heading_font = obtain_heading_font();

   float x_nud = 6;
   float left_column_x = 320 + x_nud;
   float column1_x = 320 + x_nud;
   float column2_x = 640 + x_nud;
   float column3_x = 970 + x_nud;

   float column2_c = column2_x + (column3_x - column2_x) / 2;

   float settings_list_y = 368;
   float row_h = 110; // 160
   int row_counter = 0;
   float row_y = settings_list_y + row_counter * row_h;

   // Draw the heading
   al_draw_text(
      heading_font,
      ALLEGRO_COLOR{1, 1, 1, 1},
      320,
      150, //surface_height/2-100,
      ALLEGRO_ALIGN_LEFT,
      "DISPLAY SETTINGS"
   );



   //
   // Draw each settings option in the list
   //

   float cursor_off = 52;
   if (cursor_y == row_counter) draw_cursor_pointer(left_column_x - cursor_off, row_y, ALLEGRO_COLOR{1, 1, 1, 1});


   {
      draw_label("Fullscreen", column1_x, row_y);
      draw_slider_toggle_box(obtain_fullscreen_status(), column2_x, row_y);
   }


   row_counter++;
   row_y = settings_list_y + row_counter * row_h;
   if (cursor_y == row_counter) draw_cursor_pointer(left_column_x - cursor_off, row_y, ALLEGRO_COLOR{1, 1, 1, 1});


   {
      bool is_disabled = obtain_fullscreen_status();
      int window_width;
      int window_height;
      std::tie(window_width, window_height) = obtain_window_dimensions();
      float spacing = 160;
      draw_label("Window Size", column1_x, row_y);
      draw_int_spinner(window_width, is_cursor_at(1, row_counter), column2_x, row_y, is_disabled);
      draw_int_spinner(window_height, is_cursor_at(2, row_counter), column2_x + spacing, row_y, is_disabled);
      std::string helper_text;
      if (is_disabled)
      {
         helper_text = "Cannot change window size while in fullscreen mode.";
      }
      else
      {
         //helper_text = "The window size while not in fullscreen mode. This currently cannot be changed.";
      }
      if (!helper_text.empty()) draw_helper_text(helper_text, column3_x, row_y);
   }


   row_counter++;
   row_y = settings_list_y + row_counter * row_h;
   if (cursor_y == row_counter) draw_cursor_pointer(left_column_x - cursor_off, row_y, ALLEGRO_COLOR{1, 1, 1, 1});


   {
      int display_width;
      int display_height;
      std::tie(display_width, display_height) = obtain_display_dimensions();
      float spacing = 160;
      draw_label("Actual Display Size", column1_x, row_y);
      draw_int_spinner(display_width, is_cursor_at(1, row_counter), column2_x, row_y, true);
      draw_int_spinner(display_height, is_cursor_at(2, row_counter), column2_x + spacing, row_y, true);
   }


   row_counter++;
   row_y = settings_list_y + row_counter * row_h;
   if (cursor_y == row_counter) draw_cursor_pointer(left_column_x - cursor_off, row_y, ALLEGRO_COLOR{1, 1, 1, 1});


   {
      draw_label("Inhibit screensaver", column1_x, row_y);
      draw_slider_toggle_box(obtain_screensaver_inhibited(), column2_x, row_y);
      draw_helper_text(
         "When on, prevents your computer from starting the screensaver while the game is running.",
         column3_x, row_y);
   }


   row_counter++;
   row_y = settings_list_y + row_counter * row_h;
   if (cursor_y == row_counter) draw_cursor_pointer(left_column_x - cursor_off, row_y, ALLEGRO_COLOR{1, 1, 1, 1});


   {
      draw_label("Hide mouse cursor", column1_x, row_y);
      draw_slider_toggle_box(obtain_mouse_cursor_hidden(), column2_x, row_y);
   }


   row_counter++;
   row_y = settings_list_y + row_counter * row_h;
   if (cursor_y == row_counter) draw_cursor_pointer(left_column_x - cursor_off, row_y, ALLEGRO_COLOR{1, 1, 1, 1});


   {
      draw_label("Exit", column1_x, row_y);
   }


   row_counter++;
   row_y = settings_list_y + row_counter * row_h;
   if (cursor_y == row_counter) draw_cursor_pointer(left_column_x - cursor_off, row_y, ALLEGRO_COLOR{1, 1, 1, 1});
   //if (cursor_y == row_counter) al_draw_filled_circle(left_column_x - 40, row_y, 8, ALLEGRO_COLOR{1, 1, 1, 1});




   return;
}

void DisplaySettings::do_manual_key_repat_logic()
{
   double time_now = al_get_time();
   double repeat_duration = 0.3;
   if (up_pressed || down_pressed)
   {
      static int mod_interval = 3;

      // Key up press
      if (up_pressed)
      {
         double up_pressed_age = time_now - up_pressed_at;
         if (up_pressed_age > repeat_duration)
         {
            mod_interval++;
            if (mod_interval > 3)
            {
               move_cursor_up();
            }
         }
      }

      // Key down press
      if (down_pressed)
      {
         double down_pressed_age = time_now - down_pressed_at;
         if (down_pressed_age > repeat_duration)
         {
            mod_interval++;
            if (mod_interval > 3)
            {
               move_cursor_down();
            }
         }
      }
   }
   return;
}

void DisplaySettings::primary_update_func(double time_now, double delta_time)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[DisplaySettings::primary_update_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DisplaySettings::primary_update_func: error: guard \"initialized\" not met");
   }
   update();
   return;
}

void DisplaySettings::primary_render_func()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[DisplaySettings::primary_render_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DisplaySettings::primary_render_func: error: guard \"initialized\" not met");
   }
   render();
   return;
}

void DisplaySettings::draw_cursor_pointer(float x, float y, ALLEGRO_COLOR color)
{
   float width = 36;
   float height = 24;
   x -= width;
   y -= height * 0.5;
   al_draw_filled_triangle(x, y, x+width, y+height*0.5, x, y+height, color);
   return;
}

void DisplaySettings::draw_label(std::string label, float x, float y)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[DisplaySettings::draw_label]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DisplaySettings::draw_label: error: guard \"initialized\" not met");
   }
   ALLEGRO_FONT *label_font = obtain_label_font();
   int h_line_height = al_get_font_line_height(label_font) / 2;
   al_draw_text(
      label_font,
      ALLEGRO_COLOR{1.0, 1.0, 1.0, 1.0},
      x,
      y - h_line_height,
      ALLEGRO_ALIGN_LEFT,
      label.c_str()
   );
   return;
}

void DisplaySettings::draw_helper_text(std::string text, float x, float y, float width)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[DisplaySettings::draw_helper_text]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DisplaySettings::draw_helper_text: error: guard \"initialized\" not met");
   }
   ALLEGRO_FONT *label_font = obtain_label_font();
   int h_line_height = al_get_font_line_height(label_font) / 2;
   al_draw_multiline_text(
      label_font,
      ALLEGRO_COLOR{0.53, 0.53, 0.53, 0.53},
      x,
      y - h_line_height,
      width,
      al_get_font_line_height(label_font),
      ALLEGRO_ALIGN_LEFT,
      text.c_str()
   );
   return;
}

void DisplaySettings::draw_slider_toggle_box(bool onoff, float x, float y)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[DisplaySettings::draw_slider_toggle_box]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DisplaySettings::draw_slider_toggle_box: error: guard \"initialized\" not met");
   }
   AllegroFlare::Elements::UI::SliderToggle slider_toggle;
   //float width = slider_toggle.get_width();
   float height = slider_toggle.get_height();
   slider_toggle.set_font_bin(font_bin);
   slider_toggle.set_font_size(base_font_size);
   slider_toggle.set_x(x); // - width / 2);
   slider_toggle.set_y(y - height / 2);
   slider_toggle.set_onoff(onoff);
   slider_toggle.render();
   return;
}

void DisplaySettings::draw_int_spinner(int number, bool selected, float x, float y, bool disabled)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[DisplaySettings::draw_int_spinner]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DisplaySettings::draw_int_spinner: error: guard \"initialized\" not met");
   }
   // TODO: Improve the arguments for "selected" and "disabled"
   AllegroFlare::Elements::UI::IntSpinner int_spinner;
   float height = int_spinner.get_height();
   if (selected) int_spinner.set_state(AllegroFlare::Elements::UI::IntSpinner::STATE_ACTIVE_FOCUS);
   if (disabled) int_spinner.set_state(AllegroFlare::Elements::UI::IntSpinner::STATE_DISABLED);
   int_spinner.set_font_bin(font_bin);
   int_spinner.set_font_size(base_font_size);
   int_spinner.set_x(x);
   int_spinner.set_y(y - height / 2);
   int_spinner.set_number(number);
   int_spinner.render();
   return;
}

void DisplaySettings::virtual_control_button_up_func(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_button_num, bool is_repeat)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[DisplaySettings::virtual_control_button_up_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DisplaySettings::virtual_control_button_up_func: error: guard \"initialized\" not met");
   }
   switch(virtual_controller_button_num)
   {
      case AllegroFlare::VirtualControllers::GenericController::BUTTON_UP:
         if (!is_repeat)
         {
            up_pressed = false;
            up_pressed_at = 0;
         }
      break;

      case AllegroFlare::VirtualControllers::GenericController::BUTTON_DOWN:
         if (!is_repeat)
         {
            down_pressed = false;
            down_pressed_at = 0;
         }
      break;
   }
   return;
}

void DisplaySettings::virtual_control_button_down_func(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_button_num, bool is_repeat)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[DisplaySettings::virtual_control_button_down_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DisplaySettings::virtual_control_button_down_func: error: guard \"initialized\" not met");
   }
   switch(virtual_controller_button_num)
   {
      case AllegroFlare::VirtualControllers::GenericController::BUTTON_UP:
         if (!is_repeat)
         {
            move_cursor_up();
            up_pressed = true;
            up_pressed_at = al_get_time();
         }
      break;

      case AllegroFlare::VirtualControllers::GenericController::BUTTON_DOWN:
         if (!is_repeat)
         {
            move_cursor_down();
            down_pressed = true;
            down_pressed_at = al_get_time();
         }
      break;

      case AllegroFlare::VirtualControllers::GenericController::BUTTON_RIGHT:
         move_cursor_right();
      break;

      case AllegroFlare::VirtualControllers::GenericController::BUTTON_LEFT:
         move_cursor_left();
      break;

      case AllegroFlare::VirtualControllers::GenericController::BUTTON_A:
         activate_current_option();
      break;

      default:
      break;
   }
   return;
}

void DisplaySettings::virtual_control_axis_change_func(ALLEGRO_EVENT* ev)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[DisplaySettings::virtual_control_axis_change_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DisplaySettings::virtual_control_axis_change_func: error: guard \"initialized\" not met");
   }
   // TODO: this function
   return;
}

bool DisplaySettings::obtain_fullscreen_status()
{
   return display_settings_interface->is_fullscreen();
}

bool DisplaySettings::obtain_screensaver_inhibited()
{
   return display_settings_interface->is_screensaver_inhibited();
}

bool DisplaySettings::obtain_mouse_cursor_hidden()
{
   return display_settings_interface->is_mouse_cursor_hidden();
}

std::pair<int, int> DisplaySettings::obtain_window_dimensions()
{
   return display_settings_interface->get_window_size();
}

std::pair<int, int> DisplaySettings::obtain_display_dimensions()
{
   return display_settings_interface->get_display_size();
}

ALLEGRO_FONT* DisplaySettings::obtain_heading_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[DisplaySettings::obtain_heading_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DisplaySettings::obtain_heading_font: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Oswald-Medium.ttf -82");
}

ALLEGRO_FONT* DisplaySettings::obtain_label_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[DisplaySettings::obtain_label_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DisplaySettings::obtain_label_font: error: guard \"font_bin\" not met");
   }
   std::stringstream ss;
   ss << "Inter-Regular.ttf " << base_font_size;
   return font_bin->auto_get(ss.str().c_str());
}


} // namespace Screens
} // namespace AllegroFlare


