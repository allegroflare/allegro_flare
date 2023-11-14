

#include <AllegroFlare/Elements/InputDevicesList.hpp>

#include <AllegroFlare/Elements/Scrollbar.hpp>
#include <AllegroFlare/PhysicalInputDevices/Joysticks/Base.hpp>
#include <AllegroFlare/PhysicalInputDevices/Keyboard.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <algorithm>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{


InputDevicesList::InputDevicesList(AllegroFlare::FontBin* font_bin, std::vector<std::tuple<AllegroFlare::PhysicalInputDevices::Base*, uint32_t, std::string, std::string>> input_devices, float list_item_box_width, float list_item_box_height)
   : font_bin(font_bin)
   , input_devices(input_devices)
   , list_item_box_width(list_item_box_width)
   , list_item_box_height(list_item_box_height)
   , surface_width(1920)
   , surface_height(1080)
   , cursor_pos(0)
   , selection_cursor_box({})
   , selection_cursor_button({})
   , scrollbar_position(0.0f)
   , scrollbar_position_destination(0.0f)
   , scrollbar_movement_mode(SCROLLBAR_MOVEMENT_FOLLOW_PROPORTIONAL)
   , box_gutter_y(10.0f)
   , scrollbar_reposition_multiplier(DEFAULT_SCROLLBAR_REPOSITION_MULTIPLIER)
   , initialized(false)
{
}


InputDevicesList::~InputDevicesList()
{
}


void InputDevicesList::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void InputDevicesList::set_list_item_box_width(float list_item_box_width)
{
   this->list_item_box_width = list_item_box_width;
}


void InputDevicesList::set_list_item_box_height(float list_item_box_height)
{
   this->list_item_box_height = list_item_box_height;
}


void InputDevicesList::set_surface_width(int surface_width)
{
   this->surface_width = surface_width;
}


void InputDevicesList::set_surface_height(int surface_height)
{
   this->surface_height = surface_height;
}


void InputDevicesList::set_box_gutter_y(float box_gutter_y)
{
   this->box_gutter_y = box_gutter_y;
}


std::vector<std::tuple<AllegroFlare::PhysicalInputDevices::Base*, uint32_t, std::string, std::string>> InputDevicesList::get_input_devices() const
{
   return input_devices;
}


float InputDevicesList::get_list_item_box_width() const
{
   return list_item_box_width;
}


float InputDevicesList::get_list_item_box_height() const
{
   return list_item_box_height;
}


int InputDevicesList::get_surface_width() const
{
   return surface_width;
}


int InputDevicesList::get_surface_height() const
{
   return surface_height;
}


int InputDevicesList::get_cursor_pos() const
{
   return cursor_pos;
}


float InputDevicesList::get_scrollbar_position() const
{
   return scrollbar_position;
}


float InputDevicesList::get_scrollbar_position_destination() const
{
   return scrollbar_position_destination;
}


float InputDevicesList::get_box_gutter_y() const
{
   return box_gutter_y;
}


float InputDevicesList::get_scrollbar_reposition_multiplier() const
{
   return scrollbar_reposition_multiplier;
}


bool InputDevicesList::get_initialized() const
{
   return initialized;
}


void InputDevicesList::set_input_devices(std::vector<std::tuple<AllegroFlare::PhysicalInputDevices::Base*, uint32_t, std::string, std::string>> input_devices)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[InputDevicesList::set_input_devices]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("InputDevicesList::set_input_devices: error: guard \"initialized\" not met");
   }
   this->input_devices = input_devices;
   cursor_pos = 0;
   // TODO: Set input devices
   // TODO: Set cursor_pos to 0
   // TODO: Add test for cursor_pos @ 0
   return;
}

