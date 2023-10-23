#pragma once


#include <AllegroFlare/DialogSystem/CharacterRoster.hpp>
#include <AllegroFlare/DialogSystem/CharacterStagingLayouts/Base.hpp>
#include <AllegroFlare/DialogSystemDrivers/Base.hpp>
#include <AllegroFlare/Elements/DialogRoll.hpp>


namespace AllegroFlare
{
   namespace DialogSystemDrivers
   {
      class BasicCharacterDialogDriver : public AllegroFlare::DialogSystemDrivers::Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/DialogSystemDrivers/BasicCharacterDialogDriver";

      private:
         AllegroFlare::DialogSystem::CharacterRoster* character_roster;
         AllegroFlare::DialogSystem::CharacterStagingLayouts::Base* active_character_staging_layout;
         AllegroFlare::Elements::DialogRoll dialog_roll;

      protected:


      public:
         BasicCharacterDialogDriver(AllegroFlare::DialogSystem::CharacterRoster* character_roster=nullptr);
         ~BasicCharacterDialogDriver();

         void set_character_roster(AllegroFlare::DialogSystem::CharacterRoster* character_roster);
         void set_dialog_roll(AllegroFlare::Elements::DialogRoll dialog_roll);
         AllegroFlare::DialogSystem::CharacterRoster* get_character_roster() const;
         AllegroFlare::Elements::DialogRoll get_dialog_roll() const;
         AllegroFlare::Elements::DialogRoll &get_dialog_roll_ref();
      };
   }
}



