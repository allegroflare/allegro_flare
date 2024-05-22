

#include <AllegroFlare/Elements/FUI/PanningGrid.hpp>

#include <AllegroFlare/ColorKit.hpp>
#include <AllegroFlare/StringTransformer.hpp>
#include <AllegroFlare/Useful.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{
namespace FUI
{


PanningGrid::PanningGrid()
   : AllegroFlare::Elements::Base()
   , font_bin(nullptr)
   , initialized(false)
{
}


PanningGrid::~PanningGrid()
{
}


void PanningGrid::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   if (get_initialized()) throw std::runtime_error("[PanningGrid::set_font_bin]: error: guard \"get_initialized()\" not met.");
   this->font_bin = font_bin;
}


bool PanningGrid::get_initialized() const
{
   return initialized;
}


void PanningGrid::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[PanningGrid::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PanningGrid::initialize: error: guard \"(!initialized)\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[PanningGrid::initialize]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PanningGrid::initialize: error: guard \"font_bin\" not met");
   }
   initialized = true;
   return;
}

void PanningGrid::update()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[PanningGrid::update]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PanningGrid::update: error: guard \"initialized\" not met");
   }
   return;
}

void PanningGrid::render()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[PanningGrid::render]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PanningGrid::render: error: guard \"initialized\" not met");
   }
   ALLEGRO_COLOR color = al_color_html("b8e8e8");

   ALLEGRO_COLOR c_back = AllegroFlare::ColorKit::fade(color, 0.2);
   ALLEGRO_COLOR c_mid = AllegroFlare::ColorKit::fade(color, 0.35);
   ALLEGRO_COLOR c_upper_mid = AllegroFlare::ColorKit::fade(color, 0.75);
   ALLEGRO_COLOR c_front = AllegroFlare::ColorKit::mix(color, ALLEGRO_COLOR{1, 1, 1, 1}, 0.6);

   float spacing = 120;
   float extensions = spacing / 3;
   float thickness = 2.0f;

   float width = spacing * 8; //1920/4*3;
   float height = spacing * 4; //1080/5*3;
   float x = 1920/2 - width/2;
   float y = 1080/2 - height/2;

   //float spacing = 120;
   //float extensions = spacing / 3;

   std::vector<ALLEGRO_VERTEX> result;
   std::vector<ALLEGRO_VERTEX> vertices_to_insert;


   // Add the grid
   vertices_to_insert = build_grid(x, y, 2.0f, spacing, extensions, 8, 4, 0.5f, 0.5f, c_back);
   result.insert(result.end(), vertices_to_insert.begin(), vertices_to_insert.end());


   // Left ruler

   // Add the major ruler ticks on the left
   vertices_to_insert = build_vertical_ruler(x - extensions, y, 12, 3, spacing, 5, 1.0, 0.5, c_front);
   result.insert(result.end(), vertices_to_insert.begin(), vertices_to_insert.end());

   // Add the minor ruler ticks on the left
   vertices_to_insert = build_vertical_ruler(x - extensions, y + (spacing/3)*1, 5, 2, spacing, 4, 1.0, 0.5, c_mid);
   result.insert(result.end(), vertices_to_insert.begin(), vertices_to_insert.end());
   vertices_to_insert = build_vertical_ruler(x - extensions, y + (spacing/3)*2, 5, 2, spacing, 4, 1.0, 0.5, c_mid);
   result.insert(result.end(), vertices_to_insert.begin(), vertices_to_insert.end());

   // Add the ruler numbers on the left (draw them, actually)
   draw_vertical_ruler_numbers(x - extensions - 30, y, 8, -1, spacing, 5, 1.0f, 0.5f, c_upper_mid);


   // Right ruler

   // Add the major ruler ticks on the right
   vertices_to_insert = build_vertical_ruler(x + width + extensions, y, 12, 3, spacing, 5, 0.0, 0.5, c_front);
   result.insert(result.end(), vertices_to_insert.begin(), vertices_to_insert.end());

   // Add the minor ruler ticks on the left
   vertices_to_insert = build_vertical_ruler(x + width + extensions, y + (spacing/3)*1, 5, 2, spacing, 4, 0.0, 0.5, c_mid);
   result.insert(result.end(), vertices_to_insert.begin(), vertices_to_insert.end());
   vertices_to_insert = build_vertical_ruler(x + width + extensions, y + (spacing/3)*2, 5, 2, spacing, 4, 0.0, 0.5, c_mid);
   result.insert(result.end(), vertices_to_insert.begin(), vertices_to_insert.end());

   // Add the ruler numbers on the left (draw them, actually)
   draw_vertical_ruler_numbers(x + width + extensions + 30, y, 8, -1, spacing, 5, 0.0f, 0.5f, c_upper_mid);


   // Brackets

   vertices_to_insert = build_bracket(
         x,
         y,
         spacing * 8,
         spacing * 4,
         6, 10, 1.0f, 1.0f,
         extensions + 10,
         extensions + 10,
         c_upper_mid
      );
   result.insert(result.end(), vertices_to_insert.begin(), vertices_to_insert.end());


   // Window

   float window_w = spacing * 5;
   float window_h = spacing * 3;
   float window_x = x + width/2 - window_w/2;
   float window_y = y + height/2 - window_h/2;
   vertices_to_insert = build_window_frame(
         window_x, window_y,
         window_w, window_h,
         1.0f, 1.0f,
         0.0f, 0.0f,
         2.0f,
         120,
         4.0f,
         c_upper_mid
      );
   result.insert(result.end(), vertices_to_insert.begin(), vertices_to_insert.end());

   // Window brackets

   vertices_to_insert = build_bracket(
         window_x,
         window_y,
         window_w,
         window_h,
         3, 5, 1.0f, 1.0f,
         spacing * 0.25f,
         spacing * 0.25f,
         c_upper_mid
      );
   result.insert(result.end(), vertices_to_insert.begin(), vertices_to_insert.end());


   // Some bracket "points of interest"

   float poi_s = spacing / 8 * 3;
   float poi_x = x + spacing * 2 - 10 - poi_s/2;
   float poi_y = y + spacing * 2 - poi_s/2;
   vertices_to_insert = build_bracketed_box(
         poi_x, poi_y, poi_s, poi_s, thickness, 0.0f, 0.0f, thickness, 12.0f, 12.0f, c_back, c_mid
      );
   result.insert(result.end(), vertices_to_insert.begin(), vertices_to_insert.end());

   poi_x = x + spacing * 6 - 10 - poi_s/2;
   vertices_to_insert = build_bracketed_box(
         poi_x, poi_y, poi_s, poi_s, thickness, 0.0f, 0.0f, thickness, 12.0f, 12.0f, c_back, c_mid
      );
   result.insert(result.end(), vertices_to_insert.begin(), vertices_to_insert.end());


   al_draw_prim(&result[0], NULL, NULL, 0, result.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
   return;
}