void InputDevicesList::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[InputDevicesList::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("InputDevicesList::initialize: error: guard \"(!initialized)\" not met");
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[InputDevicesList::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("InputDevicesList::initialize: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[InputDevicesList::initialize]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("InputDevicesList::initialize: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[InputDevicesList::initialize]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("InputDevicesList::initialize: error: guard \"font_bin\" not met");
   }
   selection_cursor_box.set_position(0, 0);
   selection_cursor_box.set_size(list_item_box_width, list_item_box_height);
   selection_cursor_box.set_padding(6.0f, 6.0f);

   selection_cursor_button.set_font_bin(font_bin);
   selection_cursor_button.set_text("CONFIGURE >");
   selection_cursor_button.set_core_color(selection_cursor_box.get_core_color());
   selection_cursor_button.align_to_right_centered();

   AllegroFlare::Vec2D new_button_position = build_selection_cursor_button_position_of_current_cursor_pos();
   selection_cursor_button.set_x(new_button_position.x);
   selection_cursor_button.set_y(new_button_position.y);

   initialized = true;
   return;
}

bool InputDevicesList::move_cursor_up()
{
   if (input_devices.empty()) return false;
   //if (state != STATE_MOVING_CURSOR) return false;

   int previous_cursor_pos = cursor_pos;
   cursor_pos--;
   // TODO: add optional "wrap"
   while (cursor_pos < 0)
   {
      cursor_pos += input_devices.size();
   }

   bool cursor_moved = (previous_cursor_pos != cursor_pos);
   if (cursor_moved) move_selection_cursor_box_to_current_cursor_location();

   return true;
}

bool InputDevicesList::move_cursor_down()
{
   if (input_devices.empty()) return false;
   //if (state != STATE_MOVING_CURSOR) return false;

   int previous_cursor_pos = cursor_pos;
   cursor_pos++;
   // TODO: add optional "wrap"
   while (cursor_pos >= input_devices.size())
   {
      cursor_pos -= input_devices.size();
   }

   bool cursor_moved = (previous_cursor_pos != cursor_pos);
   if (cursor_moved) move_selection_cursor_box_to_current_cursor_location();

   return cursor_moved;
}

void InputDevicesList::move_selection_cursor_box_to_current_cursor_location()
{
   // HERE
   // Move the selection cursor box
   AllegroFlare::Vec2D new_position = build_selection_cursor_box_position_of_current_cursor_pos();
   selection_cursor_box.reposition_to(new_position.x, new_position.y);

   if (current_selected_item_is_connected())
   {
      // TODO: Consider alternatives to this snapping repositioning technique. For example, an alternative
      // could be that each list element has its own button, but the button "shows" when the cursor is over the
      // list item (and "hides" when moved away). Another alternative could be to have the "CONFIGURE" button
      // belong to the cursor, moving/displacing along with it.
      AllegroFlare::Vec2D new_button_position = build_selection_cursor_button_position_of_current_cursor_pos();
      selection_cursor_button.set_x(new_button_position.x);
      selection_cursor_button.set_y(new_button_position.y);
      // TODO: Have button "re-init" it's hilight when it moves
      // TODO: Find a good way to synchronize the pulsation of the cursor and button
   }
   else
   {
      // TODO: "hide" selection_cursor_button
   }

   if (scrollbar_movement_mode_is_follow_proportional())
   {
      float new_scrollbar_position = build_scrollbar_position_at_current_cursor_pos();
      scrollbar_position_destination = new_scrollbar_position;
      // TODO: replace this logic with a "scrollbar_position_destination" type logic
      //scrollbar_position = new_scrollbar_position;
   }

   return;
}

AllegroFlare::Vec2D InputDevicesList::build_selection_cursor_box_position_of_current_cursor_pos()
{
   return AllegroFlare::Vec2D(0, cursor_pos * infer_list_item_spacing_y());
}

AllegroFlare::Vec2D InputDevicesList::build_selection_cursor_button_position_of_current_cursor_pos()
{
   AllegroFlare::Vec2D selection_cursor_box_position = build_selection_cursor_box_position_of_current_cursor_pos();
   float button_x_padding = 30;
   return AllegroFlare::Vec2D(
      selection_cursor_box_position.x + list_item_box_width - button_x_padding,
      selection_cursor_box_position.y + list_item_box_height / 2 // TODO: Consider integerizing this
   );
}

float InputDevicesList::infer_list_item_spacing_y()
{
   return list_item_box_height + box_gutter_y;
}

bool InputDevicesList::scrollbar_movement_mode_is_follow_proportional()
{
   return scrollbar_movement_mode == SCROLLBAR_MOVEMENT_FOLLOW_PROPORTIONAL;
}

void InputDevicesList::update()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[InputDevicesList::update]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("InputDevicesList::update: error: guard \"initialized\" not met");
   }
   scrollbar_position = (scrollbar_position_destination - scrollbar_position)
                      * scrollbar_reposition_multiplier + scrollbar_position;
   selection_cursor_box.update();
   return;
}

