#pragma once


#include <string>


namespace AllegroFlare
{
   namespace LoadASavedGame
   {
      namespace SaveSlots
      {
         class Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/LoadASavedGame/SaveSlots/Base";

         private:
            std::string type;

         protected:


         public:
            Base(std::string type=AllegroFlare::LoadASavedGame::SaveSlots::Base::TYPE);
            ~Base();

            std::string get_type() const;
            bool is_type(std::string possible_type="");
         };
      }
   }
}



