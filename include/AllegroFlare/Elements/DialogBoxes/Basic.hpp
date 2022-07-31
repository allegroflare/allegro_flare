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
         private:
            std::vector<std::string> pages;
            int current_page_num;
            bool finished;
            int num_revealed_characters;
            float finished_at;
            bool page_finished;
            float page_finished_at;

         public:
            Basic(std::vector<std::string> pages={});
            virtual ~Basic();

            std::vector<std::string> get_pages();
            int get_current_page_num();
            bool get_finished();
            int get_num_revealed_characters();
            float get_finished_at();
            bool get_page_finished();
            float get_page_finished_at();
            virtual void update();
            void set_pages(std::vector<std::string> pages={});
            void reset();
            std::string get_current_page_text();
            int get_current_page_num_chars();
            bool advance();
            bool next_page();
            void reset_current_page_counters();
            int num_pages();
            bool has_no_pages();
            bool at_last_page();
            bool current_page_is_valid();
            void reveal_all_characters();
            bool all_characters_are_revealed();
         };
      }
   }
}



