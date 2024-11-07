#pragma once


#include <AllegroFlare/Layouts/Elements/CursorDestination.hpp>
#include <allegro5/allegro.h>
#include <functional>
#include <map>
#include <string>
#include <tuple>


namespace AllegroFlare
{
   namespace Layouts
   {
      class CursorMap
      {
      private:
         std::string tmj_filename;
         float layout_width;
         float layout_height;
         std::map<int, AllegroFlare::Layouts::Elements::CursorDestination> positions;
         bool initialized;

      protected:


      public:
         CursorMap(std::string tmj_filename="[unset-tmj_filename]");
         ~CursorMap();

         void set_tmj_filename(std::string tmj_filename);
         bool get_initialized() const;
         float get_layout_width();
         float get_layout_height();
         void set_positions_behavior(std::map<std::string, std::tuple<std::function<void()>, std::function<void()>, std::function<void()>>> behavior_map={});
         void initialize();
         AllegroFlare::Layouts::Elements::CursorDestination* get_initial_cursor_destination();
         AllegroFlare::Layouts::Elements::CursorDestination* find_position_by_tmj_object_id(int tmj_object_id=0);
         AllegroFlare::Layouts::Elements::CursorDestination* find_position_by_name(std::string name="[unset-name]");
         void render_debug(float line_thickness=2.0);
         void draw_container_frame(float x=0.0f, float y=0.0f, float x2=0.0f, float y2=0.0f, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1}, float line_thickness=0.0f);
      };
   }
}



