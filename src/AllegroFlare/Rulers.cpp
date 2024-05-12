

#include <AllegroFlare/Rulers.hpp>

#include <AllegroFlare/Useful.hpp>
#include <AllegroFlare/Useful3D/Useful3D.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{


Rulers::Rulers(AllegroFlare::FontBin* font_bin)
   : font_bin(font_bin)
{
}


Rulers::~Rulers()
{
}


void Rulers::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


AllegroFlare::FontBin* Rulers::get_font_bin() const
{
   return font_bin;
}


void Rulers::draw_dimensional_grid(float x, float y, float z, float spacing)
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[Rulers::draw_dimensional_grid]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Rulers::draw_dimensional_grid: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Rulers::draw_dimensional_grid]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Rulers::draw_dimensional_grid: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   for (int zz=-10; zz<10; zz++)
      for (int xx=-10; xx<10; xx++)
         for (int yy=-10; yy<10; yy++)
         {
            ALLEGRO_STATE previous_target_bitmap_state;
            al_store_state(&previous_target_bitmap_state, ALLEGRO_STATE_TRANSFORM);
            //al_set_target_bitmap(display_bitmap);
            //al_use_projection_transform(&trans);

            ALLEGRO_TRANSFORM trans;

            al_copy_transform(&trans, al_get_current_transform());

            //al_identity_transform(&trans);
            al_translate_transform_3d(&trans, x+xx*spacing, y+yy*spacing, z+zz*spacing);
            al_use_transform(&trans);
            al_draw_filled_rectangle(-0.5, -0.5, 0.5, 0.5, ALLEGRO_COLOR{0.5, 0.5, 0.5, 0.5});
            //al_start_transform(&trans);

            al_restore_state(&previous_target_bitmap_state);
         }

   return;
}

void Rulers::draw_2d_grid(float x, float y, float size, float spacing)
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[Rulers::draw_2d_grid]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Rulers::draw_2d_grid: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Rulers::draw_2d_grid]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Rulers::draw_2d_grid: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   for (int xx=-10; xx<10; xx++)
      for (int yy=-10; yy<10; yy++)
      {
         ALLEGRO_STATE previous_target_bitmap_state;
         al_store_state(&previous_target_bitmap_state, ALLEGRO_STATE_TRANSFORM);
         //al_set_target_bitmap(display_bitmap);
         //al_use_projection_transform(&trans);

         ALLEGRO_TRANSFORM trans;

         al_copy_transform(&trans, al_get_current_transform());

         //al_identity_transform(&trans);
         al_translate_transform_3d(&trans, x+xx*spacing, y+yy*spacing, 0); //z+zz*spacing);
         al_use_transform(&trans);
         al_draw_filled_rectangle(-size*0.5, -size*0.5, size*0.5, size*0.5, ALLEGRO_COLOR{0.5, 0.5, 0.5, 0.5});
         //al_start_transform(&trans);

         al_restore_state(&previous_target_bitmap_state);
      }

   return;
}

void Rulers::draw_vertical_ruler(float x, float y, float tick_width, float tick_height, float y_distance, int num_ticks, float tick_align_x, float tick_align_y, ALLEGRO_COLOR color)
{
   std::vector<ALLEGRO_VERTEX> vertices = build_vertical_ruler(
         x, y, tick_width, tick_height, y_distance, num_ticks, tick_align_x, tick_align_y, color
      );
   al_draw_prim(&vertices[0], NULL, NULL, 0, vertices.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
}

void Rulers::draw_vertical_ruler_numbers(float x, float y, int number_start, int number_increment, float y_distance, int num_ticks, float text_align_x, float text_align_y, ALLEGRO_COLOR color)
{
   for (int i=0; i<num_ticks; i++)
   {
      draw_number(x, y+y_distance*i, number_start + number_increment*i, 2, text_align_x, text_align_y, color);
   }
}

std::vector<ALLEGRO_VERTEX> Rulers::build_vertical_ruler(float x, float y, float tick_width, float tick_height, float y_distance, int num_ticks, float tick_align_x, float tick_align_y, ALLEGRO_COLOR color)
{
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Rulers::build_vertical_ruler]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Rulers::build_vertical_ruler: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   ALLEGRO_VERTEX vtx_a = AllegroFlare::build_vertex(0, 0, 0, color, 0, 0);
   ALLEGRO_VERTEX vtx_b = AllegroFlare::build_vertex(1, 0, 0, color, 0, 0);
   ALLEGRO_VERTEX vtx_c = AllegroFlare::build_vertex(1, 1, 0, color, 0, 0);
   ALLEGRO_VERTEX vtx_d = AllegroFlare::build_vertex(0, 1, 0, color, 0, 0);

   // Define a triangle list set of vertices
   std::vector<ALLEGRO_VERTEX> tick_vertices = {
      vtx_a,
      vtx_b,
      vtx_d,
      vtx_b,
      vtx_c,
      vtx_d,
   };

   // Position the tick
   for (auto &vertex : tick_vertices)
   {
      vertex.x *= tick_width;
      vertex.y *= tick_height;
      vertex.x += x - tick_width * tick_align_x;
      vertex.y += y - tick_height * tick_align_y;
   }

   // Create multiple ticks
   std::vector<ALLEGRO_VERTEX> result;
   for (int i=0; i<num_ticks; i++)
   {
      std::vector<ALLEGRO_VERTEX> tick_to_insert_vertices = tick_vertices;
      for (auto &vertex : tick_to_insert_vertices)
      {
         vertex.y += (y_distance * i);
      }
      
      result.insert(result.end(), tick_to_insert_vertices.begin(), tick_to_insert_vertices.end());
   }

   return result;
}

void Rulers::draw_number(float x, float y, int number, int num_digits_filled, float align_x, float align_y, ALLEGRO_COLOR color)
{
   ALLEGRO_FONT *font = obtain_small_hud_font();
   std::string number_as_string = build_number(number, num_digits_filled);
   float text_width = al_get_text_width(font, number_as_string.c_str());
   float font_ascent = al_get_font_ascent(font);
   float font_line_height = al_get_font_line_height(font);

   al_draw_text(
         font,
         color,
         x - text_width * align_x,
         y - font_line_height + font_ascent * (1.0 - align_y),
         ALLEGRO_ALIGN_LEFT,
         number_as_string.c_str()
      );

   return;
}

std::string Rulers::build_number(int number, int num_digits_filled)
{
   std::string number_as_string = std::to_string(number);
   std::stringstream result;

   int num_digits = number_as_string.length();
   int num_digits_to_fill = num_digits_filled - num_digits;
   for (int i=0; i<num_digits_to_fill; i++)
   {
      number_as_string = "O" + number_as_string;
   }

   int digit_n = 0;
   for (auto &digit_c : number_as_string)
   {
      if (digit_c == '0') result << "O";
      else result << digit_c;

      // Add some extra spaces inside the numbers
      digit_n++;
      if (digit_n != number_as_string.length()) result << " ";
   }

   return result.str();
}

ALLEGRO_FONT* Rulers::obtain_small_hud_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Rulers::obtain_small_hud_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Rulers::obtain_small_hud_font: error: guard \"font_bin\" not met");
   }
   std::stringstream result_font_identifier;
   result_font_identifier << "Orbitron-Medium.ttf" << " " << -13;
   return font_bin->auto_get(result_font_identifier.str());
}


} // namespace AllegroFlare


