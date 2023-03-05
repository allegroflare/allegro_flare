#pragma once


#include <AllegroFlare/PhysicalInputDevice/Base.hpp>


namespace AllegroFlare
{
   namespace PhysicalInputDevice
   {
      class GenericJoystick : public AllegroFlare::PhysicalInputDevice::Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/PhysicalInputDevice/GenericJoystick";

      private:

      protected:


      public:
         GenericJoystick();
         ~GenericJoystick();

      };
   }
}



