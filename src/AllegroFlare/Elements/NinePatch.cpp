

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
   , center_column_width(256.0f)
   , right_column_width(128.0f)
   , top_row_height(128.0f)
   , middle_row_height(256.0f)
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
   return;
}

void NinePatch::build_mesh()
{
   mesh.clear();

   // TOP ROW uvs

   std::tuple<float, float, float, float> a_uv = { 0, 0, 32, 32 };
   std::tuple<float, float, float, float> b_uv = { 32, 0, 268, 32 };
   std::tuple<float, float, float, float> c_uv = { 268, 0, 300, 32 };



   // Build the TOP ROW

   // Top left
   std::vector<ALLEGRO_VERTEX> top_left_patch =
         build_vertices_for_rect2(
         0, 0, left_column_width, top_row_height,
         a_uv
      );
   mesh.insert(mesh.end(), top_left_patch.begin(), top_left_patch.end());

   // Top center
   std::vector<ALLEGRO_VERTEX> top_center_patch =
         build_vertices_for_rect2(
         left_column_width, 0, center_column_width, top_row_height,
         b_uv
      );
   mesh.insert(mesh.end(), top_center_patch.begin(), top_center_patch.end());

   // Top right
   std::vector<ALLEGRO_VERTEX> top_right_patch =
         build_vertices_for_rect2(
         left_column_width + center_column_width, 0, right_column_width, top_row_height,
         c_uv
      );
   mesh.insert(mesh.end(), top_right_patch.begin(), top_right_patch.end());


   // Build the MIDDLE ROW

   // Top left
   std::vector<ALLEGRO_VERTEX> middle_left_patch =
         build_vertices_for_rect(
         0, top_row_height, left_column_width, middle_row_height,
         0, 32, 32, 64
      );
   mesh.insert(mesh.end(), middle_left_patch.begin(), middle_left_patch.end());

   // Top center
   std::vector<ALLEGRO_VERTEX> middle_center_patch =
         build_vertices_for_rect(
         left_column_width, top_row_height, center_column_width, middle_row_height,
         32, 32, 268, 64
      );
   mesh.insert(mesh.end(), middle_center_patch.begin(), middle_center_patch.end());

   // Top right
   std::vector<ALLEGRO_VERTEX> middle_right_patch =
         build_vertices_for_rect(
         left_column_width + center_column_width, top_row_height, right_column_width, middle_row_height,
         268, 32, 300, 64
      );
   mesh.insert(mesh.end(), middle_right_patch.begin(), middle_right_patch.end());


   // Build the BOTTOM ROW

   // Top left
   std::vector<ALLEGRO_VERTEX> bottom_left_patch =
         build_vertices_for_rect(
         0, top_row_height+middle_row_height, left_column_width, bottom_row_height,
         0, 268, 32, 300
      );
   mesh.insert(mesh.end(), bottom_left_patch.begin(), bottom_left_patch.end());

   // Top center
   std::vector<ALLEGRO_VERTEX> bottom_center_patch =
         build_vertices_for_rect(
         left_column_width, top_row_height+middle_row_height, center_column_width, bottom_row_height,
         32, 268, 268, 300
      );
   mesh.insert(mesh.end(), bottom_center_patch.begin(), bottom_center_patch.end());

   // Top right
   std::vector<ALLEGRO_VERTEX> bottom_right_patch =
         build_vertices_for_rect(
         left_column_width + center_column_width, top_row_height+middle_row_height, right_column_width, bottom_row_height,
         268, 268, 300, 300
      );
   mesh.insert(mesh.end(), bottom_right_patch.begin(), bottom_right_patch.end());

   // TODO: Continue to add remaining patches
   return;
}

std::vector<ALLEGRO_VERTEX> NinePatch::build_vertices_for_rect(float x, float y, float w, float h, float u1, float v1, float u2, float v2)
{
   std::vector<ALLEGRO_VERTEX> result = {
      ALLEGRO_VERTEX{x+0, y+0, 0, u1, v1, ALLEGRO_COLOR{1, 1, 1, 1}},
      ALLEGRO_VERTEX{x+w, y+0, 0, u2, v1, ALLEGRO_COLOR{1, 1, 1, 1}},
      ALLEGRO_VERTEX{x+0, y+h, 0, u1, v2, ALLEGRO_COLOR{1, 1, 1, 1}},
      ALLEGRO_VERTEX{x+w, y+0, 0, u2, v1, ALLEGRO_COLOR{1, 1, 1, 1}},
      ALLEGRO_VERTEX{x+0, y+h, 0, u1, v2, ALLEGRO_COLOR{1, 1, 1, 1}},
      ALLEGRO_VERTEX{x+w, y+h, 0, u2, v2, ALLEGRO_COLOR{1, 1, 1, 1}},
   };
   return result;
}

std::vector<ALLEGRO_VERTEX> NinePatch::build_vertices_for_rect2(float x, float y, float w, float h, std::tuple<float, float, float, float> uv)
{
   auto &u1 = std::get<0>(uv);
   auto &v1 = std::get<1>(uv);
   auto &u2 = std::get<2>(uv);
   auto &v2 = std::get<3>(uv);
   std::vector<ALLEGRO_VERTEX> result = {
      ALLEGRO_VERTEX{x+0, y+0, 0, u1, v1, ALLEGRO_COLOR{1, 1, 1, 1}},
      ALLEGRO_VERTEX{x+w, y+0, 0, u2, v1, ALLEGRO_COLOR{1, 1, 1, 1}},
      ALLEGRO_VERTEX{x+0, y+h, 0, u1, v2, ALLEGRO_COLOR{1, 1, 1, 1}},
      ALLEGRO_VERTEX{x+w, y+0, 0, u2, v1, ALLEGRO_COLOR{1, 1, 1, 1}},
      ALLEGRO_VERTEX{x+0, y+h, 0, u1, v2, ALLEGRO_COLOR{1, 1, 1, 1}},
      ALLEGRO_VERTEX{x+w, y+h, 0, u2, v2, ALLEGRO_COLOR{1, 1, 1, 1}},
   };
   return result;
}


} // namespace Elements
} // namespace AllegroFlare


