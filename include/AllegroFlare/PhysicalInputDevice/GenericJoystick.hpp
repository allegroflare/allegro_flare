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

      protected:


      public:
         GenericJoystick();
         virtual ~GenericJoystick();

         void set_al_joystick(ALLEGRO_JOYSTICK* al_joystick);
         ALLEGRO_JOYSTICK* get_al_joystick() const;
         virtual bool is_keyboard() override;
      };
   }
}



