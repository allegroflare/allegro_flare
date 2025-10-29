

#include <AllegroFlare/SavingAndLoading/Screen.hpp>

#include <AllegroFlare/Logger.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <AllegroFlare/SavingAndLoading/EmptySaveSlotRenderer.hpp>
#include <AllegroFlare/SavingAndLoading/SaveSlotRenderer.hpp>
#include <AllegroFlare/TimeAgo.hpp>
#include <AllegroFlare/TimeStamper.hpp>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <set>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace SavingAndLoading
{


Screen::Screen(std::string data_folder_path)
   : AllegroFlare::Screens::Base(AllegroFlare::SavingAndLoading::Screen::TYPE)
   , data_folder_path(data_folder_path)
   , bitmap_bin()
   , font_bin()
   , saving_and_loading(nullptr)
   , cursor_position(0)
   , cursor_selection_box()
   , on_menu_choice_callback_func({})
   , on_menu_choice_callback_func_user_data(nullptr)
   , on_erase_focused_save_slot_func({})
   , on_erase_focused_save_slot_func_user_data(nullptr)
   , on_exit_callback_func({})
   , on_exit_callback_func_user_data(nullptr)
   , mode(MODE_UNDEF)
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


void Screen::set_saving_and_loading(AllegroFlare::SavingAndLoading::SavingAndLoading* saving_and_loading)
{
   if (get_initialized()) throw std::runtime_error("[Screen::set_saving_and_loading]: error: guard \"get_initialized()\" not met.");
   this->saving_and_loading = saving_and_loading;
}


void Screen::set_on_menu_choice_callback_func(std::function<void(AllegroFlare::SavingAndLoading::Screen*, void*)> on_menu_choice_callback_func)
{
   this->on_menu_choice_callback_func = on_menu_choice_callback_func;
}


void Screen::set_on_menu_choice_callback_func_user_data(void* on_menu_choice_callback_func_user_data)
{
   this->on_menu_choice_callback_func_user_data = on_menu_choice_callback_func_user_data;
}


void Screen::set_on_erase_focused_save_slot_func(std::function<void(AllegroFlare::SavingAndLoading::Screen*, void*)> on_erase_focused_save_slot_func)
{
   this->on_erase_focused_save_slot_func = on_erase_focused_save_slot_func;
}


void Screen::set_on_erase_focused_save_slot_func_user_data(void* on_erase_focused_save_slot_func_user_data)
{
   this->on_erase_focused_save_slot_func_user_data = on_erase_focused_save_slot_func_user_data;
}


void Screen::set_on_exit_callback_func(std::function<void(AllegroFlare::SavingAndLoading::Screen*, void*)> on_exit_callback_func)
{
   this->on_exit_callback_func = on_exit_callback_func;
}


void Screen::set_on_exit_callback_func_user_data(void* on_exit_callback_func_user_data)
{
   this->on_exit_callback_func_user_data = on_exit_callback_func_user_data;
}


std::function<void(AllegroFlare::SavingAndLoading::Screen*, void*)> Screen::get_on_menu_choice_callback_func() const
{
   return on_menu_choice_callback_func;
}


void* Screen::get_on_menu_choice_callback_func_user_data() const
{
   return on_menu_choice_callback_func_user_data;
}


std::function<void(AllegroFlare::SavingAndLoading::Screen*, void*)> Screen::get_on_erase_focused_save_slot_func() const
{
   return on_erase_focused_save_slot_func;
}


void* Screen::get_on_erase_focused_save_slot_func_user_data() const
{
   return on_erase_focused_save_slot_func_user_data;
}


std::function<void(AllegroFlare::SavingAndLoading::Screen*, void*)> Screen::get_on_exit_callback_func() const
{
   return on_exit_callback_func;
}


void* Screen::get_on_exit_callback_func_user_data() const
{
   return on_exit_callback_func_user_data;
}


uint32_t Screen::get_mode() const
{
   return mode;
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


void Screen::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::Screen::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::Screen::initialize]: error: guard \"(!initialized)\" not met");
   }
   if (!((!destroyed)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::Screen::initialize]: error: guard \"(!destroyed)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::Screen::initialize]: error: guard \"(!destroyed)\" not met");
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::Screen::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::Screen::initialize]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::Screen::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::Screen::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::Screen::initialize]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::Screen::initialize]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!((data_folder_path != DEFAULT_DATA_FOLDER_PATH)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::Screen::initialize]: error: guard \"(data_folder_path != DEFAULT_DATA_FOLDER_PATH)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::Screen::initialize]: error: guard \"(data_folder_path != DEFAULT_DATA_FOLDER_PATH)\" not met");
   }
   if (!(saving_and_loading))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::Screen::initialize]: error: guard \"saving_and_loading\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::Screen::initialize]: error: guard \"saving_and_loading\" not met");
   }
   if (!((mode != MODE_UNDEF)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::Screen::initialize]: error: guard \"(mode != MODE_UNDEF)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::Screen::initialize]: error: guard \"(mode != MODE_UNDEF)\" not met");
   }
   // Setup the update strategy
   set_update_strategy(AllegroFlare::Screens::Base::UpdateStrategy::SEPARATE_UPDATE_AND_RENDER_FUNCS);

   // Setup the bin paths
   bitmap_bin.set_full_path(AllegroFlare::BitmapBin::build_standard_path(data_folder_path));
   font_bin.set_full_path(AllegroFlare::FontBin::build_standard_path(data_folder_path));

   // Setup the cursor dimensions
   cursor_selection_box.set_padding(
      cursor_selection_box_padding_x(),
      cursor_selection_box_padding_y()
   );
   cursor_selection_box.set_size_quietly(
      infer_save_slot_width(), // + cursor_selection_box_padding_x() * 2,
      infer_save_slot_height() // + cursor_selection_box_padding_y() * 2
   );
   AllegroFlare::Vec2D cursor_position = calculate_destination_position_for_cursor_selection_box();
   cursor_selection_box.set_position_quietly(cursor_position.x, cursor_position.y);
    
   initialized = true;
   return;
}

