

#include <AllegroFlare/Screens/GameOverScreen.hpp>

#include <AllegroFlare/VirtualControllers/GenericController.hpp>
#include <iostream>
#include <set>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Screens
{


std::string GameOverScreen::DEFAULT_TITLE_TEXT = "GAME OVER";


std::vector<std::pair<std::string, std::string>> GameOverScreen::DEFAULT_MENU_OPTIONS = { { "Try again", "try_again" }, { "Go to Title Screen", "start_title_screen" } };


std::string GameOverScreen::DEFAULT_FALLBACK_INSTRUCTION_TEXT_WHEN_NO_MENU_OPTIONS = "press any key to continue";


std::string GameOverScreen::TYPE = "AllegroFlare/Screens/GameOverScreen";


GameOverScreen::GameOverScreen(AllegroFlare::EventEmitter* event_emitter, AllegroFlare::FontBin* font_bin, std::string title_text, std::string title_font_name, int title_font_size, std::string menu_font_name, int menu_font_size)
   : AllegroFlare::Screens::Base(AllegroFlare::Screens::GameOverScreen::TYPE)
   , event_emitter(event_emitter)
   , font_bin(font_bin)
   , title_text(title_text)
   , menu_options(DEFAULT_MENU_OPTIONS)
   , fallback_instruction_text_when_no_menu_options(DEFAULT_FALLBACK_INSTRUCTION_TEXT_WHEN_NO_MENU_OPTIONS)
   , on_menu_choice_callback_func()
   , on_menu_choice_callback_func_user_data(nullptr)
   , cursor_position(0)
   , title_font_name(title_font_name)
   , title_font_size(title_font_size)
   , menu_font_name(menu_font_name)
   , menu_font_size(menu_font_size)
   , reveal_counter(0)
   , state(STATE_UNDEF)
   , state_is_busy(false)
   , state_changed_at(0.0f)
   , initialized(false)
{
}


GameOverScreen::~GameOverScreen()
{
}


void GameOverScreen::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   this->event_emitter = event_emitter;
}


void GameOverScreen::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void GameOverScreen::set_title_text(std::string title_text)
{
   this->title_text = title_text;
}


void GameOverScreen::set_on_menu_choice_callback_func(std::function<void(AllegroFlare::Screens::GameOverScreen*, void*)> on_menu_choice_callback_func)
{
   this->on_menu_choice_callback_func = on_menu_choice_callback_func;
}


void GameOverScreen::set_on_menu_choice_callback_func_user_data(void* on_menu_choice_callback_func_user_data)
{
   this->on_menu_choice_callback_func_user_data = on_menu_choice_callback_func_user_data;
}


void GameOverScreen::set_title_font_name(std::string title_font_name)
{
   this->title_font_name = title_font_name;
}


void GameOverScreen::set_title_font_size(int title_font_size)
{
   this->title_font_size = title_font_size;
}


void GameOverScreen::set_menu_font_name(std::string menu_font_name)
{
   this->menu_font_name = menu_font_name;
}


void GameOverScreen::set_menu_font_size(int menu_font_size)
{
   this->menu_font_size = menu_font_size;
}


std::function<void(AllegroFlare::Screens::GameOverScreen*, void*)> GameOverScreen::get_on_menu_choice_callback_func() const
{
   return on_menu_choice_callback_func;
}


void* GameOverScreen::get_on_menu_choice_callback_func_user_data() const
{
   return on_menu_choice_callback_func_user_data;
}


std::string GameOverScreen::get_title_font_name() const
{
   return title_font_name;
}


int GameOverScreen::get_title_font_size() const
{
   return title_font_size;
}


std::string GameOverScreen::get_menu_font_name() const
{
   return menu_font_name;
}


int GameOverScreen::get_menu_font_size() const
{
   return menu_font_size;
}


bool GameOverScreen::get_initialized() const
{
   return initialized;
}


void GameOverScreen::set_menu_options(std::vector<std::pair<std::string, std::string>> menu_options)
{
   // TODO: add tests for this feature
   // TODO: Validate menu options (unique labels, non-empty datas)
   this->menu_options = menu_options;
   cursor_position = 0;
   return;
}

void GameOverScreen::clear_menu_options()
{
   set_menu_options({});
   return;
}

void GameOverScreen::initialize()
{
   //menu_options = { { "Try again", "try_again" }, { "Go to Title Screen", "start_title_screen" } };
   cursor_position = 0;
   initialized = true;
   return;
}

void GameOverScreen::on_activate()
{
   cursor_position = 0;
   set_state(STATE_REVEALING);
   return;
}

void GameOverScreen::on_deactivate()
{
   set_state(STATE_DISABLED);
   return;
}

