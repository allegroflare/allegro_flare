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



