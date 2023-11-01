#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/DialogSystem/ChapterIndex.hpp>
#include <AllegroFlare/DialogSystem/CharacterRoster.hpp>
#include <AllegroFlare/DialogSystem/CharacterStagingLayouts/Base.hpp>
#include <AllegroFlare/DialogSystem/Characters/Basic.hpp>
#include <AllegroFlare/DialogSystem/SceneIndex.hpp>
#include <AllegroFlare/DialogSystemDrivers/Base.hpp>
#include <AllegroFlare/Elements/DialogRoll.hpp>
#include <allegro5/allegro.h>
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
         AllegroFlare::BitmapBin* bitmap_bin;
         AllegroFlare::Elements::DialogRoll dialog_roll;
         bool initialized;

      protected:


      public:
         AllegroFlare::DialogSystem::CharacterStagingLayouts::Base* active_character_staging_layout;
         AllegroFlare::DialogSystem::CharacterRoster* character_roster;
         AllegroFlare::DialogSystem::SceneIndex* scene_index;
         AllegroFlare::DialogSystem::ChapterIndex* chapter_index;
         BasicCharacterDialogDriver(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
         virtual ~BasicCharacterDialogDriver();

         void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
         void set_dialog_roll(AllegroFlare::Elements::DialogRoll dialog_roll);
         AllegroFlare::Elements::DialogRoll get_dialog_roll() const;
         AllegroFlare::Elements::DialogRoll &get_dialog_roll_ref();
         void initialize();
         void destroy();
         virtual void on_switch_in() override;
         virtual void on_deactivate() override;
         virtual void on_render() override;
         virtual std::string decorate_speaking_character_name(std::string speaking_character_identifier="[unset-speaking_character_identifier]") override;
         void clear_character_staging_layout();
         AllegroFlare::DialogSystem::Characters::Basic* find_character_by_identifier_as_Basic(std::string character_identifier="[unset-character_identifier]");
         ALLEGRO_BITMAP* lookup_speaking_character_avatar(std::string speaking_character_identifier="[unset-speaking_character_identifier]", std::string speaking_character_expression="[unset-speaking_character_expression]");
         void append_to_dialog_roll(std::string speaking_character="[unset-speaking_character]", std::string dialog="[unset-dialog]");
      };
   }
}



