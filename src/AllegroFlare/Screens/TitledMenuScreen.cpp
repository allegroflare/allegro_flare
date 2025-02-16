

#include <AllegroFlare/Screens/TitledMenuScreen.hpp>

#include <AllegroFlare/ColorKit.hpp>
#include <AllegroFlare/EventNames.hpp>
#include <AllegroFlare/Logger.hpp>
#include <AllegroFlare/MotionKit.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <AllegroFlare/Screens/TitledMenuScreen.hpp>
#include <AllegroFlare/StringTransformer.hpp>
#include <AllegroFlare/VirtualControllers/GenericController.hpp>
#include <algorithm>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <iostream>
#include <set>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Screens
{


TitledMenuScreen::TitledMenuScreen(std::string data_folder_path, std::size_t surface_width, std::size_t surface_height, std::string title_text, std::string footer_text, std::string title_bitmap_name, std::string title_font_name, std::string menu_font_name, std::string footer_text_font_name, ALLEGRO_COLOR title_text_color, ALLEGRO_COLOR menu_text_color, ALLEGRO_COLOR menu_selected_text_color, ALLEGRO_COLOR menu_selector_fill_color, ALLEGRO_COLOR menu_selector_outline_color, float menu_selector_outline_stroke_thickness, float menu_selector_roundness, bool menu_selector_roundness_is_fit_to_max, bool show_triangle_cursor, float triangle_cursor_height, bool match_triangle_cursor_height_to_box_height, ALLEGRO_COLOR footer_text_color, int title_font_size, int menu_font_size, int footer_text_font_size, std::string empty_state_text, std::string empty_state_text_font_name, int empty_state_text_font_size, ALLEGRO_COLOR empty_state_text_color, float empty_state_text_x, float empty_state_text_y)
   : AllegroFlare::Screens::Base(AllegroFlare::Screens::TitledMenuScreen::TYPE)
   , data_folder_path(data_folder_path)
   , font_bin({})
   , bitmap_bin({})
   , surface_width(surface_width)
   , surface_height(surface_height)
   , title_text(title_text)
   , footer_text(footer_text)
   , title_bitmap_name(title_bitmap_name)
   , title_font_name(title_font_name)
   , menu_font_name(menu_font_name)
   , footer_text_font_name(footer_text_font_name)
   , title_text_color(title_text_color)
   , menu_text_color(menu_text_color)
   , menu_selected_text_color(menu_selected_text_color)
   , menu_selector_fill_color(menu_selector_fill_color)
   , menu_selector_outline_color(menu_selector_outline_color)
   , menu_selector_outline_stroke_thickness(menu_selector_outline_stroke_thickness)
   , menu_selector_roundness(menu_selector_roundness)
   , menu_selector_roundness_is_fit_to_max(menu_selector_roundness_is_fit_to_max)
   , show_triangle_cursor(show_triangle_cursor)
   , triangle_cursor_height(triangle_cursor_height)
   , match_triangle_cursor_height_to_box_height(match_triangle_cursor_height_to_box_height)
   , footer_text_color(footer_text_color)
   , title_font_size(title_font_size)
   , menu_font_size(menu_font_size)
   , footer_text_font_size(footer_text_font_size)
   , menu_options(build_default_menu_options())
   , empty_state_text(empty_state_text)
   , empty_state_text_font_name(empty_state_text_font_name)
   , empty_state_text_font_size(empty_state_text_font_size)
   , empty_state_text_color(empty_state_text_color)
   , empty_state_text_x(empty_state_text_x)
   , empty_state_text_y(empty_state_text_y)
   , upcase_empty_state_text(false)
   , on_menu_selection_change_callback_func()
   , on_menu_selection_change_callback_func_user_data(nullptr)
   , on_menu_choice_callback_func()
   , on_menu_choice_callback_func_user_data(nullptr)
   , on_finished_callback_func()
   , on_finished_callback_func_user_data(nullptr)
   , on_play_menu_move_sound_effect()
   , on_play_menu_move_sound_effect_user_data(nullptr)
   , on_play_menu_choose_sound_effect()
   , on_play_menu_choose_sound_effect_user_data(nullptr)
   , title_position_x(1920 / 2)
   , title_position_y((1080 / 48 * 18))
   , menu_position_x(1920 / 2)
   , menu_position_y(1080 / 24 * 14)
   , menu_item_vertical_spacing_distance(0.0f)
   , menu_item_vertical_spacing_font_line_height_multiplier(1.75f)
   , menu_item_vertical_spacing_integerize_positions(true)
   , cursor_position(0)
   , menu_move_sound_effect_identifier("menu_move")
   , menu_move_sound_effect_enabled(true)
   , menu_choose_option_sound_effect_identifier("menu_select")
   , menu_choose_option_sound_effect_enabled(true)
   , menu_option_chosen_to_activation_delay(1.0)
   , reveal_duration(1.0)
   , reveal_started_at(0.0)
   , title_revealed(false)
   , showing_menu(false)
   , showing_empty_state_text(false)
   , showing_footer_text(false)
   , state(STATE_UNDEF)
   , state_is_busy(false)
   , state_changed_at(0.0)
   , state_accumulated_age(0.0)
   , menu_option_chosen(false)
   , menu_option_chosen_at(0.0)
   , menu_option_activated(false)
   , showing_confirmation_dialog(false)
   , upcase_menu_items(false)
   , initialized(false)
   , destroyed(false)
{
}


TitledMenuScreen::~TitledMenuScreen()
{
   if (initialized && !destroyed)
   {
      AllegroFlare::Logger::warn_from(THIS_CLASS_AND_METHOD_NAME,
         "This instance is being destroyed but the destroy() method has not been called."
      );
   }
   return;
}


void TitledMenuScreen::set_data_folder_path(std::string data_folder_path)
{
   if (get_initialized()) throw std::runtime_error("[TitledMenuScreen::set_data_folder_path]: error: guard \"get_initialized()\" not met.");
   this->data_folder_path = data_folder_path;
}


void TitledMenuScreen::set_surface_width(std::size_t surface_width)
{
   this->surface_width = surface_width;
}


void TitledMenuScreen::set_surface_height(std::size_t surface_height)
{
   this->surface_height = surface_height;
}


void TitledMenuScreen::set_title_text(std::string title_text)
{
   this->title_text = title_text;
}


void TitledMenuScreen::set_footer_text(std::string footer_text)
{
   this->footer_text = footer_text;
}


void TitledMenuScreen::set_title_bitmap_name(std::string title_bitmap_name)
{
   this->title_bitmap_name = title_bitmap_name;
}


void TitledMenuScreen::set_title_font_name(std::string title_font_name)
{
   this->title_font_name = title_font_name;
}


void TitledMenuScreen::set_menu_font_name(std::string menu_font_name)
{
   this->menu_font_name = menu_font_name;
}


void TitledMenuScreen::set_footer_text_font_name(std::string footer_text_font_name)
{
   this->footer_text_font_name = footer_text_font_name;
}


void TitledMenuScreen::set_title_text_color(ALLEGRO_COLOR title_text_color)
{
   this->title_text_color = title_text_color;
}


void TitledMenuScreen::set_menu_text_color(ALLEGRO_COLOR menu_text_color)
{
   this->menu_text_color = menu_text_color;
}


void TitledMenuScreen::set_menu_selected_text_color(ALLEGRO_COLOR menu_selected_text_color)
{
   this->menu_selected_text_color = menu_selected_text_color;
}


void TitledMenuScreen::set_menu_selector_fill_color(ALLEGRO_COLOR menu_selector_fill_color)
{
   this->menu_selector_fill_color = menu_selector_fill_color;
}


void TitledMenuScreen::set_menu_selector_outline_color(ALLEGRO_COLOR menu_selector_outline_color)
{
   this->menu_selector_outline_color = menu_selector_outline_color;
}


void TitledMenuScreen::set_menu_selector_outline_stroke_thickness(float menu_selector_outline_stroke_thickness)
{
   this->menu_selector_outline_stroke_thickness = menu_selector_outline_stroke_thickness;
}


void TitledMenuScreen::set_menu_selector_roundness(float menu_selector_roundness)
{
   this->menu_selector_roundness = menu_selector_roundness;
}


void TitledMenuScreen::set_menu_selector_roundness_is_fit_to_max(bool menu_selector_roundness_is_fit_to_max)
{
   this->menu_selector_roundness_is_fit_to_max = menu_selector_roundness_is_fit_to_max;
}


void TitledMenuScreen::set_show_triangle_cursor(bool show_triangle_cursor)
{
   this->show_triangle_cursor = show_triangle_cursor;
}


void TitledMenuScreen::set_triangle_cursor_height(float triangle_cursor_height)
{
   this->triangle_cursor_height = triangle_cursor_height;
}


void TitledMenuScreen::set_match_triangle_cursor_height_to_box_height(bool match_triangle_cursor_height_to_box_height)
{
   this->match_triangle_cursor_height_to_box_height = match_triangle_cursor_height_to_box_height;
}


void TitledMenuScreen::set_footer_text_color(ALLEGRO_COLOR footer_text_color)
{
   this->footer_text_color = footer_text_color;
}


void TitledMenuScreen::set_title_font_size(int title_font_size)
{
   this->title_font_size = title_font_size;
}


void TitledMenuScreen::set_menu_font_size(int menu_font_size)
{
   this->menu_font_size = menu_font_size;
}


void TitledMenuScreen::set_footer_text_font_size(int footer_text_font_size)
{
   this->footer_text_font_size = footer_text_font_size;
}


void TitledMenuScreen::set_empty_state_text(std::string empty_state_text)
{
   this->empty_state_text = empty_state_text;
}


void TitledMenuScreen::set_empty_state_text_font_name(std::string empty_state_text_font_name)
{
   this->empty_state_text_font_name = empty_state_text_font_name;
}


void TitledMenuScreen::set_empty_state_text_font_size(int empty_state_text_font_size)
{
   this->empty_state_text_font_size = empty_state_text_font_size;
}


void TitledMenuScreen::set_empty_state_text_color(ALLEGRO_COLOR empty_state_text_color)
{
   this->empty_state_text_color = empty_state_text_color;
}


void TitledMenuScreen::set_empty_state_text_x(float empty_state_text_x)
{
   this->empty_state_text_x = empty_state_text_x;
}


void TitledMenuScreen::set_empty_state_text_y(float empty_state_text_y)
{
   this->empty_state_text_y = empty_state_text_y;
}


void TitledMenuScreen::set_upcase_empty_state_text(bool upcase_empty_state_text)
{
   this->upcase_empty_state_text = upcase_empty_state_text;
}


void TitledMenuScreen::set_on_menu_selection_change_callback_func(std::function<void(AllegroFlare::Screens::TitledMenuScreen*, std::string, void*)> on_menu_selection_change_callback_func)
{
   this->on_menu_selection_change_callback_func = on_menu_selection_change_callback_func;
}


void TitledMenuScreen::set_on_menu_selection_change_callback_func_user_data(void* on_menu_selection_change_callback_func_user_data)
{
   this->on_menu_selection_change_callback_func_user_data = on_menu_selection_change_callback_func_user_data;
}


void TitledMenuScreen::set_on_menu_choice_callback_func(std::function<void(AllegroFlare::Screens::TitledMenuScreen*, std::string, void*)> on_menu_choice_callback_func)
{
   this->on_menu_choice_callback_func = on_menu_choice_callback_func;
}


void TitledMenuScreen::set_on_menu_choice_callback_func_user_data(void* on_menu_choice_callback_func_user_data)
{
   this->on_menu_choice_callback_func_user_data = on_menu_choice_callback_func_user_data;
}


void TitledMenuScreen::set_on_finished_callback_func(std::function<void(AllegroFlare::Screens::TitledMenuScreen*, void*)> on_finished_callback_func)
{
   this->on_finished_callback_func = on_finished_callback_func;
}


void TitledMenuScreen::set_on_finished_callback_func_user_data(void* on_finished_callback_func_user_data)
{
   this->on_finished_callback_func_user_data = on_finished_callback_func_user_data;
}


void TitledMenuScreen::set_on_play_menu_move_sound_effect(std::function<void(AllegroFlare::Screens::TitledMenuScreen*, void*)> on_play_menu_move_sound_effect)
{
   this->on_play_menu_move_sound_effect = on_play_menu_move_sound_effect;
}


void TitledMenuScreen::set_on_play_menu_move_sound_effect_user_data(void* on_play_menu_move_sound_effect_user_data)
{
   this->on_play_menu_move_sound_effect_user_data = on_play_menu_move_sound_effect_user_data;
}


void TitledMenuScreen::set_on_play_menu_choose_sound_effect(std::function<void(AllegroFlare::Screens::TitledMenuScreen*, void*)> on_play_menu_choose_sound_effect)
{
   this->on_play_menu_choose_sound_effect = on_play_menu_choose_sound_effect;
}


void TitledMenuScreen::set_on_play_menu_choose_sound_effect_user_data(void* on_play_menu_choose_sound_effect_user_data)
{
   this->on_play_menu_choose_sound_effect_user_data = on_play_menu_choose_sound_effect_user_data;
}


void TitledMenuScreen::set_title_position_x(float title_position_x)
{
   this->title_position_x = title_position_x;
}


void TitledMenuScreen::set_title_position_y(float title_position_y)
{
   this->title_position_y = title_position_y;
}


void TitledMenuScreen::set_menu_position_x(float menu_position_x)
{
   this->menu_position_x = menu_position_x;
}


void TitledMenuScreen::set_menu_position_y(float menu_position_y)
{
   this->menu_position_y = menu_position_y;
}


void TitledMenuScreen::set_menu_item_vertical_spacing_distance(float menu_item_vertical_spacing_distance)
{
   this->menu_item_vertical_spacing_distance = menu_item_vertical_spacing_distance;
}


void TitledMenuScreen::set_menu_item_vertical_spacing_font_line_height_multiplier(float menu_item_vertical_spacing_font_line_height_multiplier)
{
   this->menu_item_vertical_spacing_font_line_height_multiplier = menu_item_vertical_spacing_font_line_height_multiplier;
}


void TitledMenuScreen::set_menu_item_vertical_spacing_integerize_positions(bool menu_item_vertical_spacing_integerize_positions)
{
   this->menu_item_vertical_spacing_integerize_positions = menu_item_vertical_spacing_integerize_positions;
}


void TitledMenuScreen::set_menu_move_sound_effect_identifier(std::string menu_move_sound_effect_identifier)
{
   this->menu_move_sound_effect_identifier = menu_move_sound_effect_identifier;
}


void TitledMenuScreen::set_menu_move_sound_effect_enabled(bool menu_move_sound_effect_enabled)
{
   this->menu_move_sound_effect_enabled = menu_move_sound_effect_enabled;
}


void TitledMenuScreen::set_menu_choose_option_sound_effect_identifier(std::string menu_choose_option_sound_effect_identifier)
{
   this->menu_choose_option_sound_effect_identifier = menu_choose_option_sound_effect_identifier;
}


void TitledMenuScreen::set_menu_choose_option_sound_effect_enabled(bool menu_choose_option_sound_effect_enabled)
{
   this->menu_choose_option_sound_effect_enabled = menu_choose_option_sound_effect_enabled;
}


void TitledMenuScreen::set_menu_option_chosen_to_activation_delay(double menu_option_chosen_to_activation_delay)
{
   this->menu_option_chosen_to_activation_delay = menu_option_chosen_to_activation_delay;
}


void TitledMenuScreen::set_upcase_menu_items(bool upcase_menu_items)
{
   this->upcase_menu_items = upcase_menu_items;
}


std::size_t TitledMenuScreen::get_surface_width() const
{
   return surface_width;
}


std::size_t TitledMenuScreen::get_surface_height() const
{
   return surface_height;
}


std::string TitledMenuScreen::get_title_text() const
{
   return title_text;
}


std::string TitledMenuScreen::get_footer_text() const
{
   return footer_text;
}


std::string TitledMenuScreen::get_title_bitmap_name() const
{
   return title_bitmap_name;
}


std::string TitledMenuScreen::get_title_font_name() const
{
   return title_font_name;
}


std::string TitledMenuScreen::get_menu_font_name() const
{
   return menu_font_name;
}


std::string TitledMenuScreen::get_footer_text_font_name() const
{
   return footer_text_font_name;
}


ALLEGRO_COLOR TitledMenuScreen::get_title_text_color() const
{
   return title_text_color;
}


ALLEGRO_COLOR TitledMenuScreen::get_menu_text_color() const
{
   return menu_text_color;
}


ALLEGRO_COLOR TitledMenuScreen::get_menu_selected_text_color() const
{
   return menu_selected_text_color;
}


ALLEGRO_COLOR TitledMenuScreen::get_menu_selector_fill_color() const
{
   return menu_selector_fill_color;
}


ALLEGRO_COLOR TitledMenuScreen::get_menu_selector_outline_color() const
{
   return menu_selector_outline_color;
}


float TitledMenuScreen::get_menu_selector_outline_stroke_thickness() const
{
   return menu_selector_outline_stroke_thickness;
}


float TitledMenuScreen::get_menu_selector_roundness() const
{
   return menu_selector_roundness;
}


bool TitledMenuScreen::get_menu_selector_roundness_is_fit_to_max() const
{
   return menu_selector_roundness_is_fit_to_max;
}


bool TitledMenuScreen::get_show_triangle_cursor() const
{
   return show_triangle_cursor;
}


float TitledMenuScreen::get_triangle_cursor_height() const
{
   return triangle_cursor_height;
}


bool TitledMenuScreen::get_match_triangle_cursor_height_to_box_height() const
{
   return match_triangle_cursor_height_to_box_height;
}


ALLEGRO_COLOR TitledMenuScreen::get_footer_text_color() const
{
   return footer_text_color;
}


int TitledMenuScreen::get_title_font_size() const
{
   return title_font_size;
}


int TitledMenuScreen::get_menu_font_size() const
{
   return menu_font_size;
}


int TitledMenuScreen::get_footer_text_font_size() const
{
   return footer_text_font_size;
}


std::vector<std::pair<std::string, std::string>> TitledMenuScreen::get_menu_options() const
{
   return menu_options;
}


std::string TitledMenuScreen::get_empty_state_text() const
{
   return empty_state_text;
}


std::string TitledMenuScreen::get_empty_state_text_font_name() const
{
   return empty_state_text_font_name;
}


int TitledMenuScreen::get_empty_state_text_font_size() const
{
   return empty_state_text_font_size;
}


ALLEGRO_COLOR TitledMenuScreen::get_empty_state_text_color() const
{
   return empty_state_text_color;
}


float TitledMenuScreen::get_empty_state_text_x() const
{
   return empty_state_text_x;
}


float TitledMenuScreen::get_empty_state_text_y() const
{
   return empty_state_text_y;
}


bool TitledMenuScreen::get_upcase_empty_state_text() const
{
   return upcase_empty_state_text;
}


std::function<void(AllegroFlare::Screens::TitledMenuScreen*, std::string, void*)> TitledMenuScreen::get_on_menu_selection_change_callback_func() const
{
   return on_menu_selection_change_callback_func;
}


void* TitledMenuScreen::get_on_menu_selection_change_callback_func_user_data() const
{
   return on_menu_selection_change_callback_func_user_data;
}


std::function<void(AllegroFlare::Screens::TitledMenuScreen*, std::string, void*)> TitledMenuScreen::get_on_menu_choice_callback_func() const
{
   return on_menu_choice_callback_func;
}


void* TitledMenuScreen::get_on_menu_choice_callback_func_user_data() const
{
   return on_menu_choice_callback_func_user_data;
}


std::function<void(AllegroFlare::Screens::TitledMenuScreen*, void*)> TitledMenuScreen::get_on_finished_callback_func() const
{
   return on_finished_callback_func;
}


void* TitledMenuScreen::get_on_finished_callback_func_user_data() const
{
   return on_finished_callback_func_user_data;
}


std::function<void(AllegroFlare::Screens::TitledMenuScreen*, void*)> TitledMenuScreen::get_on_play_menu_move_sound_effect() const
{
   return on_play_menu_move_sound_effect;
}


void* TitledMenuScreen::get_on_play_menu_move_sound_effect_user_data() const
{
   return on_play_menu_move_sound_effect_user_data;
}


std::function<void(AllegroFlare::Screens::TitledMenuScreen*, void*)> TitledMenuScreen::get_on_play_menu_choose_sound_effect() const
{
   return on_play_menu_choose_sound_effect;
}


void* TitledMenuScreen::get_on_play_menu_choose_sound_effect_user_data() const
{
   return on_play_menu_choose_sound_effect_user_data;
}


float TitledMenuScreen::get_title_position_x() const
{
   return title_position_x;
}


float TitledMenuScreen::get_title_position_y() const
{
   return title_position_y;
}


float TitledMenuScreen::get_menu_position_x() const
{
   return menu_position_x;
}


float TitledMenuScreen::get_menu_position_y() const
{
   return menu_position_y;
}


float TitledMenuScreen::get_menu_item_vertical_spacing_distance() const
{
   return menu_item_vertical_spacing_distance;
}


float TitledMenuScreen::get_menu_item_vertical_spacing_font_line_height_multiplier() const
{
   return menu_item_vertical_spacing_font_line_height_multiplier;
}


bool TitledMenuScreen::get_menu_item_vertical_spacing_integerize_positions() const
{
   return menu_item_vertical_spacing_integerize_positions;
}


int TitledMenuScreen::get_cursor_position() const
{
   return cursor_position;
}


std::string TitledMenuScreen::get_menu_move_sound_effect_identifier() const
{
   return menu_move_sound_effect_identifier;
}


bool TitledMenuScreen::get_menu_move_sound_effect_enabled() const
{
   return menu_move_sound_effect_enabled;
}


std::string TitledMenuScreen::get_menu_choose_option_sound_effect_identifier() const
{
   return menu_choose_option_sound_effect_identifier;
}


bool TitledMenuScreen::get_menu_choose_option_sound_effect_enabled() const
{
   return menu_choose_option_sound_effect_enabled;
}


double TitledMenuScreen::get_menu_option_chosen_to_activation_delay() const
{
   return menu_option_chosen_to_activation_delay;
}


double TitledMenuScreen::get_reveal_duration() const
{
   return reveal_duration;
}


bool TitledMenuScreen::get_upcase_menu_items() const
{
   return upcase_menu_items;
}


bool TitledMenuScreen::get_initialized() const
{
   return initialized;
}


void TitledMenuScreen::TODO()
{
   // There is some confusing naming between "selected", "chosen", etc.  Selected seems to signify
   // either "highlighted" or "chosen" depending on the casses.
   // Setup the "on_finished", indicating the title screen has "timed out" and may want to loop back around
     // to logos or something
   return;
}

void TitledMenuScreen::set_reveal_duration(double reveal_duration)
{
   if (!((reveal_duration >= 0.0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::TitledMenuScreen::set_reveal_duration]: error: guard \"(reveal_duration >= 0.0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::TitledMenuScreen::set_reveal_duration]: error: guard \"(reveal_duration >= 0.0)\" not met");
   }
   this->reveal_duration = reveal_duration;
   return;
}

void TitledMenuScreen::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::TitledMenuScreen::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::TitledMenuScreen::initialize]: error: guard \"(!initialized)\" not met");
   }
   if (!((!destroyed)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::TitledMenuScreen::initialize]: error: guard \"(!destroyed)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::TitledMenuScreen::initialize]: error: guard \"(!destroyed)\" not met");
   }
   if (!((data_folder_path != DEFAULT_DATA_FOLDER_PATH)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::TitledMenuScreen::initialize]: error: guard \"(data_folder_path != DEFAULT_DATA_FOLDER_PATH)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::TitledMenuScreen::initialize]: error: guard \"(data_folder_path != DEFAULT_DATA_FOLDER_PATH)\" not met");
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::TitledMenuScreen::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::TitledMenuScreen::initialize]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::TitledMenuScreen::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::TitledMenuScreen::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::TitledMenuScreen::initialize]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::TitledMenuScreen::initialize]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   set_update_strategy(AllegroFlare::Screens::Base::UpdateStrategy::SEPARATE_UPDATE_AND_RENDER_FUNCS);
   bitmap_bin.set_full_path(AllegroFlare::BitmapBin::build_standard_path(data_folder_path));
   font_bin.set_full_path(AllegroFlare::FontBin::build_standard_path(data_folder_path));
   initialized = true;
   return;
}

