

#include <Tileo/MeshWithNormals.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Tileo
{


MeshWithNormals::MeshWithNormals(int num_columns, int num_rows, float tile_width, float tile_height, AllegroFlare::TileMaps::PrimMeshAtlas* atlas, AllegroFlare::TileMaps::PrimMeshAtlas* normal_atlas)
   : tileo_tile_vertex_allegro_vertex_declaration()
   , num_columns(num_columns)
   , num_rows(num_rows)
   , tile_width(tile_width)
   , tile_height(tile_height)
   , atlas(atlas)
   , normal_atlas(normal_atlas)
   , tile_ids()
   , normal_tile_ids()
   , vertexes()
   , initialized(false)
   , destroyed(false)
{
}


MeshWithNormals::~MeshWithNormals()
{
}


int MeshWithNormals::get_num_columns() const
{
   return num_columns;
}


int MeshWithNormals::get_num_rows() const
{
   return num_rows;
}


std::vector<TILEO_TILE_VERTEX> &MeshWithNormals::get_vertexes_ref()
{
   return vertexes;
}


void MeshWithNormals::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Tileo::MeshWithNormals::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Tileo::MeshWithNormals::initialize]: error: guard \"(!initialized)\" not met");
   }
   if (!((num_columns >= 0)))
   {
      std::stringstream error_message;
      error_message << "[Tileo::MeshWithNormals::initialize]: error: guard \"(num_columns >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Tileo::MeshWithNormals::initialize]: error: guard \"(num_columns >= 0)\" not met");
   }
   if (!((num_rows >= 0)))
   {
      std::stringstream error_message;
      error_message << "[Tileo::MeshWithNormals::initialize]: error: guard \"(num_rows >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Tileo::MeshWithNormals::initialize]: error: guard \"(num_rows >= 0)\" not met");
   }
   tileo_tile_vertex_allegro_vertex_declaration.initialize();
   resize(num_columns, num_rows);
   initialized = true;
   return;
}

void MeshWithNormals::destroy()
{
   // TODO: guards
   tileo_tile_vertex_allegro_vertex_declaration.destroy();
   destroyed = true;
   return;
}

ALLEGRO_VERTEX_DECL* MeshWithNormals::obtain_vertex_declaration()
{
   return tileo_tile_vertex_allegro_vertex_declaration.get_vertex_declaration();
}

void MeshWithNormals::resize(int num_columns, int num_rows)
{
   if (!((num_columns >= 0)))
   {
      std::stringstream error_message;
      error_message << "[Tileo::MeshWithNormals::resize]: error: guard \"(num_columns >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Tileo::MeshWithNormals::resize]: error: guard \"(num_columns >= 0)\" not met");
   }
   if (!((num_rows >= 0)))
   {
      std::stringstream error_message;
      error_message << "[Tileo::MeshWithNormals::resize]: error: guard \"(num_rows >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Tileo::MeshWithNormals::resize]: error: guard \"(num_rows >= 0)\" not met");
   }
   this->num_columns = num_columns;
   this->num_rows = num_rows;

   clear_and_reserve();
   place_vertexes_into_tile_mesh_shape();

   return;
}

bool MeshWithNormals::set_tile(int tile_x, int tile_y, int tile_index_num)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Tileo::MeshWithNormals::set_tile]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Tileo::MeshWithNormals::set_tile]: error: guard \"initialized\" not met");
   }
   if (!(atlas))
   {
      std::stringstream error_message;
      error_message << "[Tileo::MeshWithNormals::set_tile]: error: guard \"atlas\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Tileo::MeshWithNormals::set_tile]: error: guard \"atlas\" not met");
   }
   if (tile_x < 0) return false;
   if (tile_x >= num_columns) return false;
   if (tile_y < 0) return false;
   if (tile_y >= num_rows) return false;

   tile_ids[tile_x + tile_y * num_columns] = tile_index_num;

   int atlas_bitmap_width = atlas->get_bitmap_width(); // <- TODO: consider revising scaling by atlas size
   int atlas_bitmap_height = atlas->get_bitmap_height();

   if (atlas_bitmap_width <= 0 || atlas_bitmap_height <= 0) throw std::runtime_error("jiopjojop");

   float u1, v1, u2, v2 = 0;
   if (!atlas->get_tile_uv(tile_index_num, &u1, &v1, &u2, &v2)) return false;
   u1 /= atlas_bitmap_width;
   v1 /= atlas_bitmap_height;
   u2 /= atlas_bitmap_width;
   v2 /= atlas_bitmap_height;
   if (!set_tile_uv(tile_x, tile_y, u1, v1, u2, v2)) return false;

   return true;
}

