#pragma once


#include <string>


namespace AllegroFlare
{
   namespace DialogSystem
   {
      namespace Chapters
      {
         class Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/DialogSystem/Chapters/Base";

         private:
            std::string type;

         protected:


         public:
            Base(std::string type=AllegroFlare::DialogSystem::Chapters::Base::TYPE);
            ~Base();

            std::string get_type() const;
            bool is_type(std::string possible_type="");
         };
      }
   }
}