void TitledMenuScreen::destroy()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::TitledMenuScreen::destroy]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::TitledMenuScreen::destroy]: error: guard \"initialized\" not met");
   }
   if (!((!destroyed)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::TitledMenuScreen::destroy]: error: guard \"(!destroyed)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::TitledMenuScreen::destroy]: error: guard \"(!destroyed)\" not met");
   }
   bitmap_bin.clear();
   font_bin.clear();
   initialized = true;
   return;
}

void TitledMenuScreen::start()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::TitledMenuScreen::start]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::TitledMenuScreen::start]: error: guard \"initialized\" not met");
   }
   if (!((!destroyed)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::TitledMenuScreen::start]: error: guard \"(!destroyed)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::TitledMenuScreen::start]: error: guard \"(!destroyed)\" not met");
   }
   set_state(STATE_REVEALING);
   return;
}

void TitledMenuScreen::set_font_name(std::string font_name)
{
   title_font_name = font_name;
   menu_font_name = font_name;
   footer_text_font_name = font_name;
   return;
}

void TitledMenuScreen::set_state(uint32_t state, bool override_if_busy)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::TitledMenuScreen::set_state]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::TitledMenuScreen::set_state]: error: guard \"initialized\" not met");
   }
   if (!((!destroyed)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::TitledMenuScreen::set_state]: error: guard \"(!destroyed)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::TitledMenuScreen::set_state]: error: guard \"(!destroyed)\" not met");
   }
   if (!(is_valid_state(state)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::TitledMenuScreen::set_state]: error: guard \"is_valid_state(state)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::TitledMenuScreen::set_state]: error: guard \"is_valid_state(state)\" not met");
   }
   if (this->state == state) return;
   if (!override_if_busy && state_is_busy) return;
   uint32_t previous_state = this->state;

   this->state = state;
   state_changed_at = state_accumulated_age;

   switch (state)
   {
      case STATE_REVEALING:
         reveal_started_at = state_accumulated_age;
         cursor_position = 0;
         showing_menu = false;
         showing_footer_text = false;
         menu_option_chosen = false;
         menu_option_activated = false;
         menu_option_chosen_at = 0.0f;
      break;

      case STATE_REVEALED_AND_AWAITING_USER_INPUT:
         menu_option_chosen = false;
         menu_option_activated = false;
         title_revealed = true;
         showing_menu = true;
         showing_footer_text = true;
         if (menu_options.empty()) showing_empty_state_text = true;
      break;

      case STATE_MENU_OPTION_IS_CHOSEN:
         menu_option_chosen = true;
         menu_option_activated = false;
         menu_option_chosen_at = state_accumulated_age;
      break;

      case STATE_AWAITING_USER_CONFIRMATION:
         showing_confirmation_dialog = true;
      break;

      case STATE_FINISHED:
      break;

      default:
         throw std::runtime_error("weird error");
      break;
   }

   return;
}