void InputDevicesList::render()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[InputDevicesList::render]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("InputDevicesList::render: error: guard \"initialized\" not met");
   }
   draw_input_devices_list_items_and_scrollbar();
   draw_input_devices_list_title_text_and_completed_title_text();
   return;
}

void InputDevicesList::move_scrollbar_position(float distance_y)
{
   scrollbar_position += distance_y;
   limit_scrollbar_position();
   return;
}

void InputDevicesList::set_scrollbar_position(float scrollbar_position)
{
   this->scrollbar_position = scrollbar_position;
   limit_scrollbar_position();
   return;
}

void InputDevicesList::set_scrollbar_position_to_max()
{
   this->scrollbar_position = infer_container_scroll_range();
   return;
}

float InputDevicesList::infer_scrollbar_max_position()
{
   return infer_container_scroll_range();
}

bool InputDevicesList::scrollbar_is_autohidden_because_list_contents_is_smaller_than_the_container()
{
   return list_contents_is_smaller_than_the_container();
}

bool InputDevicesList::list_contents_is_smaller_than_the_container()
{
   return infer_container_scroll_range() <= 0;
}

float InputDevicesList::build_scrollbar_position_at_current_cursor_pos()
{
   if (input_devices.size() <= 1) return 0;
   float normalized_cursor_position = (float)cursor_pos / (input_devices.size() - 1);
   float container_scroll_range = infer_container_scroll_range();
   return normalized_cursor_position * container_scroll_range;
}

std::vector<std::tuple<AllegroFlare::PhysicalInputDevices::Base*, uint32_t, std::string, std::string>> InputDevicesList::build_placeholder_input_devices()
{
   // HAVE:
   //AllegroFlare::PhysicalInputDevices::Base *physical_input_device = std::get<0>(input_devices[i]);
   //std::string status = std::get<1>(input_devices[i]);
   //std::string title = std::get<2>(input_devices[i]);

   // WANT:
   // device_name
   // connected_status
   // connected_since?
   // device_id

   // TODO: Don't use created pointers for these devices here. Find a better location to produce the
   // objects in memory, possibly just a raw AllegroFlare/InputDevicesList;

   AllegroFlare::PhysicalInputDevices::Base* keyboard = new AllegroFlare::PhysicalInputDevices::Keyboard();

   return {
      { new AllegroFlare::PhysicalInputDevices::Keyboard(),
         CONNECTION_STATUS_CONNECTED,
         "Keyboard",
         ""
      },
      { new AllegroFlare::PhysicalInputDevices::Joysticks::Base(),
         CONNECTION_STATUS_CONNECTED,
         "Joystick (1)",
         "159295b"
      },
      { new AllegroFlare::PhysicalInputDevices::Joysticks::Base(),
         CONNECTION_STATUS_CONNECTED,
         "Joystick (2)",
         "159295b"
      },
      { new AllegroFlare::PhysicalInputDevices::Joysticks::Base(),
         CONNECTION_STATUS_DISCONNECTED,
         "Joystick (3)",
         "af97a9c"
      },
      { new AllegroFlare::PhysicalInputDevices::Joysticks::Base(),
         CONNECTION_STATUS_DISCONNECTED,
         "Joystick (4)",
         "af97a9c"
      },
      { new AllegroFlare::PhysicalInputDevices::Joysticks::Base(),
         CONNECTION_STATUS_DISCONNECTED,
         "Joystick (5)",
         "af97a9c"
      },
   };
}

