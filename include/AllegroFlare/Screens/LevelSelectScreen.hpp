#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Elements/LevelSelect.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Player.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/Screens/LevelSelectScreen.hpp>
#include <AllegroFlare/VirtualControllers/Base.hpp>
#include <allegro5/allegro.h>
#include <functional>
#include <string>
#include <utility>
#include <vector>


namespace AllegroFlare
{
   namespace Screens
   {
      class LevelSelectScreen : public AllegroFlare::Screens::Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/Screens/LevelSelectScreen";

      private:
         AllegroFlare::EventEmitter* event_emitter;
         AllegroFlare::BitmapBin* bitmap_bin;
         AllegroFlare::FontBin* font_bin;
         AllegroFlare::Elements::LevelSelect level_select_element;
         std::function<void(AllegroFlare::Screens::LevelSelectScreen*, void*)> on_menu_choice_callback_func;
         void* on_menu_choice_callback_func_user_data;
         bool initialized;

      protected:


      public:
         LevelSelectScreen(AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr);
         virtual ~LevelSelectScreen();

         void set_on_menu_choice_callback_func(std::function<void(AllegroFlare::Screens::LevelSelectScreen*, void*)> on_menu_choice_callback_func);
         void set_on_menu_choice_callback_func_user_data(void* on_menu_choice_callback_func_user_data);
         std::function<void(AllegroFlare::Screens::LevelSelectScreen*, void*)> get_on_menu_choice_callback_func() const;
         void* get_on_menu_choice_callback_func_user_data() const;
         AllegroFlare::Elements::LevelSelect &get_level_select_element_ref();
         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter=nullptr);
         void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
         void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
         void set_levels_list(std::vector<std::pair<std::string, std::string>> levels_list={});
         void initialize();
         virtual void on_activate() override;
         virtual void on_deactivate() override;
         void update();
         void render();
         void activate_selected_menu_option();
         std::string infer_current_menu_option_value();
         virtual void primary_timer_func() override;
         virtual void virtual_control_button_up_func(AllegroFlare::Player* player=nullptr, AllegroFlare::VirtualControllers::Base* virtual_controller=nullptr, int virtual_controller_button_num=0, bool is_repeat=false) override;
         virtual void virtual_control_button_down_func(AllegroFlare::Player* player=nullptr, AllegroFlare::VirtualControllers::Base* virtual_controller=nullptr, int virtual_controller_button_num=0, bool is_repeat=false) override;
         virtual void virtual_control_axis_change_func(ALLEGRO_EVENT* ev=nullptr) override;
      };
   }
}