void TitledMenuScreen::reveal()
{
   if (!(is_state(STATE_REVEALING) || is_state(STATE_UNDEF))) return;
   set_state(STATE_REVEALED_AND_AWAITING_USER_INPUT);
   return;
}

void TitledMenuScreen::update()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::TitledMenuScreen::update]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::TitledMenuScreen::update]: error: guard \"initialized\" not met");
   }
   if (!((!destroyed)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::TitledMenuScreen::update]: error: guard \"(!destroyed)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::TitledMenuScreen::update]: error: guard \"(!destroyed)\" not met");
   }
   if (!(is_valid_state(state)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::TitledMenuScreen::update]: error: guard \"is_valid_state(state)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::TitledMenuScreen::update]: error: guard \"is_valid_state(state)\" not met");
   }
   float state_age = infer_age(state_changed_at, state_accumulated_age);

   switch (state)
   {
      case STATE_REVEALING: {
         float reveal_age = infer_reveal_age();
         if (state_age > reveal_duration)
         {
            set_state(STATE_REVEALED_AND_AWAITING_USER_INPUT);
         }
      } break;

      case STATE_REVEALED_AND_AWAITING_USER_INPUT:
      break;

      case STATE_MENU_OPTION_IS_CHOSEN:
         if (!menu_option_activated && state_age > menu_option_chosen_to_activation_delay)
         {
            activate_current_selected_menu_option();
            menu_option_chosen = false;
            menu_option_activated = true;
            set_state(STATE_FINISHED);
         }
      break;

      case STATE_AWAITING_USER_CONFIRMATION:
         // TODO
      break;

      case STATE_FINISHED:
      break;

      default:
         throw std::runtime_error("weird error");
      break;
   }

   return;
}

