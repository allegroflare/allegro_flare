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
            static constexpr char* TYPE = "DialogBoxes/Basic";

         private:
            std::vector<std::string> pages;
            int current_page_num;
            bool finished;
            int num_revealed_characters;
            float finished_at;
            bool page_finished;
            float page_finished_at;
            bool current_page_is_valid();

         protected:


         public:
            Basic(std::vector<std::string> pages={});
            virtual ~Basic();

            std::vector<std::string> get_pages() const;
            int get_current_page_num() const;
            bool get_finished() const;
            int get_num_revealed_characters() const;
            float get_finished_at() const;
            bool get_page_finished() const;
            float get_page_finished_at() const;
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
            void reveal_all_characters();
            bool all_characters_are_revealed();
         };
      }
   }
}



