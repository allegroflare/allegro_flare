

#include <AllegroFlare/GameConfigurations/Complete.hpp>

#include <AllegroFlare/Achievement.hpp>
#include <AllegroFlare/Elements/Backgrounds/ClearToColor.hpp>
#include <AllegroFlare/Elements/Backgrounds/None.hpp>
#include <AllegroFlare/Elements/RollingCredits/SectionFactory.hpp>
#include <AllegroFlare/Elements/RollingCredits/Sections/Base.hpp>
#include <AllegroFlare/EventNames.hpp>
#include <AllegroFlare/GameEventDatas/AchievementUnlocked.hpp>
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
namespace GameConfigurations
{


Complete::Complete(std::string type, AllegroFlare::Runners::Complete* runner)
   : type(type)
   , runner(runner)
{
}


Complete::~Complete()
{
}


void Complete::set_runner(AllegroFlare::Runners::Complete* runner)
{
   this->runner = runner;
}


std::string Complete::get_type() const
{
   return type;
}


AllegroFlare::Runners::Complete* Complete::get_runner() const
{
   return runner;
}


std::string Complete::app_icon_1024_filename()
{
   return "icons/allegro-flare-generic-icon-1024.png";
}

std::string Complete::app_title()
{
   //return "Return of the Wanderer";
   return "Untitled Game";
}

std::string Complete::title_screen_title()
{
   return "Untitled Game";
}

std::string Complete::primary_display_icon_filename()
{
   return "icons/allegro-flare-generic-icon-1024.png";
}

void Complete::on_runner_after_initialization_func(AllegroFlare::Runners::Complete* runner)
{
   // TODO: Consider renaming this method to align with other methods
   return;
}

void Complete::before_activate_screen_callback(std::string screen_identifier_that_will_activate, std::string currently_active_screen_identifier)
{
   // TODO: Consider renaming this method to align with other methods

   //type: std::function<void(std::string, std::string, AllegroFlare::Routers::Base*, void*)>
   //init_with: '{}'
   //getter: true
   //setter: true
   //- name: on_before_activate_screen_func_user_data
     //type: void*
     //init_with: nullptr
     //getter: true
     //setter: true
   return;
}

void Complete::handle_game_event(AllegroFlare::GameEvent* game_event)
{
   // NOTE: Handle top-level game events here.
   // Some examples:

   // Handling a screen Activation
   // This (Change from one screen to another). You might do a foreground show or hide
   // event
   //if (game_event->is_type(AllegroFlare::GameEventDatas::ScreenActivated::NAME))
   //{
      //AllegroFlare::GameEventDatas::ScreenActivated* as =
        //static_cast<AllegroFlare::GameEventDatas::ScreenActivated*>(game_event->get_data());

      //// TODO: Handle game-specific logic for a after a screen switch
   //}

   // Handling an Achievement
   // Achievement notification are handled by the framework, but you might trigger an auto-save if your game
   // has a save system setup.
   if (game_event->get_type() == AllegroFlare::GameEventDatas::AchievementUnlocked::NAME)
   {
      if (game_event->get_data()->is_type(AllegroFlare::GameEventDatas::AchievementUnlocked::TYPE))
      {
         AllegroFlare::GameEventDatas::AchievementUnlocked *as =
            static_cast<AllegroFlare::GameEventDatas::AchievementUnlocked *>(game_event->get_data());
         // TODO: Handle saving progress of achievements. Something like below.
         // See this guide:
         // https://docs.google.com/document/d/1QdDVa6giZOmGbF61dgom1ZJ_Ev5OFvZEM2Bc453RjGw/edit
         //mark_achievement_as_unlocked(as->get_achievement_identifier());
         //save_game_progress_and_state_info();
      }
      else
      {
         throw std::runtime_error("Gameplay/Runner/game_event_func: unexpected AchievementUnlocked event data type");
      }
   }
   return;
}

AllegroFlare::Levels::Base* Complete::load_level_by_identifier(std::string level_identifier)
{
   // TODO: Add tests for this method or consider making it a pure virtual
   AllegroFlare::Logger::throw_error(
      "AllegroFlare::GameConfigurations::Base::load_level_by_identifier"
      "Not implemented in the base class. This method must be implemented in the derived class"
   );
   return nullptr;
}

std::vector<std::pair<std::string, std::string>> Complete::build_level_list_for_level_select_screen_by_identifier(std::string identifier)
{
   // TODO: Add tests for this method or consider making it a pure virtual
   AllegroFlare::Logger::throw_error(
      "AllegroFlare::GameConfigurations::Base::build_level_list_for_level_select_screen_by_identifier"
      "Not implemented in the base class. This method must be implemented in the derived class"
   );
   return {};
}

AllegroFlare::DialogTree::NodeBank Complete::build_dialog_bank_by_identifier(std::string identifier)
{
   // TODO: Add tests for this method or consider making it a pure virtual
   AllegroFlare::DialogTree::NodeBank node_bank;
   AllegroFlare::Logger::throw_error(
      "AllegroFlare::GameConfigurations::Base::build_dialog_bank_by_identifier",
      "Not implemented in the base class. This method must be implemented in the derived class"
   );
   return node_bank;
}

std::vector<std::tuple<std::string, AllegroFlare::Achievement*, bool, bool>> Complete::build_achievements()
{
   AllegroFlare::Logger::throw_error(
      "AllegroFlare::GameConfigurations::Base::build_achievements",
      "Not implemented in the base class. This method must be implemented in the derived class"
   );
   return {};
}

std::vector<AllegroFlare::Elements::StoryboardPages::Base *> Complete::create_intro_logos_storyboard_pages()
{
   AllegroFlare::Logger::throw_error(
      "AllegroFlare::GameConfigurations::Base::create_intro_logos_storyboard_pages",
      "Not implemented in the base class. This method must be implemented in the derived class"
   );
   //page_factory.create_clubcatt_logo_page(),
   //page_factory.create_image_page(bitmap_bin->operator[]("clubcatt-website-01.jpg")),
   return {};
}

AllegroFlare::Elements::Backgrounds::Base* Complete::create_shared_background()
{
   // TODO: Customize this
   return new AllegroFlare::Elements::Backgrounds::ClearToColor(ALLEGRO_COLOR{0, 0.05, 0.1, 1});
}

AllegroFlare::Elements::Backgrounds::Base* Complete::create_shared_foreground()
{
   // TODO: Customize this
   return new AllegroFlare::Elements::Backgrounds::None();
}

std::vector<AllegroFlare::Elements::StoryboardPages::Base *> Complete::create_new_game_intro_storyboard_pages()
{
   // Create a storyboard factory and page factory
   //AllegroFlare::StoryboardFactory storyboard_factory;
   //storyboard_factory.set_font_bin(font_bin);
   //storyboard_factory.set_event_emitter(event_emitter);
   //AllegroFlare::StoryboardPageFactory page_factory;
   //page_factory.set_font_bin(font_bin);
   //page_factory.set_bitmap_bin(bitmap_bin);
   //page_factory.set_model_bin(model_bin);

   //std::vector<AllegroFlare::Elements::StoryboardPages::Base *> result =
   //{
      //page_factory.create_advancing_text_page(
        //"In a land beset by darkness, a young hero embarks on a perilous journey to retrieve a powerful "
           //"artifact that can restore light to the kingdom."
      //),
      //page_factory.create_advancing_text_page(
        //"With nothing but a trusty sword and his wits to guide him, he sets out to face whatever dangers "
           //"lie ahead."
      //),
   //};
   //return result;
   return {};
}

AllegroFlare::Screens::Gameplay* Complete::create_primary_gameplay_screen(AllegroFlare::Runners::Complete* runner)
{
   // TODO: Consider alternatives to get "runner" dependency out of this class
   // TODO: Consider that "runner" is now a member of GameConfigurations/Complex and the runner assigns it
   // during initialization
   AllegroFlare::Logger::throw_error(
      "AllegroFlare::GameConfigurations::Complete::create_primary_gameplay_screen",
      "Not implemented in the base class. This method must be implemented in the derived class"
   );
   //primary_gameplay_screen.set_event_emitter(event_emitter);
   //primary_gameplay_screen.set_bitmap_bin(bitmap_bin);
   //primary_gameplay_screen.set_font_bin(font_bin);
   //primary_gameplay_screen.set_model_bin(model_bin);
   //primary_gameplay_screen.set_game_configuration(game_configuration); // TODO: Consider how to remove this dependency
   //primary_gameplay_screen.initialize();
   return nullptr;
}

void Complete::handle_primary_gameplay_screen_paused()
{
   // NOTE: Implementation to be managed by the derived class
   AllegroFlare::Logger::throw_error(
      "AllegroFlare::GameConfigurations::Base::handle_primary_gameplay_screen_paused"
      "Not implemented in the base class. This method must be implemented in the derived class"
   );
   // NOTE: Typically:
   // TODO: Consider if game is already paused or not
   // // guards: [ primary_gameplay_screen ]
   // primary_gameplay_screen->suspend_gameplay();
   //router->emit_route_event(
      //AllegroFlare::Routers::Standard::EVENT_ACTIVATE_SUBSCREEN_SCREEN,
      //nullptr,
      //al_get_time()
   //);
   return;
}

void Complete::handle_primary_gameplay_screen_unpaused()
{
   // NOTE: Implementation to be managed by the derived class
   AllegroFlare::Logger::throw_error(
      "AllegroFlare::GameConfigurations::Base::handle_primary_gameplay_screen_unpaused"
      "Not implemented in the base class. This method must be implemented in the derived class"
   );
   // NOTE: Typically:
   // TODO: Consider if game is already unpaused or not
   // // guards: [ primary_gameplay_screen ]
   // primary_gameplay_screen->resume_suspend_gameplay();
   //router->emit_route_event(
      //AllegroFlare::Routers::Standard::EVENT_ACTIVATE_PRIMARY_GAMEPLAY_SCREEN,
      //nullptr,
      //al_get_time()
   //);
   return;
}

void Complete::handle_primary_gameplay_screen_finished()
{
   AllegroFlare::Logger::throw_error(
      "AllegroFlare::GameConfigurations::Base::handle_primary_gameplay_screen_finished"
      "Not implemented in the base class. This method must be implemented in the derived class"
   );
   // NOTE: Typically:
   //router->emit_route_event(
      //AllegroFlare::Routers::Standard::EVENT_ACTIVATE_LEVEL_SELECT_SCREEN,
      //nullptr,
      //al_get_time()
   //);
   return;
}

AllegroFlare::Screens::Subscreen::Screen* Complete::create_primary_gameplay_subscreen(AllegroFlare::Runners::Complete* runner)
{
   AllegroFlare::Logger::throw_error(
      "AllegroFlare::GameConfigurations::Base::create_primary_gameplay_subscreen"
      "Not implemented in the base class. This method must be implemented in the derived class"
   );
   return nullptr;
}

AllegroFlare::Screens::PauseScreen* Complete::create_pause_screen(AllegroFlare::Runners::Complete* runner)
{
   AllegroFlare::Logger::throw_error(
      "AllegroFlare::GameConfigurations::Base::create_pause_screen"
      "Not implemented in the base class. This method must be implemented in the derived class"
   );
   return nullptr;
}

void Complete::handle_arbitrary_storyboard_screen_finished()
{
   AllegroFlare::Logger::throw_error(
      "AllegroFlare::GameConfigurations::Base::handle_arbitrary_storyboard_screen_finished"
      "Not implemented in the base class. This method must be implemented in the derived class"
   );
   // NOTE: Typically:
   //router->emit_route_event(
      //AllegroFlare::Routers::Standard::EVENT_ACTIVATE_LEVEL_SELECT_SCREEN,
      //nullptr,
      //al_get_time()
   //);
   return;
}

std::vector<AllegroFlare::Elements::StoryboardPages::Base *> Complete::create_arbitrary_storyboard_pages_by_identifier(std::string identifier)
{
   AllegroFlare::Logger::throw_error(
      "AllegroFlare::GameConfigurations::Base::create_arbitrary_storyboard_pages_by_identifier",
      "Not implemented in the base class. This method must be implemented in the derived class"
   );
   //AllegroFlare::StoryboardPageFactory page_factory;
   //page_factory.set_font_bin(font_bin);
   //page_factory.set_bitmap_bin(bitmap_bin);
   //page_factory.set_model_bin(model_bin);

   //std::vector<AllegroFlare::Elements::StoryboardPages::Base *> result =
   //{
      //page_factory.create_image_with_advancing_text_page(
         //"storyboard-1-01-1165x500.png",
         //"Once upon a time, in a magical kingdom ruled by a wise and just queen, a young hero sets out on a "
            //"journey to prove himself and save his people from a terrible curse."
      //),
      //page_factory.create_image_with_advancing_text_page(
         //"storyboard-2-01-1165x500.png",
         //"With the help of his trusty sidekick and a band of unlikely allies, he must navigate treacherous "
            //"terrain and battle fierce foes."
      //),
      //page_factory.create_advancing_text_page(
        //"And achieve his goal to save the kingdom."
      //),
   //};
   return {};
}

std::vector<AllegroFlare::Elements::StoryboardPages::Base *> Complete::create_intro_storyboard_pages()
{
   AllegroFlare::Logger::throw_error(
      "AllegroFlare::GameConfigurations::Base::create_intro_storyboard_pages",
      "Not implemented in the base class. This method must be implemented in the derived class"
   );
   //AllegroFlare::StoryboardPageFactory page_factory;
   //page_factory.set_font_bin(font_bin);
   //page_factory.set_bitmap_bin(bitmap_bin);
   //page_factory.set_model_bin(model_bin);

   //std::vector<AllegroFlare::Elements::StoryboardPages::Base *> result =
   //{
      //page_factory.create_image_with_advancing_text_page(
         //"storyboard-1-01-1165x500.png",
         //"Once upon a time, in a magical kingdom ruled by a wise and just queen, a young hero sets out on a "
            //"journey to prove himself and save his people from a terrible curse."
      //),
      //page_factory.create_image_with_advancing_text_page(
         //"storyboard-2-01-1165x500.png",
         //"With the help of his trusty sidekick and a band of unlikely allies, he must navigate treacherous "
            //"terrain and battle fierce foes."
      //),
      //page_factory.create_advancing_text_page(
        //"And achieve his goal to save the kingdom."
      //),
   //};
   return {};
}

std::vector<AllegroFlare::LoadASavedGame::SaveSlots::Base*> Complete::build_save_slots_for_load_a_saved_game_screen()
{
   /*
   std::vector<AllegroFlare::LoadASavedGame::SaveSlots::Base*> result = {
      new AllegroFlare::LoadASavedGame::SaveSlots::Empty(), // TODO: Fill this list with items from save file
      new AllegroFlare::LoadASavedGame::SaveSlots::Empty(),
      new AllegroFlare::LoadASavedGame::SaveSlots::Empty(),
   };
   return result;
   */
   return {};
}

void Complete::load_game_progress_and_state_info_into_universe()
{
   // TODO: This method
   return;
}

void Complete::save_game_progress_and_state_info(AllegroFlare::GameSession* game_session)
{
   if (!(game_session))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::GameConfigurations::Complete::save_game_progress_and_state_info]: error: guard \"game_session\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::GameConfigurations::Complete::save_game_progress_and_state_info]: error: guard \"game_session\" not met");
   }
   if (!(game_session->is_active()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::GameConfigurations::Complete::save_game_progress_and_state_info]: error: guard \"game_session->is_active()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::GameConfigurations::Complete::save_game_progress_and_state_info]: error: guard \"game_session->is_active()\" not met");
   }
   if (!(game_session->get_game_progress_and_state_info()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::GameConfigurations::Complete::save_game_progress_and_state_info]: error: guard \"game_session->get_game_progress_and_state_info()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::GameConfigurations::Complete::save_game_progress_and_state_info]: error: guard \"game_session->get_game_progress_and_state_info()\" not met");
   }
   // NOTE: Not sure if this is an appropriate design to put this method here
   AllegroFlare::Logger::throw_error(
      "AllegroFlare::GameConfigurations::Base::save_game_progress_and_state_info",
      "Not implemented in the base class. This method must be implemented in the derived class"
   );
   return;
}

