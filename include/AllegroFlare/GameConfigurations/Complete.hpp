#pragma once


#include <AllegroFlare/Achievement.hpp>
#include <AllegroFlare/DialogTree/NodeBank.hpp>
#include <AllegroFlare/Elements/StoryboardPages/Base.hpp>
#include <AllegroFlare/GameSession.hpp>
#include <AllegroFlare/Levels/Base.hpp>
#include <string>
#include <tuple>
#include <utility>
#include <vector>


namespace AllegroFlare
{
   namespace GameConfigurations
   {
      class Complete
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/GameConfigurations/Complete";

      private:
         std::string type;

      protected:


      public:
         Complete(std::string type=AllegroFlare::GameConfigurations::Complete::TYPE);
         virtual ~Complete();

         std::string get_type() const;
         virtual AllegroFlare::Levels::Base* load_level_by_identifier(std::string level_identifier="[unset-level_identifier]");
         virtual std::vector<std::pair<std::string, std::string>> build_level_list_for_level_select_screen_by_identifier(std::string identifier="[unset-identifier]");
         virtual AllegroFlare::DialogTree::NodeBank build_dialog_bank_by_identifier(std::string identifier="[unset-identifier]");
         virtual std::vector<std::tuple<std::string, AllegroFlare::Achievement*, bool, bool>> build_achievements();
         virtual std::vector<AllegroFlare::Elements::StoryboardPages::Base *> create_intro_logos_storyboard_pages();
         void setup_new_game_progress_and_state_info(AllegroFlare::GameSession* game_session=nullptr);
         void load_last_played_session_or_start_new(AllegroFlare::GameSession* game_session=nullptr);
         void load_audio_controller();
         std::vector<std::pair<std::string, std::string>> build_title_screen_menu_options();
         bool is_type(std::string possible_type="");
      };
   }
}



