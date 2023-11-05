#pragma once


#include <AllegroFlare/LoadASavedGame/SaveSlots/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace LoadASavedGame
   {
      namespace SaveSlots
      {
         class Empty : public AllegroFlare::LoadASavedGame::SaveSlots::Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/LoadASavedGame/SaveSlots/Empty";

         private:
            std::string property;

         protected:


         public:
            Empty(std::string property="[unset-property]");
            ~Empty();

            std::string get_property() const;
            bool property_is(std::string possible_type="");
         };
      }
   }
}



