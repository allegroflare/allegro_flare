#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/DialogSystem/CharacterRoster.hpp>
#include <AllegroFlare/DialogSystem/CharacterStagingLayouts/Base.hpp>
#include <AllegroFlare/DialogSystem/Characters/Basic.hpp>
#include <AllegroFlare/DialogSystem/DialogSystem.hpp>
#include <AllegroFlare/DialogSystem/Scene.hpp>
#include <AllegroFlare/DialogSystemDrivers/Base.hpp>
#include <AllegroFlare/DialogTree/Nodes/Base.hpp>
#include <AllegroFlare/Elements/DialogRoll.hpp>
#include <allegro5/allegro.h>
#include <functional>
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
         std::function<bool(AllegroFlare::DialogSystem::DialogSystem*, void*)> activate_dialog_node_type_unhandled_func;
         void* activate_dialog_node_type_unhandled_func_user_data;
         bool initialized;

      protected:


      public:
         AllegroFlare::DialogSystem::CharacterStagingLayouts::Base* active_character_staging_layout;
         AllegroFlare::DialogSystem::CharacterRoster* character_roster;
         AllegroFlare::DialogSystem::Scene* scene_index;
         BasicCharacterDialogDriver(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
         ~BasicCharacterDialogDriver();

         void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
         void set_dialog_roll(AllegroFlare::Elements::DialogRoll dialog_roll);
         void set_activate_dialog_node_type_unhandled_func(std::function<bool(AllegroFlare::DialogSystem::DialogSystem*, void*)> activate_dialog_node_type_unhandled_func);
         void set_activate_dialog_node_type_unhandled_func_user_data(void* activate_dialog_node_type_unhandled_func_user_data);
         AllegroFlare::Elements::DialogRoll get_dialog_roll() const;
         std::function<bool(AllegroFlare::DialogSystem::DialogSystem*, void*)> get_activate_dialog_node_type_unhandled_func() const;
         void* get_activate_dialog_node_type_unhandled_func_user_data() const;
         AllegroFlare::Elements::DialogRoll &get_dialog_roll_ref();
         void initialize();
         void destroy();
         void clear_character_staging_layout();
         bool activate_dialog_node_by_name_func(AllegroFlare::DialogSystem::DialogSystem* dialog_system=nullptr, std::string active_dialog_node_name="[unset-dialog_node_identifier]", AllegroFlare::DialogTree::Nodes::Base* active_dialog_node=nullptr, void* user_data=nullptr);
         void set_speaking_character_avatar(std::string speaking_character_identifier="[unset-speaking_character_identifier]", std::string speaking_character_expression="[unset-speaking_character_expression]");
         ALLEGRO_BITMAP* lookup_speaking_character_avatar(std::string speaking_character_identifier="[unset-speaking_character_identifier]", std::string speaking_character_expression="[unset-speaking_character_expression]");
         AllegroFlare::DialogSystem::Characters::Basic* find_character_by_identifier_as_Basic(std::string character_identifier="[unset-character_identifier]");
         void append_to_dialog_roll(std::string speaking_character="[unset-speaking_character]", std::string dialog="[unset-dialog]");
      };
   }
}



