

#include <AllegroFlare/Elements/InputDeviceConfigurationList.hpp>

#include <AllegroFlare/Elements/Scrollbar.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <algorithm>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <set>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{


InputDeviceConfigurationList::InputDeviceConfigurationList(AllegroFlare::FontBin* font_bin, int player_num, AllegroFlare::PhysicalInputDevices::Base* physical_input_device, std::vector<std::tuple<std::string, uint32_t>> joystick_configuration_mapping, float list_item_box_width, float list_item_box_height)
   : font_bin(font_bin)
   , player_num(player_num)
   , physical_input_device(physical_input_device)
   , joystick_configuration_mapping(joystick_configuration_mapping)
   , list_item_box_width(list_item_box_width)
   , list_item_box_height(list_item_box_height)
   , surface_width(1920)
   , surface_height(1080)
   , cursor_pos(0)
   , selection_cursor_box({})
   , scrollbar_position(0.0f)
   , scrollbar_position_destination(0.0f)
   , scrollbar_reposition_multiplier(DEFAULT_SCROLLBAR_REPOSITION_MULTIPLIER)
   , scrollbar_movement_mode(SCROLLBAR_MOVEMENT_FOLLOW_PROPORTIONAL)
   , box_gutter_y(10.0f)
   , state(STATE_UNDEF)
   , state_is_busy(false)
   , state_changed_at(0.0f)
   , initialized(false)
{
}


InputDeviceConfigurationList::~InputDeviceConfigurationList()
{
}


void InputDeviceConfigurationList::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void InputDeviceConfigurationList::set_player_num(int player_num)
{
   this->player_num = player_num;
}


void InputDeviceConfigurationList::set_list_item_box_width(float list_item_box_width)
{
   this->list_item_box_width = list_item_box_width;
}


void InputDeviceConfigurationList::set_list_item_box_height(float list_item_box_height)
{
   this->list_item_box_height = list_item_box_height;
}


void InputDeviceConfigurationList::set_surface_width(int surface_width)
{
   this->surface_width = surface_width;
}


void InputDeviceConfigurationList::set_surface_height(int surface_height)
{
   this->surface_height = surface_height;
}


void InputDeviceConfigurationList::set_box_gutter_y(float box_gutter_y)
{
   this->box_gutter_y = box_gutter_y;
}


int InputDeviceConfigurationList::get_player_num() const
{
   return player_num;
}


AllegroFlare::PhysicalInputDevices::Base* InputDeviceConfigurationList::get_physical_input_device() const
{
   return physical_input_device;
}


std::vector<std::tuple<std::string, uint32_t>> InputDeviceConfigurationList::get_joystick_configuration_mapping() const
{
   return joystick_configuration_mapping;
}


float InputDeviceConfigurationList::get_list_item_box_width() const
{
   return list_item_box_width;
}


float InputDeviceConfigurationList::get_list_item_box_height() const
{
   return list_item_box_height;
}


int InputDeviceConfigurationList::get_surface_width() const
{
   return surface_width;
}


int InputDeviceConfigurationList::get_surface_height() const
{
   return surface_height;
}


int InputDeviceConfigurationList::get_cursor_pos() const
{
   return cursor_pos;
}


float InputDeviceConfigurationList::get_scrollbar_position() const
{
   return scrollbar_position;
}


float InputDeviceConfigurationList::get_scrollbar_position_destination() const
{
   return scrollbar_position_destination;
}


float InputDeviceConfigurationList::get_scrollbar_reposition_multiplier() const
{
   return scrollbar_reposition_multiplier;
}


float InputDeviceConfigurationList::get_box_gutter_y() const
{
   return box_gutter_y;
}


void InputDeviceConfigurationList::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::InputDeviceConfigurationList::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::InputDeviceConfigurationList::initialize]: error: guard \"(!initialized)\" not met");
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::InputDeviceConfigurationList::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::InputDeviceConfigurationList::initialize]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::InputDeviceConfigurationList::initialize]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::InputDeviceConfigurationList::initialize]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   selection_cursor_box.set_position(0, 0);
   selection_cursor_box.set_size(list_item_box_width, list_item_box_height);
   selection_cursor_box.set_padding(6.0f, 6.0f);
   initialized = true;
   return;
}

