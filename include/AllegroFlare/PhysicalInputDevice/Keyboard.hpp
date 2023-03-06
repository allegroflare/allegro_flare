#pragma once


#include <AllegroFlare/PhysicalInputDevice/Base.hpp>


namespace AllegroFlare
{
   namespace PhysicalInputDevice
   {
      class Keyboard : public AllegroFlare::PhysicalInputDevice::Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/PhysicalInputDevice/Keyboard";

      private:

      protected:


      public:
         Keyboard();
         virtual ~Keyboard();

         virtual bool is_keyboard() override;
      };
   }
}



