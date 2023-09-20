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
         public:
            static constexpr char* TYPE = (char*)"DialogBoxes/Choice";

         private:
            std::string prompt;
            std::vector<std::pair<std::string, std::string>> options;
            int cursor_position;
            bool initialized;
            bool has_valid_cursor_position();

         protected:


         public:
            Choice(std::string prompt="[prompt-question-not-set]", std::vector<std::pair<std::string, std::string>> options={});
            virtual ~Choice();

            int get_cursor_position() const;
            virtual void update() override;
            virtual void advance() override;
            void initialize();
            std::string get_prompt();
            std::vector<std::pair<std::string, std::string>> get_options();
            std::string get_current_selection_text();
            std::string get_current_selection_value();
            virtual void move_cursor_position_down() override;
            virtual void move_cursor_position_up() override;
         };
      }
   }
}