void InputDeviceConfigurationList::update()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::InputDeviceConfigurationList::update]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::InputDeviceConfigurationList::update]: error: guard \"initialized\" not met");
   }
   scrollbar_position = (scrollbar_position_destination - scrollbar_position)
                      * scrollbar_reposition_multiplier + scrollbar_position;
   selection_cursor_box.update();
   return;
}

void InputDeviceConfigurationList::render()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::InputDeviceConfigurationList::render]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::InputDeviceConfigurationList::render]: error: guard \"initialized\" not met");
   }
   draw_joystick_configuration_mapping_list_items_and_scrollbar();
   draw_joystick_configuration_mapping_list_title_text();
   return;
}

void InputDeviceConfigurationList::set_joystick_configuration_mapping(std::vector<std::tuple<std::string, uint32_t>> joystick_configuration_mapping)
{
   this->joystick_configuration_mapping = joystick_configuration_mapping;
   cursor_pos = 0;
   return;
}

void InputDeviceConfigurationList::set_physical_input_device(AllegroFlare::PhysicalInputDevices::Base* physical_input_device)
{
   this->physical_input_device = physical_input_device;
   cursor_pos = 0;
   // TODO: consider what other context-changing impliciations there might be when setting a physical_input_device
   return;
}

bool InputDeviceConfigurationList::move_cursor_up()
{
   if (joystick_configuration_mapping.empty()) return false;
   if (is_waiting_user_input_for_remap()) return false; // TODO: test this logic

   int previous_cursor_pos = cursor_pos;
   cursor_pos--;
   // TODO: add optional "wrap"
   while (cursor_pos < 0)
   {
      cursor_pos += joystick_configuration_mapping.size();
   }

   bool cursor_moved = (previous_cursor_pos != cursor_pos);
   if (cursor_moved) move_selection_cursor_box_to_current_cursor_location();

   return true;
}

bool InputDeviceConfigurationList::move_cursor_down()
{
   if (joystick_configuration_mapping.empty()) return false;
   if (is_waiting_user_input_for_remap()) return false; // TODO: test this logic

   int previous_cursor_pos = cursor_pos;
   cursor_pos++;
   // TODO: add optional "wrap"
   while (cursor_pos >= joystick_configuration_mapping.size())
   {
      cursor_pos -= joystick_configuration_mapping.size();
   }

   bool cursor_moved = (previous_cursor_pos != cursor_pos);
   if (cursor_moved) move_selection_cursor_box_to_current_cursor_location();

   return cursor_moved;
}

void InputDeviceConfigurationList::move_selection_cursor_box_to_current_cursor_location()
{
   // TODO: this function
   AllegroFlare::Vec2D new_position = build_selection_cursor_box_position_of_current_cursor_pos();
   selection_cursor_box.reposition_to(new_position.x, new_position.y);

   if (scrollbar_movement_mode_is_follow_proportional())
   {
      float new_scrollbar_position = build_scrollbar_position_at_current_cursor_pos();
      scrollbar_position_destination = new_scrollbar_position;
      // TODO: replace this logic with a "scrollbar_position_destination" type logic
      //scrollbar_position = new_scrollbar_position;
   }

   return;
}

AllegroFlare::Vec2D InputDeviceConfigurationList::build_selection_cursor_box_position_of_current_cursor_pos()
{
   return AllegroFlare::Vec2D(0, cursor_pos * infer_list_item_spacing_y());
}

float InputDeviceConfigurationList::build_scrollbar_position_at_current_cursor_pos()
{
   if (joystick_configuration_mapping.size() <= 1) return 0;
   float normalized_cursor_position = (float)cursor_pos / (joystick_configuration_mapping.size() - 1);
   float container_scroll_range = infer_container_scroll_range();
   return normalized_cursor_position * container_scroll_range;
}

bool InputDeviceConfigurationList::submit_mapping_on_currently_selected_option(uint32_t button_num)
{
   if (joystick_configuration_mapping.empty()) return false;
   if (!is_state(STATE_AWAITING_USER_INPUT_ON_OPTION)) return false; // TODO: test this condition

   std::get<1>(joystick_configuration_mapping[cursor_pos]) = button_num;

   // TODO: add sound effect
   set_state(STATE_MOVING_CURSOR);
   return true;
}

bool InputDeviceConfigurationList::select_current_option_for_remapping()
{
   if (joystick_configuration_mapping.empty()) return false;
   if (is_state(STATE_AWAITING_USER_INPUT_ON_OPTION)) return false; // TODO: test this condition

   // TODO: add sound effect
   set_state(STATE_AWAITING_USER_INPUT_ON_OPTION);
   return true;
}