void PanningGrid::draw_triangle(AllegroFlare::Vec3D v0, AllegroFlare::Vec3D v1, AllegroFlare::Vec3D v2, ALLEGRO_COLOR color)
{
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[PanningGrid::draw_triangle]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PanningGrid::draw_triangle: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   ALLEGRO_VERTEX vtx[3];
   vtx[0] = AllegroFlare::build_vertex(v0.x, v0.y, v0.z, color, 0, 0);
   vtx[1] = AllegroFlare::build_vertex(v1.x, v1.y, v1.z, color, 0, 0);
   vtx[2] = AllegroFlare::build_vertex(v2.x, v2.y, v2.z, color, 0, 0);
   al_draw_prim(vtx, NULL, NULL, 0, 3, ALLEGRO_PRIM_TRIANGLE_FAN);
   return;
}

void PanningGrid::draw_l_bracket(float x, float y, float size, ALLEGRO_COLOR color)
{
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[PanningGrid::draw_l_bracket]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PanningGrid::draw_l_bracket: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   float s = size / 2;

   // Define the points on this shape
   ALLEGRO_VERTEX vtx_a = AllegroFlare::build_vertex(0, 0, 0, color, 0, 0);
   ALLEGRO_VERTEX vtx_b = AllegroFlare::build_vertex(s, 0, 0, color, 0, 0);
   ALLEGRO_VERTEX vtx_c = AllegroFlare::build_vertex(s, s, 0, color, 0, 0);
   ALLEGRO_VERTEX vtx_d = AllegroFlare::build_vertex(s*2, s,   0, color, 0, 0);
   ALLEGRO_VERTEX vtx_e = AllegroFlare::build_vertex(s*2, s*2, 0, color, 0, 0);
   ALLEGRO_VERTEX vtx_f = AllegroFlare::build_vertex(0,   s*2, 0, color, 0, 0);

   // Define a triangle list set of vertices
   std::vector<ALLEGRO_VERTEX> vertices = {
      vtx_a,
      vtx_b,
      vtx_f,
      vtx_b,
      vtx_c,
      vtx_f,
      vtx_c,
      vtx_d,
      vtx_f,
      vtx_d,
      vtx_e,
      vtx_f,
   };

   // Position the bracket
   for (auto &vertex : vertices)
   {
      vertex.x += x;
      vertex.y += y;
   }

   al_draw_prim(&vertices[0], NULL, NULL, 0, vertices.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
   return;
}

void PanningGrid::draw_3d_dimensional_grid(float x, float y, float z, float spacing)
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[PanningGrid::draw_3d_dimensional_grid]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PanningGrid::draw_3d_dimensional_grid: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[PanningGrid::draw_3d_dimensional_grid]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PanningGrid::draw_3d_dimensional_grid: error: guard \"al_is_primitives_addon_initialized()\" not met");
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

void PanningGrid::draw_2d_grid(float x, float y, float size, float spacing)
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[PanningGrid::draw_2d_grid]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PanningGrid::draw_2d_grid: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[PanningGrid::draw_2d_grid]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PanningGrid::draw_2d_grid: error: guard \"al_is_primitives_addon_initialized()\" not met");
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

void PanningGrid::draw_number(float x, float y, int number, int num_digits_filled, float align_x, float align_y, ALLEGRO_COLOR color)
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

std::string PanningGrid::build_number(int number, int num_digits_filled)
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

