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
         AllegroFlare::Vec2D position;
         AllegroFlare::Vec2D position_destination;
         AllegroFlare::Vec2D size;
         AllegroFlare::Vec2D size_destination;
         AllegroFlare::Vec2D padding;
         ALLEGRO_COLOR core_color;
         float roundness;
         float thickness;
         bool visible;
         float reposition_multiplier;
         float last_repositioned_at;
         void update_last_repositioned_at(float time_now=al_get_time());
         ALLEGRO_COLOR build_cursor_color();
         void draw_cursor_rectangle(float x=0.0f, float y=0.0f, float w=0.0f, float h=0.0f, float padding_x=0.0f, float padding_y=0.0f);
         void draw_cursor();
         float infer_cursor_change_age(float time_now=al_get_time());

      protected:


      public:
         SelectionCursorBox();
         ~SelectionCursorBox();

         void set_core_color(ALLEGRO_COLOR core_color);
         void set_roundness(float roundness);
         void set_thickness(float thickness);
         AllegroFlare::Vec2D get_position() const;
         AllegroFlare::Vec2D get_position_destination() const;
         AllegroFlare::Vec2D get_size() const;
         AllegroFlare::Vec2D get_size_destination() const;
         AllegroFlare::Vec2D get_padding() const;
         ALLEGRO_COLOR get_core_color() const;
         float get_roundness() const;
         float get_thickness() const;
         float get_reposition_multiplier() const;
         float get_last_repositioned_at() const;
         void show();
         void hide();
         void reposition_to(float x=0.0f, float y=0.0f, float time_now=al_get_time());
         void resize_to(float x=0.0f, float y=0.0f, float time_now=al_get_time());
         void set_position(float x=0.0f, float y=0.0f, float time_now=al_get_time());
         void set_position_quietly(float x=0.0f, float y=0.0f);
         void set_size(float x=0.0f, float y=0.0f, float time_now=al_get_time());
         void set_size_quietly(float x=0.0f, float y=0.0f);
         void set_padding(float padding_x=0.0f, float padding_y=0.0f, float time_now=0 /* this arg currently not used */);
         void update();
         void render();
      };
   }
}