void GameOverScreen::move_cursor_up()
{
   if (menu_options.empty()) return;
   cursor_position--;
   if (cursor_position < 0) cursor_position += menu_options.size();
   return;
}

void GameOverScreen::move_cursor_down()
{
   if (menu_options.empty()) return;
   cursor_position++;
   if (cursor_position >= menu_options.size()) cursor_position = cursor_position % menu_options.size();
   return;
}

void GameOverScreen::activate_current_chosen_menu_option()
{
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::GameOverScreen::activate_current_chosen_menu_option]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::GameOverScreen::activate_current_chosen_menu_option]: error: guard \"event_emitter\" not met");
   }
   // TODO: Test this callback
   // TODO: Consider if callback should override emission of game event
   if (on_menu_choice_callback_func) on_menu_choice_callback_func(this, on_menu_choice_callback_func_user_data);
   return;
}

void GameOverScreen::choose_menu_option()
{
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::GameOverScreen::choose_menu_option]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::GameOverScreen::choose_menu_option]: error: guard \"event_emitter\" not met");
   }
   // TODO: Add a delay mechanism or spawn an animation prior to activating the menu option
   //activate_current_chosen_menu_option();
   set_state(STATE_CLOSING_DOWN);
   return;
}

void GameOverScreen::primary_timer_func()
{
   update();
   render();
   return;
}

void GameOverScreen::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::GameOverScreen::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::GameOverScreen::render]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::GameOverScreen::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::GameOverScreen::render]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(get_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::GameOverScreen::render]: error: guard \"get_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::GameOverScreen::render]: error: guard \"get_initialized()\" not met");
   }
   draw_primary_text();
   draw_menu();
   return;
}

void GameOverScreen::draw_primary_text()
{
   // TODO: review guards on this function
   ALLEGRO_FONT *title_font = obtain_title_font();
   float font_line_height = al_get_font_line_height(title_font);
   int surface_width = 1920;
   int surface_height = 1080;

   ALLEGRO_COLOR text_color = ALLEGRO_COLOR{0.8, 0.72, 0.61, 1.0};
   text_color.r *= reveal_counter;
   text_color.g *= reveal_counter;
   text_color.b *= reveal_counter;
   text_color.a *= reveal_counter;

   al_draw_text(
      title_font,
      text_color,
      surface_width / 2,
      surface_height / 2 - font_line_height,
      ALLEGRO_ALIGN_CENTER,
      title_text.c_str()
   );
   return;
}

void GameOverScreen::draw_menu()
{
   if (!is_state(STATE_AWAITING_USER_INPUT)) return;

   // TODO: review guards on this function
   ALLEGRO_FONT *menu_font = obtain_menu_font();
   float font_line_height = al_get_font_line_height(menu_font);
   int surface_width = 1920;
   int surface_height = 1080;

   float menu_item_vertical_spacing = (int)(al_get_font_line_height(menu_font) * 1.25f);
   int menu_item_num = 0;

   if (menu_options.empty())
   {
      al_draw_text(
         menu_font,
         ALLEGRO_COLOR{1, 1, 1, 1},
         surface_width / 2,
         surface_height / 2 + menu_item_vertical_spacing * menu_item_num + font_line_height * 2,
         ALLEGRO_ALIGN_CENTER,
         fallback_instruction_text_when_no_menu_options.c_str()
      );
   }
   else
   {
      for (auto &menu_option : menu_options)
      {
         bool showing_cursor_on_this_option = false;
         if (menu_item_num == cursor_position) showing_cursor_on_this_option = true;

         std::string menu_item_text = std::get<0>(menu_option);
         al_draw_text(
            menu_font,
            ALLEGRO_COLOR{1, 1, 1, 1},
            surface_width / 2,
            surface_height / 2 + menu_item_vertical_spacing * menu_item_num + font_line_height * 2,
            ALLEGRO_ALIGN_CENTER,
            menu_item_text.c_str()
         );

         if (showing_cursor_on_this_option)
         {
            float menu_item_text_width = al_get_text_width(menu_font, menu_item_text.c_str());
            al_draw_text(
               menu_font,
               ALLEGRO_COLOR{1, 1, 1, 1},
               surface_width / 2 - (menu_item_text_width * 0.5),
               surface_height / 2 + menu_item_vertical_spacing * menu_item_num + font_line_height * 2,
               ALLEGRO_ALIGN_RIGHT,
               ">  "
            );
         }

         menu_item_num++;
      }
   }
   return;
}

