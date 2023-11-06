

#include <AllegroFlare/GameConfigurations/Complete.hpp>

#include <AllegroFlare/Achievement.hpp>
#include <AllegroFlare/Elements/Backgrounds/ClearToColor.hpp>
#include <AllegroFlare/Elements/RollingCredits/SectionFactory.hpp>
#include <AllegroFlare/Elements/RollingCredits/Sections/Base.hpp>
#include <AllegroFlare/GameProgressAndStateInfos/Base.hpp>
#include <AllegroFlare/Logger.hpp>
#include <ReleaseInfo.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace GameConfigurations
{


Complete::Complete(std::string type)
   : type(type)
{
}


Complete::~Complete()
{
}


std::string Complete::get_type() const
{
   return type;
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
   return new AllegroFlare::Elements::Backgrounds::ClearToColor(ALLEGRO_COLOR{0, 0.05, 0.1, 1});
}

std::vector<AllegroFlare::Elements::StoryboardPages::Base *> Complete::create_new_game_intro_storyboard_pages()
{
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

std::vector<AllegroFlare::LoadASavedGame::SaveSlots::Base*> Complete::build_save_slots_for_load_screen()
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

void Complete::continue_from_last_save()
{
   // TODO: This method
   return;
}

void Complete::setup_new_game_progress_and_state_info(AllegroFlare::GameSession* game_session)
{
   if (!(game_session))
   {
      std::stringstream error_message;
      error_message << "[Complete::setup_new_game_progress_and_state_info]: error: guard \"game_session\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Complete::setup_new_game_progress_and_state_info: error: guard \"game_session\" not met");
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
      error_message << "[Complete::load_last_played_session_or_start_new]: error: guard \"game_session\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Complete::load_last_played_session_or_start_new: error: guard \"game_session\" not met");
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

void Complete::load_audio_controller()
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
      error_message << "[Complete::build_copyright_text]: error: guard \"release_info\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Complete::build_copyright_text: error: guard \"release_info\" not met");
   }
   std::string text = "(c) 2023 CLUBCATT Games         clubcatt.com         version " + release_info->get_version();
   return text;
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

      section_factory.create_spacer(),

      section_factory.create_text(
         "KrampusHack 2023\nhttps://tins.amarillion.org/krampu23"
      ),

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
   //});
   //std::vector<AllegroFlare::Elements::RollingCredits::Sections::Base*> result = {
   };
   // TODO: Append disclaimers
   rolling_credits_screen.append_sections(section_factory.create_standard_disclaimers_text());
   return result;
   */
   return {};
}

bool Complete::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}


} // namespace GameConfigurations
} // namespace AllegroFlare