int InputDevicesList::count_num_input_devices_connected()
{
   int count = 0;
   for (int i=0; i<input_devices.size(); i++)
   {
      bool is_connected = (std::get<1>(input_devices[i]) == CONNECTION_STATUS_CONNECTED);
      if (is_connected) count++;
   }
   return count;
}

int InputDevicesList::count_num_input_devices_disconnected()
{
   return count_num_input_devices() - count_num_input_devices_connected();
}

void InputDevicesList::draw_header_title_backfill()
{
   // draw inputs
   float backfill_opacity = 0.35;
   float bar_height = 160;
   ALLEGRO_COLOR backfill_color = ALLEGRO_COLOR{0, 0, 0, backfill_opacity};
   al_draw_filled_rectangle(0, 0, surface_width, bar_height, backfill_color);
   return;
}

int InputDevicesList::count_num_input_devices()
{
   return input_devices.size();
}

std::string InputDevicesList::build_input_devices_count_string()
{
   std::stringstream result;
   result << count_num_input_devices_connected() << " connected (" << count_num_input_devices_disconnected()
          << " disconnected)";
   return result.str();
}

void InputDevicesList::draw_input_devices_list_title_text_and_completed_title_text()
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
      "I N P U T   D E V I C E S"
   );

   // draw the number achieved
   al_draw_text(
      font,
      color,
      1920-surface_padding_x,
      100,
      ALLEGRO_ALIGN_RIGHT,
      build_input_devices_count_string().c_str()
   );
   return;
}

float InputDevicesList::infer_container_height()
{
   return 800;
   //return (list_item_box_height + box_gutter_y) * 5.5;
}

float InputDevicesList::infer_list_item_y_spacing()
{
   return list_item_box_height + box_gutter_y;
}

float InputDevicesList::infer_container_contents_height_for_n_elements(int num_elements)
{
   if (!(num_elements >= 0))
   {
      std::stringstream error_message;
      error_message << "[InputDevicesList::infer_container_contents_height_for_n_elements]: error: guard \"num_elements >= 0\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("InputDevicesList::infer_container_contents_height_for_n_elements: error: guard \"num_elements >= 0\" not met");
   }
   if (num_elements == 0) return 0;
   return num_elements * infer_list_item_y_spacing() - box_gutter_y;
}

float InputDevicesList::infer_container_contents_height()
{
   return infer_container_contents_height_for_n_elements(input_devices.size());
}

float InputDevicesList::infer_container_scroll_range()
{
   return infer_container_contents_height() - infer_container_height();
}

void InputDevicesList::limit_scrollbar_position()
{
   float container_height = infer_container_height();
   float container_contents_height = infer_container_contents_height();
   float container_scroll_range = infer_container_scroll_range();
   scrollbar_position = std::max(0.0f, std::min(container_scroll_range, scrollbar_position));
   return;
}

void InputDevicesList::draw_scrollarea_contents()
{
   float input_devices_box_list_x = 0;
   float input_devices_box_list_y = 0;
   float y_spacing = infer_list_item_y_spacing();

   for (int i=0; i<input_devices.size(); i++)
   {
      AllegroFlare::PhysicalInputDevices::Base *physical_input_device = std::get<0>(input_devices[i]);
      uint32_t connected_status = std::get<1>(input_devices[i]);
      std::string title = std::get<2>(input_devices[i]);
      std::string device_id = std::get<3>(input_devices[i]);

      draw_input_device_box(
         input_devices_box_list_x,
         input_devices_box_list_y + i * y_spacing,
         physical_input_device,
         connected_status,
         title,
         device_id
      );
   }

   // Show the selection cursor
   selection_cursor_box.render();

   // Show the selection cursor button (if item is not disabled)
   if (current_selected_item_is_connected()) // TODO: Consider a "show"/"hide" concept on the button instead
   {
      selection_cursor_button.render();
   }
}