bool InputDeviceConfigurationList::abort_current_option_for_remapping()
{
   if (joystick_configuration_mapping.empty()) return true;
   if (!is_state(STATE_AWAITING_USER_INPUT_ON_OPTION)) return false; // TODO: test this condition

   // TODO: add sound effect
   set_state(STATE_MOVING_CURSOR);
   return true;
}

void InputDeviceConfigurationList::move_scrollbar_position(float distance_y)
{
   scrollbar_position += distance_y;
   limit_scrollbar_position();
   return;
}

void InputDeviceConfigurationList::set_scrollbar_position(float scrollbar_position)
{
   this->scrollbar_position = scrollbar_position;
   limit_scrollbar_position();
   return;
}

void InputDeviceConfigurationList::set_scrollbar_reposition_multiplier(float scrollbar_reposition_multiplier)
{
   if (!((scrollbar_reposition_multiplier > 0.001)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::InputDeviceConfigurationList::set_scrollbar_reposition_multiplier]: error: guard \"(scrollbar_reposition_multiplier > 0.001)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::InputDeviceConfigurationList::set_scrollbar_reposition_multiplier]: error: guard \"(scrollbar_reposition_multiplier > 0.001)\" not met");
   }
   if (!((scrollbar_reposition_multiplier <= 1.0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::InputDeviceConfigurationList::set_scrollbar_reposition_multiplier]: error: guard \"(scrollbar_reposition_multiplier <= 1.0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::InputDeviceConfigurationList::set_scrollbar_reposition_multiplier]: error: guard \"(scrollbar_reposition_multiplier <= 1.0)\" not met");
   }
   // TODO: test this function
   this->scrollbar_reposition_multiplier = scrollbar_reposition_multiplier;
   return;
}

void InputDeviceConfigurationList::set_scrollbar_position_to_max()
{
   this->scrollbar_position = infer_container_scroll_range();
   return;
}

float InputDeviceConfigurationList::infer_scrollbar_max_position()
{
   return infer_container_scroll_range();
}

bool InputDeviceConfigurationList::scrollbar_is_autohidden_because_list_contents_is_smaller_than_the_container()
{
   return infer_container_scroll_range() <= 0;
}

std::vector<std::tuple<std::string, uint32_t>> InputDeviceConfigurationList::build_placeholder_joystick_configuration_mapping()
{
   return {
      { "Up", 7 },
      { "Down", 8 },
      { "Left", 9 },
      { "Right", 10 },
      { "Primary Action", 1 },
      { "Secondary Action", 2 },
      { "Back", 3 },
      { "Start / Menu", 4 },
      { "Right Bumper", 5 },
      { "Left Bumper", 6 },
      //{ "unlocked", "Fade In", "Start out in the world." },
      //{ "locked",   "Call to Adventure", "Leave what you know in order to take on a challenge you must face." },
      //{ "locked",   "Save the Cat", "Define the hero and make the audience like them." },
      //{ "unlocked", "Break the Fourth Wall", "Make the developer realize they're looking at test data." },
      //{ "hidden",   "Top Secrets", "Find the box of secrets in the 2nd act." },
      //{ "locked",   "I'm Lovin' It", "Complete the AchievementsList feature." },
      //{ "unlocked", "Everyone is Beautiful", "Make multiline text fit into the box with the correct width." },
      //{ "hidden",   "Save the Best for Last", "Find out the most important part in the very end." },
   };
}

void InputDeviceConfigurationList::draw_header_title_backfill()
{
   // draw inputs
   float backfill_opacity = 0.35;
   float bar_height = 160;
   ALLEGRO_COLOR backfill_color = ALLEGRO_COLOR{0, 0, 0, backfill_opacity};
   al_draw_filled_rectangle(0, 0, surface_width, bar_height, backfill_color);
   return;
}

int InputDeviceConfigurationList::count_num_joystick_configuration_mapping()
{
   return joystick_configuration_mapping.size();
}

bool InputDeviceConfigurationList::joystick_configuration_mapping_is_empty()
{
   return joystick_configuration_mapping.empty();
}