bool TitledMenuScreen::is_valid_state(uint32_t state)
{
   std::set<uint32_t> valid_states =
   {
      STATE_REVEALING,
      STATE_REVEALED_AND_AWAITING_USER_INPUT,
      STATE_MENU_OPTION_IS_CHOSEN,
      STATE_AWAITING_USER_CONFIRMATION,
      STATE_FINISHED,
   };
   return (valid_states.count(state) > 0);
}

double TitledMenuScreen::infer_age(double time_of_event, double time_now)
{
   return std::max(0.0, time_now - time_of_event);
}

double TitledMenuScreen::infer_reveal_age()
{
   return std::max(0.0, infer_age(reveal_started_at, state_accumulated_age));
}

double TitledMenuScreen::infer_title_reveal_opacity()
{
   if (reveal_duration <= 0.0) return 1.0;
   if (title_revealed) return 1.0;
   return std::max(0.0, std::min(1.0, infer_reveal_age() / reveal_duration));
}

void TitledMenuScreen::on_activate()
{
   start();
   return;
}

void TitledMenuScreen::skip_to_title()
{
   set_state(STATE_REVEALED_AND_AWAITING_USER_INPUT);
   return;
}

void TitledMenuScreen::clear_menu_options()
{
   menu_options.clear();
   cursor_position = 0;
   signal_menu_selection_change(); // TODO: Consider if this is correct behavior, consider adding an option, possibly
                                   // an argument to this method
   return;
}

void TitledMenuScreen::set_menu_options(std::vector<std::pair<std::string, std::string>> menu_options)
{
   this->menu_options = menu_options;
   cursor_position = 0;
   signal_menu_selection_change(); // TODO: Consider if this is correct behavior, consider adding an option, possibly
                                   // an argument to this method
   return;
}