void Complete::load_game_progress_and_state_info(AllegroFlare::GameSession* game_session)
{
   if (!(game_session))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::GameConfigurations::Complete::load_game_progress_and_state_info]: error: guard \"game_session\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::GameConfigurations::Complete::load_game_progress_and_state_info]: error: guard \"game_session\" not met");
   }
   if (!(game_session->get_game_progress_and_state_info()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::GameConfigurations::Complete::load_game_progress_and_state_info]: error: guard \"game_session->get_game_progress_and_state_info()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::GameConfigurations::Complete::load_game_progress_and_state_info]: error: guard \"game_session->get_game_progress_and_state_info()\" not met");
   }
   // NOTE: Not sure if this is an appropriate design to put this method here
   // TODO: Should "game_session->is_active" be a guard here?
   //std::string save_file_content = AllegroFlare::php::file_get_contents(save_state_filename);
   //game_session->get_game_progress_and_state_info()->import_from_string(save_file_content);
   return;
}

void Complete::setup_new_game_progress_and_state_info(AllegroFlare::GameSession* game_session)
{
   if (!(game_session))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::GameConfigurations::Complete::setup_new_game_progress_and_state_info]: error: guard \"game_session\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::GameConfigurations::Complete::setup_new_game_progress_and_state_info]: error: guard \"game_session\" not met");
   }
   // TODO: This method
   AllegroFlare::Logger::throw_error(
      "AllegroFlare::GameConfigurations::Base::setup_new_game_progress_and_state_info",
      "Not implemented in the base class. This method must be implemented in the derived class"
   );
   //AllegroFlare::GameProgressAndStateInfos::Base *game_progress_and_state_info =
     //game_session->get_game_progress_and_state_info();
   return;
}

