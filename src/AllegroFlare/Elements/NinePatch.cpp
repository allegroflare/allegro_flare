

#include <AllegroFlare/Elements/NinePatch.hpp>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{


NinePatch::NinePatch()
   : source_texture(nullptr)
   , left_column_width(16.0f)
   , center_column_width(16.0f)
   , right_column_width(16.0f)
   , top_row_height(16.0f)
   , middle_row_height(16.0f)
   , bottom_row_height(16.0f)
   , mesh()
{
}


NinePatch::~NinePatch()
{
}


void NinePatch::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[NinePatch::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("NinePatch::render: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[NinePatch::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("NinePatch::render: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   //al_draw_prim(v, NULL, NULL, 0, 4, ALLEGRO_PRIM_TRIANGLE_FAN);
   return;
}

void NinePatch::build_mesh()
{
   mesh.clear();
   //vector1.insert(vector1.end(), vector2.begin(), vector2.end());
   std::vector<ALLEGRO_VERTEX> top_left = adjust_rect(
         build_vertices_for_rect(),
         0,
         0,
         left_column_width,
         right_column_width,
         0,
         0,
         16,
         16
      );
   return;
}

std::vector<ALLEGRO_VERTEX> NinePatch::build_vertices_for_rect()
{
   std::vector<ALLEGRO_VERTEX> result = {
      ALLEGRO_VERTEX{0, 0, 0, 0, 0, ALLEGRO_COLOR{1, 1, 1, 1}},
      ALLEGRO_VERTEX{1, 0, 0, 1, 0, ALLEGRO_COLOR{1, 1, 1, 1}},
      ALLEGRO_VERTEX{0, 1, 0, 0, 1, ALLEGRO_COLOR{1, 1, 1, 1}},
      ALLEGRO_VERTEX{1, 0, 0, 1, 0, ALLEGRO_COLOR{1, 1, 1, 1}},
      ALLEGRO_VERTEX{0, 1, 0, 0, 1, ALLEGRO_COLOR{1, 1, 1, 1}},
      ALLEGRO_VERTEX{1, 1, 0, 1, 1, ALLEGRO_COLOR{1, 1, 1, 1}},
   };
   return result;
}

std::vector<ALLEGRO_VERTEX> NinePatch::adjust_rect(std::vector<ALLEGRO_VERTEX> vertices, float x, float y, float w, float h, float u, float v, float uw, float vh)
{
   for (auto &vertex : vertices)
   {
      vertex.x = vertex.x * w + x;
      vertex.y = vertex.y * h + y;
      vertex.u = vertex.u * u + uw;
      vertex.v = vertex.v * v + vh;
   }
   return vertices;
}


} // namespace Elements
} // namespace AllegroFlare