std::vector<ALLEGRO_VERTEX> PanningGrid::build_bracket(float x, float y, float width, float height, float thickness, float length, float bracket_align_x, float bracket_align_y, float bracket_offset_x, float bracket_offset_y, ALLEGRO_COLOR color)
{
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[PanningGrid::build_bracket]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PanningGrid::build_bracket: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   // Create the segments
   std::vector<ALLEGRO_VERTEX> built_segments;

   std::vector<ALLEGRO_VERTEX> result;

   // Top left bracket
   built_segments = build_tall_cross_segments(
         x - bracket_offset_x,
         y - bracket_offset_y,
         thickness,
         length,
         bracket_align_x,
         bracket_align_y,
         false, true, true, false, true, color
      );
   result.insert(result.end(), built_segments.begin(), built_segments.end());

   // Top right bracket
   built_segments = build_tall_cross_segments(
         x + width + bracket_offset_x,
         y - bracket_offset_y,
         thickness,
         length,
         1.0 - bracket_align_x,
         bracket_align_y,
         false, false, true, true, true, color
      );
   result.insert(result.end(), built_segments.begin(), built_segments.end());

   // Bottom right bracket
   built_segments = build_tall_cross_segments(
         x + width + bracket_offset_x,
         y + height + bracket_offset_y,
         thickness,
         length,
         1.0 - bracket_align_x,
         1.0 - bracket_align_y,
         true, false, false, true, true, color
      );
   result.insert(result.end(), built_segments.begin(), built_segments.end());

   // Bottom left bracket
   built_segments = build_tall_cross_segments(
         x - bracket_offset_x,
         y + height + bracket_offset_y,
         thickness,
         length,
         bracket_align_x,
         1.0 - bracket_align_y,
         true, true, false, false, true, color
      );
   result.insert(result.end(), built_segments.begin(), built_segments.end());

   return result;
}

std::pair<float, float> PanningGrid::draw_text(float x, float y, std::string text, int font_size, float align_x, float align_y, ALLEGRO_COLOR color)
{
   ALLEGRO_FONT *font = obtain_sized_font(font_size);
   text = AllegroFlare::StringTransformer(text).upcase().expand().get_text();

   //std::string number_as_string = build_number(number, num_digits_filled);
   float text_width = al_get_text_width(font, text.c_str());
   float font_ascent = al_get_font_ascent(font);
   float font_line_height = al_get_font_line_height(font);

   al_draw_text(
         font,
         color,
         x - text_width * align_x,
         y - font_line_height + font_ascent * (1.0 - align_y),
         ALLEGRO_ALIGN_LEFT,
         text.c_str()
      );

   return {text_width, font_ascent};
}

std::vector<ALLEGRO_VERTEX> PanningGrid::build_tab(float x, float y, float width, float thickness, float align, bool on_top, bool slant_left, bool slant_right, bool is_vertical, ALLEGRO_COLOR color)
{
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[PanningGrid::build_tab]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PanningGrid::build_tab: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   // Create the segments
   std::vector<ALLEGRO_VERTEX> built_segments;

   std::vector<ALLEGRO_VERTEX> result;

   float length_a = 0.57735026919f; // (sqrt(3)/3)
   float length_b = 1.73205080757f; // sqrt(3)

   ALLEGRO_VERTEX vtx_a = AllegroFlare::build_vertex(0, 0, 0, color, 0, 0);
   ALLEGRO_VERTEX vtx_b = AllegroFlare::build_vertex(1, 0, 0, color, 0, 0);
   ALLEGRO_VERTEX vtx_c = AllegroFlare::build_vertex(1, 1, 0, color, 0, 0);
   ALLEGRO_VERTEX vtx_d = AllegroFlare::build_vertex(0, 1, 0, color, 0, 0);
   std::vector<ALLEGRO_VERTEX> segment_vertices = { vtx_a, vtx_b, vtx_d, vtx_b, vtx_c, vtx_d };

   built_segments = segment_vertices;
   for (auto &vertex : built_segments)
   {
      vertex.x *= width;
      vertex.y *= thickness;
      vertex.x += -(align * width);
      vertex.y += 0;

      if (on_top) vertex.y -= thickness;
   }

   // Reposition the "b" vertex for this tab
   if (on_top)
   {
      if (slant_left)
      {
         built_segments[0].x += (length_a * thickness);
      }
      if (slant_right)
      {
         built_segments[1].x -= (length_a * thickness);
         built_segments[3].x -= (length_a * thickness);
      }
   }
   else // (!on_top)
   {
      if (slant_left)
      {
         built_segments[2].x += (length_a * thickness);
         built_segments[5].x += (length_a * thickness);
      }
      if (slant_right)
      {
         built_segments[4].x -= (length_a * thickness);
      }
   }

   // Rotate to the right 90 degrees (if it's a vertical tab)
   if (is_vertical)
   {
      for (auto &vertex : built_segments)
      {
          float old_x = vertex.x;
          vertex.x = vertex.y;
          vertex.y = -old_x;
      }
   }

   // Move the tab to the coordinates
   for (auto &vertex : built_segments)
   {
      vertex.x += x;
      vertex.y += y;
   }

   result.insert(result.end(), built_segments.begin(), built_segments.end());

   return result;
}

