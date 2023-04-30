#pragma once


#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/Frameworks/Full.hpp>
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
         AllegroFlare::EventEmitter* event_emitter;
         AllegroFlare::Frameworks::Full* framework;

      protected:


      public:
         Base(std::string type=AllegroFlare::Routers::Base::TYPE, AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::Frameworks::Full* framework=nullptr);
         virtual ~Base();

         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
         void set_framework(AllegroFlare::Frameworks::Full* framework);
         std::string get_type() const;
         AllegroFlare::EventEmitter* get_event_emitter() const;
         AllegroFlare::Frameworks::Full* get_framework() const;
         void register_screen(std::string screen_identifier="[unset-screen_identifier]", AllegroFlare::Screens::Base* screen=nullptr);
         void activate_screen(std::string screen_identifier="[unset-screen_identifier]");
         void emit_route_event(uint32_t route_event=0);
         virtual void on_route_event(uint32_t route_event=0);
         bool is_type(std::string possible_type="");
      };
   }
}



