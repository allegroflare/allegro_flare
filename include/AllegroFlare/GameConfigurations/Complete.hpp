#pragma once


#include <AllegroFlare/Achievement.hpp>
#include <AllegroFlare/DialogTree/NodeBank.hpp>
#include <AllegroFlare/Elements/Backgrounds/Base.hpp>
#include <AllegroFlare/Elements/RollingCredits/Sections/Base.hpp>
#include <AllegroFlare/Elements/StoryboardPages/Base.hpp>
#include <AllegroFlare/GameEvent.hpp>
#include <AllegroFlare/GameSession.hpp>
#include <AllegroFlare/Levels/Base.hpp>
#include <AllegroFlare/LoadASavedGame/SaveSlots/Base.hpp>
#include <ReleaseInfo.hpp>
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
         virtual void handle_game_event(AllegroFlare::GameEvent* game_event=nullptr);
         virtual AllegroFlare::Levels::Base* load_level_by_identifier(std::string level_identifier="[unset-level_identifier]");
         virtual std::vector<std::pair<std::string, std::string>> build_level_list_for_level_select_screen_by_identifier(std::string identifier="[unset-identifier]");
         virtual AllegroFlare::DialogTree::NodeBank build_dialog_bank_by_identifier(std::string identifier="[unset-identifier]");
         virtual std::vector<std::tuple<std::string, AllegroFlare::Achievement*, bool, bool>> build_achievements();
         virtual std::vector<AllegroFlare::Elements::StoryboardPages::Base *> create_intro_logos_storyboard_pages();
         virtual AllegroFlare::Elements::Backgrounds::Base* create_shared_background();
         virtual std::vector<AllegroFlare::Elements::StoryboardPages::Base *> create_new_game_intro_storyboard_pages();
         virtual std::vector<AllegroFlare::Elements::StoryboardPages::Base *> create_intro_storyboard_pages();
         virtual std::vector<AllegroFlare::LoadASavedGame::SaveSlots::Base*> build_save_slots_for_load_screen();
         virtual void continue_from_last_save();
         virtual void setup_new_game_progress_and_state_info(AllegroFlare::GameSession* game_session=nullptr);
         virtual void load_last_played_session_or_start_new(AllegroFlare::GameSession* game_session=nullptr);
         virtual void load_audio_controller();
         virtual std::vector<std::pair<std::string, std::string>> build_title_screen_menu_options();
         virtual std::string build_copyright_text(ReleaseInfo* release_info=nullptr);
         virtual std::vector<AllegroFlare::Elements::RollingCredits::Sections::Base*> build_rolling_credits_sections();
         bool is_type(std::string possible_type="");
      };
   }
}



