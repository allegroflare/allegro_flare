

#include <AllegroFlare/LoadASavedGame/Screen.hpp>

#include <AllegroFlare/LoadASavedGame/SaveSlotRenderer.hpp>
#include <AllegroFlare/Logger.hpp>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <set>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace LoadASavedGame
{


Screen::Screen(std::string data_folder_path)
   : AllegroFlare::Screens::Base(AllegroFlare::LoadASavedGame::Screen::TYPE)
   , data_folder_path(data_folder_path)
   , bitmap_bin({})
   , font_bin({})
   , save_slots({})
   , cursor_position(0)
   , on_menu_choice_callback_func({})
   , on_menu_choice_callback_func_user_data(nullptr)
   , on_erase_focused_save_slot_func({})
   , on_erase_focused_save_slot_func_user_data(nullptr)
   , on_exit_callback_func({})
   , on_exit_callback_func_user_data(nullptr)
   , state(STATE_UNDEF)
   , state_is_busy(false)
   , state_changed_at(0.0f)
   , initialized(false)
   , destroyed(false)
{
}


Screen::~Screen()
{
   if (initialized && !destroyed)
   {
      AllegroFlare::Logger::warn_from(THIS_CLASS_AND_METHOD_NAME,
         "This instance is being destroyed but the destroy() method has not been called."
      );
   }
   return;
}


void Screen::set_data_folder_path(std::string data_folder_path)
{
   if (get_initialized()) throw std::runtime_error("[Screen::set_data_folder_path]: error: guard \"get_initialized()\" not met.");
   this->data_folder_path = data_folder_path;
}


void Screen::set_on_menu_choice_callback_func(std::function<void(AllegroFlare::LoadASavedGame::Screen*, void*)> on_menu_choice_callback_func)
{
   this->on_menu_choice_callback_func = on_menu_choice_callback_func;
}


void Screen::set_on_menu_choice_callback_func_user_data(void* on_menu_choice_callback_func_user_data)
{
   this->on_menu_choice_callback_func_user_data = on_menu_choice_callback_func_user_data;
}


void Screen::set_on_erase_focused_save_slot_func(std::function<void(AllegroFlare::LoadASavedGame::Screen*, void*)> on_erase_focused_save_slot_func)
{
   this->on_erase_focused_save_slot_func = on_erase_focused_save_slot_func;
}


void Screen::set_on_erase_focused_save_slot_func_user_data(void* on_erase_focused_save_slot_func_user_data)
{
   this->on_erase_focused_save_slot_func_user_data = on_erase_focused_save_slot_func_user_data;
}


void Screen::set_on_exit_callback_func(std::function<void(AllegroFlare::LoadASavedGame::Screen*, void*)> on_exit_callback_func)
{
   this->on_exit_callback_func = on_exit_callback_func;
}


void Screen::set_on_exit_callback_func_user_data(void* on_exit_callback_func_user_data)
{
   this->on_exit_callback_func_user_data = on_exit_callback_func_user_data;
}


std::vector<AllegroFlare::LoadASavedGame::SaveSlots::Base*> Screen::get_save_slots() const
{
   return save_slots;
}


std::function<void(AllegroFlare::LoadASavedGame::Screen*, void*)> Screen::get_on_menu_choice_callback_func() const
{
   return on_menu_choice_callback_func;
}


void* Screen::get_on_menu_choice_callback_func_user_data() const
{
   return on_menu_choice_callback_func_user_data;
}


std::function<void(AllegroFlare::LoadASavedGame::Screen*, void*)> Screen::get_on_erase_focused_save_slot_func() const
{
   return on_erase_focused_save_slot_func;
}


void* Screen::get_on_erase_focused_save_slot_func_user_data() const
{
   return on_erase_focused_save_slot_func_user_data;
}


std::function<void(AllegroFlare::LoadASavedGame::Screen*, void*)> Screen::get_on_exit_callback_func() const
{
   return on_exit_callback_func;
}


void* Screen::get_on_exit_callback_func_user_data() const
{
   return on_exit_callback_func_user_data;
}


uint32_t Screen::get_state() const
{
   return state;
}


bool Screen::get_initialized() const
{
   return initialized;
}


bool Screen::get_destroyed() const
{
   return destroyed;
}


void Screen::set_save_slots(std::vector<AllegroFlare::LoadASavedGame::SaveSlots::Base*> save_slots)
{
   if (!((save_slots.size() <= 3)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::LoadASavedGame::Screen::set_save_slots]: error: guard \"(save_slots.size() <= 3)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::LoadASavedGame::Screen::set_save_slots]: error: guard \"(save_slots.size() <= 3)\" not met");
   }
   this->save_slots = save_slots;
   cursor_position = 0;
   return;
}

