#pragma once


#include <AllegroFlare/DialogSystem/Characters/Basic.hpp>
#include <string>


namespace AllegroFlare
{
   namespace DialogSystem
   {
      class CharacterFactory
      {
      private:

      protected:


      public:
         CharacterFactory();
         ~CharacterFactory();

         AllegroFlare::DialogSystem::Characters::Basic* create_basic_character(std::string display_name="[unset-display_name]", std::string feature_description="[unset-feature_description]", std::string avatar_thumbnail_identifier="[unset-avatar_thumbnail_identifier]", std::string avatar_portrait_identifier="[unset-avatar_portrait_identifier]");
      };
   }
}



