

#include <AllegroFlare/Testing/GameConfigurations/Complete/SimpleConfiguration.hpp>

#include <AllegroFlare/Achievement.hpp>
#include <AllegroFlare/Elements/Backgrounds/ClearToColor.hpp>
#include <AllegroFlare/EventNames.hpp>
#include <AllegroFlare/GameEventDatas/ScreenActivated.hpp>
#include <AllegroFlare/GameProgressAndStateInfos/Base.hpp>
#include <AllegroFlare/Logger.hpp>
#include <AllegroFlare/TemplatedText.hpp>
#include <AllegroFlare/UnicodeCharacters.hpp>
#include <ReleaseInfo.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Testing
{
namespace GameConfigurations
{
namespace Complete
{


SimpleConfiguration::SimpleConfiguration()
   : AllegroFlare::GameConfigurations::Complete(AllegroFlare::Testing::GameConfigurations::Complete::SimpleConfiguration::TYPE)
{
}


SimpleConfiguration::~SimpleConfiguration()
{
}


std::vector<std::pair<std::string, std::string>> SimpleConfiguration::build_title_screen_menu_options()
{
   std::vector<std::pair<std::string, std::string>> options = {
      { "Start New Game",    "start_new_game" },
      { "Display Settings",  "goto_display_settings_screen" },
      { "Quit",              "quit" },
   };
   return options;
}

void SimpleConfiguration::handle_game_event(AllegroFlare::GameEvent* game_event)
{
   return;
}

AllegroFlare::Levels::Base* SimpleConfiguration::load_level_by_identifier(std::string level_identifier)
{
   // TODO
   return nullptr;
}

std::vector<std::pair<std::string, std::string>> SimpleConfiguration::build_level_list_for_level_select_screen_by_identifier(std::string identifier)
{
   // TODO
   return {};
}

AllegroFlare::DialogTree::NodeBank SimpleConfiguration::build_dialog_bank_by_identifier(std::string identifier)
{
   // TODO
   AllegroFlare::DialogTree::NodeBank node_bank;
   return node_bank;
}

std::vector<std::tuple<std::string, AllegroFlare::Achievement*, bool, bool>> SimpleConfiguration::build_achievements()
{
   // TODO
   return {};
}

AllegroFlare::Screens::Gameplay* SimpleConfiguration::create_primary_gameplay_screen(AllegroFlare::Runners::Complete* runner)
{
   // 
     //default_argument_dependency_symbols:
       //- AllegroFlare::ForwardDeclarations::AllegroFlare::Runners::Complete
       //- AllegroFlare::ForwardDeclarations::AllegroFlare::GameConfigurations::Complete
   // TODO: Find a better alternative to creating a raw Screens::Gameplay
   return new AllegroFlare::Screens::Gameplay;
}

AllegroFlare::Screens::Subscreen::Screen* SimpleConfiguration::create_primary_gameplay_subscreen(AllegroFlare::Runners::Complete* runner)
{
   return new AllegroFlare::Screens::Subscreen::Screen; // TODO: Investigate if this result object is too
                                                        // "base class"y for this test class.
}

AllegroFlare::Screens::PauseScreen* SimpleConfiguration::create_pause_screen(AllegroFlare::Runners::Complete* runner)
{
   return new AllegroFlare::Screens::PauseScreen;
}

std::vector<AllegroFlare::Elements::StoryboardPages::Base *> SimpleConfiguration::create_intro_logos_storyboard_pages()
{
   return {};
}

AllegroFlare::Elements::Backgrounds::Base* SimpleConfiguration::create_shared_background()
{
   return new AllegroFlare::Elements::Backgrounds::ClearToColor(ALLEGRO_COLOR{0, 0.05, 0.1, 1});
}

std::vector<AllegroFlare::Elements::StoryboardPages::Base *> SimpleConfiguration::create_new_game_intro_storyboard_pages()
{
   return {};
}

std::vector<AllegroFlare::Elements::StoryboardPages::Base *> SimpleConfiguration::create_intro_storyboard_pages()
{
   return {};
}

std::vector<AllegroFlare::LoadASavedGame::SaveSlots::Base*> SimpleConfiguration::build_save_slots_for_load_a_saved_game_screen()
{
   return {};
}

void SimpleConfiguration::load_game_progress_and_state_info_into_universe()
{
   // Nothing to do
   return;
}

void SimpleConfiguration::setup_new_game_progress_and_state_info(AllegroFlare::GameSession* game_session)
{
   if (!(game_session))
   {
      std::stringstream error_message;
      error_message << "[SimpleConfiguration::setup_new_game_progress_and_state_info]: error: guard \"game_session\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SimpleConfiguration::setup_new_game_progress_and_state_info: error: guard \"game_session\" not met");
   }
   // Nothing to do
   return;
}

void SimpleConfiguration::load_last_played_session_or_start_new(AllegroFlare::GameSession* game_session)
{
   if (!(game_session))
   {
      std::stringstream error_message;
      error_message << "[SimpleConfiguration::load_last_played_session_or_start_new]: error: guard \"game_session\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SimpleConfiguration::load_last_played_session_or_start_new: error: guard \"game_session\" not met");
   }
   // Nothing to do
   return;
}

void SimpleConfiguration::load_audio_controller(AllegroFlare::AudioController* audio_controller)
{
   // Nothing to do
   return;
}

std::string SimpleConfiguration::build_copyright_text(ReleaseInfo* release_info)
{
   if (!(release_info))
   {
      std::stringstream error_message;
      error_message << "[SimpleConfiguration::build_copyright_text]: error: guard \"release_info\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SimpleConfiguration::build_copyright_text: error: guard \"release_info\" not met");
   }
   AllegroFlare::TemplatedText templated_text(
      "[[COPYRIGHT_SYMBOL]] 2024 CLUBCATT Games         clubcatt.com         version [[VERSION_NUMBER]]",
      {
         { "[[COPYRIGHT_SYMBOL]]", AllegroFlare::UnicodeCharacters::COPYRIGHT_SYMBOL },
         { "[[VERSION_NUMBER]]",   release_info->get_version() },
      }
   );
   return templated_text.generate_content();
}

std::vector<AllegroFlare::Elements::RollingCredits::Sections::Base*> SimpleConfiguration::build_rolling_credits_sections()
{
   return {};
}

bool SimpleConfiguration::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}


} // namespace Complete
} // namespace GameConfigurations
} // namespace Testing
} // namespace AllegroFlare


