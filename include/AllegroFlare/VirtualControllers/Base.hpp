#pragma once


#include <string>


namespace AllegroFlare
{
   namespace VirtualControllers
   {
      class Base
      {
      public:
         static constexpr char* TYPE = (char*)"VirtualControllers/Base";

      private:
         std::string type;
         std::string name;

      protected:


      public:
         Base(std::string type=AllegroFlare::VirtualControllers::Base::TYPE, std::string name="Virtual Controller");
         ~Base();

         std::string get_type() const;
         std::string get_name() const;
         bool is_type(std::string possible_type="");
      };
   }
}



