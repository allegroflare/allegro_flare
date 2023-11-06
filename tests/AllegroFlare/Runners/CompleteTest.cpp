
#include <gtest/gtest.h>

#include <AllegroFlare/Runners/Complete.hpp>


class MyGameConfiguration : public AllegroFlare::GameConfigurations::Complete
{
   virtual AllegroFlare::Levels::Base*
      load_level_by_identifier(std::string level_identifier="[unset-level_identifier]") override;
   //build_level_list_for_level_select_screen_by_identifier(std::string identifier="[unset-identifier]");
   //build_dialog_bank_by_identifier(std::string identifier="[unset-identifier]");
   //build_achievements();
   //create_intro_logos_storyboard_pages();
   //continue_from_last_save();
   //setup_new_game_progress_and_state_info(AllegroFlare::GameSession* game_session=nullptr);
   //load_last_played_session_or_start_new(AllegroFlare::GameSession* game_session=nullptr);
   //load_audio_controller();
   //build_title_screen_menu_options();

   // Consider
   //void configure_level_select_screen(AllegroFlare::LevelSelectScreen::Screen *level_select_screen=nullptr);
   //void configure_load_a_saved_game_screen(AllegroFlare::LoadASavedGame::Screen *load_a_saved_game_screen=nullptr);
};


TEST(AllegroFlare_Runners_CompleteTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Runners::Complete complete;
}


TEST(AllegroFlare_Runners_CompleteTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/Runners/Complete",
     AllegroFlare::Runners::Complete::TYPE
   );
}


TEST(AllegroFlare_Runners_CompleteTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Runners::Complete complete;
   EXPECT_EQ(AllegroFlare::Runners::Complete::TYPE, complete.get_type());
}


TEST(AllegroFlare_Runners_CompleteTest, run__will_work_as_expected)
{
   AllegroFlare::GameConfigurations::Complete *configuration = new AllegroFlare::GameConfigurations::Complete();
   // TODO: HERE: Make this run:
   //AllegroFlare::Runners::Complete::run(configuration, "test");
}



