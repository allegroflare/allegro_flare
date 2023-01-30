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
         float last_repositioned_at;
         ALLEGRO_COLOR build_cursor_color();
         void draw_cursor_rectangle(float x=0.0f, float y=0.0f, float w=0.0f, float h=0.0f);
         void draw_cursor();

      protected:


      public:
         SelectionCursorBox();
         ~SelectionCursorBox();

         float get_cursor_reposition_multiplier() const;
         float get_last_repositioned_at() const;
         void reposition_to(float x=0.0f, float y=0.0f, float time_now=al_get_time());
         void update();
         void render();
         float infer_cursor_change_age(float time_now=al_get_time());
      };
   }
}



