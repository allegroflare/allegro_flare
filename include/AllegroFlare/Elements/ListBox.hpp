#pragma once


#include <allegro5/allegro.h>
#include <string>
#include <utility>
#include <vector>


namespace AllegroFlare
{
   namespace Elements
   {
      class ListBox
      {
      private:
         std::vector<std::pair<std::string, std::string>> items;
         float created_at;
         int cursor_position;
         bool wrap_at_edges;

      protected:


      public:
         ListBox();
         ~ListBox();

         void set_created_at(float created_at);
         void set_wrap_at_edges(bool wrap_at_edges);
         std::vector<std::pair<std::string, std::string>> get_items() const;
         float get_created_at() const;
         int get_cursor_position() const;
         bool get_wrap_at_edges() const;
         void set_items(std::vector<std::pair<std::string, std::string>> items={});
         std::vector<std::string> get_item_labels();
         int num_items();
         bool has_valid_currently_selected_item();
         std::string get_currently_selected_item_label();
         std::string get_currently_selected_item_value();
         float infer_age(float time_now=al_get_time());
         void set_cursor_position(int cursor_position=0);
         void move_cursor_up();
         void move_cursor_down();
      };
   }
}