void InputDeviceConfigurationList::draw_joystick_configuration_mapping_list_title_text()
{
   ALLEGRO_FONT *font = obtain_title_font();
   ALLEGRO_COLOR color = ALLEGRO_COLOR{1.0, 1.0, 1.0, 1.0};
   float surface_padding_x = 300;

   // draw the backfill
   draw_header_title_backfill();

   // draw the title text
   al_draw_text(
      font,
      color,
      surface_padding_x,
      100,
      ALLEGRO_ALIGN_LEFT,
      build_heading_label().c_str()
      //"J O Y S T I C K   C O N F I G U R A T I O N"
   );

   //// draw the number achieved
   //al_draw_text(
      //font,
      //color,
      //1920-surface_padding_x,
      //100,
      //ALLEGRO_ALIGN_RIGHT,
      //build_joystick_configuration_mapping_count_string().c_str()
   //);

   return;
}

std::string InputDeviceConfigurationList::build_heading_label()
{
   std::stringstream ss;
   if (!physical_input_device)
   {
      ss << "Input Configuration (no input devices connected)";
      // TODO: add case/conditional for when the input device is disconnected
   }
   else
   {
      ss << "Player " << (player_num+1) << " ";
      ss << "Input Configuration ";
      ss << "(Using " << physical_input_device->get_name() << ")";
   }
   return ss.str();
}

float InputDeviceConfigurationList::infer_container_height()
{
   return 800;
   //return (list_item_box_height + box_gutter_y) * 5.5;
}

float InputDeviceConfigurationList::infer_container_contents_height()
{
   if (joystick_configuration_mapping.empty()) return 0;
   float y_spacing = list_item_box_height + box_gutter_y;
   return joystick_configuration_mapping.size() * y_spacing - box_gutter_y;
}

float InputDeviceConfigurationList::infer_list_item_height()
{
   return list_item_box_height;
}

float InputDeviceConfigurationList::infer_list_item_spacing_y()
{
   return list_item_box_height + box_gutter_y;
}

float InputDeviceConfigurationList::infer_container_scroll_range()
{
   return infer_container_contents_height() - infer_container_height();
}

void InputDeviceConfigurationList::limit_scrollbar_position()
{
   float container_height = infer_container_height();
   float container_scroll_range = infer_container_scroll_range();
   scrollbar_position = std::max(0.0f, std::min(container_scroll_range, scrollbar_position));
   return;
}

bool InputDeviceConfigurationList::scrollbar_movement_mode_is_follow_proportional()
{
   return scrollbar_movement_mode == SCROLLBAR_MOVEMENT_FOLLOW_PROPORTIONAL;
}