void Screen::destroy()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::Screen::destroy]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::Screen::destroy]: error: guard \"initialized\" not met");
   }
   if (!((!destroyed)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::Screen::destroy]: error: guard \"(!destroyed)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::Screen::destroy]: error: guard \"(!destroyed)\" not met");
   }
   bitmap_bin.clear();
   font_bin.clear();
   destroyed = true;
   return;
}

void Screen::set_mode(uint32_t mode)
{
   if (!(is_valid_mode(mode)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::Screen::set_mode]: error: guard \"is_valid_mode(mode)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::Screen::set_mode]: error: guard \"is_valid_mode(mode)\" not met");
   }
   this->mode = mode;
}

void Screen::on_activate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::Screen::on_activate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::Screen::on_activate]: error: guard \"initialized\" not met");
   }
   cursor_position = 0;
   update_selection_cursor_box_position_to_changed_cursor_position();
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
      error_message << "[AllegroFlare::SavingAndLoading::Screen::on_deactivate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::Screen::on_deactivate]: error: guard \"initialized\" not met");
   }
   //emit_hide_and_restore_size_input_hints_bar_event();
   return;
}

void Screen::reveal_screen()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::Screen::reveal_screen]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::Screen::reveal_screen]: error: guard \"initialized\" not met");
   }
   set_state(STATE_REVEALING);
   return;
}

bool Screen::handling_user_input()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::Screen::handling_user_input]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::Screen::handling_user_input]: error: guard \"initialized\" not met");
   }
   return is_state(STATE_REVEALED_AND_HANDLING_USER_INPUT);
}

std::vector<AllegroFlare::SavingAndLoading::SaveSlot*> Screen::get_save_slots()
{
   return get_manual_save_slots();
}

std::vector<AllegroFlare::SavingAndLoading::SaveSlot*> Screen::get_manual_save_slots()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::Screen::get_manual_save_slots]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::Screen::get_manual_save_slots]: error: guard \"initialized\" not met");
   }
   int current_profile_id = 1; // TODO: Account for switching profile_id
   return saving_and_loading->get_manual_save_slots(current_profile_id);
}

void Screen::move_cursor_up()
{
   if (get_save_slots().empty()) return;
   if (!handling_user_input()) return;

   cursor_position--;
   if (cursor_position < 0) cursor_position += get_save_slots().size();
   update_selection_cursor_box_position_to_changed_cursor_position();
   return;
}

void Screen::move_cursor_down()
{
   int num_save_slots = get_save_slots().size();
   if (num_save_slots == 0) return;
   if (!handling_user_input()) return;

   cursor_position++;
   if (cursor_position >= num_save_slots) cursor_position -= num_save_slots;
   update_selection_cursor_box_position_to_changed_cursor_position();
   return;
}

