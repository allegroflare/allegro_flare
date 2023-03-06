#pragma once


#include <AllegroFlare/PhysicalInputDevices/Base.hpp>


namespace AllegroFlare
{
   namespace PhysicalInputDevices
   {
      class Keyboard : public AllegroFlare::PhysicalInputDevices::Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/PhysicalInputDevices/Keyboard";

      private:

      protected:


      public:
         Keyboard();
         virtual ~Keyboard();

         virtual bool is_keyboard() override;
      };
   }
}