void Complete::load_last_played_session_or_start_new(AllegroFlare::GameSession* game_session)
{
   if (!(game_session))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::GameConfigurations::Complete::load_last_played_session_or_start_new]: error: guard \"game_session\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::GameConfigurations::Complete::load_last_played_session_or_start_new]: error: guard \"game_session\" not met");
   }
   // TODO: This method
   AllegroFlare::Logger::throw_error(
      "AllegroFlare::GameConfigurations::Base::load_last_played_session_or_start_new",
      "Not implemented in the base class. This method must be implemented in the derived class"
   );
   //AllegroFlare::GameProgressAndStateInfos::Base *game_progress_and_state_info =
     //game_session->get_game_progress_and_state_info();
   return;
}

void Complete::load_audio_controller(AllegroFlare::AudioController* audio_controller)
{
   AllegroFlare::Logger::throw_error(
      "AllegroFlare::GameConfigurations::Base::load_audio_controller",
      "Not implemented in the base class. This method must be implemented in the derived class"
   );
   //AllegroFlare::AudioController &audio_controller = framework->get_audio_controller_ref();
   //audio_controller.set_and_load_sound_effect_elements({
      //// { "menu_move", { "menu_move_tink-02.ogg", false, "restart" } }, // TODO: Throw on an unknown replay type
   //});
   //audio_controller.set_and_load_music_track_elements({
      //// An example of how to load a music track:
      ////{ "intro_music", { "wanderer-01.ogg", true, "ignore" } },
   //});
   //// An example of how to play a music track:
   //// event_emitter->emit_play_music_track_event("intro_music");
   return;
}

