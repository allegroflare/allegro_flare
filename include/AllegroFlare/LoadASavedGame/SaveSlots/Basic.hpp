#pragma once


#include <AllegroFlare/LoadASavedGame/SaveSlots/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace LoadASavedGame
   {
      namespace SaveSlots
      {
         class Basic : public AllegroFlare::LoadASavedGame::SaveSlots::Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/LoadASavedGame/SaveSlots/Basic";

         private:
            std::string property;

         protected:


         public:
            Basic(std::string property="[unset-property]");
            ~Basic();

            std::string get_property() const;
            bool property_is(std::string possible_type="");
         };
      }
   }
}



