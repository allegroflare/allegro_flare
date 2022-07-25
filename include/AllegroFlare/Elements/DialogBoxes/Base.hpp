#pragma once


#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace DialogBoxes
      {
         class Base
         {
         private:
            std::string type;
            std::vector<std::string> pages;
            int current_page_num;
            bool finished;
            int num_revealed_characters;
            float created_at;

         public:
            Base(std::string type="Base", std::vector<std::string> pages={});
            virtual ~Base();

            void set_created_at(float created_at);
            std::string get_type();
            std::vector<std::string> get_pages();
            int get_current_page_num();
            bool get_finished();
            int get_num_revealed_characters();
            float get_created_at();
            void set_pages(std::vector<std::string> pages={});
            void reset();
            virtual void update();
            std::string get_current_page_text();
            bool next_page();
            int num_pages();
            bool has_no_pages();
            bool at_last_page();
            bool current_page_is_valid();
            bool is_type(std::string possible_type="");
            void reveal_all_characters();
         };
      }
   }
}



