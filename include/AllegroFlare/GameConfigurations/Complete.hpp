#pragma once


#include <AllegroFlare/Achievement.hpp>
#include <AllegroFlare/AudioController.hpp>
#include <AllegroFlare/DialogTree/NodeBank.hpp>
#include <AllegroFlare/Elements/Backgrounds/Base.hpp>
#include <AllegroFlare/Elements/RollingCredits/Sections/Base.hpp>
#include <AllegroFlare/Elements/StoryboardPages/Base.hpp>
#include <AllegroFlare/ForwardDeclarations/AllegroFlare/GameConfigurations/Complete.hpp>
#include <AllegroFlare/ForwardDeclarations/AllegroFlare/Runners/Complete.hpp>
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
   namespace GameConfigurations
   {
      class Complete
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/GameConfigurations/Complete";

      private:
         std::string type;
         AllegroFlare::Runners::Complete* runner;

      protected:


      public:
         Complete(std::string type=AllegroFlare::GameConfigurations::Complete::TYPE, AllegroFlare::Runners::Complete* runner=nullptr);
         virtual ~Complete();

         void set_runner(AllegroFlare::Runners::Complete* runner);
         std::string get_type() const;
         AllegroFlare::Runners::Complete* get_runner() const;
         virtual std::string app_icon_1024_filename();
         virtual std::string app_title();
         virtual std::string title_screen_title();
         virtual std::string primary_display_icon_filename();
         virtual void handle_game_event(AllegroFlare::GameEvent* game_event=nullptr);
         virtual AllegroFlare::Levels::Base* load_level_by_identifier(std::string level_identifier="[unset-level_identifier]");
         virtual std::vector<std::pair<std::string, std::string>> build_level_list_for_level_select_screen_by_identifier(std::string identifier="[unset-identifier]");
         virtual AllegroFlare::DialogTree::NodeBank build_dialog_bank_by_identifier(std::string identifier="[unset-identifier]");
         virtual std::vector<std::tuple<std::string, AllegroFlare::Achievement*, bool, bool>> build_achievements();
         virtual std::vector<AllegroFlare::Elements::StoryboardPages::Base *> create_intro_logos_storyboard_pages();
         virtual AllegroFlare::Elements::Backgrounds::Base* create_shared_background();
         virtual AllegroFlare::Elements::Backgrounds::Base* create_shared_foreground();
         virtual std::vector<AllegroFlare::Elements::StoryboardPages::Base *> create_new_game_intro_storyboard_pages();
         virtual AllegroFlare::Screens::Gameplay* create_primary_gameplay_screen(AllegroFlare::Runners::Complete* runner=nullptr);
         virtual void handle_primary_gameplay_screen_finished();
         virtual void handle_arbitrary_storyboard_screen_finished();
         virtual std::vector<AllegroFlare::Elements::StoryboardPages::Base *> create_arbitrary_storyboard_pages_by_identifier(std::string identifier="[unset-identifier]");
         virtual std::vector<AllegroFlare::Elements::StoryboardPages::Base *> create_intro_storyboard_pages();
         virtual std::vector<AllegroFlare::LoadASavedGame::SaveSlots::Base*> build_save_slots_for_load_a_saved_game_screen();
         virtual void load_game_progress_and_state_info_into_universe();
         virtual void save_game_progress_and_state_info(AllegroFlare::GameSession* game_session=nullptr);
         virtual void load_game_progress_and_state_info(AllegroFlare::GameSession* game_session=nullptr);
         virtual void setup_new_game_progress_and_state_info(AllegroFlare::GameSession* game_session=nullptr);
         virtual void load_last_played_session_or_start_new(AllegroFlare::GameSession* game_session=nullptr);
         virtual void load_audio_controller(AllegroFlare::AudioController* audio_controller=nullptr);
         virtual std::vector<std::pair<std::string, std::string>> build_title_screen_menu_options();
         virtual std::string build_copyright_text(ReleaseInfo* release_info=nullptr);
         virtual std::vector<AllegroFlare::Elements::RollingCredits::Sections::Base*> build_rolling_credits_sections();
         bool is_type(std::string possible_type="");
      };
   }
}



