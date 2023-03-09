#pragma once


#include <AllegroFlare/PhysicalInputDevices/Base.hpp>
#include <allegro5/allegro.h>
#include <cstdint>
#include <map>
#include <string>


namespace AllegroFlare
{
   namespace PhysicalInputDevices
   {
      namespace Joysticks
      {
         class Base : public AllegroFlare::PhysicalInputDevices::Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/PhysicalInputDevices/Joysticks/Base";

         private:
            ALLEGRO_JOYSTICK* al_joystick;
            std::string name;
            std::map<uint32_t, std::string> buttons;
            bool has_been_setup;

         protected:


         public:
            Base();
            virtual ~Base();

            ALLEGRO_JOYSTICK* get_al_joystick() const;
            std::string get_name() const;
            std::map<uint32_t, std::string> get_buttons() const;
            void set_al_joystick(ALLEGRO_JOYSTICK* al_joystick=nullptr);
            std::string get_name();
            std::map<uint32_t, std::string> get_buttons();
            bool setup();
            virtual bool is_joystick() override;
            bool is_using_al_joystick(ALLEGRO_JOYSTICK* possibly_same_al_joystick=nullptr);
         };
      }
   }
}



