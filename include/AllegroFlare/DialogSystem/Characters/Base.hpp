#pragma once


#include <string>


namespace AllegroFlare
{
   namespace DialogSystem
   {
      namespace Characters
      {
         class Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/DialogSystem/Characters/Base";

         private:
            std::string type;

         protected:


         public:
            Base(std::string type=AllegroFlare::DialogSystem::Characters::Base::TYPE);
            ~Base();

            std::string get_type() const;
            std::string get_display_name();
            bool is_type(std::string possible_type="");
         };
      }
   }
}