void Screen::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::LoadASavedGame::Screen::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::LoadASavedGame::Screen::initialize]: error: guard \"(!initialized)\" not met");
   }
   if (!((!destroyed)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::LoadASavedGame::Screen::initialize]: error: guard \"(!destroyed)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::LoadASavedGame::Screen::initialize]: error: guard \"(!destroyed)\" not met");
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::LoadASavedGame::Screen::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::LoadASavedGame::Screen::initialize]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::LoadASavedGame::Screen::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::LoadASavedGame::Screen::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::LoadASavedGame::Screen::initialize]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::LoadASavedGame::Screen::initialize]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!((data_folder_path != DEFAULT_DATA_FOLDER_PATH)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::LoadASavedGame::Screen::initialize]: error: guard \"(data_folder_path != DEFAULT_DATA_FOLDER_PATH)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::LoadASavedGame::Screen::initialize]: error: guard \"(data_folder_path != DEFAULT_DATA_FOLDER_PATH)\" not met");
   }
   set_update_strategy(AllegroFlare::Screens::Base::UpdateStrategy::SEPARATE_UPDATE_AND_RENDER_FUNCS);
   bitmap_bin.set_full_path(AllegroFlare::BitmapBin::build_standard_path(data_folder_path));
   font_bin.set_full_path(AllegroFlare::FontBin::build_standard_path(data_folder_path));
   initialized = true;
   return;
}

void Screen::destroy()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::LoadASavedGame::Screen::destroy]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::LoadASavedGame::Screen::destroy]: error: guard \"initialized\" not met");
   }
   if (!((!destroyed)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::LoadASavedGame::Screen::destroy]: error: guard \"(!destroyed)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::LoadASavedGame::Screen::destroy]: error: guard \"(!destroyed)\" not met");
   }
   bitmap_bin.clear();
   font_bin.clear();
   destroyed = true;
   return;
}

void Screen::on_activate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::LoadASavedGame::Screen::on_activate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::LoadASavedGame::Screen::on_activate]: error: guard \"initialized\" not met");
   }
   cursor_position = 0;
   reveal_screen();
   //emit_event_to_update_input_hints_bar();
   //emit_show_and_size_input_hints_bar_event();
   return;
}

void Screen::on_deactivate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::LoadASavedGame::Screen::on_deactivate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::LoadASavedGame::Screen::on_deactivate]: error: guard \"initialized\" not met");
   }
   //emit_hide_and_restore_size_input_hints_bar_event();
   return;
}

void Screen::reveal_screen()
{
   set_state(STATE_REVEALING);
   return;
}

bool Screen::handling_user_input()
{
   return is_state(STATE_REVEALED_AND_HANDLING_USER_INPUT);
}

void Screen::move_cursor_up()
{
   if (save_slots.empty()) return;
   if (!handling_user_input()) return;

   cursor_position--;
   if (cursor_position < 0) cursor_position += save_slots.size();
   return;
}

void Screen::move_cursor_down()
{
   if (save_slots.empty()) return;
   if (!handling_user_input()) return;

   cursor_position++;
   if (cursor_position >= save_slots.size()) cursor_position -= save_slots.size();
   return;
}

std::pair<int, AllegroFlare::LoadASavedGame::SaveSlots::Base*> Screen::get_currently_selected_save_slot()
{
   if (save_slots.empty()) return std::make_pair(-1, nullptr);
   // TODO: This assumes that the cursor will never be in an invalid position. Please review this to be sure that
   // is the case.
   return { cursor_position, save_slots[cursor_position] };
}

void Screen::exit_screen()
{
   // TODO: Test this method
   if (on_exit_callback_func)
   {
      on_exit_callback_func(this, on_exit_callback_func_user_data);
   }
   else
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::LoadASavedGame::Screen::exit_screen",
         "Expecting an \"on_exit_callback_func\" to be present, but it is not."
      );
   }

   return;
}

void Screen::activate_current_focused_menu_option()
{
   // TODO: Test this method
   if (on_menu_choice_callback_func)
   {
      on_menu_choice_callback_func(this, on_menu_choice_callback_func_user_data);
   }
   else
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::LoadASavedGame::Screen::activate_current_focused_menu_option",
         "Expecting an \"on_menu_choice_callback_func\" to be present, but it is not."
      );
   }
   return;
}

void Screen::erase_current_focused_save_slot()
{
   // TODO: Add dialog confirmation
   // TODO: Test this method
   if (on_erase_focused_save_slot_func)
   {
      on_erase_focused_save_slot_func(this, on_erase_focused_save_slot_func_user_data);
   }
   else
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::LoadASavedGame::Screen::on_erase_focused_save_slot_func",
         "Expecting an \"on_menu_choice_callback_func\" to be present, but it is not."
      );
   }
   return;
}

