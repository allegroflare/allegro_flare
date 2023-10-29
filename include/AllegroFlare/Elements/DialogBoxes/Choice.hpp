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
            std::string speaking_character;
            AllegroFlare::Elements::AdvancingText advancing_text;
            AllegroFlare::Elements::ListBox breakout_list_box;
            bool breakout_list_box_active;
            bool cursor_active;
            bool initialized;
            void reveal_breakout_list_box();
            bool has_valid_cursor_position();

         protected:


         public:
            Choice(std::string prompt="[prompt-question-not-set]", std::vector<std::pair<std::string, std::string>> options={});
            virtual ~Choice();

            void set_speaking_character(std::string speaking_character);
            std::string get_speaking_character() const;
            bool get_breakout_list_box_active() const;
            bool get_cursor_active() const;
            virtual void start() override;
            virtual void update() override;
            virtual void advance() override;
            void initialize();
            bool has_speaking_character();
            void set_prompt(std::string prompt="[unset-prompt]");
            void set_options(std::vector<std::pair<std::string, std::string>> options={});
            float infer_breakout_list_box_age();
            std::string get_prompt_full_text();
            std::string get_prompt_revealed_text();
            std::vector<std::pair<std::string, std::string>> get_options();
            std::vector<std::string> get_options_labels();
            std::string get_current_selection_text();
            std::string get_current_selection_value();
            virtual bool move_cursor_position_down() override;
            virtual bool move_cursor_position_up() override;
            void set_cursor_position(int cursor_position=0);
            int get_cursor_position();
         };
      }
   }
}



