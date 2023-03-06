#pragma once


#include <AllegroFlare/PhysicalInputDevice/Base.hpp>
#include <allegro5/allegro.h>


namespace AllegroFlare
{
   namespace PhysicalInputDevice
   {
      class GenericJoystick : public AllegroFlare::PhysicalInputDevice::Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/PhysicalInputDevice/GenericJoystick";

      private:
         ALLEGRO_JOYSTICK* al_joystick;
         bool connected;

      protected:


      public:
         GenericJoystick();
         ~GenericJoystick();

         void set_al_joystick(ALLEGRO_JOYSTICK* al_joystick);
         void set_connected(bool connected);
         ALLEGRO_JOYSTICK* get_al_joystick() const;
         bool get_connected() const;
      };
   }
}