bool Screen::can_exit_screen()
{
   // User can exit the screen when it is still revealing and when it's handling normal input
   if (is_state(STATE_REVEALING)) return true;
   if (is_state(STATE_REVEALED_AND_HANDLING_USER_INPUT)) return true;
   return false;
}

bool Screen::can_select_current_focused_menu_option()
{
   if (!is_state(STATE_REVEALED_AND_HANDLING_USER_INPUT)) return false;
   return true;
}

void Screen::select_current_focused_menu_option()
{
   if (!(is_state(STATE_REVEALED_AND_HANDLING_USER_INPUT)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::LoadASavedGame::Screen::select_current_focused_menu_option]: error: guard \"is_state(STATE_REVEALED_AND_HANDLING_USER_INPUT)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::LoadASavedGame::Screen::select_current_focused_menu_option]: error: guard \"is_state(STATE_REVEALED_AND_HANDLING_USER_INPUT)\" not met");
   }
   // For now, do a direct call to activate the option. In the future, this would begin a shutdown state, the end
   // of which would then "activate" the current selected menu option.
   set_state(STATE_MENU_OPTION_IS_CHOSEN);
   return;
}

void Screen::render()
{
   render_title();
   render_save_slots();
   return;
}

void Screen::render_title()
{
   ALLEGRO_FONT *font = obtain_heading_font();
   float line_height = al_get_font_line_height(font);
   std::string title_text = "Select a Save Slot";
   al_draw_text(
      font,
      ALLEGRO_COLOR{1, 1, 1, 1},
      1920/2,
      260-line_height,
      ALLEGRO_ALIGN_CENTER,
      title_text.c_str()
   );
   return;
}

void Screen::render_save_slots()
{
   float y_cursor = 400;
   float y_distance = 1080/6;
   int i=0;
   for (auto &save_slot : save_slots)
   {
      float x = 1920/2;
      float y = y_cursor + y_distance*i;
      // HERE: Continue on this
      AllegroFlare::LoadASavedGame::SaveSlotRenderer renderer;
      renderer.set_bitmap_bin(&bitmap_bin);
      renderer.set_font_bin(&font_bin);
      renderer.render(
         save_slot,
         x,
         y
      );

      // If this is currently focused under the cursor, draw the cursor (for now)
      // TODO: Replace this with a more active cursor
      bool this_save_slot_is_focused = (i == cursor_position);
      if (this_save_slot_is_focused)
      {
         float roundness = 6.0f;
         float padding_x = 20;
         float padding_y = 15;
         float slot_width = renderer.get_slot_width();
         float slot_h_width = slot_width/2;
         float slot_height = renderer.get_slot_height();
         float slot_h_height = slot_height/2;
         al_draw_rounded_rectangle(
            x-slot_h_width - padding_x,
            y-slot_h_height - padding_y,
            x+slot_h_width + padding_x,
            y+slot_h_height + padding_y,
            roundness,
            roundness,
            ALLEGRO_COLOR{1, 1, 1, 1},
            6.0
         );
      }

      i++;
   }
   return;
}

void Screen::primary_update_func(double time_now, double time_step)
{
   //state_accumulated_age += time_step;
   update_state(time_now); // TODO: Sort out proper time accumulation
   return;
}

void Screen::primary_render_func()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::LoadASavedGame::Screen::primary_render_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::LoadASavedGame::Screen::primary_render_func]: error: guard \"initialized\" not met");
   }
   render();
   return;
}

void Screen::primary_timer_func()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::LoadASavedGame::Screen::primary_timer_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::LoadASavedGame::Screen::primary_timer_func]: error: guard \"initialized\" not met");
   }
   AllegroFlare::Logger::throw_error(THIS_CLASS_AND_METHOD_NAME, "Not expected to be in this code path.");
   return;
}

void Screen::key_char_func(ALLEGRO_EVENT* event)
{
   if (!(event))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::LoadASavedGame::Screen::key_char_func]: error: guard \"event\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::LoadASavedGame::Screen::key_char_func]: error: guard \"event\" not met");
   }
   switch(event->keyboard.keycode)
   {
      case ALLEGRO_KEY_UP:
         move_cursor_up();
      break;

      case ALLEGRO_KEY_DOWN:
         move_cursor_down();
      break;

      case ALLEGRO_KEY_D:
         erase_current_focused_save_slot();
      break;

      case ALLEGRO_KEY_Q:
      case ALLEGRO_KEY_X:
         if (can_exit_screen()) exit_screen();
      break;

      case ALLEGRO_KEY_ENTER:
         if (can_select_current_focused_menu_option()) select_current_focused_menu_option();
      break;
   }
   return;
}

void Screen::virtual_control_button_down_func(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_button_num, bool is_repeat)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::LoadASavedGame::Screen::virtual_control_button_down_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::LoadASavedGame::Screen::virtual_control_button_down_func]: error: guard \"initialized\" not met");
   }
   // TODO: this function
   return;
}

