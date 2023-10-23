#pragma once


#include <AllegroFlare/DialogSystem/CharacterRoster.hpp>
#include <AllegroFlare/DialogSystem/CharacterStagingLayouts/Base.hpp>
#include <AllegroFlare/DialogSystem/DialogSystem.hpp>
#include <AllegroFlare/DialogSystemDrivers/Base.hpp>
#include <AllegroFlare/DialogTree/Nodes/Base.hpp>
#include <AllegroFlare/Elements/DialogRoll.hpp>
#include <string>


namespace AllegroFlare
{
   namespace DialogSystemDrivers
   {
      class BasicCharacterDialogDriver : public AllegroFlare::DialogSystemDrivers::Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/DialogSystemDrivers/BasicCharacterDialogDriver";

      private:
         AllegroFlare::Elements::DialogRoll dialog_roll;
         bool initialized;

      protected:


      public:
         AllegroFlare::DialogSystem::CharacterStagingLayouts::Base* active_character_staging_layout;
         AllegroFlare::DialogSystem::CharacterRoster* character_roster;
         BasicCharacterDialogDriver();
         ~BasicCharacterDialogDriver();

         void set_dialog_roll(AllegroFlare::Elements::DialogRoll dialog_roll);
         AllegroFlare::Elements::DialogRoll get_dialog_roll() const;
         AllegroFlare::Elements::DialogRoll &get_dialog_roll_ref();
         void initialize();
         void destroy();
         void clear_character_staging_layout();
         bool activate_dialog_node_by_name_func(AllegroFlare::DialogSystem::DialogSystem* dialog_system=nullptr, std::string active_dialog_node_name="[unset-dialog_node_identifier]", AllegroFlare::DialogTree::Nodes::Base* active_dialog_node=nullptr, void* user_data=nullptr);
         void append_to_dialog_roll(std::string speaking_character="[unset-speaking_character]", std::string dialog="[unset-dialog]");
      };
   }
}