std::vector<std::pair<std::string, std::string>> Complete::build_title_screen_menu_options()
{
   AllegroFlare::Logger::throw_error(
      "AllegroFlare::GameConfigurations::Base::build_title_screen_menu_options",
      "Not implemented in the base class. This method must be implemented in the derived class"
   );
   std::vector<std::pair<std::string, std::string>> options = {
      //{ "Continue",          "continue_from_last_save" },       // TODO: If game session is saved and valid
      //{ "Load a Saved Game", "goto_load_a_saved_game_screen" }, // TODO: If game session is saved and valid,
                                                                // and the game supports save slots
      //{ "Start New Game",    "start_new_game" },                // TODO: If the game session has not begun
      //{ "Achievements",      "goto_achievements_screen" },
      //{ "Settings",          "goto_settings_screen" },
      //{ "Version",           "goto_version_screen" },
      //{ "Credits",           "goto_credits_screen" },           // TODO: If game has been won
      //{ "Quit",              "quit" },
   };
   return options;
}

std::string Complete::build_copyright_text(ReleaseInfo* release_info)
{
   if (!(release_info))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::GameConfigurations::Complete::build_copyright_text]: error: guard \"release_info\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::GameConfigurations::Complete::build_copyright_text]: error: guard \"release_info\" not met");
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