AllegroFlare::Vec2D Screen::calculate_destination_position_for_cursor_selection_box()
{
   float box_width = infer_save_slot_width();
   float box_height = infer_save_slot_height();
   float position_x = infer_first_box_initial_position_x(); // - cursor_selection_box_padding_x();
   float position_y = infer_first_box_initial_position_y() // - cursor_selection_box_padding_y()
                    + infer_save_slot_y_distance() * cursor_position;
   return { position_x - box_width * 0.5f, position_y - box_height * 0.5f };
}

void Screen::update_selection_cursor_box_position_to_changed_cursor_position()
{
   AllegroFlare::Vec2D position = calculate_destination_position_for_cursor_selection_box();
   cursor_selection_box.reposition_to(position.x, position.y);
   return;
}

AllegroFlare::SavingAndLoading::SaveSlot* Screen::get_currently_selected_save_slot()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::Screen::get_currently_selected_save_slot]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::Screen::get_currently_selected_save_slot]: error: guard \"initialized\" not met");
   }
   if (!((!destroyed)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::Screen::get_currently_selected_save_slot]: error: guard \"(!destroyed)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::Screen::get_currently_selected_save_slot]: error: guard \"(!destroyed)\" not met");
   }
   auto save_slots = get_save_slots();
   if (save_slots.empty()) return nullptr;
   // TODO: This assumes that the cursor will never be in an invalid position. Please review this to be sure that
   // is the case.
   return save_slots[cursor_position];
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
      AllegroFlare::Logger::throw_error(THIS_CLASS_AND_METHOD_NAME,
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
      AllegroFlare::Logger::throw_error(THIS_CLASS_AND_METHOD_NAME,
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
      AllegroFlare::Logger::throw_error(THIS_CLASS_AND_METHOD_NAME,
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
   AllegroFlare::SavingAndLoading::SaveSlot* currently_selected_save_slot = get_currently_selected_save_slot();

   if (!currently_selected_save_slot) return false;
   if (!is_state(STATE_REVEALED_AND_HANDLING_USER_INPUT)) return false;
   if (is_mode(MODE_USER_CAN_CHOOSE_POPULATED_SLOT_OR_EMPTY_SLOT)) return true;
   if (is_mode(MODE_USER_CAN_CHOOSE_POPULATED_SLOT_ONLY) && !currently_selected_save_slot->is_empty()) return true;
   if (is_mode(MODE_USER_CAN_CHOOSE_EMPTY_SLOT_ONLY) && currently_selected_save_slot->is_empty()) return true;
   return false;
}

bool Screen::current_focused_menu_option_is_an_empty_slot()
{
   AllegroFlare::SavingAndLoading::SaveSlot* currently_selected_save_slot = get_currently_selected_save_slot();
   if (!currently_selected_save_slot) return false;
   return currently_selected_save_slot->is_empty();
}

void Screen::select_current_focused_menu_option()
{
   if (!(is_state(STATE_REVEALED_AND_HANDLING_USER_INPUT)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::Screen::select_current_focused_menu_option]: error: guard \"is_state(STATE_REVEALED_AND_HANDLING_USER_INPUT)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::Screen::select_current_focused_menu_option]: error: guard \"is_state(STATE_REVEALED_AND_HANDLING_USER_INPUT)\" not met");
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
   render_dialogs_overlay();
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

float Screen::infer_first_box_initial_position_x()
{
   return 1920/2;
}

float Screen::infer_first_box_initial_position_y()
{
   return 400;
}

float Screen::infer_save_slot_width()
{
   return AllegroFlare::SavingAndLoading::SaveSlotRenderer::DEFAULT_WIDTH;
}

float Screen::infer_save_slot_height()
{
   return AllegroFlare::SavingAndLoading::SaveSlotRenderer::DEFAULT_HEIGHT;
}

float Screen::infer_save_slot_y_distance()
{
   return 1080/6 + 20;
}

float Screen::cursor_selection_box_padding_x()
{
   return 20;
}

float Screen::cursor_selection_box_padding_y()
{
   return 15;
}

void Screen::render_save_slots()
{
   float save_slot_width = infer_save_slot_width();
   float save_slot_height = infer_save_slot_height();
   float y_distance = infer_save_slot_y_distance();
   float first_box_initial_position_x = infer_first_box_initial_position_x();
   float first_box_initial_position_y = infer_first_box_initial_position_y();

   AllegroFlare::Placement2D placement;
   placement.size.x = save_slot_width;
   placement.size.y = save_slot_height;

   // Draw the save slots
   int i=0;
   for (auto &save_slot : get_save_slots())
   {
      placement.position.x = first_box_initial_position_x;
      placement.position.y = first_box_initial_position_y + y_distance*i;


      placement.start_transform();
      if (save_slot->is_empty())
      {
         // HERE: Continue on this
         AllegroFlare::SavingAndLoading::EmptySaveSlotRenderer empty_renderer;
         empty_renderer.set_bitmap_bin(&bitmap_bin);
         empty_renderer.set_font_bin(&font_bin);
         empty_renderer.render();
      }
      else
      {
         // HERE: Continue on this
         AllegroFlare::SavingAndLoading::SaveSlotRenderer renderer;
         renderer.set_bitmap_bin(&bitmap_bin);
         renderer.set_font_bin(&font_bin);

         // Calculate and format time information
         std::time_t time_now = std::time(nullptr);
         std::time_t save_time__seconds_since_epoch =
            save_slot->get_header_data()->save_time__seconds_since_epoch;
         std::string user_friendly_time_of_save =
            AllegroFlare::TimeStamper::user_friendly_time(save_time__seconds_since_epoch);
         std::time_t time_ago_value;
         std::string time_ago_string;
         std::tie(time_ago_value, time_ago_string) =
            AllegroFlare::TimeAgo::time_ago(save_time__seconds_since_epoch, time_now);

         // Fill renderer with data
         std::string time_of_save_str = save_slot->get_header_data()->date_and_time_of_save;
         renderer.set_date_and_time_of_save(user_friendly_time_of_save);
         renderer.set_time_since_text(time_ago_string);
         renderer.set_time_since_value(time_ago_value);
         renderer.set_save_slot_type(save_slot->get_save_slot_type());
         renderer.set_screenshot_of_gameplay_at_save_identifier(
            save_slot->get_header_data()->screenshot_of_gameplay_at_save_identifier
         );
         renderer.set_location_of_save(
            save_slot->get_header_data()->location_of_save
         );

         // Render the slot
         renderer.render();
      }

      placement.restore_transform();

      i++;
   }

   // Draw the selection cursor
   cursor_selection_box.render();

   return;
}

void Screen::render_dialogs_overlay()
{
   if (!is_state(STATE_CONFIRMING_DELETING_SAVE_SLOT_DATA)) return;

   float box_width = 1920/3;
   float box_height = 1080/5;

   AllegroFlare::Placement2D placement;
   placement.position.x = 1920/2;
   placement.position.y = 1080/2;
   placement.size.x = box_width;
   placement.size.y = box_height;

   placement.start_transform();

   // Backfill
   al_draw_filled_rectangle(
      0,
      0,
      box_width,
      box_height,
      al_color_name("darkred")
   );

   // Outline
   float outline_padding = 20.0f;
   float outline_stroke_thickness = 26.0f;
   float roundness = 20.0f;
   al_draw_rounded_rectangle(
      -outline_padding,
      -outline_padding,
      box_width+outline_padding,
      box_height+outline_padding,
      roundness,
      roundness,
      al_color_name("firebrick"),
      outline_stroke_thickness
   );

   ALLEGRO_FONT *heading_font = obtain_heading_font();
   float primary_text_line_height = al_get_font_line_height(heading_font);
   ALLEGRO_FONT *text_font = obtain_text_font();
   float text_font_line_height = al_get_font_line_height(text_font);
   float text_padding = 20;

   std::string primary_text = "WARNING";
   std::string secondary_text = "Are you sure you want to delete this save data?";

   // Primary text
   al_draw_text(
      heading_font,
      ALLEGRO_COLOR{1, 1, 1, 1},
      box_width/2,
      box_height/2-primary_text_line_height-30,
      ALLEGRO_ALIGN_CENTER,
      primary_text.c_str()
   );

   // Body text
   al_draw_multiline_text(
      text_font,
      ALLEGRO_COLOR{1, 1, 1, 1},
      box_width/2,
      box_height/2-text_font_line_height+10,
      box_width - text_padding * 2,
      text_font_line_height,
      ALLEGRO_ALIGN_CENTER,
      secondary_text.c_str()
   );

   // YES / NO instructions
   {
      float choice_text_y = box_height - box_height/6 * 2;
      ALLEGRO_COLOR action_text_color = ALLEGRO_COLOR{1.0, 1.0, 1.0, 1.0};
      ALLEGRO_COLOR hint_text_color = ALLEGRO_COLOR{0.7, 0.7, 0.7, 0.7};

      al_draw_text(
         text_font,
         action_text_color,
         box_width/4 * 3,
         choice_text_y,
         ALLEGRO_ALIGN_CENTER,
         "DELETE"
      );

      al_draw_text(
         text_font,
         hint_text_color,
         box_width/4 * 3,
         choice_text_y + text_font_line_height,
         ALLEGRO_ALIGN_CENTER,
         "(press ENTER key)"
      );

      al_draw_text(
         text_font,
         action_text_color,
         box_width/4,
         choice_text_y,
         ALLEGRO_ALIGN_CENTER,
         "CANCEL"
      );

      al_draw_text(
         text_font,
         hint_text_color,
         box_width/4,
         choice_text_y + text_font_line_height,
         ALLEGRO_ALIGN_CENTER,
         "(press ESCAPE key)"
      );
   }

   placement.restore_transform();

   return;
}

void Screen::delete_save_slot_at_current_cursor()
{
   AllegroFlare::SavingAndLoading::SaveSlot* currently_selected_save_slot = get_currently_selected_save_slot();
   if (!currently_selected_save_slot)
   {
      // TOOD: Consider info message
   }
   currently_selected_save_slot->delete_header_and_content_files_and_clear();
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
      error_message << "[AllegroFlare::SavingAndLoading::Screen::primary_render_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::Screen::primary_render_func]: error: guard \"initialized\" not met");
   }
   render();
   return;
}

void Screen::primary_timer_func()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::Screen::primary_timer_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::Screen::primary_timer_func]: error: guard \"initialized\" not met");
   }
   AllegroFlare::Logger::throw_error(THIS_CLASS_AND_METHOD_NAME, "Not expected to be in this code path.");
   return;
}