std::string GameOverScreen::infer_current_menu_option_value()
{
   if (menu_options.empty()) return "";
   if (cursor_position < 0 || cursor_position >= menu_options.size())
   {
      throw std::runtime_error("[AllegroFlare/Screens/TitleScreen]: error: cursor_position is not in "
                               "a valid position to get the current menu choice's value.");
   }
   std::string current_menu_option_value = std::get<1>(menu_options[cursor_position]);
   return current_menu_option_value;
}

std::string GameOverScreen::infer_current_menu_option_label()
{
   if (menu_options.empty()) return "";
   if (cursor_position < 0 || cursor_position >= menu_options.size())
   {
      throw std::runtime_error("[AllegroFlare/Screens/TitleScreen]: error: cursor_position is not in "
                               "a valid position to get the current menu choice's label.");
   }
   std::string current_menu_option_value = std::get<1>(menu_options[cursor_position]);
   return current_menu_option_value;
}

void GameOverScreen::virtual_control_button_down_func(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_button_num, bool is_repeat)
{
   if (!is_state(STATE_AWAITING_USER_INPUT)) return;

   if (virtual_controller_button_num == VirtualControllers::GenericController::BUTTON_UP) move_cursor_up();
   if (virtual_controller_button_num == VirtualControllers::GenericController::BUTTON_DOWN) move_cursor_down();
   if (virtual_controller_button_num == VirtualControllers::GenericController::BUTTON_A
      || virtual_controller_button_num == VirtualControllers::GenericController::BUTTON_MENU
      )
   {
      choose_menu_option();
   }
}

void GameOverScreen::set_state(uint32_t state, bool override_if_busy)
{
   if (!(is_valid_state(state)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::GameOverScreen::set_state]: error: guard \"is_valid_state(state)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::GameOverScreen::set_state]: error: guard \"is_valid_state(state)\" not met");
   }
   if (this->state == state) return;
   if (!override_if_busy && state_is_busy) return;
   uint32_t previous_state = this->state;

   switch (state)
   {
      case STATE_REVEALING: {
         reveal_counter = 0.0f;
      } break;

      case STATE_AWAITING_USER_INPUT: {
         reveal_counter = 1.0f;
      } break;

      case STATE_CLOSING_DOWN: {
      } break;

      case STATE_DISABLED: {
      } break;

      default: {
         throw std::runtime_error("weird error");
      } break;
   }

   this->state = state;
   state_changed_at = al_get_time();

   return;
}

void GameOverScreen::update(float time_now)
{
   if (!(is_valid_state(state)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::GameOverScreen::update]: error: guard \"is_valid_state(state)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::GameOverScreen::update]: error: guard \"is_valid_state(state)\" not met");
   }
   float age = infer_current_state_age(time_now);

   switch (state)
   {
      case STATE_REVEALING: {
         float reveal_speed = 0.01f;
         reveal_counter += reveal_speed;
         if (reveal_counter >= 1.0)
         {
            reveal_counter = 0.01f;
            set_state(STATE_AWAITING_USER_INPUT);
         }
      } break;

      case STATE_AWAITING_USER_INPUT: {
      } break;

      case STATE_CLOSING_DOWN: {
         float hide_speed = 0.01f;
         reveal_counter -= hide_speed;
         if (reveal_counter <= 0.0)
         {
            reveal_counter = 0.0f;
            activate_current_chosen_menu_option();
         }
      } break;

      case STATE_DISABLED: {
      } break;

      default: {
         throw std::runtime_error("weird error");
      } break;
   }

   return;
}

bool GameOverScreen::is_valid_state(uint32_t state)
{
   std::set<uint32_t> valid_states =
   {
      STATE_REVEALING,
      STATE_AWAITING_USER_INPUT,
      STATE_CLOSING_DOWN,
      STATE_DISABLED,
   };
   return (valid_states.count(state) > 0);
}

bool GameOverScreen::is_state(uint32_t possible_state)
{
   return (state == possible_state);
}

float GameOverScreen::infer_current_state_age(float time_now)
{
   return (time_now - state_changed_at);
}

ALLEGRO_FONT* GameOverScreen::obtain_title_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::GameOverScreen::obtain_title_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::GameOverScreen::obtain_title_font]: error: guard \"font_bin\" not met");
   }
   std::stringstream title_font_identifier;
   title_font_identifier << title_font_name << " " << title_font_size;
   return font_bin->auto_get(title_font_identifier.str());
}

ALLEGRO_FONT* GameOverScreen::obtain_menu_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::GameOverScreen::obtain_menu_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::GameOverScreen::obtain_menu_font]: error: guard \"font_bin\" not met");
   }
   std::stringstream menu_font_identifier;
   menu_font_identifier << menu_font_name << " " << menu_font_size;
   return font_bin->auto_get(menu_font_identifier.str());
}


} // namespace Screens
} // namespace AllegroFlare


