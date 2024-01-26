#pragma once


#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <tuple>
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
         std::tuple<float, float, float, float> a_uv;
         std::tuple<float, float, float, float> b_uv;
         std::tuple<float, float, float, float> c_uv;
         std::tuple<float, float, float, float> d_uv;
         std::tuple<float, float, float, float> e_uv;
         std::tuple<float, float, float, float> f_uv;
         std::tuple<float, float, float, float> g_uv;
         std::tuple<float, float, float, float> h_uv;
         std::tuple<float, float, float, float> i_uv;
         std::vector<ALLEGRO_VERTEX> mesh;
         bool initialized;
         void build_mesh();
         std::vector<ALLEGRO_VERTEX> build_vertices_for_rect(float x=0.0f, float y=0.0f, float w=0.0f, float h=0.0f, float u1=0.0f, float v1=0.0f, float u2=1.0f, float v2=1.0f);
         std::vector<ALLEGRO_VERTEX> build_vertices_for_rect2(float x=0.0f, float y=0.0f, float w=0.0f, float h=0.0f, std::tuple<float, float, float, float> uv={ 0, 0, 0, 0 });

      protected:


      public:
         NinePatch();
         ~NinePatch();

         void set_source_texture(ALLEGRO_BITMAP* source_texture);
         void set_left_column_width(float left_column_width);
         void set_center_column_width(float center_column_width);
         void set_right_column_width(float right_column_width);
         void set_top_row_height(float top_row_height);
         void set_middle_row_height(float middle_row_height);
         void set_bottom_row_height(float bottom_row_height);
         void set_a_uv(std::tuple<float, float, float, float> a_uv);
         void set_b_uv(std::tuple<float, float, float, float> b_uv);
         void set_c_uv(std::tuple<float, float, float, float> c_uv);
         void set_d_uv(std::tuple<float, float, float, float> d_uv);
         void set_e_uv(std::tuple<float, float, float, float> e_uv);
         void set_f_uv(std::tuple<float, float, float, float> f_uv);
         void set_g_uv(std::tuple<float, float, float, float> g_uv);
         void set_h_uv(std::tuple<float, float, float, float> h_uv);
         void set_i_uv(std::tuple<float, float, float, float> i_uv);
         ALLEGRO_BITMAP* get_source_texture() const;
         float get_left_column_width() const;
         float get_center_column_width() const;
         float get_right_column_width() const;
         float get_top_row_height() const;
         float get_middle_row_height() const;
         float get_bottom_row_height() const;
         std::tuple<float, float, float, float> get_a_uv() const;
         std::tuple<float, float, float, float> get_b_uv() const;
         std::tuple<float, float, float, float> get_c_uv() const;
         std::tuple<float, float, float, float> get_d_uv() const;
         std::tuple<float, float, float, float> get_e_uv() const;
         std::tuple<float, float, float, float> get_f_uv() const;
         std::tuple<float, float, float, float> get_g_uv() const;
         std::tuple<float, float, float, float> get_h_uv() const;
         std::tuple<float, float, float, float> get_i_uv() const;
         std::vector<ALLEGRO_VERTEX> get_mesh();
         void initialize();
         void render();
      };
   }
}