void TitledMenuScreen::move_cursor_up()
{
   if (!processing_user_input_on_main_menu()) return;

   if (menu_move_sound_effect_enabled) play_menu_move_sound_effect();

   int previous_position = cursor_position;
   cursor_position--;
   if (cursor_position < 0) cursor_position += menu_options.size();
   if (cursor_position != previous_position) signal_menu_selection_change();

   return;
}

void TitledMenuScreen::move_cursor_down()
{
   if (!processing_user_input_on_main_menu()) return;

   if (menu_move_sound_effect_enabled) play_menu_move_sound_effect();

   int previous_position = cursor_position;
   cursor_position++;
   if (cursor_position >= menu_options.size()) cursor_position = cursor_position % menu_options.size();
   if (cursor_position != previous_position) signal_menu_selection_change();

   return;
}

void TitledMenuScreen::signal_menu_selection_change()
{
   if (!on_menu_selection_change_callback_func) return;

   // TODO: Test this logic
   std::string current_menu_option_value = infer_current_menu_option_value();
   on_menu_selection_change_callback_func(
      this,
      current_menu_option_value,
      on_menu_selection_change_callback_func_user_data
   );
   return;
}

void TitledMenuScreen::activate_current_selected_menu_option()
{
   if (!on_menu_choice_callback_func) return;
   // TODO: Consider a case where there is an empty list
   // TODO: Test this callback
   std::string current_menu_option_value = infer_current_menu_option_value();
   on_menu_choice_callback_func(this, current_menu_option_value, on_menu_choice_callback_func_user_data);
   return;
}

void TitledMenuScreen::select_menu_option()
{
   if (!processing_user_input_on_main_menu()) return;

   if (menu_is_empty())
   {
      std::cout <<
         "[AllegroFlare::Screens::TitledMenuScreen::select_menu_option()] error: can not select a menu item, "
         "the menu is empty."
         << std::endl;
      return;
   }

   if (current_menu_option_must_be_confirmed()) set_state(STATE_AWAITING_USER_CONFIRMATION);
   else set_state(STATE_MENU_OPTION_IS_CHOSEN);

   if (menu_choose_option_sound_effect_enabled) play_menu_select_option_sound_effect();

   return;
}

bool TitledMenuScreen::current_menu_option_must_be_confirmed()
{
   std::set<std::string> choices_requiring_confirmation = { "exit_game*" };
   std::string current_menu_value = infer_current_menu_option_value();
   return choices_requiring_confirmation.find(current_menu_value) != choices_requiring_confirmation.end();
}

bool TitledMenuScreen::processing_user_input_on_main_menu()
{
   return is_state(STATE_REVEALED_AND_AWAITING_USER_INPUT); 
}

bool TitledMenuScreen::is_state(uint32_t possible_state)
{
   return (state == possible_state);
}

void TitledMenuScreen::primary_update_func(double time_now, double time_step)
{
   state_accumulated_age += time_step;
   update();
   return;
}

void TitledMenuScreen::primary_render_func()
{
   render();
   return;
}

void TitledMenuScreen::render()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::TitledMenuScreen::render]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::TitledMenuScreen::render]: error: guard \"initialized\" not met");
   }
   if (!((!destroyed)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::TitledMenuScreen::render]: error: guard \"(!destroyed)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::TitledMenuScreen::render]: error: guard \"(!destroyed)\" not met");
   }
   if (!(is_valid_state(state)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::TitledMenuScreen::render]: error: guard \"is_valid_state(state)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::TitledMenuScreen::render]: error: guard \"is_valid_state(state)\" not met");
   }
   draw_title();
   if (showing_footer_text) draw_footer_text();
   if (showing_menu) draw_menu();
   if (showing_empty_state_text) draw_empty_state_text();
   if (showing_confirmation_dialog) draw_confirmation_dialog();
   return;
}

void TitledMenuScreen::draw_title()
{
   if (!title_bitmap_name.empty())
   {
      ALLEGRO_BITMAP *title_bitmap = obtain_title_bitmap();
      float reveal_opacity = infer_title_reveal_opacity();
      ALLEGRO_COLOR tint = ALLEGRO_COLOR{reveal_opacity, reveal_opacity, reveal_opacity, reveal_opacity};
      if (title_bitmap)
      {
         AllegroFlare::Placement2D place;
         place.position.x = title_position_x;
         place.position.y = title_position_y;
         place.size.x = al_get_bitmap_width(title_bitmap);
         place.size.y = al_get_bitmap_height(title_bitmap);
         place.start_transform();
         al_draw_tinted_bitmap(title_bitmap, tint, 0, 0, 0);
         place.restore_transform();
      }
   }
   else if (!title_text.empty())
   {
      // TODO: review guards on this function
      ALLEGRO_FONT *title_font = obtain_title_font();
      float reveal_opacity = infer_title_reveal_opacity();
      ALLEGRO_COLOR revealed_color = ALLEGRO_COLOR{
         reveal_opacity * title_text_color.r,
         reveal_opacity * title_text_color.g,
         reveal_opacity * title_text_color.b,
         reveal_opacity * title_text_color.a
      };
      //int surface_width = 1920;
      //int surface_height = 1080;
      al_draw_multiline_text(
         title_font,
         revealed_color,
         title_position_x,
         title_position_y,
         1920,
         al_get_font_line_height(title_font),
         ALLEGRO_ALIGN_CENTER,
         get_title_text().c_str()
      );
   }
   return;
}

void TitledMenuScreen::draw_footer_text()
{
   // TODO: review guards on this function
   ALLEGRO_FONT *footer_text_font = obtain_footer_text_font();
   //int surface_width = 1920;
   //int surface_height = 1080;
   float line_height = al_get_font_line_height(footer_text_font);

   int number_of_lines = 1;
   for (int i = 0; i < footer_text.size(); i++) if (footer_text[i] == '\n') number_of_lines++;

   al_draw_multiline_text(
      footer_text_font,
      footer_text_color,
      surface_width/2,
      surface_height - 72 - (int)(number_of_lines * line_height / 2),
      surface_width * 2,
      line_height,
      ALLEGRO_ALIGN_CENTER,
      footer_text.c_str()
   );

   return;
}

