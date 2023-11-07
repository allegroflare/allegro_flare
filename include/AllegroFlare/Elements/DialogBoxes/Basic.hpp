#pragma once


#include <AllegroFlare/Elements/DialogBoxes/Base.hpp>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace DialogBoxes
      {
         class Basic : public AllegroFlare::Elements::DialogBoxes::Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/Elements/DialogBoxes/Basic";

         private:
            std::vector<std::string> pages;
            std::string speaking_character;
            int current_page_num;
            int num_revealed_characters;
            float finished_at;
            bool page_finished;
            float page_finished_at;
            bool current_page_is_valid();

         protected:


         public:
            Basic(std::vector<std::string> pages={});
            virtual ~Basic();

            void set_speaking_character(std::string speaking_character);
            std::vector<std::string> get_pages() const;
            std::string get_speaking_character() const;
            int get_current_page_num() const;
            int get_num_revealed_characters() const;
            float get_finished_at() const;
            bool get_page_finished() const;
            float get_page_finished_at() const;
            virtual void start() override;
            bool has_speaking_character();
            virtual void update() override;
            virtual void advance() override;
            void set_pages(std::vector<std::string> pages={});
            void reset();
            std::string get_current_page_text();
            int get_current_page_num_chars();
            bool next_page();
            void reset_current_page_counters();
            int num_pages();
            bool has_no_pages();
            bool at_last_page();
            void reveal_all_characters();
            bool all_characters_are_revealed();
         };
      }
   }
}



