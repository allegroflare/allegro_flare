#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Elements/InputDeviceConfigurationList.hpp>
#include <AllegroFlare/Elements/InputDevicesList.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/InputDevicesList.hpp>
#include <AllegroFlare/Player.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/Screens/InputDeviceConfiguration.hpp>
#include <AllegroFlare/VirtualControllers/Base.hpp>
#include <allegro5/allegro.h>
#include <cstddef>
#include <functional>


namespace AllegroFlare
{
   namespace Screens
   {
      class InputDeviceConfiguration : public AllegroFlare::Screens::Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/Screens/InputDeviceConfiguration";

      private:
         AllegroFlare::EventEmitter* event_emitter;
         AllegroFlare::BitmapBin* bitmap_bin;
         AllegroFlare::FontBin* font_bin;
         std::size_t surface_width;
         std::size_t surface_height;
         std::function<void(AllegroFlare::Screens::InputDeviceConfiguration*, void*)> on_exit_callback_func;
         void* on_exit_callback_func_user_data;
         AllegroFlare::InputDevicesList* input_devices_list;
         AllegroFlare::Elements::InputDevicesList input_devices_list_element;
         AllegroFlare::Elements::InputDeviceConfigurationList input_device_configuration_element;
         bool initialized;
         void call_on_exit_callback();

      protected:


      public:
         InputDeviceConfiguration(AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, std::size_t surface_width=1920, std::size_t surface_height=1090, AllegroFlare::InputDevicesList* input_devices_list=nullptr);
         virtual ~InputDeviceConfiguration();

         void set_surface_width(std::size_t surface_width);
         void set_surface_height(std::size_t surface_height);
         void set_on_exit_callback_func(std::function<void(AllegroFlare::Screens::InputDeviceConfiguration*, void*)> on_exit_callback_func);
         void set_on_exit_callback_func_user_data(void* on_exit_callback_func_user_data);
         std::size_t get_surface_width() const;
         std::size_t get_surface_height() const;
         std::function<void(AllegroFlare::Screens::InputDeviceConfiguration*, void*)> get_on_exit_callback_func() const;
         void* get_on_exit_callback_func_user_data() const;
         AllegroFlare::Elements::InputDevicesList &get_input_devices_list_element_ref();
         AllegroFlare::Elements::InputDeviceConfigurationList &get_input_device_configuration_element_ref();
         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter=nullptr);
         void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
         void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
         void set_input_devices_list(AllegroFlare::InputDevicesList* input_devices_list=nullptr);
         void initialize();
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