void TitledMenuScreen::draw_cursor_box(float x, float y, float width, float height, ALLEGRO_COLOR fill_color, ALLEGRO_COLOR outline_color, float roundness, float outline_stroke_thickness, AllegroFlare::Screens::TitledMenuScreen::OutlineStrokeAlignment outline_stroke_alignment, bool menu_option_chosen, float menu_option_chosen_at, float menu_option_chosen_to_activation_delay, float time_now)
{
   ALLEGRO_COLOR result_fill_color = fill_color; //ALLEGRO_COLOR{0, 0, 0, 0};
   ALLEGRO_COLOR result_outline_color = outline_color; //ALLEGRO_COLOR{1, 1, 1, 1};

   float outline_stroke_alignment_adjustment = 0.0f;
   switch (outline_stroke_alignment)
   {
      case AllegroFlare::Screens::TitledMenuScreen::OutlineStrokeAlignment::OUTLINE_STROKE_ALIGNMENT_INSIDE: {
         outline_stroke_alignment_adjustment = 0.5f;
      } break;

      case AllegroFlare::Screens::TitledMenuScreen::OutlineStrokeAlignment::OUTLINE_STROKE_ALIGNMENT_CENTER: {
         outline_stroke_alignment_adjustment = 0.0f;
      } break;

      case AllegroFlare::Screens::TitledMenuScreen::OutlineStrokeAlignment::OUTLINE_STROKE_ALIGNMENT_OUTSIDE: {
         outline_stroke_alignment_adjustment = -0.5f;
      } break;
   }

   if (menu_option_chosen)
   {
      float selection_animation_length = menu_option_chosen_to_activation_delay;
      float selection_strobes_per_second = 14.0f;

      float menu_option_chosen_at_age = AllegroFlare::MotionKit::age(menu_option_chosen_at, time_now);
      bool strobe_on = AllegroFlare::MotionKit::strobe(
         menu_option_chosen_at,
         time_now,
         selection_strobes_per_second
      );

      float menu_option_chosen_at_normalized_age = AllegroFlare::MotionKit::normalize_age(
         menu_option_chosen_at,
         menu_option_chosen_at + selection_animation_length,
         time_now
      );
      ALLEGRO_COLOR cursor_color_a = AllegroFlare::ColorKit::fade(result_fill_color, 1.0);
      ALLEGRO_COLOR cursor_color_b = AllegroFlare::ColorKit::fade(result_fill_color, 0.5);
      ALLEGRO_COLOR cursor_animation_at_rest_color = AllegroFlare::ColorKit::fade(result_fill_color, 0.2);

      ALLEGRO_COLOR strobing_color = AllegroFlare::ColorKit::mix(
         cursor_color_a,
         cursor_color_b,
         strobe_on ? 1.0f : 0.0f
      );

      result_fill_color = AllegroFlare::ColorKit::mix(
         strobing_color,
         cursor_animation_at_rest_color,
         menu_option_chosen_at_normalized_age
      );
   }

   float h_box_width = width * 0.5;
   float h_box_height = height * 0.5;
   //float roundness = 6.0f;

   // draw the fill
   al_draw_filled_rounded_rectangle(
      x-h_box_width,
      y-h_box_height,
      x+h_box_width,
      y+h_box_height,
      roundness,
      roundness,
      result_fill_color
   );

   // draw the outline (which is invisible by default)
   al_draw_rounded_rectangle(
      x-h_box_width + outline_stroke_thickness * outline_stroke_alignment_adjustment,
      y-h_box_height + outline_stroke_thickness * outline_stroke_alignment_adjustment,
      x+h_box_width - outline_stroke_thickness * outline_stroke_alignment_adjustment,
      y+h_box_height - outline_stroke_thickness * outline_stroke_alignment_adjustment,
      roundness,
      roundness,
      result_outline_color,
      outline_stroke_thickness
   );
   return;
}

float TitledMenuScreen::calculate_menu_item_vertical_spacing()
{
   ALLEGRO_FONT *menu_font = obtain_menu_font();
   float result =
      (al_get_font_line_height(menu_font) * menu_item_vertical_spacing_font_line_height_multiplier)
      + menu_item_vertical_spacing_distance;
   if (menu_item_vertical_spacing_integerize_positions) result = (int)result;
   return result;
}

void TitledMenuScreen::draw_cursor_triangle(float x, float y, float length, float height, ALLEGRO_COLOR color)
{

   // Calculate offsets using 60 degrees
   //float dx = side_length / 2.0f;
   //float dy = (side_length * std::sqrt(3.0f)) / 2.0f;
   float hh = height * 0.5f;
   //float dy = (side_length * std::sqrt(3.0f)) / 2.0f;

   // Compute the two missing points
   float x_top = x - length;
   float y_top = y - hh;
   float x_bottom = x - length;
   float y_bottom = y + hh;

   // Output the three points
   //std::cout << "Rightmost point:   (" << x << ", " << y << ")\n";
   //std::cout << "Top-left point:    (" << x_top << ", " << y_top << ")\n";
   //std::cout << "Bottom-left point: (" << x_bottom << ", " << y_bottom << ")\n";

   al_draw_filled_triangle(x, y, x_top, y_top, x_bottom, y_bottom, color);
}

void TitledMenuScreen::draw_empty_state_text()
{
   //std::string empty_state_text = "Press any key to continue";
   //ALLEGRO_COLOR empty_state_text_color = ALLEGRO_COLOR{0.3, 0.3, 0.3, 0.3};
   //float empty_state_text_x = 1920 / 2;
   //float empty_state_text_y = 1080 / 12 * 7;
   //std::string empty_state_text_font_name = "RobotoCondensed-Regular.ttf";
   //std::string empty_state_text_font_size = -46;

   ALLEGRO_FONT *empty_state_text_font = obtain_empty_state_text_font(); // TODO: Fix this to obtain empty state font
   float h_font_line_height = (int)(al_get_font_line_height(empty_state_text_font) * 0.5f);
   std::string text = upcase_empty_state_text
                    ? AllegroFlare::StringTransformer(empty_state_text).upcase().get_text()
                    : empty_state_text;

   al_draw_text(
      empty_state_text_font,
      empty_state_text_color,
      (int)empty_state_text_x,
      (int)(empty_state_text_y-h_font_line_height),
      ALLEGRO_ALIGN_CENTER,
      text.c_str()
   );

   return;
}

void TitledMenuScreen::draw_menu()
{
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::TitledMenuScreen::draw_menu]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::TitledMenuScreen::draw_menu]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   // TODO: review guards on this function
   ALLEGRO_FONT *menu_font = obtain_menu_font();
   //int surface_width = 1920;
   //int surface_height = 1080;
   float h_font_line_height = (int)(al_get_font_line_height(menu_font) * 0.5f);
   float menu_item_vertical_spacing = calculate_menu_item_vertical_spacing();
   int menu_item_num = 0;

   // get longest menu option text length
   int longest_menu_option_text_width = 0;
   for (auto &menu_option : menu_options)
   {
      std::string menu_item_text = transform_menu_item_text(std::get<0>(menu_option));

      int this_menu_item_text_width = al_get_text_width(menu_font, menu_item_text.c_str());
      if (this_menu_item_text_width > longest_menu_option_text_width)
         longest_menu_option_text_width = this_menu_item_text_width;
   }

   float box_width = longest_menu_option_text_width + 126;
   float box_height = al_get_font_line_height(menu_font) + 16; // Previously 8
   float cursor_triangle_distance = 32.0f;
   float cursor_triangle_side_length =
      match_triangle_cursor_height_to_box_height ? box_height * 0.85f : triangle_cursor_height;

   // render each menu item
   for (auto &menu_option : menu_options)
   {
      bool showing_cursor_on_this_option = false;
      if (menu_item_num == cursor_position) showing_cursor_on_this_option = true;
      std::string menu_item_text = transform_menu_item_text(std::get<0>(menu_option));

      ALLEGRO_COLOR this_menu_text_color = showing_cursor_on_this_option
         ? (menu_option_chosen ? menu_text_color : menu_selected_text_color) : menu_text_color;

      float x = menu_position_x;
      float y = menu_position_y + menu_item_vertical_spacing * menu_item_num;

      if (showing_cursor_on_this_option)
      {
         //float box_width = longest_menu_option_text_width + 126;
         //float box_height = al_get_font_line_height(menu_font) + 16; // Previously 8
         float roundness = menu_selector_roundness_is_fit_to_max ? box_height * 0.5 : menu_selector_roundness;

         draw_cursor_box(
            x,
            y,
            box_width,
            box_height,
            menu_selector_fill_color,
            menu_selector_outline_color,
            roundness,
            menu_selector_outline_stroke_thickness,
            AllegroFlare::Screens::TitledMenuScreen::OutlineStrokeAlignment::OUTLINE_STROKE_ALIGNMENT_INSIDE,
            menu_option_chosen,
            menu_option_chosen_at,
            menu_option_chosen_to_activation_delay,
            state_accumulated_age
         );

         if (show_triangle_cursor)
         {
            draw_cursor_triangle(
               x - box_width * 0.5 - cursor_triangle_distance,
               y, 
               cursor_triangle_side_length * 0.8669254, // (sqrt(3) / 2)
               cursor_triangle_side_length,
               menu_selector_fill_color
            );
         }
      }

      al_draw_text(
         menu_font,
         this_menu_text_color,
         (int)x,
         (int)(y-h_font_line_height),
         ALLEGRO_ALIGN_CENTER,
         menu_item_text.c_str()
      );

      menu_item_num++;
   }
   return;
}

