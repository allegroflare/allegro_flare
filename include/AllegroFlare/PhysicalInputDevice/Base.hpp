#pragma once


#include <string>


namespace AllegroFlare
{
   namespace PhysicalInputDevice
   {
      class Base
      {
      public:
         static constexpr char* TYPE = (char*)"PhysicalInputDevice/Base";

      private:
         std::string type;
         std::string name;

      protected:


      public:
         Base(std::string type=AllegroFlare::PhysicalInputDevice::Base::TYPE, std::string name="Unknown Input Device");
         virtual ~Base();

         std::string get_type() const;
         std::string get_name() const;
         virtual bool is_keyboard();
         virtual bool is_joystick();
         bool is_type(std::string possible_type="");
      };
   }
}



