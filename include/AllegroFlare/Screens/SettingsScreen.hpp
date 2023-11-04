#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/ModelBin.hpp>
#include <AllegroFlare/Player.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/Screens/SettingsScreen.hpp>
#include <AllegroFlare/VirtualControllers/Base.hpp>
#include <allegro5/allegro.h>
#include <functional>


namespace AllegroFlare
{
   namespace Screens
   {
      class SettingsScreen : public AllegroFlare::Screens::Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/Screens/SettingsScreen";

      private:
         AllegroFlare::EventEmitter* event_emitter;
         AllegroFlare::BitmapBin* bitmap_bin;
         AllegroFlare::FontBin* font_bin;
         AllegroFlare::ModelBin* model_bin;
         std::function<void(AllegroFlare::Screens::SettingsScreen*, void*)> on_exit_callback_func;
         void* on_exit_callback_func_user_data;
         int surface_width;
         int surface_height;
         bool initialized;
         ALLEGRO_FONT* obtain_heading_font();
         ALLEGRO_FONT* obtain_text_font();

      protected:


      public:
         SettingsScreen(AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::ModelBin* model_bin=nullptr);
         virtual ~SettingsScreen();

         void set_on_exit_callback_func(std::function<void(AllegroFlare::Screens::SettingsScreen*, void*)> on_exit_callback_func);
         void set_on_exit_callback_func_user_data(void* on_exit_callback_func_user_data);
         void set_surface_height(int surface_height);
         std::function<void(AllegroFlare::Screens::SettingsScreen*, void*)> get_on_exit_callback_func() const;
         void* get_on_exit_callback_func_user_data() const;
         int get_surface_width() const;
         int get_surface_height() const;
         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter=nullptr);
         void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
         void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
         void set_model_bin(AllegroFlare::ModelBin* model_bin=nullptr);
         void initialize();
         void exit_screen();
         virtual void on_activate() override;
         virtual void on_deactivate() override;
         void update();
         void render();
         virtual void primary_timer_func() override;
         virtual void virtual_control_button_up_func(AllegroFlare::Player* player=nullptr, AllegroFlare::VirtualControllers::Base* virtual_controller=nullptr, int virtual_controller_button_num=0, bool is_repeat=false) override;
         virtual void virtual_control_button_down_func(AllegroFlare::Player* player=nullptr, AllegroFlare::VirtualControllers::Base* virtual_controller=nullptr, int virtual_controller_button_num=0, bool is_repeat=false) override;
         virtual void virtual_control_axis_change_func(ALLEGRO_EVENT* ev=nullptr) override;
      };
   }
}