std::string TitledMenuScreen::transform_menu_item_text(std::string menu_item_text)
{
   if (upcase_menu_items) menu_item_text = AllegroFlare::StringTransformer(menu_item_text).upcase().get_text();
   return menu_item_text;
}

void TitledMenuScreen::draw_confirmation_dialog()
{
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::TitledMenuScreen::draw_confirmation_dialog]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::TitledMenuScreen::draw_confirmation_dialog]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   // TODO: review guards on this function
   ALLEGRO_FONT *menu_font = obtain_menu_font();
   //int surface_width = 1920;
   //int surface_height = 1080;
   float h_font_line_height = (int)(al_get_font_line_height(menu_font) * 0.5f);
   float menu_item_vertical_spacing = calculate_menu_item_vertical_spacing();
   int menu_item_num = 0;

   // get longest menu option text length
   int longest_menu_option_text_width = 0;
   auto confirmation_dialog_menu_options = build_confirmation_dialog_menu_options();
   for (auto &menu_option : confirmation_dialog_menu_options)
   {
      std::string menu_item_text = transform_menu_item_text(std::get<0>(menu_option));

      int this_menu_item_text_width = al_get_text_width(menu_font, menu_item_text.c_str());
      if (this_menu_item_text_width > longest_menu_option_text_width)
         longest_menu_option_text_width = this_menu_item_text_width;
   }

   // render each menu item

   for (auto &menu_option : confirmation_dialog_menu_options)
   {
      bool showing_cursor_on_this_option = false;
      if (menu_item_num == cursor_position) showing_cursor_on_this_option = true;
      std::string menu_item_text = transform_menu_item_text(std::get<0>(menu_option));

      ALLEGRO_COLOR this_menu_text_color = showing_cursor_on_this_option
         ? (menu_option_chosen ? menu_text_color : menu_selected_text_color) : menu_text_color;

      float x = menu_position_x + 200;
      float y = menu_position_y + menu_item_vertical_spacing * menu_item_num;

      if (showing_cursor_on_this_option)
      {
         float box_width = longest_menu_option_text_width + 148;
         float box_height = al_get_font_line_height(menu_font) + 6;
         float roundness = menu_selector_roundness_is_fit_to_max ? box_height * 0.5 : menu_selector_roundness;

         draw_cursor_box(
            x,
            y,
            box_width,
            box_height,
            menu_selector_fill_color,
            menu_selector_outline_color,
            roundness,
            menu_selector_outline_stroke_thickness,
            AllegroFlare::Screens::TitledMenuScreen::OutlineStrokeAlignment::OUTLINE_STROKE_ALIGNMENT_INSIDE,
            menu_option_chosen,
            menu_option_chosen_at,
            menu_option_chosen_to_activation_delay,
            state_accumulated_age
         );
      }

      al_draw_text(
         menu_font,
         this_menu_text_color,
         (int)x,
         (int)(y-h_font_line_height),
         ALLEGRO_ALIGN_CENTER,
         menu_item_text.c_str()
      );

      menu_item_num++;
   }
   return;
}

std::string TitledMenuScreen::infer_current_menu_option_value()
{
   if (menu_options.empty()) return "";
   if (cursor_position < 0 || cursor_position >= menu_options.size())
   {
      throw std::runtime_error("[AllegroFlare/Screens/TitledMenuScreen]: error: cursor_position is not in "
                               "a valid position to get the current menu choice's value.");
   }
   std::string current_menu_option_value = std::get<1>(menu_options[cursor_position]);
   return current_menu_option_value;
}

std::string TitledMenuScreen::infer_current_menu_option_label()
{
   if (menu_options.empty()) return "";
   if (cursor_position < 0 || cursor_position >= menu_options.size())
   {
      throw std::runtime_error("[AllegroFlare/Screens/TitledMenuScreen]: error: cursor_position is not in "
                               "a valid position to get the current menu choice's label.");
   }
   std::string current_menu_option_value = std::get<1>(menu_options[cursor_position]);
   return current_menu_option_value;
}

void TitledMenuScreen::play_menu_move_sound_effect()
{
   if (on_play_menu_move_sound_effect)
   {
      on_play_menu_move_sound_effect(this, on_play_menu_move_sound_effect_user_data);
   }
   return;
}

void TitledMenuScreen::play_menu_select_option_sound_effect()
{
   if (on_play_menu_choose_sound_effect)
   {
      on_play_menu_choose_sound_effect(this, on_play_menu_choose_sound_effect_user_data);
   }
   return;
}

ALLEGRO_FONT* TitledMenuScreen::obtain_title_font()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::TitledMenuScreen::obtain_title_font]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::TitledMenuScreen::obtain_title_font]: error: guard \"initialized\" not met");
   }
   if (!((!destroyed)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::TitledMenuScreen::obtain_title_font]: error: guard \"(!destroyed)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::TitledMenuScreen::obtain_title_font]: error: guard \"(!destroyed)\" not met");
   }
   std::stringstream composite_font_str;
   composite_font_str << title_font_name << " " << title_font_size;
   return font_bin.auto_get(composite_font_str.str());
}

ALLEGRO_FONT* TitledMenuScreen::obtain_menu_font()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::TitledMenuScreen::obtain_menu_font]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::TitledMenuScreen::obtain_menu_font]: error: guard \"initialized\" not met");
   }
   if (!((!destroyed)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::TitledMenuScreen::obtain_menu_font]: error: guard \"(!destroyed)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::TitledMenuScreen::obtain_menu_font]: error: guard \"(!destroyed)\" not met");
   }
   std::stringstream composite_font_str;
   composite_font_str << menu_font_name << " " << menu_font_size;
   return font_bin.auto_get(composite_font_str.str());
}

ALLEGRO_FONT* TitledMenuScreen::obtain_empty_state_text_font()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::TitledMenuScreen::obtain_empty_state_text_font]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::TitledMenuScreen::obtain_empty_state_text_font]: error: guard \"initialized\" not met");
   }
   if (!((!destroyed)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::TitledMenuScreen::obtain_empty_state_text_font]: error: guard \"(!destroyed)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::TitledMenuScreen::obtain_empty_state_text_font]: error: guard \"(!destroyed)\" not met");
   }
   std::stringstream composite_font_str;
   composite_font_str << empty_state_text_font_name << " " << empty_state_text_font_size;
   return font_bin.auto_get(composite_font_str.str());
}

ALLEGRO_FONT* TitledMenuScreen::obtain_footer_text_font()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::TitledMenuScreen::obtain_footer_text_font]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::TitledMenuScreen::obtain_footer_text_font]: error: guard \"initialized\" not met");
   }
   if (!((!destroyed)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::TitledMenuScreen::obtain_footer_text_font]: error: guard \"(!destroyed)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::TitledMenuScreen::obtain_footer_text_font]: error: guard \"(!destroyed)\" not met");
   }
   std::stringstream composite_font_str;
   composite_font_str << footer_text_font_name << " " << footer_text_font_size;
   return font_bin.auto_get(composite_font_str.str());
}

ALLEGRO_BITMAP* TitledMenuScreen::obtain_title_bitmap()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::TitledMenuScreen::obtain_title_bitmap]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::TitledMenuScreen::obtain_title_bitmap]: error: guard \"initialized\" not met");
   }
   if (!((!destroyed)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::TitledMenuScreen::obtain_title_bitmap]: error: guard \"(!destroyed)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::TitledMenuScreen::obtain_title_bitmap]: error: guard \"(!destroyed)\" not met");
   }
   return bitmap_bin.auto_get(title_bitmap_name);
}