void InputDeviceConfigurationList::draw_joystick_configuration_mapping_list_items_and_scrollbar()
{
   float joystick_configuration_mapping_list_x = surface_width/2;
   float joystick_configuration_mapping_list_y = surface_height/2 + 40;
   float joystick_configuration_mapping_list_width = list_item_box_width;
   float scrollbar_x_padding = 70;
   float scrollbar_y_padding = 26;
   ALLEGRO_COLOR joystick_configuration_mapping_list_frame_color = ALLEGRO_COLOR{0.2, 0.205, 0.21, 1.0};
   ALLEGRO_COLOR scrollbar_bar_color = ALLEGRO_COLOR{0.2, 0.205, 0.21, 1.0};
   ALLEGRO_COLOR scrollbar_handle_color = ALLEGRO_COLOR{0.5, 0.505, 0.51, 1.0};
   float joystick_configuration_mapping_box_list_x = 0;
   float joystick_configuration_mapping_box_list_y = 0;
   float y_spacing = infer_list_item_spacing_y();
   float frame_thickness = 6.0;
   float frame_outset = box_gutter_y + 2;
   float joystick_configuration_mapping_list_height = infer_container_height();
   float container_contents_height = infer_container_contents_height();
   float container_scroll_range = infer_container_scroll_range();
   float normalized_scrollbar_position = scrollbar_position / container_scroll_range;

   AllegroFlare::Placement2D place(
      joystick_configuration_mapping_list_x,
      joystick_configuration_mapping_list_y,
      joystick_configuration_mapping_list_width,
      joystick_configuration_mapping_list_height
   );

   AllegroFlare::Placement2D scrollarea_contents(
      0,
      -scrollbar_position,
      0,
      0
   );

   place.start_transform();

   // Draw the empty state (if there is no configuration)
   if (joystick_configuration_mapping.empty())
   {
      std::string empty_state_text_string = "There are no items to configure";
      ALLEGRO_FONT *empty_state_text_font = obtain_empty_state_text_font();
      // TODO: Consider if this empty_state_text_color value might correlate with the empty state text color
      // in the framework (for example, the "No screens are currently showing" message).
      ALLEGRO_COLOR empty_state_text_color = ALLEGRO_COLOR{0.4, 0.4, 0.4, 0.4};
      float empty_state_text_x = joystick_configuration_mapping_list_width / 2;
      float empty_state_text_y = joystick_configuration_mapping_list_height / 2
                               - al_get_font_line_height(empty_state_text_font);
      al_draw_text(
         empty_state_text_font,
         empty_state_text_color,
         empty_state_text_x,
         empty_state_text_y,
         ALLEGRO_ALIGN_CENTER,
         empty_state_text_string.c_str()
      );
   }
   else // There are items to render in the configuration list
   {
      // Draw the scrollarea contents
      scrollarea_contents.start_transform();

      // Draw the items in the list
      for (int i=0; i<joystick_configuration_mapping.size(); i++)
      {
         std::string action_label = std::get<0>(joystick_configuration_mapping[i]);
         uint32_t mapped_button_num = std::get<1>(joystick_configuration_mapping[i]);
         //std::string description = std::get<2>(joystick_configuration_mapping[i]);
         // TODO:
         // HERE: render
         draw_joystick_configuration_item_box(
            joystick_configuration_mapping_box_list_x,
            joystick_configuration_mapping_box_list_y + i * y_spacing,
            action_label,
            "Button " + std::to_string(mapped_button_num)
         );
      }

      // Show the selection cursor
      selection_cursor_box.render();

      scrollarea_contents.restore_transform();

      // draw the scrollbar
      if (!scrollbar_is_autohidden_because_list_contents_is_smaller_than_the_container())
      {
         AllegroFlare::Elements::Scrollbar scrollbar(
            joystick_configuration_mapping_list_width + scrollbar_x_padding,
            scrollbar_y_padding,
            joystick_configuration_mapping_list_height - scrollbar_y_padding * 2,
            normalized_scrollbar_position,
            scrollbar_bar_color,
            scrollbar_handle_color
         );
         scrollbar.render();
      }
   }


   place.restore_transform();
   return;
}

bool InputDeviceConfigurationList::is_waiting_user_input_for_remap()
{
   return is_state(STATE_AWAITING_USER_INPUT_ON_OPTION);
}

void InputDeviceConfigurationList::draw_joystick_configuration_item_box(float x, float y, std::string action_name, std::string mapped_button_name)
{
   ALLEGRO_COLOR box_color = ALLEGRO_COLOR{0.1, 0.105, 0.11, 1.0};
   ALLEGRO_FONT *item_title_font = obtain_item_title_font();
   float box_padding_x = 26;
   float box_padding_y = 10;
   int text_y = (list_item_box_height / 2) - (al_get_font_line_height(item_title_font) / 2);

   // draw the backfill box
   al_draw_filled_rectangle(x, y, x + list_item_box_width, y + list_item_box_height, box_color);

   // draw the action_name
   al_draw_text(
      item_title_font,
      ALLEGRO_COLOR{1, 1, 1, 1},
      x + box_padding_x,
      y + text_y, // update this to be vertical-centered
      ALLEGRO_ALIGN_LEFT,
      action_name.c_str()
   );

   // draw the mapped_button_name
   // draw the mapped_button_name background box
   float column_2_x = 550;
   float mapped_button_background_box_width = 160;
   float mapped_button_background_box_height = list_item_box_height - box_padding_y*2;
   float mapped_button_name_x = x + list_item_box_width - mapped_button_background_box_width - box_padding_x;
   float mapped_button_name_y = text_y;

   al_draw_filled_rectangle(
      mapped_button_name_x - mapped_button_background_box_width,
      y + box_padding_y,
      mapped_button_name_x + mapped_button_background_box_width,
      y + box_padding_y + mapped_button_background_box_height,
      ALLEGRO_COLOR{0.2, 0.2, 0.2, 0.2}
   );

   // draw the mapped_button_name text
   al_draw_text(
      item_title_font,
      ALLEGRO_COLOR{1, 1, 1, 1},
      mapped_button_name_x,
      y + mapped_button_name_y,
      ALLEGRO_ALIGN_CENTER,
      mapped_button_name.c_str()
   );
   return;
}

