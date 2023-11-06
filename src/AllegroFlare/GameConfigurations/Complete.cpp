

#include <AllegroFlare/GameConfigurations/Complete.hpp>

#include <AllegroFlare/Achievement.hpp>
#include <AllegroFlare/GameProgressAndStateInfos/Base.hpp>
#include <AllegroFlare/Logger.hpp>
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
      "AllegroFlare::GameConfigurations::Base::create_intro_logos_storyboard_pagse",
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
      { "Continue",          "continue_from_last_save" },       // TODO: If game session is saved and valid
      { "Load a Saved Game", "goto_load_a_saved_game_screen" }, // TODO: If game session is saved and valid,
                                                                // and the game supports save slots
      { "Start New Game",    "start_new_game" },                // TODO: If the game session has not begun
      { "Achievements",      "goto_achievements_screen" },
      { "Settings",          "goto_settings_screen" },
      { "Version",           "goto_version_screen" },
      { "Credits",           "goto_credits_screen" },           // TODO: If game has been won
      { "Quit",              "quit" },
   };
   return options;
}

bool Complete::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}


} // namespace GameConfigurations
} // namespace AllegroFlare