void Screen::virtual_control_axis_change_func(ALLEGRO_EVENT* ev)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::LoadASavedGame::Screen::virtual_control_axis_change_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::LoadASavedGame::Screen::virtual_control_axis_change_func]: error: guard \"initialized\" not met");
   }
   // TODO: this function
   return;
}

void Screen::set_state(uint32_t state, bool override_if_busy)
{
   if (!(is_valid_state(state)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::LoadASavedGame::Screen::set_state]: error: guard \"is_valid_state(state)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::LoadASavedGame::Screen::set_state]: error: guard \"is_valid_state(state)\" not met");
   }
   if (this->state == state) return;
   if (!override_if_busy && state_is_busy) return;
   uint32_t previous_state = this->state;

   switch (state)
   {
      case STATE_REVEALING:
      break;

      case STATE_REVEALED_AND_HANDLING_USER_INPUT:
      break;

      case STATE_MENU_OPTION_IS_CHOSEN:
      break;

      case STATE_CLOSING_DOWN:
      break;

      case STATE_CLOSED_DOWN_AND_AWAITING_MENU_CHOICE_ACTIVATION:
      break;

      case STATE_FINISHED:
      break;

      default:
         AllegroFlare::Logger::throw_error(
            "ClassName::set_state",
            "Unable to handle case for state \"" + std::to_string(state) + "\""
         );
      break;
   }

   this->state = state;
   state_changed_at = al_get_time();

   return;
}

void Screen::begin_shutdown_after_selection()
{
   if (!(is_state(STATE_MENU_OPTION_IS_CHOSEN)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::LoadASavedGame::Screen::begin_shutdown_after_selection]: error: guard \"is_state(STATE_MENU_OPTION_IS_CHOSEN)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::LoadASavedGame::Screen::begin_shutdown_after_selection]: error: guard \"is_state(STATE_MENU_OPTION_IS_CHOSEN)\" not met");
   }
   set_state(STATE_CLOSING_DOWN);
   return;
}

void Screen::complete_shutdown_and_activate_current_focused_menu_option()
{
   if (!(is_state(STATE_CLOSING_DOWN)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::LoadASavedGame::Screen::complete_shutdown_and_activate_current_focused_menu_option]: error: guard \"is_state(STATE_CLOSING_DOWN)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::LoadASavedGame::Screen::complete_shutdown_and_activate_current_focused_menu_option]: error: guard \"is_state(STATE_CLOSING_DOWN)\" not met");
   }
   // HERE
   set_state(STATE_CLOSED_DOWN_AND_AWAITING_MENU_CHOICE_ACTIVATION);
   activate_current_focused_menu_option();
   set_state(STATE_FINISHED);
   return;
}

void Screen::update_state(float time_now)
{
   if (!(is_valid_state(state)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::LoadASavedGame::Screen::update_state]: error: guard \"is_valid_state(state)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::LoadASavedGame::Screen::update_state]: error: guard \"is_valid_state(state)\" not met");
   }
   float age = infer_current_state_age(time_now);

   switch (state)
   {
      case STATE_REVEALING:
         if (age > 1.0) set_state(STATE_REVEALED_AND_HANDLING_USER_INPUT);
      break;

      case STATE_REVEALED_AND_HANDLING_USER_INPUT:
      break;

      case STATE_MENU_OPTION_IS_CHOSEN:
         if (age > 1.0) begin_shutdown_after_selection();
      break;

      case STATE_CLOSING_DOWN:
         if (age > 1.0) complete_shutdown_and_activate_current_focused_menu_option();
      break;

      case STATE_CLOSED_DOWN_AND_AWAITING_MENU_CHOICE_ACTIVATION:
      break;

      case STATE_FINISHED:
      break;

      default:
         AllegroFlare::Logger::throw_error(
            "ClassName::update_state",
            "Unable to handle case for state \"" + std::to_string(state) + "\""
         );
      break;
   }

   return;
}

bool Screen::is_valid_state(uint32_t state)
{
   std::set<uint32_t> valid_states =
   {
      STATE_REVEALING,
      STATE_REVEALED_AND_HANDLING_USER_INPUT,
      STATE_MENU_OPTION_IS_CHOSEN,
      STATE_CLOSING_DOWN,
      STATE_CLOSED_DOWN_AND_AWAITING_MENU_CHOICE_ACTIVATION,
      STATE_FINISHED,
   };
   return (valid_states.count(state) > 0);
}

bool Screen::is_state(uint32_t possible_state)
{
   return (state == possible_state);
}

float Screen::infer_current_state_age(float time_now)
{
   return (time_now - state_changed_at);
}

ALLEGRO_FONT* Screen::obtain_heading_font()
{
   return font_bin["Oswald-Medium.ttf -74"];
}


} // namespace LoadASavedGame
} // namespace AllegroFlare


