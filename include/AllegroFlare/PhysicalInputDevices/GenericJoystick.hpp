#pragma once


#include <AllegroFlare/PhysicalInputDevices/Base.hpp>
#include <allegro5/allegro.h>


namespace AllegroFlare
{
   namespace PhysicalInputDevices
   {
      class GenericJoystick : public AllegroFlare::PhysicalInputDevices::Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/PhysicalInputDevices/GenericJoystick";

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