void InputDevicesList::draw_input_devices_list_items_and_scrollbar()
{
   float input_devices_list_x = surface_width/2;
   float input_devices_list_y = surface_height/2 + 40;
   float input_devices_list_width = list_item_box_width;
   float scrollbar_x_padding = 70;
   float scrollbar_y_padding = 26;
   ALLEGRO_COLOR input_devices_list_frame_color = ALLEGRO_COLOR{0.2, 0.205, 0.21, 1.0};
   ALLEGRO_COLOR scrollbar_bar_color = ALLEGRO_COLOR{0.2, 0.205, 0.21, 1.0};
   ALLEGRO_COLOR scrollbar_handle_color = ALLEGRO_COLOR{0.5, 0.505, 0.51, 1.0};
   //float input_devices_box_list_x = 0;
   //float input_devices_box_list_y = 0;
   float y_spacing = infer_list_item_y_spacing();
   float frame_thickness = 6.0;
   float frame_outset = box_gutter_y + 2;
   float container_height = infer_container_height();
   float container_contents_height = infer_container_contents_height();
   float container_scroll_range = infer_container_scroll_range();
   float normalized_scrollbar_position = scrollbar_position / container_scroll_range; // OK

   AllegroFlare::Placement2D place(
      input_devices_list_x,
      input_devices_list_y,
      input_devices_list_width,
      container_height
   );

   AllegroFlare::Placement2D scrollarea_contents(
      0,
      -scrollbar_position,
      0,
      0
   );

   place.start_transform();

   // draw the items in the list
   if (input_devices.empty())
   {
      // TODO: Render empty state
      // TODO: Test this condition
   }
   else // There are no items to render
   {
      // TODO: Test this condition

      //// draw the scrollarea contents DEBUGGING:
      //float frame_outset = 1;
      //al_draw_rounded_rectangle(
         //0 - frame_outset,
         //0 - frame_outset,
         //input_devices_list_width + frame_outset,
         //container_contents_height + frame_outset,
         //5.0,
         //5.0,
         //ALLEGRO_COLOR{.5, 0.3, 0.4, 0.5},
         //frame_thickness
      //);

      // Draw the scrollarea contents
      // TODO: Test this transforming and non-transforming state
      if (!list_contents_is_smaller_than_the_container())
      {
         scrollarea_contents.start_transform();
      }

      draw_scrollarea_contents();

      if (!list_contents_is_smaller_than_the_container())
      {
         scrollarea_contents.restore_transform();
      }

      //// draw the frame DEBUGGING:
      //frame_outset = -1;
      //al_draw_rounded_rectangle(
         //0 - frame_outset,
         //0 - frame_outset,
         //input_devices_list_width + frame_outset,
         //container_height + frame_outset,
         //5.0,
         //5.0,
         //input_devices_list_frame_color,
         //frame_thickness
      //);

      // draw the scrollbar
      if (!scrollbar_is_autohidden_because_list_contents_is_smaller_than_the_container())
      {
         AllegroFlare::Elements::Scrollbar scrollbar(
            input_devices_list_width + scrollbar_x_padding,
            scrollbar_y_padding,
            container_height - scrollbar_y_padding * 2,
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

void InputDevicesList::draw_input_device_box(float x, float y, AllegroFlare::PhysicalInputDevices::Base* physical_input_device, uint32_t connection_status, std::string title, std::string device_id)
{
   ALLEGRO_FONT *item_title_font = obtain_item_title_font();
   ALLEGRO_FONT *description_font = obtain_item_description_font();
   ALLEGRO_FONT *icon_font = obtain_icon_font();
   //float list_item_box_width = 800.0f;
   //float list_item_box_height = 150.0f;
   float box_padding_x = 20;
   float box_padding_y = 20;
   float title_padding_y = 10;
   ALLEGRO_COLOR title_text_color_normal = ALLEGRO_COLOR{1, 1, 1, 1};
   ALLEGRO_COLOR box_color = ALLEGRO_COLOR{0.1, 0.105, 0.11, 1.0};
   ALLEGRO_COLOR icon_container_box_color = ALLEGRO_COLOR{0.2, 0.205, 0.21, 1.0};
   ALLEGRO_COLOR icon_locked_color = ALLEGRO_COLOR{0.4, 0.405, 0.41, 1};
   ALLEGRO_COLOR icon_hidden_color = icon_container_box_color;
   ALLEGRO_COLOR icon_achieved_color = ALLEGRO_COLOR{1, 1, 1, 1};
   ALLEGRO_COLOR description_text_color = icon_locked_color;
   ALLEGRO_COLOR title_text_color_hidden = icon_locked_color;
   float item_title_font_line_height = al_get_font_line_height(item_title_font);
   float description_font_line_height = al_get_font_line_height(description_font);
   float icon_font_line_height = al_get_font_line_height(icon_font);
   float icon_container_box_size = list_item_box_height - box_padding_x*2;
   float text_y_offset = 10;
   float icon_container_box_text_x_padding = 30;
   float text_x_offset = icon_container_box_size + icon_container_box_text_x_padding;

   ALLEGRO_COLOR title_text_color = (connection_status == CONNECTION_STATUS_DISCONNECTED) ? title_text_color_hidden : title_text_color_normal;

   float icon_box_center_x = x + box_padding_x + icon_container_box_size / 2;
   float icon_box_center_y = y + box_padding_y + icon_container_box_size / 2;
   int32_t icon_character = infer_icon_character_for_physical_input_device(physical_input_device);
   ALLEGRO_COLOR icon_color = infer_icon_color_by_connection_status(
      connection_status,
      icon_locked_color,
      icon_hidden_color,
      icon_achieved_color
   );

   // draw the filled rectangle
   if (connection_status == CONNECTION_STATUS_DISCONNECTED)
   {
      float hidden_box_stroke_thickness = 4.0f;
      float h_thickness = hidden_box_stroke_thickness * 0.5;
      al_draw_rectangle(
         x + h_thickness,
         y + h_thickness,
         x + list_item_box_width - h_thickness,
         y + list_item_box_height - h_thickness,
         box_color,
         hidden_box_stroke_thickness
      );
   }
   else
   {
      al_draw_filled_rectangle(x, y, x + list_item_box_width, y + list_item_box_height, box_color);
   }

   // Draw the icon container box rectangle
   // TODO: Consider always making this a solid box, with a darker color
   if (connection_status == CONNECTION_STATUS_DISCONNECTED)
   {
      float hidden_icon_box_stroke_thickness = 4.0f;
      float h_thickness = hidden_icon_box_stroke_thickness * 0.5;
      al_draw_rectangle(
         x + box_padding_x + h_thickness,
         y + box_padding_y + h_thickness,
         x + box_padding_x + icon_container_box_size - h_thickness,
         y + box_padding_y + icon_container_box_size - h_thickness,
         icon_container_box_color,
         hidden_icon_box_stroke_thickness
      );
   }
   else
   {
      al_draw_filled_rectangle(
         x + box_padding_x,
         y + box_padding_y,
         x + box_padding_x + icon_container_box_size,
         y + box_padding_y + icon_container_box_size,
         icon_container_box_color
      );
   }

   // draw the icon
   draw_unicode_character(
      icon_font,
      icon_color,
      icon_box_center_x,
      icon_box_center_y - icon_font_line_height / 2,
      icon_character,
      ALLEGRO_ALIGN_CENTER
   );

   // draw the title text
   al_draw_text(
      item_title_font,
      title_text_color,
      x + box_padding_x + text_x_offset,
      y + box_padding_y + text_y_offset,
      ALLEGRO_ALIGN_LEFT,
      filter_item_title_through_connection_status(title, connection_status).c_str()
   );

   // draw the description text
   al_draw_multiline_text(
      description_font,
      description_text_color,
      x + box_padding_x + text_x_offset,
      y + box_padding_y + item_title_font_line_height + title_padding_y + text_y_offset,
      list_item_box_width - (box_padding_x + icon_container_box_size + icon_container_box_text_x_padding*2),
      description_font_line_height,
      ALLEGRO_ALIGN_LEFT,
      build_item_description(device_id, connection_status).c_str()
   );

   return;
}

int32_t InputDevicesList::infer_icon_character_for_physical_input_device(AllegroFlare::PhysicalInputDevices::Base* physical_input_device)
{
   if (!physical_input_device) return 0xf127; // a "broken link" icon (TODO: consider another icon)

   if (physical_input_device->is_keyboard()) return 0xf11c; // a "keyboard" icon
   if (physical_input_device->is_joystick()) return 0xf11b; // a "gamepad" controller icon

   return 0xf2fd; // a question with a box around it
}

ALLEGRO_COLOR InputDevicesList::infer_icon_color_by_connection_status(uint32_t connection_status, ALLEGRO_COLOR icon_locked_color, ALLEGRO_COLOR icon_hidden_color, ALLEGRO_COLOR icon_achieved_color)
{
   // TODO: finish these status changes
   if (connection_status == CONNECTION_STATUS_CONNECTED) return icon_achieved_color;
   if (connection_status == CONNECTION_STATUS_DISCONNECTED) return icon_locked_color;
   //else if (status == "locked") return icon_locked_color;
   //else if (status == "hidden") return icon_hidden_color;
   return ALLEGRO_COLOR{1, 0, 0, 1};
}

bool InputDevicesList::current_selected_item_is_connected()
{
   if (input_devices.empty()) return false;
   uint32_t connection_status = std::get<1>(input_devices[cursor_pos]);
   return (connection_status == CONNECTION_STATUS_CONNECTED);
}

std::string InputDevicesList::filter_item_title_through_connection_status(std::string title, uint32_t connection_status)
{
   if (connection_status != CONNECTION_STATUS_CONNECTED) return title + " (disconnected)";
   return title;
}

std::string InputDevicesList::build_item_description(std::string device_id, uint32_t connection_status)
{
   if (device_id.empty()) return "";
   return "Device ID: " + device_id;
}

ALLEGRO_FONT* InputDevicesList::obtain_title_font()
{
   return font_bin->auto_get("Inter-Bold.ttf -40");
}

ALLEGRO_FONT* InputDevicesList::obtain_item_title_font()
{
   return font_bin->auto_get("Inter-Bold.ttf -45");
}

ALLEGRO_FONT* InputDevicesList::obtain_item_description_font()
{
   return font_bin->auto_get("Inter-Regular.ttf -26");
}

ALLEGRO_FONT* InputDevicesList::obtain_icon_font()
{
   return font_bin->auto_get("Font_Awesome_6_Free-Solid-900.otf -50");
}

void InputDevicesList::draw_unicode_character(ALLEGRO_FONT* font, ALLEGRO_COLOR color, int x, int y, uint32_t icon, int flags)
{
   static ALLEGRO_USTR *ustr = NULL;
   if (!ustr) ustr = al_ustr_new("");
   al_ustr_set_chr(ustr, 0, icon);
   al_draw_ustr(font, color, x, y, flags, ustr);
   return;
}


} // namespace Elements
} // namespace AllegroFlare