void TitledMenuScreen::joy_button_down_func(ALLEGRO_EVENT* ev)
{
   // NOTE: These joystick controls are intended to be temporary, and eventually replaced with virtual controls
   // TODO: Replace these with virtual controls
   select_menu_option();
   return;
}

void TitledMenuScreen::joy_axis_func(ALLEGRO_EVENT* ev)
{
   // NOTE: These joystick controls are intended to be temporary, and eventually replaced with virtual controls
   // TODO: Replace these with virtual controls

   static float axis_x = 0;
   static float axis_y = 0;

   int stick = ev->joystick.stick;
   int axis = ev->joystick.axis;
   float pos = ev->joystick.pos;

   float min_stick_break_threshold = 0.4;

   switch (stick)
   {
      case 0: { // The primary joystick, on the left
        if (axis == 0) // horizontal axis
        {
           //if (axis_x < min_stick_break_threshold && pos >= min_stick_break_threshold) 
               //level_select_element.move_cursor_right();
           //if (axis_x > -min_stick_break_threshold && pos <= -min_stick_break_threshold) 
               //level_select_element.move_cursor_left();
           axis_x = pos;
        }
        else if (axis == 1) // vertical axis
        {
           if (axis_y < min_stick_break_threshold && pos >= min_stick_break_threshold) move_cursor_down();
               //level_select_element.move_cursor_down();
           if (axis_y > -min_stick_break_threshold && pos <= -min_stick_break_threshold) move_cursor_up();
               //level_select_element.move_cursor_up();
           axis_y = pos;
        }
      } break;

      case 1: { // The secondary joystick, on the right
      } break;

      case 2: { // The hat, on the left
      } break;
   }

   return;
}

void TitledMenuScreen::virtual_control_button_down_func(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_button_num, bool is_repeat)
{
   if (!processing_user_input_on_main_menu()) return;

   if (virtual_controller_button_num == VirtualControllers::GenericController::BUTTON_UP) move_cursor_up();
   if (virtual_controller_button_num == VirtualControllers::GenericController::BUTTON_DOWN) move_cursor_down();
   if (virtual_controller_button_num == VirtualControllers::GenericController::BUTTON_A
      || virtual_controller_button_num == VirtualControllers::GenericController::BUTTON_MENU
      )
   {
      select_menu_option();
   }
}

bool TitledMenuScreen::menu_is_empty()
{
   return menu_options.empty();
}

bool TitledMenuScreen::menu_has_items()
{
   return !menu_is_empty();
}

std::vector<std::pair<std::string, std::string>> TitledMenuScreen::build_default_menu_options()
{
   std::vector<std::pair<std::string, std::string>> result;
   result = {
      { "Start new game", "start_new_game" },
      { "Credits", "show_credits" },
      { "Exit", "exit_game*" }
   };
   return result;
}

std::vector<std::pair<std::string, std::string>> TitledMenuScreen::build_confirmation_dialog_menu_options()
{
   std::vector<std::pair<std::string, std::string>> result;
   result = {
      { "yes", "exit_game" },
      { "no", "close_confirmation_dialog" },
   };
   return result;
}

AllegroFlare::Screens::TitledMenuScreen* TitledMenuScreen::create_standard_pause_screen(std::string data_folder_path, std::string footer_text_probably_game_name_and_version)
{
   if (!((data_folder_path != DEFAULT_DATA_FOLDER_PATH)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::TitledMenuScreen::create_standard_pause_screen]: error: guard \"(data_folder_path != DEFAULT_DATA_FOLDER_PATH)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::TitledMenuScreen::create_standard_pause_screen]: error: guard \"(data_folder_path != DEFAULT_DATA_FOLDER_PATH)\" not met");
   }
   AllegroFlare::Screens::TitledMenuScreen* result = new AllegroFlare::Screens::TitledMenuScreen(data_folder_path);

   // Title
   result->set_title_text("PAUSED");

   // Footer
   result->set_footer_text(footer_text_probably_game_name_and_version);

   // Menus
   result->set_menu_options({
      { "Resume", "resume" },
      { "Exit to Title Screen", "exit_to_title_screen" },
   });
   result->set_show_triangle_cursor(true);

   // Menu Font
   result->set_menu_font_name("RobotoCondensed-Regular.ttf");

   result->initialize();

   return result;
}

AllegroFlare::Screens::TitledMenuScreen* TitledMenuScreen::create_standard_title_screen(std::string data_folder_path, std::string game_title, std::string footer_text_probably_copyright_game_name_and_version)
{
   if (!((data_folder_path != DEFAULT_DATA_FOLDER_PATH)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::TitledMenuScreen::create_standard_title_screen]: error: guard \"(data_folder_path != DEFAULT_DATA_FOLDER_PATH)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::TitledMenuScreen::create_standard_title_screen]: error: guard \"(data_folder_path != DEFAULT_DATA_FOLDER_PATH)\" not met");
   }
   AllegroFlare::Screens::TitledMenuScreen* result = new AllegroFlare::Screens::TitledMenuScreen(data_folder_path);

   // Title
   result->set_title_text(game_title);

   // Footer
   result->set_footer_text(footer_text_probably_copyright_game_name_and_version);

   // Menus
   result->set_menu_options({
      { "Start new game", "start_new_game" },
      { "Credits", "show_credits" },
      { "Exit", "exit_game*" }
   });

   // Menu Font
   result->set_menu_font_name("RobotoCondensed-Regular.ttf");

   result->initialize();

   return result;
}

AllegroFlare::Screens::TitledMenuScreen* TitledMenuScreen::create_standard_game_won_screen(std::string data_folder_path, std::string title_text)
{
   if (!((data_folder_path != DEFAULT_DATA_FOLDER_PATH)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::TitledMenuScreen::create_standard_game_won_screen]: error: guard \"(data_folder_path != DEFAULT_DATA_FOLDER_PATH)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::TitledMenuScreen::create_standard_game_won_screen]: error: guard \"(data_folder_path != DEFAULT_DATA_FOLDER_PATH)\" not met");
   }
   // Some options could be "YOU WIN", "GAME OVER", "THANK YOU FOR PLAYING"
   AllegroFlare::Screens::TitledMenuScreen* result = new AllegroFlare::Screens::TitledMenuScreen(data_folder_path);

   // Title
   result->set_title_text("YOU WIN");
   result->set_title_position_y(1080 / 14 * 6);

   // Footer
   result->set_footer_text(""); // Consider adding "clear_footer_text"

   // Menus
   result->clear_menu_options();

   // Empty state text
   //title_screen.set_upcase_empty_state_text(true);
   result->set_empty_state_text(""); // Consider adding "
   result->set_empty_state_text_font_name("RobotoCondensed-Regular.ttf");

   result->initialize();

   return result;
}

AllegroFlare::Screens::TitledMenuScreen* TitledMenuScreen::create_standard_game_over_screen(std::string data_folder_path)
{
   if (!((data_folder_path != DEFAULT_DATA_FOLDER_PATH)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::TitledMenuScreen::create_standard_game_over_screen]: error: guard \"(data_folder_path != DEFAULT_DATA_FOLDER_PATH)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::TitledMenuScreen::create_standard_game_over_screen]: error: guard \"(data_folder_path != DEFAULT_DATA_FOLDER_PATH)\" not met");
   }
   AllegroFlare::Screens::TitledMenuScreen* result = new AllegroFlare::Screens::TitledMenuScreen(data_folder_path);

   // Title
   result->set_title_text("GAME OVER");

   // Footer
   result->set_footer_text(""); // Consider adding "clear_footer_text"

   // Menus
   result->clear_menu_options();

   // Empty state text
   result->set_upcase_empty_state_text(true);
   result->set_empty_state_text("Press any key to continue");
   result->set_empty_state_text_font_name("RobotoCondensed-Regular.ttf");

   result->initialize();

   return result;
}


} // namespace Screens
} // namespace AllegroFlare


