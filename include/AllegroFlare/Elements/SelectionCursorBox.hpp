#pragma once


#include <AllegroFlare/Vec2D.hpp>
#include <allegro5/allegro.h>


namespace AllegroFlare
{
   namespace Elements
   {
      class SelectionCursorBox
      {
      public:
         static constexpr float DEFAULT_CURSOR_REPOSITION_MULTIPLIER = 0.6f;

      private:
         AllegroFlare::Vec2D cursor_location;
         AllegroFlare::Vec2D cursor_location_destination;
         AllegroFlare::Vec2D cursor_size;
         AllegroFlare::Vec2D cursor_size_destination;
         float cursor_reposition_multiplier;
         ALLEGRO_COLOR build_cursor_color();
         void draw_cursor_rectangle(float x=0.0f, float y=0.0f, float w=0.0f, float h=0.0f);
         void draw_cursor();

      protected:


      public:
         SelectionCursorBox();
         ~SelectionCursorBox();

         float get_cursor_reposition_multiplier() const;
         void reposition_to(float x=0.0f, float y=0.0f);
         void update();
         void render();
      };
   }
}



