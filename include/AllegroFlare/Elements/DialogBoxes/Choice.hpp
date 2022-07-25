#pragma once


#include <AllegroFlare/Elements/DialogBoxes/Base.hpp>
#include <string>
#include <utility>
#include <vector>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace DialogBoxes
      {
         class Choice : public AllegroFlare::Elements::DialogBoxes::Base
         {
         private:
            std::string prompt;
            std::vector<std::pair<std::string, std::string>> options;
            int cursor_position;
            bool initialized;

         public:
            Choice(std::string prompt="[prompt-question-not-set]", std::vector<std::pair<std::string, std::string>> options={});
            ~Choice();

            int get_cursor_position();
            void initialize();
            std::string get_prompt();
            std::vector<std::pair<std::string, std::string>> get_options();
            std::string get_current_selection_text();
            std::string get_current_selection_value();
            void move_cursor_position_down();
            void move_cursor_position_up();
            bool has_valid_cursor_position();
         };
      }
   }
}



