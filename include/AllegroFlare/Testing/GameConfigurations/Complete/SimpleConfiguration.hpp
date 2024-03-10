#pragma once


#include <AllegroFlare/Achievement.hpp>
#include <AllegroFlare/AudioController.hpp>
#include <AllegroFlare/DialogTree/NodeBank.hpp>
#include <AllegroFlare/Elements/Backgrounds/Base.hpp>
#include <AllegroFlare/Elements/RollingCredits/Sections/Base.hpp>
#include <AllegroFlare/Elements/StoryboardPages/Base.hpp>
#include <AllegroFlare/GameConfigurations/Complete.hpp>
#include <AllegroFlare/GameEvent.hpp>
#include <AllegroFlare/GameSession.hpp>
#include <AllegroFlare/Levels/Base.hpp>
#include <AllegroFlare/LoadASavedGame/SaveSlots/Base.hpp>
#include <AllegroFlare/Runners/Complete.hpp>
#include <AllegroFlare/Screens/Gameplay.hpp>
#include <ReleaseInfo.hpp>
#include <string>
#include <tuple>
#include <utility>
#include <vector>


namespace AllegroFlare
{
   namespace Testing
   {
      namespace GameConfigurations
      {
         namespace Complete
         {
            class SimpleConfiguration : public AllegroFlare::GameConfigurations::Complete
            {
            public:
               static constexpr char* TYPE = (char*)"AllegroFlare/Testing/GameConfigurations/Complete/SimpleConfiguration";

            private:

            protected:


            public:
               SimpleConfiguration();
               virtual ~SimpleConfiguration();

               virtual std::vector<std::pair<std::string, std::string>> build_title_screen_menu_options() override;
               virtual void handle_game_event(AllegroFlare::GameEvent* game_event=nullptr) override;
               virtual AllegroFlare::Levels::Base* load_level_by_identifier(std::string level_identifier="[unset-level_identifier]") override;
               virtual std::vector<std::pair<std::string, std::string>> build_level_list_for_level_select_screen_by_identifier(std::string identifier="[unset-identifier]") override;
               virtual AllegroFlare::DialogTree::NodeBank build_dialog_bank_by_identifier(std::string identifier="[unset-identifier]") override;
               virtual std::vector<std::tuple<std::string, AllegroFlare::Achievement*, bool, bool>> build_achievements() override;
               virtual AllegroFlare::Screens::Gameplay* create_primary_gameplay_screen(AllegroFlare::Runners::Complete* runner=nullptr) override;
               virtual std::vector<AllegroFlare::Elements::StoryboardPages::Base *> create_intro_logos_storyboard_pages() override;
               virtual AllegroFlare::Elements::Backgrounds::Base* create_shared_background() override;
               virtual std::vector<AllegroFlare::Elements::StoryboardPages::Base *> create_new_game_intro_storyboard_pages() override;
               virtual std::vector<AllegroFlare::Elements::StoryboardPages::Base *> create_intro_storyboard_pages() override;
               virtual std::vector<AllegroFlare::LoadASavedGame::SaveSlots::Base*> build_save_slots_for_load_a_saved_game_screen() override;
               virtual void load_game_progress_and_state_info_into_universe() override;
               virtual void setup_new_game_progress_and_state_info(AllegroFlare::GameSession* game_session=nullptr) override;
               virtual void load_last_played_session_or_start_new(AllegroFlare::GameSession* game_session=nullptr) override;
               virtual void load_audio_controller(AllegroFlare::AudioController* audio_controller=nullptr) override;
               virtual std::string build_copyright_text(ReleaseInfo* release_info=nullptr) override;
               virtual std::vector<AllegroFlare::Elements::RollingCredits::Sections::Base*> build_rolling_credits_sections() override;
               bool is_type(std::string possible_type="");
            };
         }
      }
   }
}



