#pragma once


#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/Frameworks/Full.hpp>
#include <AllegroFlare/GameSession.hpp>
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
         AllegroFlare::GameSession* game_session;

      protected:


      public:
         Base(std::string type=AllegroFlare::Routers::Base::TYPE, AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::Frameworks::Full* framework=nullptr, AllegroFlare::GameSession* game_session=nullptr);
         virtual ~Base();

         std::string get_type() const;
         AllegroFlare::EventEmitter* get_event_emitter() const;
         AllegroFlare::Frameworks::Full* get_framework() const;
         AllegroFlare::GameSession* get_game_session() const;
         void register_screen(std::string screen_identifier="[unset-screen_identifier]", AllegroFlare::Screens::Base* screen=nullptr);
         void activate_screen(std::string screen_identifier="[unset-screen_identifier]");
         void emit_route_event(uint32_t route_event=0);
         virtual void on_route_event(uint32_t route_event=0);
         bool is_type(std::string possible_type="");
      };
   }
}