bool MeshWithNormals::set_normal_tile(int tile_x, int tile_y, int tile_index_num)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Tileo::MeshWithNormals::set_normal_tile]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Tileo::MeshWithNormals::set_normal_tile]: error: guard \"initialized\" not met");
   }
   if (!(normal_atlas))
   {
      std::stringstream error_message;
      error_message << "[Tileo::MeshWithNormals::set_normal_tile]: error: guard \"normal_atlas\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Tileo::MeshWithNormals::set_normal_tile]: error: guard \"normal_atlas\" not met");
   }
   if (tile_x < 0) return false;
   if (tile_x >= num_columns) return false;
   if (tile_y < 0) return false;
   if (tile_y >= num_rows) return false;

   normal_tile_ids[tile_x + tile_y * num_columns] = tile_index_num;

   int normal_atlas_bitmap_width = normal_atlas->get_bitmap_width(); // <-- TODO: consider revising scaling by atlas
   int normal_atlas_bitmap_height = normal_atlas->get_bitmap_height();

   if (normal_atlas_bitmap_width <= 0 || normal_atlas_bitmap_height <= 0) throw std::runtime_error("asdfadfs");

   float u1, v1, u2, v2 = 0;
   if (!normal_atlas->get_tile_uv(tile_index_num, &u1, &v1, &u2, &v2)) return false;
   u1 /= normal_atlas_bitmap_width;
   v1 /= normal_atlas_bitmap_height;
   u2 /= normal_atlas_bitmap_width;
   v2 /= normal_atlas_bitmap_height;
   if (!set_normal_tile_uv(tile_x, tile_y, u1, v1, u2, v2)) return false;

   return true;
}

bool MeshWithNormals::set_tile_uv(int tile_x, int tile_y, float u1, float v1, float u2, float v2)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Tileo::MeshWithNormals::set_tile_uv]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Tileo::MeshWithNormals::set_tile_uv]: error: guard \"initialized\" not met");
   }
   if (tile_x < 0) return false;
   if (tile_x >= num_columns) return false;
   if (tile_y < 0) return false;
   if (tile_y >= num_rows) return false;

   int id_start = (tile_x + tile_y * num_columns) * 6;
   //int id_start = (tile_x * 6) * (tile_y * num_columns);

   if (id_start >= vertexes.size())
   {
      throw std::runtime_error("MeshWithNormals:set_tile_uv: unexpected assignment error");
   }

   int &i = id_start;
   vertexes[i+0].texture_u = u1;
   vertexes[i+0].texture_v = v1;
   vertexes[i+1].texture_u = u1;
   vertexes[i+1].texture_v = v2;
   vertexes[i+2].texture_u = u2;
   vertexes[i+2].texture_v = v2;
   vertexes[i+3].texture_u = u2;
   vertexes[i+3].texture_v = v2;
   vertexes[i+4].texture_u = u2;
   vertexes[i+4].texture_v = v1;
   vertexes[i+5].texture_u = u1;
   vertexes[i+5].texture_v = v1;
   return true;
}

bool MeshWithNormals::set_normal_tile_uv(int tile_x, int tile_y, float u1, float v1, float u2, float v2)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Tileo::MeshWithNormals::set_normal_tile_uv]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Tileo::MeshWithNormals::set_normal_tile_uv]: error: guard \"initialized\" not met");
   }
   if (tile_x < 0) return false;
   if (tile_x >= num_columns) return false;
   if (tile_y < 0) return false;
   if (tile_y >= num_rows) return false;

   int id_start = (tile_x + tile_y * num_columns) * 6;

   if (id_start >= vertexes.size())
   {
      throw std::runtime_error("MeshWithNormals:set_normal_tile_uv: unexpected assignment error");
   }

   int &i = id_start;
   vertexes[i+0].normal_u = u1;
   vertexes[i+0].normal_v = v1;
   vertexes[i+1].normal_u = u1;
   vertexes[i+1].normal_v = v2;
   vertexes[i+2].normal_u = u2;
   vertexes[i+2].normal_v = v2;
   vertexes[i+3].normal_u = u2;
   vertexes[i+3].normal_v = v2;
   vertexes[i+4].normal_u = u2;
   vertexes[i+4].normal_v = v1;
   vertexes[i+5].normal_u = u1;
   vertexes[i+5].normal_v = v1;
   return true;
}

void MeshWithNormals::place_vertexes_into_tile_mesh_shape()
{
   // TODO: add test

   // place the vertexes to create a mesh of boxes for tiles
   int num_vertexes = num_columns*num_rows*6;
   for (int v=0; v<num_vertexes; v+=6)
   {
      int tile_num = v / 6;
      float x1 = (tile_num % num_columns);
      float y1 = (tile_num / num_columns);
      float x2 = x1 + 1;
      float y2 = y1 + 1;

      vertexes[v+0].x = x1;
      vertexes[v+0].y = y1;
      vertexes[v+1].x = x1;
      vertexes[v+1].y = y2;
      vertexes[v+2].x = x2;
      vertexes[v+2].y = y2;
      vertexes[v+3].x = x2;
      vertexes[v+3].y = y2;
      vertexes[v+4].x = x2;
      vertexes[v+4].y = y1;
      vertexes[v+5].x = x1;
      vertexes[v+5].y = y1;
   }

   // "scale" the vertexes to tile_width and tile_height, and set other default values
   for (int v=0; v<num_vertexes; v++)
   {
      vertexes[v].x *= tile_width;
      vertexes[v].y *= tile_height;
      vertexes[v].z = 0;
      vertexes[v].color = ALLEGRO_COLOR{1, 1, 1, 1};
   }

   return;
}

void MeshWithNormals::clear_and_reserve()
{
   int num_elements = num_rows * num_columns;
   TILEO_TILE_VERTEX empty_vertex = Tileo::TileoTileVertexAllegroVertexDeclaration::build_empty_vertex();

   tile_ids.clear();
   normal_tile_ids.clear();
   vertexes.clear();

   tile_ids.resize(num_elements, 0);
   normal_tile_ids.resize(num_elements, 0);
   vertexes.resize(num_elements*6, empty_vertex);

   return;
}


} // namespace Tileo