void Screen::key_char_func(ALLEGRO_EVENT* event)
{
   if (!(event))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::Screen::key_char_func]: error: guard \"event\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::Screen::key_char_func]: error: guard \"event\" not met");
   }
   if (is_state(STATE_CONFIRMING_DELETING_SAVE_SLOT_DATA))
   {
      switch(event->keyboard.keycode)
      {
         case ALLEGRO_KEY_X:
         case ALLEGRO_KEY_ESCAPE: {
            set_state(STATE_REVEALED_AND_HANDLING_USER_INPUT);
         } break;

         case ALLEGRO_KEY_ENTER: {
            delete_save_slot_at_current_cursor();
            set_state(STATE_REVEALED_AND_HANDLING_USER_INPUT);
         } break;
      }
   }
   else
   {
      switch(event->keyboard.keycode)
      {
         case ALLEGRO_KEY_UP: {
            move_cursor_up();
         } break;

         case ALLEGRO_KEY_DOWN: {
            move_cursor_down();
         } break;

         case ALLEGRO_KEY_D: {
            erase_current_focused_save_slot();
         } break;

         case ALLEGRO_KEY_Q:
         case ALLEGRO_KEY_X: {
            if (can_exit_screen()) exit_screen();
         } break;

         case ALLEGRO_KEY_DELETE:
         case ALLEGRO_KEY_BACKSPACE:
         case ALLEGRO_KEY_PAD_DELETE: {
            if (!current_focused_menu_option_is_an_empty_slot()) set_state(STATE_CONFIRMING_DELETING_SAVE_SLOT_DATA);
         } break;

         case ALLEGRO_KEY_ENTER: {
            if (can_select_current_focused_menu_option()) select_current_focused_menu_option();
         } break;
      }
   }
   return;
}

