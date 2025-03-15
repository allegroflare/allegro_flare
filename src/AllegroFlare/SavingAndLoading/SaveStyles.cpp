

#include <AllegroFlare/SavingAndLoading/SaveStyles.hpp>

#include <AllegroFlare/Logger.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace SavingAndLoading
{


SaveStyles::SaveStyles(AllegroFlare::SavingAndLoading::SaveStyles::StartStyle start_style, AllegroFlare::SavingAndLoading::SaveStyles::SaveStyle save_style, AllegroFlare::SavingAndLoading::SaveStyles::LoadStyle load_style)
   : start_style(start_style)
   , save_style(save_style)
   , load_style(load_style)
   , initialized(false)
{
}


SaveStyles::~SaveStyles()
{
}


void SaveStyles::set_start_style(AllegroFlare::SavingAndLoading::SaveStyles::StartStyle start_style)
{
   if (get_initialized()) throw std::runtime_error("[SaveStyles::set_start_style]: error: guard \"get_initialized()\" not met.");
   this->start_style = start_style;
}


void SaveStyles::set_save_style(AllegroFlare::SavingAndLoading::SaveStyles::SaveStyle save_style)
{
   if (get_initialized()) throw std::runtime_error("[SaveStyles::set_save_style]: error: guard \"get_initialized()\" not met.");
   this->save_style = save_style;
}


void SaveStyles::set_load_style(AllegroFlare::SavingAndLoading::SaveStyles::LoadStyle load_style)
{
   if (get_initialized()) throw std::runtime_error("[SaveStyles::set_load_style]: error: guard \"get_initialized()\" not met.");
   this->load_style = load_style;
}


AllegroFlare::SavingAndLoading::SaveStyles::StartStyle SaveStyles::get_start_style() const
{
   return start_style;
}


AllegroFlare::SavingAndLoading::SaveStyles::SaveStyle SaveStyles::get_save_style() const
{
   return save_style;
}


AllegroFlare::SavingAndLoading::SaveStyles::LoadStyle SaveStyles::get_load_style() const
{
   return load_style;
}


bool SaveStyles::get_initialized() const
{
   return initialized;
}


void SaveStyles::initialize()
{
   if (!((start_style != StartStyle::GAME_START_STYLE_UNDEF)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::SaveStyles::initialize]: error: guard \"(start_style != StartStyle::GAME_START_STYLE_UNDEF)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::SaveStyles::initialize]: error: guard \"(start_style != StartStyle::GAME_START_STYLE_UNDEF)\" not met");
   }
   if (!((save_style != SaveStyle::GAME_SAVE_STYLE_UNDEF)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::SaveStyles::initialize]: error: guard \"(save_style != SaveStyle::GAME_SAVE_STYLE_UNDEF)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::SaveStyles::initialize]: error: guard \"(save_style != SaveStyle::GAME_SAVE_STYLE_UNDEF)\" not met");
   }
   if (!((load_style != LoadStyle::GAME_LOAD_STYLE_UNDEF)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::SaveStyles::initialize]: error: guard \"(load_style != LoadStyle::GAME_LOAD_STYLE_UNDEF)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::SaveStyles::initialize]: error: guard \"(load_style != LoadStyle::GAME_LOAD_STYLE_UNDEF)\" not met");
   }
   // TODO: Ensure valid combinations of styles
   initialized = true;
   return;
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
   // TODO: Review the correctness of the action names (should be constants, too) for each menu item.
   switch (start_style)
   {
      case StartStyle::GAME_START_STYLE_A: {
         return {
            { "Play", "goto_load_a_saved_game_screen" },
         };
      } break;

      case StartStyle::GAME_START_STYLE_B: { // 1 profile, 1 save. Save slot is never interacted with
         if (!infer_existing_save_data_exists())
         {
            return {
               { "Start new game", "start_new_game" },
            };
         }
         else
         {
            return {
               { "Continue",       "continue_from_last_save" },
               { "Start new game", "prompt_to_clear_existing_data_then_start_new_game" }, // TODO: Fulfill this
            };
         }
      } break;

      case StartStyle::GAME_START_STYLE_C: { // 1 profile, multiple saves. Saves are listed by time desc
         if (!infer_existing_save_data_exists())
         {
            return {
               { "Start new game", "start_new_game" }
            };
         }
         else
         {
            return {
               { "Continue",       "goto_load_a_saved_game_screen" },
               { "Start new game", "prompt_to_clear_existing_data_then_start_new_game" }, // TODO: Fulfill this
            };
         }
      } break;

      case StartStyle::GAME_START_STYLE_D: { // Tunic style
         if (!infer_existing_save_data_exists())
         {
            return {
               { "Start new game", "start_new_game" },
            };
         }
         else
         {
            return {
               { "Continue",  "load_most_recent_save_file_and_start_game" }, // TODO: Fulfill this
               { "New game",  "[unset-action_name_for_new_game]" }, // NOTE: TODO: This option is contingent on there
                                                                    // being an available save slot. Review if this
                                                                    // is true
                                                                    // TODO: Fulfill this
               { "Load game", "[unset-action_name_for_load_game]" }, // TODO: Fulfill this
            };
         }
      } break;

      case StartStyle::GAME_START_STYLE_E: {
         if (!infer_existing_save_data_exists())
         {
            return {
               { "Start new game", "start_new_game" },
            };
         }
         else
         {
            return {
               { "Continue",  "load_most_recent_save_file_and_start_game" }, // TODO: Fulfill this
               { "New game",  "[unset-action_name_for_new_game]" }, // TODO: Fulfill this
               { "Load game", "[unset-action_name_for_load_game]" }, // TODO: Fulfill this
            };
         }
      } break;

      case StartStyle::GAME_START_STYLE_F: { // No real profies or save slots
         return {
            { "Start game", "start_new_game" },
            { "Enter passcode", "goto_enter_passcode_screen" },
         };
      } break;

      case StartStyle::GAME_START_STYLE_G: {
         return {
            { "Start game", "start_new_game" },
            { "Change profile", "goto_change_save_profile_screen" }, // TODO: Fulfill this
         };
      } break;

      default: {
         AllegroFlare::Logger::throw_error(THIS_CLASS_AND_METHOD_NAME,
            "Unexpected logic path to here (1). Please review."
         );
      } break;
   }

   AllegroFlare::Logger::throw_error(THIS_CLASS_AND_METHOD_NAME,
      "Unexpected logic path to here (2). Please review."
   );

   return {};

   //std::vector<std::pair<std::string, std::string>> game_start_options = {



      // Start style A (Metroid Prime):
      //{ "Play",              "goto_load_a_saved_game_screen" },



      // Start style B (Fade to White) (with no saves)
      //{ "Start new game",    "..." },

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



   //};
   //return game_start_options;
}

bool SaveStyles::infer_existing_save_data_exists()
{
   return false; // TODO: Sort out this logic
}


} // namespace SavingAndLoading
} // namespace AllegroFlare


