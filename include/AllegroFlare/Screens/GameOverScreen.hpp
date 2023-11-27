#pragma once


#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Player.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/Screens/GameOverScreen.hpp>
#include <AllegroFlare/VirtualControllers/Base.hpp>
#include <allegro5/allegro_font.h>
#include <cstdint>
#include <functional>
#include <string>
#include <utility>
#include <vector>


namespace AllegroFlare
{
   namespace Screens
   {
      class GameOverScreen : public AllegroFlare::Screens::Base
      {
      private:
         enum States
         {
            STATE_UNDEF = 0,
            STATE_REVEALING,
            STATE_AWAITING_USER_INPUT,
            STATE_CLOSING_DOWN,
            STATE_DISABLED,
         };
         AllegroFlare::EventEmitter* event_emitter;
         AllegroFlare::FontBin* font_bin;
         std::string title_text;
         std::vector<std::pair<std::string, std::string>> menu_options;
         std::string fallback_instruction_text_when_no_menu_options;
         std::function<void(AllegroFlare::Screens::GameOverScreen*, void*)> on_menu_choice_callback_func;
         void* on_menu_choice_callback_func_user_data;
         int cursor_position;
         std::string title_font_name;
         int title_font_size;
         std::string menu_font_name;
         int menu_font_size;
         float reveal_counter;
         uint32_t state;
         bool state_is_busy;
         float state_changed_at;
         bool initialized;
         static std::string DEFAULT_TITLE_TEXT;
         static std::vector<std::pair<std::string, std::string>> DEFAULT_MENU_OPTIONS;
         static std::string DEFAULT_FALLBACK_INSTRUCTION_TEXT_WHEN_NO_MENU_OPTIONS;
         void move_cursor_up();
         void move_cursor_down();
         void activate_current_chosen_menu_option();
         ALLEGRO_FONT* obtain_title_font();
         ALLEGRO_FONT* obtain_menu_font();

      protected:


      public:
         GameOverScreen(AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::FontBin* font_bin=nullptr, std::string title_text=DEFAULT_TITLE_TEXT, std::string title_font_name="Inter-Regular.ttf", int title_font_size=-64, std::string menu_font_name="Inter-Regular.ttf", int menu_font_size=-32);
         virtual ~GameOverScreen();

         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
         void set_font_bin(AllegroFlare::FontBin* font_bin);
         void set_title_text(std::string title_text);
         void set_on_menu_choice_callback_func(std::function<void(AllegroFlare::Screens::GameOverScreen*, void*)> on_menu_choice_callback_func);
         void set_on_menu_choice_callback_func_user_data(void* on_menu_choice_callback_func_user_data);
         void set_title_font_name(std::string title_font_name);
         void set_title_font_size(int title_font_size);
         void set_menu_font_name(std::string menu_font_name);
         void set_menu_font_size(int menu_font_size);
         std::function<void(AllegroFlare::Screens::GameOverScreen*, void*)> get_on_menu_choice_callback_func() const;
         void* get_on_menu_choice_callback_func_user_data() const;
         std::string get_title_font_name() const;
         int get_title_font_size() const;
         std::string get_menu_font_name() const;
         int get_menu_font_size() const;
         bool get_initialized() const;
         void set_menu_options(std::vector<std::pair<std::string, std::string>> menu_options={});
         void clear_menu_options();
         void initialize();
         virtual void on_activate() override;
         virtual void on_deactivate() override;
         void choose_menu_option();
         virtual void primary_timer_func() override;
         void render();
         void draw_primary_text();
         void draw_menu();
         std::string infer_current_menu_option_value();
         std::string infer_current_menu_option_label();
         virtual void virtual_control_button_down_func(AllegroFlare::Player* player=nullptr, AllegroFlare::VirtualControllers::Base* virtual_controller=nullptr, int virtual_controller_button_num=0, bool is_repeat=false) override;
         void set_state(uint32_t state=STATE_UNDEF, bool override_if_busy=false);
         void update(float time_now=al_get_time());
         static bool is_valid_state(uint32_t state=STATE_UNDEF);
         bool is_state(uint32_t possible_state=STATE_UNDEF);
         float infer_current_state_age(float time_now=al_get_time());
      };
   }
}



