#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Player.hpp>
#include <AllegroFlare/SavingAndLoading/SaveSlot.hpp>
#include <AllegroFlare/SavingAndLoading/SavingAndLoading.hpp>
#include <AllegroFlare/SavingAndLoading/Screen.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/VirtualControllers/Base.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <cstdint>
#include <functional>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace SavingAndLoading
   {
      class Screen : public AllegroFlare::Screens::Base
      {
      public:
         static constexpr char* DEFAULT_DATA_FOLDER_PATH = (char*)"[unset-data_folder_path]";
         static constexpr char* TYPE = (char*)"AllegroFlare/SavingAndLoading/Screen";

      public:

         enum
         {
            STATE_UNDEF = 0,
            STATE_REVEALING,
            STATE_REVEALED_AND_HANDLING_USER_INPUT,
            STATE_MENU_OPTION_IS_CHOSEN,
            __UNIMPLEMENTED__STATE_AWAITING_USER_CONFIRMATION,
            STATE_CLOSING_DOWN,
            STATE_CLOSED_DOWN_AND_AWAITING_MENU_CHOICE_ACTIVATION,
            STATE_FINISHED,
         };
      private:
         std::string data_folder_path;
         AllegroFlare::BitmapBin bitmap_bin;
         AllegroFlare::FontBin font_bin;
         AllegroFlare::SavingAndLoading::SavingAndLoading* saving_and_loading;
         int cursor_position;
         std::function<void(AllegroFlare::SavingAndLoading::Screen*, void*)> on_menu_choice_callback_func;
         void* on_menu_choice_callback_func_user_data;
         std::function<void(AllegroFlare::SavingAndLoading::Screen*, void*)> on_erase_focused_save_slot_func;
         void* on_erase_focused_save_slot_func_user_data;
         std::function<void(AllegroFlare::SavingAndLoading::Screen*, void*)> on_exit_callback_func;
         void* on_exit_callback_func_user_data;
         uint32_t state;
         bool state_is_busy;
         float state_changed_at;
         bool initialized;
         bool destroyed;
         std::vector<AllegroFlare::SavingAndLoading::SaveSlot*> get_manual_save_slots();
         ALLEGRO_FONT* obtain_heading_font();

      protected:


      public:
         Screen(std::string data_folder_path=DEFAULT_DATA_FOLDER_PATH);
         virtual ~Screen();

         void set_data_folder_path(std::string data_folder_path);
         void set_saving_and_loading(AllegroFlare::SavingAndLoading::SavingAndLoading* saving_and_loading);
         void set_on_menu_choice_callback_func(std::function<void(AllegroFlare::SavingAndLoading::Screen*, void*)> on_menu_choice_callback_func);
         void set_on_menu_choice_callback_func_user_data(void* on_menu_choice_callback_func_user_data);
         void set_on_erase_focused_save_slot_func(std::function<void(AllegroFlare::SavingAndLoading::Screen*, void*)> on_erase_focused_save_slot_func);
         void set_on_erase_focused_save_slot_func_user_data(void* on_erase_focused_save_slot_func_user_data);
         void set_on_exit_callback_func(std::function<void(AllegroFlare::SavingAndLoading::Screen*, void*)> on_exit_callback_func);
         void set_on_exit_callback_func_user_data(void* on_exit_callback_func_user_data);
         std::function<void(AllegroFlare::SavingAndLoading::Screen*, void*)> get_on_menu_choice_callback_func() const;
         void* get_on_menu_choice_callback_func_user_data() const;
         std::function<void(AllegroFlare::SavingAndLoading::Screen*, void*)> get_on_erase_focused_save_slot_func() const;
         void* get_on_erase_focused_save_slot_func_user_data() const;
         std::function<void(AllegroFlare::SavingAndLoading::Screen*, void*)> get_on_exit_callback_func() const;
         void* get_on_exit_callback_func_user_data() const;
         uint32_t get_state() const;
         bool get_initialized() const;
         bool get_destroyed() const;
         void initialize();
         virtual void destroy() override;
         virtual void on_activate() override;
         virtual void on_deactivate() override;
         void reveal_screen();
         bool handling_user_input();
         std::vector<AllegroFlare::SavingAndLoading::SaveSlot*> get_save_slots();
         void move_cursor_up();
         void move_cursor_down();
         AllegroFlare::SavingAndLoading::SaveSlot* get_currently_selected_save_slot();
         void exit_screen();
         void activate_current_focused_menu_option();
         void erase_current_focused_save_slot();
         bool can_exit_screen();
         bool can_select_current_focused_menu_option();
         void select_current_focused_menu_option();
         void render();
         void render_title();
         void render_save_slots();
         virtual void primary_update_func(double time_now=0.0, double time_step=0.0) override;
         virtual void primary_render_func() override;
         virtual void primary_timer_func() override;
         virtual void key_char_func(ALLEGRO_EVENT* event=nullptr) override;
         virtual void virtual_control_button_down_func(AllegroFlare::Player* player=nullptr, AllegroFlare::VirtualControllers::Base* virtual_controller=nullptr, int virtual_controller_button_num=0, bool is_repeat=false) override;
         virtual void virtual_control_axis_change_func(ALLEGRO_EVENT* ev=nullptr) override;
         void set_state(uint32_t state=STATE_UNDEF, bool override_if_busy=false);
         void begin_shutdown_after_selection();
         void complete_shutdown_and_activate_current_focused_menu_option();
         void update_state(float time_now=al_get_time());
         static bool is_valid_state(uint32_t state=STATE_UNDEF);
         bool is_state(uint32_t possible_state=STATE_UNDEF);
         float infer_current_state_age(float time_now=al_get_time());
         bool infer_currently_drawing_user_cursor();
      };
   }
}



