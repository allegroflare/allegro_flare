#pragma once


#include <string>


namespace AllegroFlare
{
   namespace DialogSystemDrivers
   {
      class Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/DialogSystemDrivers/Base";

      private:
         std::string type;

      protected:


      public:
         Base(std::string type=AllegroFlare::DialogSystemDrivers::Base::TYPE);
         virtual ~Base();

         std::string get_type() const;
         virtual void on_deactivate();
         virtual void on_render();
         bool is_type(std::string possible_type="");
      };
   }
}



