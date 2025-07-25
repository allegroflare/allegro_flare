#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <string>
#include <vector>


namespace AllegroFlare
{
   class Rulers
   {
   private:
      AllegroFlare::FontBin* font_bin;
      ALLEGRO_FONT* obtain_small_hud_font();

   protected:


   public:
      Rulers(AllegroFlare::FontBin* font_bin=nullptr);
      ~Rulers();

      void set_font_bin(AllegroFlare::FontBin* font_bin);
      AllegroFlare::FontBin* get_font_bin() const;
      static void draw_dimensional_grid(float x=0.0f, float y=0.0f, float z=0.0f, float spacing=(16*4.8));
      static void draw_2d_grid(float x=0.0f, float y=0.0f, float size=1.0f, float spacing=(16*4.8));
      static std::vector<ALLEGRO_VERTEX> build_hd_layout_grid(float x=(1920/2.0f), float y=(1080/2.0f), float width=1920.0f, float height=1080.0f, int num_sections_x=10, int num_sections_y=6, ALLEGRO_COLOR color=ALLEGRO_COLOR{0.5, 0.5, 0.5, 0.5}, float line_thickness=1.0f, float dot_spacing=10.0f, float dot_length=10.0f);
      static void draw_hd_layout_grid(float x=(1920/2.0f), float y=(1080/2.0f), float width=1920.0f, float height=1080.0f, int num_sections_x=10, int num_sections_y=6, ALLEGRO_COLOR color=ALLEGRO_COLOR{0.5, 0.5, 0.5, 0.5}, float line_thickness=1.0f, float dot_spacing=10.0f, float dot_length=10.0f);
      static void draw_vertical_ruler(float x=0.0f, float y=0.0f, float tick_width=30.0f, float tick_height=4.0f, float y_distance=160.0f, int num_ticks=5, float tick_align_x=0.0f, float tick_align_y=0.0f, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1});
      void draw_vertical_ruler_numbers(float x=0.0f, float y=0.0f, int number_start=0, int number_increment=1, float y_distance=160.0f, int num_ticks=5, float text_align_x=0.0f, float text_align_y=0.0f, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1});
      static std::vector<ALLEGRO_VERTEX> build_vertical_ruler(float x=0.0f, float y=0.0f, float tick_width=30.0f, float tick_height=4.0f, float y_distance=160.0f, int num_ticks=5, float tick_align_x=0.0f, float tick_align_y=0.0f, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1});
      static void draw_horizontal_ruler(float x=0.0f, float y=0.0f, float tick_width=4.0f, float tick_height=30.0f, float x_distance=160.0f, int num_ticks=5, float tick_align_x=0.0f, float tick_align_y=0.0f, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1});
      void draw_horizontal_ruler_numbers(float x=0.0f, float y=0.0f, int number_start=0, int number_increment=1, float x_distance=160.0f, int num_ticks=5, float text_align_x=0.0f, float text_align_y=0.0f, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1});
      static std::vector<ALLEGRO_VERTEX> build_horizontal_ruler(float x=0.0f, float y=0.0f, float tick_width=4.0f, float tick_height=30.0f, float x_distance=160.0f, int num_ticks=5, float tick_align_x=0.0f, float tick_align_y=0.0f, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1});
      void draw_number(float x=0.0f, float y=0.0f, int number=137, int num_digits_filled=-1, float align_x=0.5f, float align_y=0.5f, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1});
      static std::string build_number(int number=137, int num_digits_filled=-1);
      static void draw_crosshair(float x=0.0f, float y=0.0f, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 0, 0, 1}, float size=200.0f);
      static void draw_crosshair_blue(float x=0.0f, float y=0.0f, ALLEGRO_COLOR color=ALLEGRO_COLOR{0, 0, 1, 1}, float size=100.0f);
      static void draw_horizontal_crosshair(float x=0.0f, float y=0.0f, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 0, 0, 1}, float size_v=30.0f, float size_h=600.0f);
      static void draw_vertical_crosshair(float x=0.0f, float y=0.0f, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 0, 0, 1}, float size_v=600.0f, float size_h=30.0f);
      static void draw_rectangle(float x=0.0f, float y=0.0f, float width=160.0f, float height=90.0f, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 0, 0, 1}, float size=100.0f);
   };
}



