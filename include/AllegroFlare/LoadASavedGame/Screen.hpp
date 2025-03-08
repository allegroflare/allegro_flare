#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/LoadASavedGame/SaveSlots/Base.hpp>
#include <AllegroFlare/LoadASavedGame/Screen.hpp>
#include <AllegroFlare/ModelBin.hpp>
#include <AllegroFlare/Player.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/VirtualControllers/Base.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <cstdint>
#include <functional>
#include <vector>


namespace AllegroFlare
{
   namespace LoadASavedGame
   {
      class Screen : public AllegroFlare::Screens::Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/LoadASavedGame/Screen";

      public:

         enum
         {
            STATE_UNDEF = 0,
            STATE_REVEALING,
            STATE_REVEALED_AND_AWAITING_USER_INPUT,
            STATE_MENU_OPTION_IS_CHOSEN,
            __UNIMPLEMENTED__STATE_AWAITING_USER_CONFIRMATION,
            STATE_CLOSING_DOWN,
            STATE_FINISHED,
         };
      private:
         AllegroFlare::EventEmitter* event_emitter;
         AllegroFlare::BitmapBin* bitmap_bin;
         AllegroFlare::FontBin* font_bin;
         AllegroFlare::ModelBin* model_bin;
         std::vector<AllegroFlare::LoadASavedGame::SaveSlots::Base*> save_slots;
         int cursor_position;
         std::function<void(AllegroFlare::LoadASavedGame::Screen*, void*)> on_menu_choice_callback_func;
         void* on_menu_choice_callback_func_user_data;
         std::function<void(AllegroFlare::LoadASavedGame::Screen*, void*)> on_erase_focused_save_slot_func;
         void* on_erase_focused_save_slot_func_user_data;
         std::function<void(AllegroFlare::LoadASavedGame::Screen*, void*)> on_exit_callback_func;
         void* on_exit_callback_func_user_data;
         uint32_t state;
         bool state_is_busy;
         float state_changed_at;
         bool initialized;
         ALLEGRO_FONT* obtain_heading_font();

      protected:


      public:
         Screen(AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::ModelBin* model_bin=nullptr);
         virtual ~Screen();

         void set_on_menu_choice_callback_func(std::function<void(AllegroFlare::LoadASavedGame::Screen*, void*)> on_menu_choice_callback_func);
         void set_on_menu_choice_callback_func_user_data(void* on_menu_choice_callback_func_user_data);
         void set_on_erase_focused_save_slot_func(std::function<void(AllegroFlare::LoadASavedGame::Screen*, void*)> on_erase_focused_save_slot_func);
         void set_on_erase_focused_save_slot_func_user_data(void* on_erase_focused_save_slot_func_user_data);
         void set_on_exit_callback_func(std::function<void(AllegroFlare::LoadASavedGame::Screen*, void*)> on_exit_callback_func);
         void set_on_exit_callback_func_user_data(void* on_exit_callback_func_user_data);
         std::vector<AllegroFlare::LoadASavedGame::SaveSlots::Base*> get_save_slots() const;
         std::function<void(AllegroFlare::LoadASavedGame::Screen*, void*)> get_on_menu_choice_callback_func() const;
         void* get_on_menu_choice_callback_func_user_data() const;
         std::function<void(AllegroFlare::LoadASavedGame::Screen*, void*)> get_on_erase_focused_save_slot_func() const;
         void* get_on_erase_focused_save_slot_func_user_data() const;
         std::function<void(AllegroFlare::LoadASavedGame::Screen*, void*)> get_on_exit_callback_func() const;
         void* get_on_exit_callback_func_user_data() const;
         uint32_t get_state() const;
         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter=nullptr);
         void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
         void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
         void set_model_bin(AllegroFlare::ModelBin* model_bin=nullptr);
         void set_save_slots(std::vector<AllegroFlare::LoadASavedGame::SaveSlots::Base*> save_slots={});
         void initialize();
         virtual void on_activate() override;
         virtual void on_deactivate() override;
         void move_cursor_up();
         void move_cursor_down();
         AllegroFlare::LoadASavedGame::SaveSlots::Base* get_currently_selected_save_slot();
         void exit_screen();
         void activate_current_focused_menu_option();
         void erase_current_focused_save_slot();
         void select_current_focused_menu_option();
         void update();
         void render();
         void render_title();
         void render_save_slots();
         virtual void primary_timer_func() override;
         virtual void key_char_func(ALLEGRO_EVENT* event=nullptr) override;
         virtual void virtual_control_button_down_func(AllegroFlare::Player* player=nullptr, AllegroFlare::VirtualControllers::Base* virtual_controller=nullptr, int virtual_controller_button_num=0, bool is_repeat=false) override;
         virtual void virtual_control_axis_change_func(ALLEGRO_EVENT* ev=nullptr) override;
         void set_state(uint32_t state=STATE_UNDEF, bool override_if_busy=false);
         void update_state(float time_now=al_get_time());
         static bool is_valid_state(uint32_t state=STATE_UNDEF);
         bool is_state(uint32_t possible_state=STATE_UNDEF);
         float infer_current_state_age(float time_now=al_get_time());
      };
   }
}