std::vector<ALLEGRO_VERTEX> PanningGrid::build_grid(float x, float y, float line_size, float distance, float extensions_distance, int num_horizontal_repeats, int num_vertical_repeats, float line_align_x, float line_align_y, ALLEGRO_COLOR color)
{
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[PanningGrid::build_grid]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PanningGrid::build_grid: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   // TODO: Work out what to do when grid is 0 rows, 0 columns, currently it's missing the top "tick"

   // Create multiple line segments
   std::vector<ALLEGRO_VERTEX> built_segments;

   // Create the segments
   std::vector<ALLEGRO_VERTEX> result;

   float &short_height = extensions_distance;
   //float short_height = distance * 0.3;

   // Create the initial segment
   //float stride = distance-line_size;
   int yy=0;
   int xx=0;
   for (yy=0; yy<num_vertical_repeats; yy++)
   {
      xx=0;

      // Build the "short height" bars along the left
      built_segments = build_tall_cross_segments(
            x+distance*xx,
            y+distance*yy,
            line_size,
            short_height,
            0.5f, 0.5f,
            false, false, false, true, false, color
         );
      result.insert(result.end(), built_segments.begin(), built_segments.end());

      for (xx=0; xx<num_horizontal_repeats; xx++)
      {
         // Build the "short height" bars along the top (only along the top row)
         if (yy == 0)
         {
            built_segments = build_tall_cross_segments(
                  x+distance*xx,
                  y+distance*yy,
                  line_size,
                  short_height,
                  0.5f, 0.5f,
                  true, false, false, false, false, color
               );
            result.insert(result.end(), built_segments.begin(), built_segments.end());
         }

         // Build the main grid columns segments
         built_segments = build_tall_cross_segments(
               x+distance*xx, y+distance*yy, line_size, distance-line_size, 0.5f, 0.5f, false, true, true, false, true, color
            );
         result.insert(result.end(), built_segments.begin(), built_segments.end());

         // Build the last column segments (if on the last row)
         bool on_last_row = (yy == (num_vertical_repeats-1));
         if (on_last_row)
         {
            built_segments = build_tall_cross_segments(
                  x+distance*xx, y+distance*(yy+1), line_size, distance-line_size, 0.5f, 0.5f, false, true, false, false, true, color
               );
            result.insert(result.end(), built_segments.begin(), built_segments.end());

            // Build the "short height" bars along the bottom (again, only along the bottom row)
            built_segments = build_tall_cross_segments(
                  x+distance*xx,
                  y+distance*(yy+1),
                  line_size,
                  short_height,
                  0.5f, 0.5f,
                  false, false, true, false, false, color
               );
            result.insert(result.end(), built_segments.begin(), built_segments.end());
         }
      }

      // Build the last "short height" bar along the top
      if (yy == 0)
      {
         built_segments = build_tall_cross_segments(
               x+distance*xx,
               y+distance*yy,
               line_size,
               short_height,
               0.5f, 0.5f,
               true, false, false, false, false, color
            );
         result.insert(result.end(), built_segments.begin(), built_segments.end());
      }

      // Build the last column segments
      built_segments = build_tall_cross_segments(
            x+distance*xx, y+distance*yy, line_size, distance-line_size, 0.5f, 0.5f, false, false, true, false, true, color
         );
      result.insert(result.end(), built_segments.begin(), built_segments.end());

      // Build the "short height" bars along the right
      built_segments = build_tall_cross_segments(
            x+distance*xx,
            y+distance*yy,
            line_size,
            short_height,
            0.5f, 0.5f,
            false, true, false, false, false, color
         );
      result.insert(result.end(), built_segments.begin(), built_segments.end());
   }

   // Build the last "short height" bars on the bottom right
   built_segments = build_tall_cross_segments(
         x+distance*xx,
         y+distance*yy,
         line_size,
         short_height,
         0.5f, 0.5f,
         false, true, true, false, true, color
      );
   result.insert(result.end(), built_segments.begin(), built_segments.end());

   // Build the last "short height" bar on left at the bottom
   built_segments = build_tall_cross_segments(
         x, //+distance*xx,
         y+distance*yy,
         line_size,
         short_height,
         0.5f, 0.5f,
         false, false, false, true, false, color
      );
   result.insert(result.end(), built_segments.begin(), built_segments.end());

   return result;
}

std::vector<ALLEGRO_VERTEX> PanningGrid::build_window_frame(float x, float y, float width, float height, float frame_align_x, float frame_align_y, float frame_offset_x, float frame_offset_y, float thickness, float tab_length, float tab_thickness, ALLEGRO_COLOR color)
{
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[PanningGrid::build_window_frame]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PanningGrid::build_window_frame: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   std::vector<ALLEGRO_VERTEX> built_segments;
   bool t = true;

   // Create the segments
   std::vector<ALLEGRO_VERTEX> result;

   // Build the frame
   built_segments = build_rectangle_frame_segments(
         x + frame_offset_x,
         y + frame_offset_y,
         width - frame_offset_x*2,
         height - frame_offset_y*2,
         thickness,
         frame_align_x,
         frame_align_y,
         t, t, t, t, t, t, t, t,
         color
      );
   result.insert(result.end(), built_segments.begin(), built_segments.end());

   // Build the tab (right side on the bottom)
   float align_offset_x = thickness*frame_align_x;
   float align_offset_y = thickness*frame_align_y;
   built_segments = build_tab(
      x+width + align_offset_x + frame_offset_x,
      y+height + align_offset_y + frame_offset_y,
      tab_length,
      tab_thickness,
      0.0f,
      false, false, true, true,
      color
   );
   result.insert(result.end(), built_segments.begin(), built_segments.end());

   return result;
}

