

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
   , left_column_width(128.0f)
   , center_column_width(128.0f)
   , right_column_width(128.0f)
   , top_row_height(128.0f)
   , middle_row_height(128.0f)
   , bottom_row_height(128.0f)
   , mesh()
{
}


NinePatch::~NinePatch()
{
}


void NinePatch::set_source_texture(ALLEGRO_BITMAP* source_texture)
{
   this->source_texture = source_texture;
}


ALLEGRO_BITMAP* NinePatch::get_source_texture() const
{
   return source_texture;
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
   if (!(source_texture))
   {
      std::stringstream error_message;
      error_message << "[NinePatch::render]: error: guard \"source_texture\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("NinePatch::render: error: guard \"source_texture\" not met");
   }
   al_draw_prim(&mesh[0], NULL, source_texture, 0, mesh.size(), ALLEGRO_PRIM_TRIANGLE_LIST);

   //al_draw_prim(v, NULL, NULL, 0, 4, ALLEGRO_PRIM_TRIANGLE_FAN);
   return;
}

void NinePatch::build_mesh()
{
   mesh.clear();
   //vector1.insert(vector1.end(), vector2.begin(), vector2.end());
   std::vector<ALLEGRO_VERTEX> top_left_patch = adjust_rect(
         build_vertices_for_rect(),
         0,
         0,
         left_column_width,
         top_row_height,
         0,
         0,
         32,
         32
      );
   mesh.insert(mesh.end(), top_left_patch.begin(), top_left_patch.end());
   // TODO: Continue to add remaining patches
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
      vertex.u = vertex.u * uw + u;
      vertex.v = vertex.v * vh + v;
   }
   return vertices;
}


} // namespace Elements
} // namespace AllegroFlare


