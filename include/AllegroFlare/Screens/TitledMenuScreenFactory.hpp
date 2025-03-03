#pragma once


#include <AllegroFlare/Screens/TitledMenuScreen.hpp>
#include <string>


namespace AllegroFlare
{
   namespace Screens
   {
      class TitledMenuScreenFactory
      {
      public:
         static constexpr char* DEFAULT_DATA_FOLDER_PATH = (char*)"[unset-data_folder_path]";
         static constexpr char* RESUME_PAUSED_GAMEPLAY_EVENT_NAME = (char*)"resume_suspended_gameplay";
         static constexpr char* EXIT_TO_TITLE_SCREEN_EVENT_NAME = (char*)"exit_to_title_screen";

      private:

      protected:


      public:
         TitledMenuScreenFactory();
         ~TitledMenuScreenFactory();

         static AllegroFlare::Screens::TitledMenuScreen* create_standard_pause_screen(std::string data_folder_path=DEFAULT_DATA_FOLDER_PATH, std::string footer_text_probably_game_name_and_version="");
         static AllegroFlare::Screens::TitledMenuScreen* create_standard_title_screen(std::string data_folder_path=DEFAULT_DATA_FOLDER_PATH, std::string game_title="", std::string footer_text_probably_copyright_game_name_and_version="");
         static AllegroFlare::Screens::TitledMenuScreen* create_standard_game_won_screen(std::string data_folder_path=DEFAULT_DATA_FOLDER_PATH, std::string title_text="YOU WIN");
         static AllegroFlare::Screens::TitledMenuScreen* create_standard_game_over_screen(std::string data_folder_path=DEFAULT_DATA_FOLDER_PATH);
      };
   }
}



