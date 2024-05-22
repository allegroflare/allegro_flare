#pragma once


#include <AllegroFlare/Elements/Base.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Vec3D.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <string>
#include <utility>
#include <vector>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace FUI
      {
         class PanningGrid : public AllegroFlare::Elements::Base
         {
         private:
            AllegroFlare::FontBin* font_bin;
            bool initialized;
            ALLEGRO_FONT* obtain_small_hud_font();
            ALLEGRO_FONT* obtain_sized_font(int size=-13);

         protected:


         public:
            PanningGrid();
            ~PanningGrid();

            void set_font_bin(AllegroFlare::FontBin* font_bin);
            bool get_initialized() const;
            void initialize();
            void update();
            void render();
            void draw_triangle(AllegroFlare::Vec3D v0={}, AllegroFlare::Vec3D v1={}, AllegroFlare::Vec3D v2={}, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1});
            void draw_l_bracket(float x=0.0f, float y=0.0f, float size=10.0f, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1});
            static void draw_3d_dimensional_grid(float x=0.0f, float y=0.0f, float z=0.0f, float spacing=(16*4.8));
            static void draw_2d_grid(float x=0.0f, float y=0.0f, float size=1.0f, float spacing=(16*4.8));
            void draw_number(float x=0.0f, float y=0.0f, int number=137, int num_digits_filled=-1, float align_x=0.5f, float align_y=0.5f, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1});
            static std::string build_number(int number=137, int num_digits_filled=-1);
            std::vector<ALLEGRO_VERTEX> build_bracket(float x=0.0f, float y=0.0f, float width=0.0f, float height=0.0f, float thickness=12.0f, float length=20.0f, float bracket_align_x=0.5f, float bracket_align_y=0.5f, float bracket_offset_x=0.0f, float bracket_offset_y=0.0f, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1});
            std::pair<float, float> draw_text(float x=0.0f, float y=0.0f, std::string text="[unset-text]", int font_size=16, float align_x=0.0f, float align_y=0.0f, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1});
            std::vector<ALLEGRO_VERTEX> build_tab(float x=0.0f, float y=0.0f, float width=120.0f, float thickness=12.0f, float align=1.0f, bool on_top=true, bool slant_left=false, bool slant_right=false, bool is_vertical=false, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1});
            std::vector<ALLEGRO_VERTEX> build_grid(float x=0.0f, float y=0.0f, float line_size=3.0f, float distance=160.0f, float extensions_distance=60.0f, int num_horizontal_repeats=5, int num_vertical_repeats=3, float line_align_x=0.0f, float line_align_y=0.0f, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1});
            std::vector<ALLEGRO_VERTEX> build_window_frame(float x=0.0f, float y=0.0f, float width=600.0f, float height=200.0f, float frame_align_x=1.0f, float frame_align_y=1.0f, float frame_offset_x=0.0f, float frame_offset_y=0.0f, float thickness=3.0f, float tab_length=100.0f, float tab_thickness=6.0f, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1});
            std::vector<ALLEGRO_VERTEX> build_bracketed_box(float x=0.0f, float y=0.0f, float width=600.0f, float height=200.0f, float thickness=3.0f, float align_x=0.0f, float align_y=0.0f, float bracket_thickness=3.0f, float bracket_offset_x=16.0f, float bracket_offset_y=16.0f, ALLEGRO_COLOR box_color=ALLEGRO_COLOR{1, 1, 1, 1}, ALLEGRO_COLOR bracket_color=ALLEGRO_COLOR{1, 1, 1, 1});
            std::vector<ALLEGRO_VERTEX> build_rectangle_frame_segments(float x=0.0f, float y=0.0f, float width=600.0f, float height=200.0f, float thickness=3.0f, float align_x=0.5f, float align_y=0.5f, bool include_top_segment=true, bool include_top_right_segment=true, bool include_right_segment=true, bool include_bottom_right_segment=true, bool include_bottom_segment=true, bool include_bottom_left_segment=true, bool include_left_segment=true, bool include_top_left_segment=true, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1});
            std::vector<ALLEGRO_VERTEX> build_tall_cross_segments(float x=0.0f, float y=0.0f, float line_size=3.0f, float y_distance=160.0f, float line_align_x=0.0f, float line_align_y=0.0f, bool include_top_segment=true, bool include_right_segment=true, bool include_bottom_segment=true, bool include_left_segment=true, bool include_middle_segment=true, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1});
            std::vector<ALLEGRO_VERTEX> draw_tall_cross(float x=0.0f, float y=0.0f, float line_size=3.0f, float y_distance=160.0f, int num_ticks=5, float line_align_x=0.0f, float line_align_y=0.0f, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1});
            std::vector<ALLEGRO_VERTEX> draw_cross(float x=0.0f, float y=0.0f, float line_size=3.0f, float line_align_x=0.0f, float line_align_y=0.0f, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1});
            void draw_vertical_ruler(float x=0.0f, float y=0.0f, float tick_width=30.0f, float tick_height=4.0f, float y_distance=160.0f, int num_ticks=5, float tick_align_x=0.0f, float tick_align_y=0.0f, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1});
            void draw_vertical_ruler_numbers(float x=0.0f, float y=0.0f, int number_start=0, int number_increment=1, float y_distance=160.0f, int num_ticks=5, float text_align_x=0.0f, float text_align_y=0.0f, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1});
            std::vector<ALLEGRO_VERTEX> build_vertical_ruler(float x=0.0f, float y=0.0f, float tick_width=30.0f, float tick_height=4.0f, float y_distance=160.0f, int num_ticks=5, float tick_align_x=0.0f, float tick_align_y=0.0f, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1});
         };
      }
   }
}



