#pragma once


#include <AllegroFlare/Elements/AdvancingText.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Base.hpp>
#include <AllegroFlare/Elements/ListBox.hpp>
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
            AllegroFlare::Elements::AdvancingText advancing_text;
            AllegroFlare::Elements::ListBox breakout_list_box;
            bool showing_breakout_list_box;
            bool initialized;
            bool has_valid_cursor_position();

         protected:


         public:
            Choice(std::string prompt="[prompt-question-not-set]", std::vector<std::pair<std::string, std::string>> options={});
            virtual ~Choice();

            int get_cursor_position() const;
            virtual void start() override;
            virtual void update() override;
            AllegroFlare::Elements::ListBox* get_breakout_list_box();
            void reveal_breakout_list_box();
            virtual void advance() override;
            void initialize();
            std::string get_prompt_full_text();
            std::string get_prompt_revealed_text();
            std::vector<std::pair<std::string, std::string>> get_options();
            std::vector<std::string> get_item_labels();
            std::string get_current_selection_text();
            std::string get_current_selection_value();
            virtual void move_cursor_position_down() override;
            virtual void move_cursor_position_up() override;
         };
      }
   }
}



