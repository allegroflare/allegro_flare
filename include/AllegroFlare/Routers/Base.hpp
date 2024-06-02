#pragma once


#include <AllegroFlare/RouteEventDatas/Base.hpp>
#include <AllegroFlare/Routers/Base.hpp>
#include <AllegroFlare/ScreenManagers/Dictionary.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <cstdint>
#include <functional>
#include <string>


namespace AllegroFlare
{
   namespace Routers
   {
      class Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/Routers/Base";

      private:
         std::string type;
         AllegroFlare::ScreenManagers::Dictionary* screen_manager;
         std::function<void(std::string, std::string, AllegroFlare::Routers::Base*, void*)> on_before_activate_screen_func;
         void* on_before_activate_screen_func_user_data;

      protected:


      public:
         Base(std::string type=AllegroFlare::Routers::Base::TYPE, AllegroFlare::ScreenManagers::Dictionary* screen_manager=nullptr);
         virtual ~Base();

         void set_screen_manager(AllegroFlare::ScreenManagers::Dictionary* screen_manager);
         void set_on_before_activate_screen_func(std::function<void(std::string, std::string, AllegroFlare::Routers::Base*, void*)> on_before_activate_screen_func);
         void set_on_before_activate_screen_func_user_data(void* on_before_activate_screen_func_user_data);
         std::string get_type() const;
         AllegroFlare::ScreenManagers::Dictionary* get_screen_manager() const;
         std::function<void(std::string, std::string, AllegroFlare::Routers::Base*, void*)> get_on_before_activate_screen_func() const;
         void* get_on_before_activate_screen_func_user_data() const;
         void register_screen(std::string screen_identifier="[unset-screen_identifier]", AllegroFlare::Screens::Base* screen=nullptr);
         void unregister_screen(AllegroFlare::Screens::Base* screen=nullptr);
         void activate_screen(std::string screen_identifier="[unset-screen_identifier]");
         virtual void on_route_event(uint32_t route_event=0, AllegroFlare::RouteEventDatas::Base* route_event_data=nullptr, float time_now=0.0f);
         bool is_type(std::string possible_type="");
      };
   }
}



