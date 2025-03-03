

#include <AllegroFlare/Screens/TitledMenuScreenFactory.hpp>

#include <AllegroFlare/Screens/TitledMenuScreen.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Screens
{


TitledMenuScreenFactory::TitledMenuScreenFactory()
{
}


TitledMenuScreenFactory::~TitledMenuScreenFactory()
{
}


AllegroFlare::Screens::TitledMenuScreen* TitledMenuScreenFactory::create_standard_pause_screen(std::string data_folder_path, std::string footer_text_probably_game_name_and_version)
{
   if (!((data_folder_path != DEFAULT_DATA_FOLDER_PATH)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::TitledMenuScreenFactory::create_standard_pause_screen]: error: guard \"(data_folder_path != DEFAULT_DATA_FOLDER_PATH)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::TitledMenuScreenFactory::create_standard_pause_screen]: error: guard \"(data_folder_path != DEFAULT_DATA_FOLDER_PATH)\" not met");
   }
   AllegroFlare::Screens::TitledMenuScreen* result = new AllegroFlare::Screens::TitledMenuScreen(data_folder_path);

   // Title
   result->set_title_text("PAUSED");

   // Footer
   result->set_footer_text(footer_text_probably_game_name_and_version);

   // Menus
   result->set_menu_options({
      { "Resume", "resume" },
      { "Exit to Title Screen", "exit_to_title_screen" },
   });
   result->set_show_triangle_cursor(true);

   // Pause screen menu should be usable instantly with no delay
   // TODO: Test this
   result->set_reveal_duration(0.0);

   // Unpausing should occour instantly
   // TODO: Test this
   result->set_menu_option_chosen_to_activation_delay(0.0);

   // Menu Font
   result->set_menu_font_name("RobotoCondensed-Regular.ttf");

   result->initialize();

   return result;
}

AllegroFlare::Screens::TitledMenuScreen* TitledMenuScreenFactory::create_standard_title_screen(std::string data_folder_path, std::string game_title, std::string footer_text_probably_copyright_game_name_and_version)
{
   if (!((data_folder_path != DEFAULT_DATA_FOLDER_PATH)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::TitledMenuScreenFactory::create_standard_title_screen]: error: guard \"(data_folder_path != DEFAULT_DATA_FOLDER_PATH)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::TitledMenuScreenFactory::create_standard_title_screen]: error: guard \"(data_folder_path != DEFAULT_DATA_FOLDER_PATH)\" not met");
   }
   AllegroFlare::Screens::TitledMenuScreen* result = new AllegroFlare::Screens::TitledMenuScreen(data_folder_path);

   // Title
   result->set_title_text(game_title);

   // Footer
   result->set_footer_text(footer_text_probably_copyright_game_name_and_version);

   // Menus
   result->set_menu_options({
      { "Start new game", "start_new_game" }, // NOTE: This value is a constant expected by Routers/Complete
      { "Credits", "goto_credits_screen" }, // NOTE: This value is a constant expected by Routers/Complete
      { "Exit", "quit" } // NOTE: This value is a constant expected by Routers/Complete
   });

   // Menu Font
   result->set_menu_font_name("RobotoCondensed-Regular.ttf");

   result->initialize();

   return result;
}

AllegroFlare::Screens::TitledMenuScreen* TitledMenuScreenFactory::create_standard_game_won_screen(std::string data_folder_path, std::string title_text)
{
   if (!((data_folder_path != DEFAULT_DATA_FOLDER_PATH)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::TitledMenuScreenFactory::create_standard_game_won_screen]: error: guard \"(data_folder_path != DEFAULT_DATA_FOLDER_PATH)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::TitledMenuScreenFactory::create_standard_game_won_screen]: error: guard \"(data_folder_path != DEFAULT_DATA_FOLDER_PATH)\" not met");
   }
   // Some options could be "YOU WIN", "GAME OVER", "THANK YOU FOR PLAYING"
   AllegroFlare::Screens::TitledMenuScreen* result = new AllegroFlare::Screens::TitledMenuScreen(data_folder_path);

   // Title
   result->set_title_text("YOU WIN");
   result->set_title_position_y(1080 / 14 * 6);

   // Footer
   result->set_footer_text(""); // Consider adding "clear_footer_text"

   // Menus
   result->clear_menu_options();

   // Empty state text
   //title_screen.set_upcase_empty_state_text(true);
   result->set_empty_state_text(""); // Consider adding "
   result->set_empty_state_text_font_name("RobotoCondensed-Regular.ttf");

   result->initialize();

   return result;
}

AllegroFlare::Screens::TitledMenuScreen* TitledMenuScreenFactory::create_standard_game_over_screen(std::string data_folder_path)
{
   if (!((data_folder_path != DEFAULT_DATA_FOLDER_PATH)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::TitledMenuScreenFactory::create_standard_game_over_screen]: error: guard \"(data_folder_path != DEFAULT_DATA_FOLDER_PATH)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::TitledMenuScreenFactory::create_standard_game_over_screen]: error: guard \"(data_folder_path != DEFAULT_DATA_FOLDER_PATH)\" not met");
   }
   AllegroFlare::Screens::TitledMenuScreen* result = new AllegroFlare::Screens::TitledMenuScreen(data_folder_path);

   // Title
   result->set_title_text("GAME OVER");

   // Footer
   result->set_footer_text(""); // Consider adding "clear_footer_text"

   // Menus
   result->clear_menu_options();

   // Empty state text
   result->set_upcase_empty_state_text(true);
   result->set_empty_state_text("Press any key to continue");
   result->set_empty_state_text_font_name("RobotoCondensed-Regular.ttf");

   result->initialize();

   return result;
}


} // namespace Screens
} // namespace AllegroFlare