std::vector<ALLEGRO_VERTEX> PanningGrid::build_bracketed_box(float x, float y, float width, float height, float thickness, float align_x, float align_y, float bracket_thickness, float bracket_offset_x, float bracket_offset_y, ALLEGRO_COLOR box_color, ALLEGRO_COLOR bracket_color)
{
   std::vector<ALLEGRO_VERTEX> built_segments;
   std::vector<ALLEGRO_VERTEX> result;
   bool t = true;

   // Build box
   built_segments = build_rectangle_frame_segments(
      x,
      y,
      width,
      height,
      thickness,
      align_x,
      align_y,
      t, t, t, t, t, t, t, t,
      box_color
   );
   result.insert(result.end(), built_segments.begin(), built_segments.end());

   // Build brackets
   built_segments = build_bracket(
         x,
         y,
         width,
         height,
         bracket_thickness, bracket_thickness * 3, 1.0f, 1.0f,
         bracket_offset_x,
         bracket_offset_y,
         bracket_color
      );
   result.insert(result.end(), built_segments.begin(), built_segments.end());

   return result;
}

std::vector<ALLEGRO_VERTEX> PanningGrid::build_rectangle_frame_segments(float x, float y, float width, float height, float thickness, float align_x, float align_y, bool include_top_segment, bool include_top_right_segment, bool include_right_segment, bool include_bottom_right_segment, bool include_bottom_segment, bool include_bottom_left_segment, bool include_left_segment, bool include_top_left_segment, ALLEGRO_COLOR color)
{
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[PanningGrid::build_rectangle_frame_segments]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PanningGrid::build_rectangle_frame_segments: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   std::vector<ALLEGRO_VERTEX> built_segments;
   std::vector<ALLEGRO_VERTEX> result;

   float bar_width = width - (thickness * (1.0 - align_x)) * 2;
   float bar_height = height - (thickness * (1.0 - align_y)) * 2;
   float bar_additional_offset_x = (thickness * (1.0 - align_x));
   float bar_additional_offset_y = (thickness * (1.0 - align_y));

   ALLEGRO_VERTEX vtx_a = AllegroFlare::build_vertex(0, 0, 0, color, 0, 0);
   ALLEGRO_VERTEX vtx_b = AllegroFlare::build_vertex(1, 0, 0, color, 0, 0);
   ALLEGRO_VERTEX vtx_c = AllegroFlare::build_vertex(1, 1, 0, color, 0, 0);
   ALLEGRO_VERTEX vtx_d = AllegroFlare::build_vertex(0, 1, 0, color, 0, 0);
   std::vector<ALLEGRO_VERTEX> segment_vertices = { vtx_a, vtx_b, vtx_d, vtx_b, vtx_c, vtx_d };

   // Top left
   if (include_top_left_segment)
   {
      built_segments = build_tall_cross_segments(
            x,
            y,
            thickness,
            width-thickness,
            align_x,
            align_y,
            false, false, false, false, true, color
         );
      result.insert(result.end(), built_segments.begin(), built_segments.end());
   }

   // Top right
   if (include_top_right_segment)
   {
      built_segments = build_tall_cross_segments(
            x+width,
            y,
            thickness,
            height-thickness,
            1.0 - align_x,
            align_y,
            false, false, false, false, true, color
         );
      result.insert(result.end(), built_segments.begin(), built_segments.end());
   }

   // Bottom right
   if (include_bottom_right_segment)
   {
      built_segments = build_tall_cross_segments(
            x+width,
            y+height,
            thickness,
            0.0f,
            1.0 - align_x,
            1.0 - align_y,
            false, false, false, false, true, color
         );
      result.insert(result.end(), built_segments.begin(), built_segments.end());
   }

   // Bottom left
   if (include_bottom_left_segment)
   {
      built_segments = build_tall_cross_segments(
            x,
            y+height,
            thickness,
            width-thickness,
            align_x,
            1.0 - align_y,
            false, false, false, false, true, color
         );
      result.insert(result.end(), built_segments.begin(), built_segments.end());
   }

   // Top bar
   if (include_top_segment)
   {
      built_segments = segment_vertices;
      for (auto &vertex : built_segments)
      {
         vertex.x *= bar_width;
         vertex.y *= thickness;
         vertex.x += x + bar_additional_offset_x;
         vertex.y += y - (thickness * align_y);
      }
      result.insert(result.end(), built_segments.begin(), built_segments.end());
   }

   // Bottom bar
   if (include_bottom_segment)
   {
      built_segments = segment_vertices;
      for (auto &vertex : built_segments)
      {
         vertex.x *= bar_width;
         vertex.y *= thickness;
         vertex.x += x + bar_additional_offset_x;
         vertex.y += y + height - (thickness * (1.0 - align_y));
      }
      result.insert(result.end(), built_segments.begin(), built_segments.end());
   }

   // Left bar
   if (include_left_segment)
   {
      built_segments = segment_vertices;
      for (auto &vertex : built_segments)
      {
         vertex.x *= thickness;
         vertex.y *= bar_height;
         vertex.x += x - (thickness * align_x);
         vertex.y += y + bar_additional_offset_y;
      }
      result.insert(result.end(), built_segments.begin(), built_segments.end());
   }

   // Right bar
   if (include_right_segment)
   {
      built_segments = segment_vertices;
      for (auto &vertex : built_segments)
      {
         vertex.x *= thickness;
         vertex.y *= bar_height;
         vertex.x += x + width - (thickness * (1.0 - align_x));
         vertex.y += y + bar_additional_offset_y;
      }
      result.insert(result.end(), built_segments.begin(), built_segments.end());
   }

   return result;
}

