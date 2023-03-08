#pragma once


#include <AllegroFlare/PhysicalInputDevices/Base.hpp>
#include <allegro5/allegro.h>


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

         protected:


         public:
            Base();
            virtual ~Base();

            void set_al_joystick(ALLEGRO_JOYSTICK* al_joystick);
            ALLEGRO_JOYSTICK* get_al_joystick() const;
            virtual bool is_joystick() override;
            bool is_using_al_joystick(ALLEGRO_JOYSTICK* possibly_same_al_joystick=nullptr);
         };
      }
   }
}



