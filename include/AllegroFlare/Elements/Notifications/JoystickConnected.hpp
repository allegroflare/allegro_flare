#pragma once


#include <AllegroFlare/Elements/Notifications/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace Notifications
      {
         class JoystickConnected : public AllegroFlare::Elements::Notifications::Base
         {
         private:
            std::string joystick_name;

         protected:


         public:
            JoystickConnected(std::string joystick_name="[unset-joystick_name]");
            ~JoystickConnected();

            void set_joystick_name(std::string joystick_name);
            std::string get_joystick_name() const;
         };
      }
   }
}



