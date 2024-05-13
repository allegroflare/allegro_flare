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
      void draw_vertical_ruler(float x=0.0f, float y=0.0f, float tick_width=30.0f, float tick_height=4.0f, float y_distance=160.0f, int num_ticks=5, float tick_align_x=0.0f, float tick_align_y=0.0f, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1});
      void draw_vertical_ruler_numbers(float x=0.0f, float y=0.0f, int number_start=0, int number_increment=1, float y_distance=160.0f, int num_ticks=5, float text_align_x=0.0f, float text_align_y=0.0f, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1});
      std::vector<ALLEGRO_VERTEX> build_vertical_ruler(float x=0.0f, float y=0.0f, float tick_width=30.0f, float tick_height=4.0f, float y_distance=160.0f, int num_ticks=5, float tick_align_x=0.0f, float tick_align_y=0.0f, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1});
      void draw_horizontal_ruler(float x=0.0f, float y=0.0f, float tick_width=4.0f, float tick_height=30.0f, float x_distance=160.0f, int num_ticks=5, float tick_align_x=0.0f, float tick_align_y=0.0f, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1});
      void draw_horizontal_ruler_numbers(float x=0.0f, float y=0.0f, int number_start=0, int number_increment=1, float x_distance=160.0f, int num_ticks=5, float text_align_x=0.0f, float text_align_y=0.0f, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1});
      std::vector<ALLEGRO_VERTEX> build_horizontal_ruler(float x=0.0f, float y=0.0f, float tick_width=4.0f, float tick_height=30.0f, float x_distance=160.0f, int num_ticks=5, float tick_align_x=0.0f, float tick_align_y=0.0f, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1});
      void draw_number(float x=0.0f, float y=0.0f, int number=137, int num_digits_filled=-1, float align_x=0.5f, float align_y=0.5f, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1});
      static std::string build_number(int number=137, int num_digits_filled=-1);
   };
}



