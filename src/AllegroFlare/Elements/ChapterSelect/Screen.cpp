

#include <AllegroFlare/Elements/ChapterSelect/Screen.hpp>

#include <AllegroFlare/Elements/ChapterSelect/CarouselElements/ThumbnailWithLabelUnlockable.hpp>
#include <AllegroFlare/Logger.hpp>
#include <AllegroFlare/VirtualControllers/GenericController.hpp>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{
namespace ChapterSelect
{


Screen::Screen(AllegroFlare::EventEmitter* event_emitter, AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin)
   : AllegroFlare::Screens::Base(AllegroFlare::Elements::ChapterSelect::Screen::TYPE)
   , event_emitter(event_emitter)
   , bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , chapter_select_element({})
   , background(nullptr)
   , on_menu_choice_callback_func()
   , on_menu_choice_callback_func_user_data(nullptr)
   , on_exit_screen_callback_func()
   , on_exit_screen_callback_func_user_data(nullptr)
   , select_menu_sound_effect_identifier(DEFAULT_SELECT_MENU_SOUND_EFFECT_IDENTIFIER)
   , failed_select_menu_sound_effect_identifier(DEFAULT_FAILED_SELECT_MENU_SOUND_EFFECT_IDENTIFIER)
   , initialized(false)
{
}


Screen::~Screen()
{
}


void Screen::set_background(AllegroFlare::Elements::Backgrounds::Base* background)
{
   this->background = background;
}


void Screen::set_on_menu_choice_callback_func(std::function<void(AllegroFlare::Elements::ChapterSelect::Screen*, void*)> on_menu_choice_callback_func)
{
   this->on_menu_choice_callback_func = on_menu_choice_callback_func;
}


void Screen::set_on_menu_choice_callback_func_user_data(void* on_menu_choice_callback_func_user_data)
{
   this->on_menu_choice_callback_func_user_data = on_menu_choice_callback_func_user_data;
}


void Screen::set_on_exit_screen_callback_func(std::function<void(AllegroFlare::Elements::ChapterSelect::Screen*, void*)> on_exit_screen_callback_func)
{
   this->on_exit_screen_callback_func = on_exit_screen_callback_func;
}


void Screen::set_on_exit_screen_callback_func_user_data(void* on_exit_screen_callback_func_user_data)
{
   this->on_exit_screen_callback_func_user_data = on_exit_screen_callback_func_user_data;
}


void Screen::set_select_menu_sound_effect_identifier(std::string select_menu_sound_effect_identifier)
{
   this->select_menu_sound_effect_identifier = select_menu_sound_effect_identifier;
}


void Screen::set_failed_select_menu_sound_effect_identifier(std::string failed_select_menu_sound_effect_identifier)
{
   this->failed_select_menu_sound_effect_identifier = failed_select_menu_sound_effect_identifier;
}


AllegroFlare::Elements::Backgrounds::Base* Screen::get_background() const
{
   return background;
}


std::function<void(AllegroFlare::Elements::ChapterSelect::Screen*, void*)> Screen::get_on_menu_choice_callback_func() const
{
   return on_menu_choice_callback_func;
}


void* Screen::get_on_menu_choice_callback_func_user_data() const
{
   return on_menu_choice_callback_func_user_data;
}


std::function<void(AllegroFlare::Elements::ChapterSelect::Screen*, void*)> Screen::get_on_exit_screen_callback_func() const
{
   return on_exit_screen_callback_func;
}


void* Screen::get_on_exit_screen_callback_func_user_data() const
{
   return on_exit_screen_callback_func_user_data;
}


std::string Screen::get_select_menu_sound_effect_identifier() const
{
   return select_menu_sound_effect_identifier;
}


std::string Screen::get_failed_select_menu_sound_effect_identifier() const
{
   return failed_select_menu_sound_effect_identifier;
}


void Screen::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Screen::set_event_emitter]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::set_event_emitter: error: guard \"(!initialized)\" not met");
   }
   this->event_emitter = event_emitter;
   return;
}

void Screen::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Screen::set_bitmap_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::set_bitmap_bin: error: guard \"(!initialized)\" not met");
   }
   this->bitmap_bin = bitmap_bin;
   return;
}