int32_t InputDeviceConfigurationList::infer_icon_character_by_status(std::string status)
{
   if (status == "unlocked") return 0xf091;
   else if (status == "locked") return 0xf023;
   else if (status == "hidden") return 0x3f;
   return 0xe1fe;
}

ALLEGRO_COLOR InputDeviceConfigurationList::infer_icon_color_by_status(std::string status, ALLEGRO_COLOR icon_locked_color, ALLEGRO_COLOR icon_hidden_color, ALLEGRO_COLOR icon_achieved_color)
{
   if (status == "unlocked") return icon_achieved_color;
   else if (status == "locked") return icon_locked_color;
   else if (status == "hidden") return icon_hidden_color;
   return ALLEGRO_COLOR{1, 0, 0, 1};
}

std::string InputDeviceConfigurationList::filter_item_title_through_status(std::string title, std::string status)
{
   if (status == "hidden") return "Hidden Achievement";
   return title;
}

std::string InputDeviceConfigurationList::filter_item_description_through_status(std::string description, std::string status)
{
   if (status == "hidden") return "";
   return description;
}

void InputDeviceConfigurationList::set_state(uint32_t state, bool override_if_busy)
{
   if (!(is_valid_state(state)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::InputDeviceConfigurationList::set_state]: error: guard \"is_valid_state(state)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::InputDeviceConfigurationList::set_state]: error: guard \"is_valid_state(state)\" not met");
   }
   if (this->state == state) return;
   if (!override_if_busy && state_is_busy) return;
   uint32_t previous_state = this->state;

   switch (state)
   {
      case STATE_MOVING_CURSOR:
      break;

      case STATE_AWAITING_USER_INPUT_ON_OPTION:
      break;

      default:
         throw std::runtime_error("JoystickConfigurationList: weird error");
      break;
   }

   this->state = state;
   state_changed_at = al_get_time();

   return;
}

bool InputDeviceConfigurationList::is_valid_state(uint32_t state)
{
   std::set<uint32_t> valid_states =
   {
      //STATE_REVEALING, <-- TODO: add this eventually
      STATE_MOVING_CURSOR,
      STATE_AWAITING_USER_INPUT_ON_OPTION,
      //STATE_CLOSING_DOWN, <-- TODO: add this eventually
   };
   return (valid_states.count(state) > 0);
}

bool InputDeviceConfigurationList::is_state(uint32_t possible_state)
{
   return (state == possible_state);
}

float InputDeviceConfigurationList::infer_current_state_age(float time_now)
{
   return (time_now - state_changed_at);
}

ALLEGRO_FONT* InputDeviceConfigurationList::obtain_title_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::InputDeviceConfigurationList::obtain_title_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::InputDeviceConfigurationList::obtain_title_font]: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Inter-Bold.ttf -40");
}

ALLEGRO_FONT* InputDeviceConfigurationList::obtain_item_title_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::InputDeviceConfigurationList::obtain_item_title_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::InputDeviceConfigurationList::obtain_item_title_font]: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Inter-Bold.ttf -34");
}

ALLEGRO_FONT* InputDeviceConfigurationList::obtain_empty_state_text_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::InputDeviceConfigurationList::obtain_empty_state_text_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::InputDeviceConfigurationList::obtain_empty_state_text_font]: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Inter-Regular.ttf -34");
}

ALLEGRO_FONT* InputDeviceConfigurationList::obtain_item_description_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::InputDeviceConfigurationList::obtain_item_description_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::InputDeviceConfigurationList::obtain_item_description_font]: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Inter-Regular.ttf -26");
}

ALLEGRO_FONT* InputDeviceConfigurationList::obtain_icon_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::InputDeviceConfigurationList::obtain_icon_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::InputDeviceConfigurationList::obtain_icon_font]: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("fa-solid-900.ttf -50");
}

void InputDeviceConfigurationList::draw_unicode_character(ALLEGRO_FONT* font, ALLEGRO_COLOR color, int x, int y, uint32_t icon, int flags)
{
   static ALLEGRO_USTR *ustr = NULL;
   if (!ustr) ustr = al_ustr_new("");
   al_ustr_set_chr(ustr, 0, icon);
   al_draw_ustr(font, color, x, y, flags, ustr);
   return;
}


} // namespace Elements
} // namespace AllegroFlare