std::vector<ALLEGRO_VERTEX> PanningGrid::build_tall_cross_segments(float x, float y, float line_size, float y_distance, float line_align_x, float line_align_y, bool include_top_segment, bool include_right_segment, bool include_bottom_segment, bool include_left_segment, bool include_middle_segment, ALLEGRO_COLOR color)
{
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[PanningGrid::build_tall_cross_segments]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PanningGrid::build_tall_cross_segments: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   // TODO: Revise this method's arguments for clarity and practical application
   float t = line_size; // "t" means "thickness"
   float l = y_distance / line_size;      // "l" means "length"

   ALLEGRO_VERTEX vtx_a = AllegroFlare::build_vertex(0, 0, 0, color, 0, 0);
   ALLEGRO_VERTEX vtx_b = AllegroFlare::build_vertex(1, 0, 0, color, 0, 0);
   ALLEGRO_VERTEX vtx_c = AllegroFlare::build_vertex(1, 1, 0, color, 0, 0);
   ALLEGRO_VERTEX vtx_d = AllegroFlare::build_vertex(0, 1, 0, color, 0, 0);

   ALLEGRO_VERTEX vtx_e = AllegroFlare::build_vertex(0, -l, 0, color, 0, 0);
   ALLEGRO_VERTEX vtx_f = AllegroFlare::build_vertex(1, -l, 0, color, 0, 0);
   ALLEGRO_VERTEX vtx_g = AllegroFlare::build_vertex(-l, 0, 0, color, 0, 0);
   ALLEGRO_VERTEX vtx_h = AllegroFlare::build_vertex(-l, 1, 0, color, 0, 0);

   ALLEGRO_VERTEX vtx_i = AllegroFlare::build_vertex(0, 1+l, 0, color, 0, 0);
   ALLEGRO_VERTEX vtx_j = AllegroFlare::build_vertex(1, 1+l, 0, color, 0, 0);
   ALLEGRO_VERTEX vtx_k = AllegroFlare::build_vertex(1+l, 0, 0, color, 0, 0);
   ALLEGRO_VERTEX vtx_l = AllegroFlare::build_vertex(1+l, 1, 0, color, 0, 0);

   // Define a segments
   std::vector<ALLEGRO_VERTEX> initial_segment_vertices = { vtx_a, vtx_b, vtx_d, vtx_b, vtx_c, vtx_d };
   std::vector<ALLEGRO_VERTEX> left_segment_vertices = { vtx_g, vtx_a, vtx_h, vtx_a, vtx_d, vtx_h };
   std::vector<ALLEGRO_VERTEX> right_segment_vertices = { vtx_b, vtx_k, vtx_c, vtx_k, vtx_l, vtx_c };
   std::vector<ALLEGRO_VERTEX> top_segment_vertices = { vtx_e, vtx_f, vtx_a, vtx_f, vtx_b, vtx_a };
   std::vector<ALLEGRO_VERTEX> bottom_segment_vertices = { vtx_d, vtx_c, vtx_i, vtx_c, vtx_j, vtx_i };

   // Create multiple line segments
   std::vector<ALLEGRO_VERTEX> result;

   // Create the initial segment
   //std::vector<ALLEGRO_VERTEX> segment_to_insert_vertices = segment_vertices;
   if (include_middle_segment)
      result.insert(result.end(), initial_segment_vertices.begin(), initial_segment_vertices.end());

   if (include_left_segment)
      result.insert(result.end(), left_segment_vertices.begin(), left_segment_vertices.end());

   if (include_right_segment)
      result.insert(result.end(), right_segment_vertices.begin(), right_segment_vertices.end());

   if (include_top_segment)
      result.insert(result.end(), top_segment_vertices.begin(), top_segment_vertices.end());

   if (include_bottom_segment)
      result.insert(result.end(), bottom_segment_vertices.begin(), bottom_segment_vertices.end());

   // Create the segment above
   //std::vector<ALLEGRO_VERTEX> segment_to_insert_vertices = segment_vertices;
      //for (auto &vertex : segment_to_insert_vertices)
      //{
          //vertex.y += (y_distance * i);
   //result.insert(result.end(), segment_to_insert_vertices.begin(), segment_to_insert_vertices.end());

   //for (int i=0; i<num_ticks; i++)
   //{
      //std::vector<ALLEGRO_VERTEX> segment_to_insert_vertices = segment_vertices;
      //for (auto &vertex : segment_to_insert_vertices)
      //{
          //vertex.y += (y_distance * i);
      //}

      //result.insert(result.end(), segment_to_insert_vertices.begin(), segment_to_insert_vertices.end());
   //}

   // Scane and position the result
   for (auto &vertex : result)
   {
      vertex.x *= line_size;
      vertex.y *= line_size;
      vertex.x += x - line_size * line_align_x;
      vertex.y += y - line_size * line_align_y;
   }

   //al_draw_prim(&result[0], NULL, NULL, 0, result.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
   return result;
}