void Screen::virtual_control_button_down_func(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_button_num, bool is_repeat)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::Screen::virtual_control_button_down_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::Screen::virtual_control_button_down_func]: error: guard \"initialized\" not met");
   }
   // TODO: this function
   return;
}

void Screen::virtual_control_axis_change_func(ALLEGRO_EVENT* ev)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::Screen::virtual_control_axis_change_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::Screen::virtual_control_axis_change_func]: error: guard \"initialized\" not met");
   }
   // TODO: this function
   return;
}

void Screen::set_state(uint32_t state, bool override_if_busy)
{
   if (!(is_valid_state(state)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::Screen::set_state]: error: guard \"is_valid_state(state)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::Screen::set_state]: error: guard \"is_valid_state(state)\" not met");
   }
   if (this->state == state) return;
   if (!override_if_busy && state_is_busy) return;
   uint32_t previous_state = this->state;

   switch (previous_state)
   {
      case STATE_UNDEF:
         // Do nothing
      break;

      case STATE_REVEALING:
      break;

      case STATE_REVEALED_AND_HANDLING_USER_INPUT:
         cursor_selection_box.hide();
      break;

      case STATE_MENU_OPTION_IS_CHOSEN:
      break;

      case STATE_CLOSING_DOWN:
      break;

      case STATE_CONFIRMING_DELETING_SAVE_SLOT_DATA:
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

   switch (state)
   {
      case STATE_REVEALING:
      break;

      case STATE_REVEALED_AND_HANDLING_USER_INPUT:
         cursor_selection_box.show();
      break;

      case STATE_MENU_OPTION_IS_CHOSEN:
      break;

      case STATE_CLOSING_DOWN:
      break;

      case STATE_CONFIRMING_DELETING_SAVE_SLOT_DATA:
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
      error_message << "[AllegroFlare::SavingAndLoading::Screen::begin_shutdown_after_selection]: error: guard \"is_state(STATE_MENU_OPTION_IS_CHOSEN)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::Screen::begin_shutdown_after_selection]: error: guard \"is_state(STATE_MENU_OPTION_IS_CHOSEN)\" not met");
   }
   set_state(STATE_CLOSING_DOWN);
   return;
}

