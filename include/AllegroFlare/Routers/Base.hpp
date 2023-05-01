#pragma once


#include <AllegroFlare/RouteEventDatas/Base.hpp>
#include <AllegroFlare/ScreenManagers/Dictionary.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <cstdint>
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

      protected:


      public:
         Base(std::string type=AllegroFlare::Routers::Base::TYPE, AllegroFlare::ScreenManagers::Dictionary* screen_manager=nullptr);
         virtual ~Base();

         void set_screen_manager(AllegroFlare::ScreenManagers::Dictionary* screen_manager);
         std::string get_type() const;
         AllegroFlare::ScreenManagers::Dictionary* get_screen_manager() const;
         void register_screen(std::string screen_identifier="[unset-screen_identifier]", AllegroFlare::Screens::Base* screen=nullptr);
         void unregister_screen(AllegroFlare::Screens::Base* screen=nullptr);
         void activate_screen(std::string screen_identifier="[unset-screen_identifier]");
         virtual void on_route_event(uint32_t route_event=0, AllegroFlare::RouteEventDatas::Base* route_event_data=nullptr, float time_now=0.0f);
         bool is_type(std::string possible_type="");
      };
   }
}



