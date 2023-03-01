#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Elements/JoystickConfigurationList.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <allegro5/allegro.h>
#include <cstddef>


namespace AllegroFlare
{
   namespace Screens
   {
      class JoystickConfiguration : public AllegroFlare::Screens::Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/Screens/JoystickConfiguration";

      private:
         AllegroFlare::EventEmitter* event_emitter;
         AllegroFlare::BitmapBin* bitmap_bin;
         AllegroFlare::FontBin* font_bin;
         std::size_t surface_width;
         std::size_t surface_height;
         AllegroFlare::Elements::JoystickConfigurationList joystick_configuration_element;
         bool initialized;

      protected:


      public:
         JoystickConfiguration(AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, std::size_t surface_width=1920, std::size_t surface_height=1090);
         virtual ~JoystickConfiguration();

         void set_surface_width(std::size_t surface_width);
         void set_surface_height(std::size_t surface_height);
         std::size_t get_surface_width() const;
         std::size_t get_surface_height() const;
         AllegroFlare::Elements::JoystickConfigurationList &get_joystick_configuration_element_ref();
         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter=nullptr);
         void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
         void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
         void initialize();
         virtual void on_activate() override;
         virtual void on_deactivate() override;
         void update();
         void render();
         virtual void primary_timer_func() override;
         virtual void virtual_control_button_up_func(int player_num=0, int button_num=0, bool repeat=false) override;
         virtual void virtual_control_button_down_func(int player_num=0, int button_num=0, bool repeat=false) override;
         virtual void virtual_control_axis_change_func(ALLEGRO_EVENT* ev=nullptr) override;
      };
   }
}



