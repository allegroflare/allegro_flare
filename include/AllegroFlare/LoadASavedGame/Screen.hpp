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
         bool initialized;
         ALLEGRO_FONT* obtain_heading_font();
         ALLEGRO_FONT* obtain_text_font();

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
      };
   }
}



