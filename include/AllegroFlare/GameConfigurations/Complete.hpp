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
#include <AllegroFlare/GameProgressAndStateInfos/Base.hpp>
#include <AllegroFlare/GameSession.hpp>
#include <AllegroFlare/Levels/Base.hpp>
#include <AllegroFlare/LoadASavedGame/SaveSlots/Base.hpp>
#include <AllegroFlare/Runners/Complete.hpp>
#include <AllegroFlare/SavingAndLoading/SavingAndLoading.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/Screens/Gameplay.hpp>
#include <AllegroFlare/Screens/Subscreen/Screen.hpp>
#include <ReleaseInfo.hpp>
#include <set>
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
         virtual int get_num_save_profiles();
         virtual int get_num_manual_save_slots();
         virtual int get_num_autosave_save_slots();
         virtual int get_num_quicksave_save_slots();
         virtual AllegroFlare::SavingAndLoading::SavingAndLoading::StartStyle get_saving_and_loading_start_style();
         virtual AllegroFlare::SavingAndLoading::SavingAndLoading::SaveStyle get_saving_and_loading_save_style();
         virtual AllegroFlare::SavingAndLoading::SavingAndLoading::LoadStyle get_saving_and_loading_load_style();
         virtual void on_runner_after_initialization_func(AllegroFlare::Runners::Complete* runner=nullptr);
         virtual void before_activate_screen_callback(std::string screen_identifier_that_will_activate="[unset-screen_identifier_that_will_activate]", std::string currently_active_screen_identifier="[unset-currently_active_screen_identifier]");
         virtual void handle_game_event(AllegroFlare::GameEvent* game_event=nullptr);
         virtual AllegroFlare::Levels::Base* load_level_by_identifier(std::string level_identifier="[unset-level_identifier]");
         virtual std::vector<std::pair<std::string, std::string>> build_level_list_for_level_select_screen_by_identifier(std::string identifier="[unset-identifier]");
         virtual std::set<std::string> build_locked_list_for_level_select_screen();
         virtual AllegroFlare::DialogTree::NodeBank build_dialog_bank_by_identifier(std::string identifier="[unset-identifier]");
         virtual std::vector<std::tuple<std::string, AllegroFlare::Achievement*, bool, bool>> build_achievements();
         virtual std::vector<AllegroFlare::Elements::StoryboardPages::Base *> create_intro_logos_storyboard_pages();
         virtual AllegroFlare::Elements::Backgrounds::Base* create_shared_background();
         virtual AllegroFlare::Elements::Backgrounds::Base* create_shared_foreground();
         virtual std::vector<AllegroFlare::Elements::StoryboardPages::Base *> create_new_game_intro_storyboard_pages();
         virtual AllegroFlare::Screens::Gameplay* create_primary_gameplay_screen(AllegroFlare::Runners::Complete* runner=nullptr);
         virtual void destroy_primary_gameplay_screen();
         virtual void handle_primary_gameplay_screen_paused();
         virtual void handle_primary_gameplay_screen_unpaused();
         virtual void handle_primary_gameplay_screen_finished();
         virtual AllegroFlare::Screens::Subscreen::Screen* create_primary_gameplay_subscreen(AllegroFlare::Runners::Complete* runner=nullptr);
         virtual AllegroFlare::Screens::Base* create_pause_screen(AllegroFlare::Runners::Complete* runner=nullptr);
         virtual void destroy_pause_screen();
         virtual void handle_arbitrary_storyboard_screen_finished();
         virtual std::vector<AllegroFlare::Elements::StoryboardPages::Base *> create_arbitrary_storyboard_pages_by_identifier(std::string identifier="[unset-identifier]");
         virtual std::vector<AllegroFlare::Elements::StoryboardPages::Base *> create_intro_storyboard_pages();
         virtual std::vector<AllegroFlare::LoadASavedGame::SaveSlots::Base*> build_save_slots_for_load_a_saved_game_screen();
         virtual void load_game_progress_and_state_info_into_universe();
         virtual void load_save_file_content_into_gameplay(std::string save_file_content="[unset-save_file_content]");
         virtual std::string build_save_file_content_for_current_game();
         virtual void handle_save_file_loading_finished();
         virtual void save_game_progress_and_state_info(AllegroFlare::GameSession* game_session=nullptr);
         virtual void load_game_progress_and_state_info(AllegroFlare::GameSession* game_session=nullptr);
         virtual void setup_new_game_progress_and_state_info_DEPRECATED(AllegroFlare::GameSession* game_session=nullptr);
         virtual AllegroFlare::GameProgressAndStateInfos::Base* create_game_progress_and_state_info_saver_loader();
         virtual void load_last_played_session_or_start_new(AllegroFlare::GameSession* game_session=nullptr);
         virtual void load_audio_controller(AllegroFlare::AudioController* audio_controller=nullptr);
         virtual std::vector<std::pair<std::string, std::string>> obtain_context_sensitive_menu_items_for_starting_or_loading_the_game();
         virtual std::vector<std::pair<std::string, std::string>> build_title_screen_menu_options();
         virtual std::string build_copyright_text(ReleaseInfo* release_info=nullptr);
         virtual std::vector<AllegroFlare::Elements::RollingCredits::Sections::Base*> build_rolling_credits_sections();
         bool is_type(std::string possible_type="");
      };
   }
}



