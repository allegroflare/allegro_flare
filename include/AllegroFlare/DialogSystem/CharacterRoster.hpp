#pragma once


#include <AllegroFlare/DialogSystem/Characters/Base.hpp>
#include <map>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace DialogSystem
   {
      class CharacterRoster
      {
      private:
         std::map<std::string, AllegroFlare::DialogSystem::Characters::Base*> characters;

      protected:


      public:
         CharacterRoster();
         ~CharacterRoster();

         void set_characters(std::map<std::string, AllegroFlare::DialogSystem::Characters::Base*> characters);
         std::map<std::string, AllegroFlare::DialogSystem::Characters::Base*> &get_characters_ref();
         int num_characters();
         std::vector<std::string> get_character_names();
         void add_character(std::string name="[unset-name]", AllegroFlare::DialogSystem::Characters::Base* character=nullptr);
         bool character_exists_by_name(std::string name="[unset-name]");
         AllegroFlare::DialogSystem::Characters::Base* find_character_by_name(std::string name="[unset-name]");
      };
   }
}



