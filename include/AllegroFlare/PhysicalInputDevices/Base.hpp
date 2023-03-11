#pragma once


#include <string>


namespace AllegroFlare
{
   namespace PhysicalInputDevices
   {
      class Base
      {
      public:
         static constexpr char* TYPE = (char*)"PhysicalInputDevice/Base";

      private:
         std::string type;
         std::string name;
         bool connected;

      protected:


      public:
         Base(std::string type=AllegroFlare::PhysicalInputDevices::Base::TYPE, std::string name="Unknown Input Device", bool connected=false);
         virtual ~Base();

         void set_connected(bool connected);
         std::string get_type() const;
         std::string get_name() const;
         bool get_connected() const;
         virtual bool is_keyboard();
         virtual bool is_joystick();
         bool is_type(std::string possible_type="");
      };
   }
}