void Screen::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Screen::set_font_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::set_font_bin: error: guard \"(!initialized)\" not met");
   }
   this->font_bin = font_bin;
   return;
}

void Screen::set_title_font_identifier(std::string title_font_identifier)
{
   chapter_select_element.set_title_font_identifier(title_font_identifier);
   return;
}

void Screen::set_title_font_size(int title_font_size)
{
   chapter_select_element.set_title_font_size(title_font_size);
   return;
}

void Screen::set_carousel_element_font_identifier(std::string carousel_element_font_identifier)
{
   chapter_select_element.set_carousel_element_font_identifier(carousel_element_font_identifier);
   return;
}

void Screen::set_carousel_element_font_size(int carousel_element_font_size)
{
   chapter_select_element.set_carousel_element_font_size(carousel_element_font_size);
   return;
}

void Screen::set_rotate_carousel_sound_effect_identifier(std::string rotate_carousel_sound_effect_identifier)
{
   chapter_select_element.set_rotate_carousel_sound_effect_identifier(rotate_carousel_sound_effect_identifier);
   return;
}

void Screen::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Screen::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::initialize: error: guard \"(!initialized)\" not met");
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[Screen::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::initialize: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Screen::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::initialize: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Screen::initialize]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::initialize: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[Screen::initialize]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::initialize: error: guard \"event_emitter\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[Screen::initialize]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::initialize: error: guard \"bitmap_bin\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Screen::initialize]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::initialize: error: guard \"font_bin\" not met");
   }
   chapter_select_element.set_event_emitter(event_emitter);
   chapter_select_element.set_bitmap_bin(bitmap_bin);
   chapter_select_element.set_font_bin(font_bin);
   chapter_select_element.initialize();
   initialized = true;
   return;
}

void Screen::set_elements(std::vector<AllegroFlare::Elements::ChapterSelect::CarouselElements::Base*> elements)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Screen::set_elements]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::set_elements: error: guard \"initialized\" not met");
   }
   // TODO: Introduce a mechanism where each chapter and its status is stored
   chapter_select_element.set_carousel_elements(elements);
   return;
}

void Screen::set_pagination_bar_elements(std::vector<bool> elements)
{
   // TODO: Introduce a mechanism where each chapter and its status is stored
   chapter_select_element.set_pagination_bar_elements(elements);
   return;
}

void Screen::on_activate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Screen::on_activate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::on_activate: error: guard \"initialized\" not met");
   }
   // TODO: Introduce a "show" mechanism
   //emit_event_to_update_input_hints_bar();
   //emit_show_and_size_input_hints_bar_event();
   return;
}

void Screen::on_deactivate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Screen::on_deactivate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::on_deactivate: error: guard \"initialized\" not met");
   }
   // TODO: Introduce a "hide" mechanism
   //emit_hide_and_restore_size_input_hints_bar_event();
   return;
}

void Screen::update()
{
   chapter_select_element.update();
   return;
}

void Screen::render()
{
   chapter_select_element.render();
   return;
}

AllegroFlare::Elements::ChapterSelect::CarouselElements::Base* Screen::get_focused_carousel_element()
{
   if (!(chapter_select_element.has_elements()))
   {
      std::stringstream error_message;
      error_message << "[Screen::get_focused_carousel_element]: error: guard \"chapter_select_element.has_elements()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::get_focused_carousel_element: error: guard \"chapter_select_element.has_elements()\" not met");
   }
   // TODO: Test this method
   return chapter_select_element.get_focused_carousel_element();
}

bool Screen::current_focused_carousel_element_can_be_selected()
{
   AllegroFlare::Elements::ChapterSelect::CarouselElements::Base* focused_element = get_focused_carousel_element();
   if (!focused_element)
   {
      AllegroFlare::Logger::throw_error(
            "AllegroFlare::Elements::ChapterSelect::Screen::current_focused_carousel_element_can_be_selected",
            "\"focused_element\" cannot be a nullptr."
         );
   }

   if (focused_element->is_type(
            AllegroFlare::Elements::ChapterSelect::CarouselElements::ThumbnailWithLabelUnlockable::TYPE
         )
      )
   {
      // TODO: Determine selection status
   }
   else
   {
      AllegroFlare::Logger::throw_error(
            "AllegroFlare::Elements::ChapterSelect::Screen::current_focused_carousel_element_can_be_selected",
            "Unable to determine selectability status of type \"" + focused_element->get_type() + "\"."
         );
   }
   return true;
}

