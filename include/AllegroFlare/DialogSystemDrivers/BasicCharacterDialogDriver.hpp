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
         AllegroFlare::Elements::DialogRoll dialog_roll;

      protected:


      public:
         AllegroFlare::DialogSystem::CharacterStagingLayouts::Base* active_character_staging_layout;
         AllegroFlare::DialogSystem::CharacterRoster* character_roster;
         BasicCharacterDialogDriver();
         ~BasicCharacterDialogDriver();

         void set_dialog_roll(AllegroFlare::Elements::DialogRoll dialog_roll);
         AllegroFlare::Elements::DialogRoll get_dialog_roll() const;
         AllegroFlare::Elements::DialogRoll &get_dialog_roll_ref();
      };
   }
}