std::vector<ALLEGRO_VERTEX> PanningGrid::draw_tall_cross(float x, float y, float line_size, float y_distance, int num_ticks, float line_align_x, float line_align_y, ALLEGRO_COLOR color)
{
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[PanningGrid::draw_tall_cross]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PanningGrid::draw_tall_cross: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   // TODO: Is this method copy/pasta? Is it used anywhere?
   // TODO: Revise this method's arguments for clarity and practical application
   float t = line_size; // "t" means "thickness"
   float l = y_distance / line_size;      // "l" means "length"

   ALLEGRO_VERTEX vtx_a = AllegroFlare::build_vertex(0, 0, 0, color, 0, 0);
   ALLEGRO_VERTEX vtx_b = AllegroFlare::build_vertex(1, 0, 0, color, 0, 0);
   ALLEGRO_VERTEX vtx_c = AllegroFlare::build_vertex(1, 1, 0, color, 0, 0);
   ALLEGRO_VERTEX vtx_d = AllegroFlare::build_vertex(0, 1, 0, color, 0, 0);

   ALLEGRO_VERTEX vtx_e = AllegroFlare::build_vertex(0, -l, 0, color, 0, 0);
   ALLEGRO_VERTEX vtx_f = AllegroFlare::build_vertex(1, -l, 0, color, 0, 0);
   ALLEGRO_VERTEX vtx_g = AllegroFlare::build_vertex(-l, 0, 0, color, 0, 0);
   ALLEGRO_VERTEX vtx_h = AllegroFlare::build_vertex(-l, 1, 0, color, 0, 0);

   ALLEGRO_VERTEX vtx_i = AllegroFlare::build_vertex(0, 1+l, 0, color, 0, 0);
   ALLEGRO_VERTEX vtx_j = AllegroFlare::build_vertex(1, 1+l, 0, color, 0, 0);
   ALLEGRO_VERTEX vtx_k = AllegroFlare::build_vertex(1+l, 0, 0, color, 0, 0);
   ALLEGRO_VERTEX vtx_l = AllegroFlare::build_vertex(1+l, 1, 0, color, 0, 0);

   // Define a segments
   std::vector<ALLEGRO_VERTEX> initial_segment_vertices = { vtx_a, vtx_b, vtx_d, vtx_b, vtx_c, vtx_d };
   std::vector<ALLEGRO_VERTEX> left_segment_vertices = { vtx_g, vtx_a, vtx_h, vtx_a, vtx_d, vtx_h };
   std::vector<ALLEGRO_VERTEX> right_segment_vertices = { vtx_b, vtx_k, vtx_c, vtx_k, vtx_l, vtx_c };
   std::vector<ALLEGRO_VERTEX> top_segment_vertices = { vtx_e, vtx_f, vtx_a, vtx_f, vtx_b, vtx_a };
   std::vector<ALLEGRO_VERTEX> bottom_segment_vertices = { vtx_d, vtx_c, vtx_i, vtx_c, vtx_j, vtx_i };

   // Create multiple line segments
   std::vector<ALLEGRO_VERTEX> result;

   // Create the initial segment
   //std::vector<ALLEGRO_VERTEX> segment_to_insert_vertices = segment_vertices;
   result.insert(result.end(), initial_segment_vertices.begin(), initial_segment_vertices.end());
   result.insert(result.end(), left_segment_vertices.begin(), left_segment_vertices.end());
   result.insert(result.end(), right_segment_vertices.begin(), right_segment_vertices.end());
   result.insert(result.end(), top_segment_vertices.begin(), top_segment_vertices.end());
   result.insert(result.end(), bottom_segment_vertices.begin(), bottom_segment_vertices.end());

   // Create the segment above
   //std::vector<ALLEGRO_VERTEX> segment_to_insert_vertices = segment_vertices;
      //for (auto &vertex : segment_to_insert_vertices)
      //{
          //vertex.y += (y_distance * i);
   //result.insert(result.end(), segment_to_insert_vertices.begin(), segment_to_insert_vertices.end());

   //for (int i=0; i<num_ticks; i++)
   //{
      //std::vector<ALLEGRO_VERTEX> segment_to_insert_vertices = segment_vertices;
      //for (auto &vertex : segment_to_insert_vertices)
      //{
          //vertex.y += (y_distance * i);
      //}

      //result.insert(result.end(), segment_to_insert_vertices.begin(), segment_to_insert_vertices.end());
   //}

   // Scane and position the result
   for (auto &vertex : result)
   {
      vertex.x *= line_size;
      vertex.y *= line_size;
      vertex.x += x - line_size * line_align_x;
      vertex.y += y - line_size * line_align_y;
   }

   al_draw_prim(&result[0], NULL, NULL, 0, result.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
   return result;
}

std::vector<ALLEGRO_VERTEX> PanningGrid::draw_cross(float x, float y, float line_size, float line_align_x, float line_align_y, ALLEGRO_COLOR color)
{
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[PanningGrid::draw_cross]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PanningGrid::draw_cross: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   float segment_length = 6;

   ALLEGRO_VERTEX vtx_a = AllegroFlare::build_vertex(0, 0, 0, color, 0, 0);
   ALLEGRO_VERTEX vtx_b = AllegroFlare::build_vertex(1, 0, 0, color, 0, 0);
   ALLEGRO_VERTEX vtx_c = AllegroFlare::build_vertex(1, 1, 0, color, 0, 0);
   ALLEGRO_VERTEX vtx_d = AllegroFlare::build_vertex(0, 1, 0, color, 0, 0);

   ALLEGRO_VERTEX vtx_e = AllegroFlare::build_vertex(0, -1, 0, color, 0, 0);
   ALLEGRO_VERTEX vtx_f = AllegroFlare::build_vertex(1, -1, 0, color, 0, 0);
   ALLEGRO_VERTEX vtx_g = AllegroFlare::build_vertex(-1, 0, 0, color, 0, 0);
   ALLEGRO_VERTEX vtx_h = AllegroFlare::build_vertex(-1, 1, 0, color, 0, 0);

   ALLEGRO_VERTEX vtx_i = AllegroFlare::build_vertex(0, 2, 0, color, 0, 0);
   ALLEGRO_VERTEX vtx_j = AllegroFlare::build_vertex(1, 2, 0, color, 0, 0);
   ALLEGRO_VERTEX vtx_k = AllegroFlare::build_vertex(2, 0, 0, color, 0, 0);
   ALLEGRO_VERTEX vtx_l = AllegroFlare::build_vertex(2, 1, 0, color, 0, 0);

   // Define a segments
   std::vector<ALLEGRO_VERTEX> initial_segment_vertices = { vtx_a, vtx_b, vtx_d, vtx_b, vtx_c, vtx_d };
   std::vector<ALLEGRO_VERTEX> left_segment_vertices = { vtx_g, vtx_a, vtx_h, vtx_a, vtx_d, vtx_h };
   std::vector<ALLEGRO_VERTEX> right_segment_vertices = { vtx_b, vtx_k, vtx_c, vtx_k, vtx_l, vtx_c };
   std::vector<ALLEGRO_VERTEX> top_segment_vertices = { vtx_e, vtx_f, vtx_a, vtx_f, vtx_b, vtx_a };
   std::vector<ALLEGRO_VERTEX> bottom_segment_vertices = { vtx_d, vtx_c, vtx_i, vtx_c, vtx_j, vtx_i };

   // Create multiple line segments
   std::vector<ALLEGRO_VERTEX> result;

   // Create the initial segment
   result.insert(result.end(), initial_segment_vertices.begin(), initial_segment_vertices.end());
   result.insert(result.end(), left_segment_vertices.begin(), left_segment_vertices.end());
   result.insert(result.end(), right_segment_vertices.begin(), right_segment_vertices.end());
   result.insert(result.end(), top_segment_vertices.begin(), top_segment_vertices.end());
   result.insert(result.end(), bottom_segment_vertices.begin(), bottom_segment_vertices.end());

   // Scane and position the result
   for (auto &vertex : result)
   {
      vertex.x *= line_size;
      vertex.y *= line_size;
      vertex.x += x - line_size * line_align_x;
      vertex.y += y - line_size * line_align_y;
   }

   al_draw_prim(&result[0], NULL, NULL, 0, result.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
   return result;
}

void PanningGrid::draw_vertical_ruler(float x, float y, float tick_width, float tick_height, float y_distance, int num_ticks, float tick_align_x, float tick_align_y, ALLEGRO_COLOR color)
{
   std::vector<ALLEGRO_VERTEX> vertices = build_vertical_ruler(
         x, y, tick_width, tick_height, y_distance, num_ticks, tick_align_x, tick_align_y, color
      );
   al_draw_prim(&vertices[0], NULL, NULL, 0, vertices.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
}

void PanningGrid::draw_vertical_ruler_numbers(float x, float y, int number_start, int number_increment, float y_distance, int num_ticks, float text_align_x, float text_align_y, ALLEGRO_COLOR color)
{
   for (int i=0; i<num_ticks; i++)
   {
      draw_number(x, y+y_distance*i, number_start + number_increment*i, 2, text_align_x, text_align_y, color);
   }
}

std::vector<ALLEGRO_VERTEX> PanningGrid::build_vertical_ruler(float x, float y, float tick_width, float tick_height, float y_distance, int num_ticks, float tick_align_x, float tick_align_y, ALLEGRO_COLOR color)
{
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[PanningGrid::build_vertical_ruler]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PanningGrid::build_vertical_ruler: error: guard \"al_is_primitives_addon_initialized()\" not met");
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

ALLEGRO_FONT* PanningGrid::obtain_small_hud_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[PanningGrid::obtain_small_hud_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PanningGrid::obtain_small_hud_font: error: guard \"font_bin\" not met");
   }
   std::stringstream result_font_identifier;
   result_font_identifier << "Orbitron-Medium.ttf" << " " << -13;
   return font_bin->auto_get(result_font_identifier.str());
}

ALLEGRO_FONT* PanningGrid::obtain_sized_font(int size)
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[PanningGrid::obtain_sized_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PanningGrid::obtain_sized_font: error: guard \"font_bin\" not met");
   }
   std::stringstream result_font_identifier;
   result_font_identifier << "Orbitron-Medium.ttf" << " " << size;
   return font_bin->auto_get(result_font_identifier.str());
}


} // namespace FUI
} // namespace Elements
} // namespace AllegroFlare


