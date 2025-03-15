

#include <AllegroFlare/SavingAndLoading/SaveStyles.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace SavingAndLoading
{


SaveStyles::SaveStyles()
   : game_start_style(AllegroFlare::SavingAndLoading::SaveStyles::StartStyle::GAME_START_STYLE_UNDEF)
   , in_game_save_style(AllegroFlare::SavingAndLoading::SaveStyles::SaveStyle::GAME_SAVE_STYLE_UNDEF)
   , in_game_load_style(AllegroFlare::SavingAndLoading::SaveStyles::LoadStyle::GAME_LOAD_STYLE_UNDEF)
   , initialized(false)
{
}


SaveStyles::~SaveStyles()
{
}


void SaveStyles::set_game_start_style(AllegroFlare::SavingAndLoading::SaveStyles::StartStyle game_start_style)
{
   if (get_initialized()) throw std::runtime_error("[SaveStyles::set_game_start_style]: error: guard \"get_initialized()\" not met.");
   this->game_start_style = game_start_style;
}


void SaveStyles::set_in_game_save_style(AllegroFlare::SavingAndLoading::SaveStyles::SaveStyle in_game_save_style)
{
   if (get_initialized()) throw std::runtime_error("[SaveStyles::set_in_game_save_style]: error: guard \"get_initialized()\" not met.");
   this->in_game_save_style = in_game_save_style;
}


void SaveStyles::set_in_game_load_style(AllegroFlare::SavingAndLoading::SaveStyles::LoadStyle in_game_load_style)
{
   if (get_initialized()) throw std::runtime_error("[SaveStyles::set_in_game_load_style]: error: guard \"get_initialized()\" not met.");
   this->in_game_load_style = in_game_load_style;
}


AllegroFlare::SavingAndLoading::SaveStyles::StartStyle SaveStyles::get_game_start_style() const
{
   return game_start_style;
}


AllegroFlare::SavingAndLoading::SaveStyles::SaveStyle SaveStyles::get_in_game_save_style() const
{
   return in_game_save_style;
}


AllegroFlare::SavingAndLoading::SaveStyles::LoadStyle SaveStyles::get_in_game_load_style() const
{
   return in_game_load_style;
}


bool SaveStyles::get_initialized() const
{
   return initialized;
}


std::vector<std::pair<std::string, std::string>> SaveStyles::obtain_context_sensitive_menu_items_for_starting_or_loading_the_game()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::SaveStyles::obtain_context_sensitive_menu_items_for_starting_or_loading_the_game]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::SaveStyles::obtain_context_sensitive_menu_items_for_starting_or_loading_the_game]: error: guard \"initialized\" not met");
   }
   std::vector<std::pair<std::string, std::string>> game_start_options = {



      // Start style A (Metroid Prime):
      //{ "Play",              "goto_load_a_saved_game_screen" },



      // Start style B (Fade to White) (with no saves)
      //{ "Start new game",    "continue_from_last_save" },

      // Start style B (Fade to White) (with existing saves)
      //{ "Continue",          "..." }, // Loads the most recent save, Will advance to wherever the game wants
      //{ "Start new game",    "..." }, // Will prompt to erase all save data



      // Start style C (Zelda:BOTW) (with no saves)
      //{ "Start new game",    "..." },

      // Start style C (Zelda:BOTW) (with existing saves)
      //{ "Continue",          "..." }, // Will advance to the load_a_saved_game_screen (with list of recent saves)
      //{ "Start new game",    "..." }, // Will prompt to erase all save data



      // Start style D (Tunic) (with no saves) (This is the same as Start Style A, but with convenience),
                                               // Tunic has up to 10 save slots
      //{ "Start new game",    "..." },

      // Start style D (Tunic) (with existing saves)
      //{ "Continue",          "..." }, // Will load the most recent save, from the most recent profile
      //{ "New game",          "..." },
      //{ "Load game",         "..." },



      // Start style E (Final Fantasy), same as Start Style D, but there are many save slots



      // Start style F (Mega Man)
      //{ "Start game",        "..." },
      //{ "Enter passcode",    "..." },



      // Start style G (Signalis, Wolfenstein II: The New Colossus)
      //{ "Start game",        "..." }, // Will continue from last most recent save on this profile
      //{ "Change profile",    "..." },



   };
   return game_start_options;
}


} // namespace SavingAndLoading
} // namespace AllegroFlare