std::vector<AllegroFlare::Elements::RollingCredits::Sections::Base*> Complete::build_rolling_credits_sections()
{
   /*
   AllegroFlare::Elements::RollingCredits::SectionFactory section_factory;
   std::vector<AllegroFlare::Elements::RollingCredits::Sections::Base*> result = {
      section_factory.create_spacer(),

      section_factory.create_text(
         "A game by Mark Oates"
      ),

      //section_factory.create_spacer(),

      //section_factory.create_text(
         //"KrampusHack 2024\nhttps://tins.amarillion.org/krampu23"
      //),

      section_factory.create_section_spacer(),

      section_factory.create_header("Programming"),
      section_factory.create_column_with_labels({
         { "Made with", "Allegro (5.2.9)" },
         {          "", "https://liballeg.org/" },
         //{          "", "by Allegro Developers" },
         { "Framework", "AllegroFlare (0.8.11-wip)" },
         {          "", "https://github.com/allegroflare/allegro_flare" },
         {          "", "by Mark Oates" },
      }),

      section_factory.create_section_spacer(),

      section_factory.create_header("People who have contributed code to Allegro 5"),
      section_factory.create_allegro5_contributors_list(3),

      section_factory.create_section_spacer(),
   //});
   //std::vector<AllegroFlare::Elements::RollingCredits::Sections::Base*> result = {
   };
   // TODO: Append disclaimers
   rolling_credits_screen.append_sections(section_factory.create_standard_disclaimers_text());
   return result;
   */

   AllegroFlare::Elements::RollingCredits::SectionFactory section_factory;
   std::vector<AllegroFlare::Elements::RollingCredits::Sections::Base*> result = {
      section_factory.create_spacer(),

      section_factory.create_text(
         "A game by Mark Oates"
      ),

      section_factory.create_spacer(),

      section_factory.create_text(
         "Thank you for playing."
      ),

   };
   //rolling_credits_screen.append_sections(section_factory.create_standard_disclaimers_text());
   return result;


   //return {};
}

bool Complete::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}


} // namespace GameConfigurations
} // namespace AllegroFlare