void Screen::complete_shutdown_and_activate_current_focused_menu_option()
{
   if (!(is_state(STATE_CLOSING_DOWN)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::Screen::complete_shutdown_and_activate_current_focused_menu_option]: error: guard \"is_state(STATE_CLOSING_DOWN)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::Screen::complete_shutdown_and_activate_current_focused_menu_option]: error: guard \"is_state(STATE_CLOSING_DOWN)\" not met");
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
      error_message << "[AllegroFlare::SavingAndLoading::Screen::update_state]: error: guard \"is_valid_state(state)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::Screen::update_state]: error: guard \"is_valid_state(state)\" not met");
   }
   float age = infer_current_state_age(time_now);

   cursor_selection_box.update();

   switch (state)
   {
      case STATE_REVEALING:
         if (age > 0.25) set_state(STATE_REVEALED_AND_HANDLING_USER_INPUT);
      break;

      case STATE_REVEALED_AND_HANDLING_USER_INPUT:
      break;

      case STATE_MENU_OPTION_IS_CHOSEN:
         if (age > 1.0) begin_shutdown_after_selection();
      break;

      case STATE_CLOSING_DOWN:
         if (age > 1.0) complete_shutdown_and_activate_current_focused_menu_option();
      break;

      case STATE_CONFIRMING_DELETING_SAVE_SLOT_DATA:
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
      STATE_CONFIRMING_DELETING_SAVE_SLOT_DATA,
      STATE_FINISHED,
   };
   return (valid_states.count(state) > 0);
}

bool Screen::is_valid_mode(uint32_t mode)
{
   std::set<uint32_t> valid_modes =
   {
      MODE_USER_CAN_CHOOSE_POPULATED_SLOT_ONLY,
      MODE_USER_CAN_CHOOSE_POPULATED_SLOT_OR_EMPTY_SLOT,
      MODE_USER_CAN_CHOOSE_EMPTY_SLOT_ONLY,
   };
   return (valid_modes.count(mode) > 0);
}

bool Screen::is_mode(uint32_t possible_mode)
{
   return (mode == possible_mode);
}

bool Screen::is_state(uint32_t possible_state)
{
   return (state == possible_state);
}

float Screen::infer_current_state_age(float time_now)
{
   return (time_now - state_changed_at);
}

bool Screen::infer_currently_drawing_user_cursor()
{
   if (is_state(STATE_REVEALED_AND_HANDLING_USER_INPUT)) return true;
   return false;
}

ALLEGRO_FONT* Screen::obtain_heading_font()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::Screen::obtain_heading_font]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::Screen::obtain_heading_font]: error: guard \"initialized\" not met");
   }
   return font_bin["Oswald-Medium.ttf -74"];
}

ALLEGRO_FONT* Screen::obtain_text_font()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::Screen::obtain_text_font]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::Screen::obtain_text_font]: error: guard \"initialized\" not met");
   }
   return font_bin["RobotoCondensed-Regular.ttf -32"];
}


} // namespace SavingAndLoading
} // namespace AllegroFlare


