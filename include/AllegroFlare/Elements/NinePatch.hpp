#pragma once


#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <vector>


namespace AllegroFlare
{
   namespace Elements
   {
      class NinePatch
      {
      private:
         ALLEGRO_BITMAP* source_texture;
         float left_column_width;
         float center_column_width;
         float right_column_width;
         float top_row_height;
         float middle_row_height;
         float bottom_row_height;
         std::vector<ALLEGRO_VERTEX> mesh;

      protected:


      public:
         NinePatch();
         ~NinePatch();

         void set_source_texture(ALLEGRO_BITMAP* source_texture);
         ALLEGRO_BITMAP* get_source_texture() const;
         void render();
         void build_mesh();
         std::vector<ALLEGRO_VERTEX> build_vertices_for_rect(float x=0.0f, float y=0.0f, float w=0.0f, float h=0.0f, float u1=0.0f, float v1=0.0f, float u2=1.0f, float v2=1.0f);
      };
   }
}