void Screen::activate_menu_option()
{
   if (on_menu_choice_callback_func)
   {
      on_menu_choice_callback_func(this, on_menu_choice_callback_func_user_data);
   }
   else
   {
      AllegroFlare::Logger::throw_error(
            "AllegroFlare::Elements::ChapterSelect::Screen::activate_menu_option",
            "No callback has been assigned to \"on_menu_choice_callback_func\" so an activation of a menu "
                  "choice is not handled."
         );
   }

   return;
}

void Screen::select_menu_option()
{
   if (!is_processing_user_input()) return;

   if (chapter_select_element.has_no_elements())
   {
      std::cout <<
         "[AllegroFlare::Elements::ChapterSelect::Screen::select_menu_option()] error: can not select a menu item, "
         "the menu is empty."
         << std::endl;
      return;
   }

   if (current_focused_carousel_element_can_be_selected())
   {
      // TODO: Introduce a state so that this activate_menu_option() activation can be delayed
      emit_select_menu_sound_effect();
      activate_menu_option();
   }
   else
   {
      // Play a bonk effect
      emit_failed_select_menu_sound_effect();
   }

   return;
}

void Screen::exit_screen()
{
   if (!(on_exit_screen_callback_func))
   {
      std::stringstream error_message;
      error_message << "[Screen::exit_screen]: error: guard \"on_exit_screen_callback_func\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::exit_screen: error: guard \"on_exit_screen_callback_func\" not met");
   }
   on_exit_screen_callback_func(this, on_exit_screen_callback_func_user_data);
   return;
}

void Screen::primary_timer_func()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Screen::primary_timer_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::primary_timer_func: error: guard \"initialized\" not met");
   }
   if (background) background->update();
   update();
   if (background) background->render();
   render();
   return;
}

void Screen::virtual_control_button_up_func(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_button_num, bool is_repeat)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Screen::virtual_control_button_up_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::virtual_control_button_up_func: error: guard \"initialized\" not met");
   }
   // TODO: this function
   return;
}

void Screen::virtual_control_button_down_func(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_button_num, bool is_repeat)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Screen::virtual_control_button_down_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::virtual_control_button_down_func: error: guard \"initialized\" not met");
   }
   // TODO: Consider validating the controller is GenericController
   if (!is_processing_user_input()) return;

   if (virtual_controller_button_num == VirtualControllers::GenericController::BUTTON_RIGHT)
   {
      chapter_select_element.rotate_carousel_right();
   }
   if (virtual_controller_button_num == VirtualControllers::GenericController::BUTTON_LEFT)
   {
      chapter_select_element.rotate_carousel_left();
   }
   if (virtual_controller_button_num == VirtualControllers::GenericController::BUTTON_A
      || virtual_controller_button_num == VirtualControllers::GenericController::BUTTON_MENU
      )
   {
      select_menu_option();
   }
   if (virtual_controller_button_num == VirtualControllers::GenericController::BUTTON_X)
   {
      exit_screen();
   }
   return;
}

void Screen::emit_select_menu_sound_effect()
{
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[Screen::emit_select_menu_sound_effect]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::emit_select_menu_sound_effect: error: guard \"event_emitter\" not met");
   }
   // TODO: test this event emission
   event_emitter->emit_play_sound_effect_event(select_menu_sound_effect_identifier);
   return;
}

void Screen::emit_failed_select_menu_sound_effect()
{
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[Screen::emit_failed_select_menu_sound_effect]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::emit_failed_select_menu_sound_effect: error: guard \"event_emitter\" not met");
   }
   // TODO: test this event emission
   event_emitter->emit_play_sound_effect_event(failed_select_menu_sound_effect_identifier);
   return;
}

void Screen::virtual_control_axis_change_func(ALLEGRO_EVENT* ev)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Screen::virtual_control_axis_change_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::virtual_control_axis_change_func: error: guard \"initialized\" not met");
   }
   // TODO: this function
   return;
}

bool Screen::is_processing_user_input()
{
   // TODO: Update this to only return TRUE when the player is permitted to move the cursor
   return true;
}


} // namespace ChapterSelect
} // namespace Elements
} // namespace AllegroFlare


