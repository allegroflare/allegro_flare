

#include <AllegroFlare/TileMaps/MultiMesh.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace TileMaps
{


MultiMesh::MultiMesh(std::size_t num_items)
   : num_items(num_items)
   , vertex_buffer(nullptr)
   , vertex_decl(nullptr)
   , texture(nullptr)
   , vertices_in_use(0)
   , atlas()
   , initialized(false)
{
}


MultiMesh::~MultiMesh()
{
}


void MultiMesh::set_texture(ALLEGRO_BITMAP* texture)
{
   this->texture = texture;
}


std::size_t MultiMesh::get_num_items() const
{
   return num_items;
}


ALLEGRO_BITMAP* MultiMesh::get_texture() const
{
   return texture;
}


void MultiMesh::set_atlas(AllegroFlare::TileMaps::MultiMeshUVAtlas atlas)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TileMaps::MultiMesh::set_atlas]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TileMaps::MultiMesh::set_atlas]: error: guard \"(!initialized)\" not met");
   }
   this->atlas = atlas;
   return;
}

void MultiMesh::set_num_items(std::size_t num_items)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TileMaps::MultiMesh::set_num_items]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TileMaps::MultiMesh::set_num_items]: error: guard \"(!initialized)\" not met");
   }
   this->num_items = num_items;
   return;
}

int MultiMesh::infer_num_items_in_use()
{
   return (vertices_in_use / VERTICES_PER_ITEM);
}

int MultiMesh::infer_largest_index_num_in_use()
{
   return (vertices_in_use / VERTICES_PER_ITEM) - 1;
}

void MultiMesh::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TileMaps::MultiMesh::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TileMaps::MultiMesh::initialize]: error: guard \"(!initialized)\" not met");
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TileMaps::MultiMesh::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TileMaps::MultiMesh::initialize]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TileMaps::MultiMesh::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TileMaps::MultiMesh::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   int num_vertices = num_items * VERTICES_PER_ITEM;

   // create the vertex declaration
   ALLEGRO_VERTEX_ELEMENT elems[] = {
      {ALLEGRO_PRIM_POSITION, ALLEGRO_PRIM_FLOAT_3, offsetof(ALLEGRO_VERTEX, x)},
      {ALLEGRO_PRIM_TEX_COORD_PIXEL, ALLEGRO_PRIM_FLOAT_2, offsetof(ALLEGRO_VERTEX, u)},
      {ALLEGRO_PRIM_COLOR_ATTR, 0, offsetof(ALLEGRO_VERTEX, color)},
      {0, 0, 0}
   };
   vertex_decl = al_create_vertex_decl(elems, sizeof(ALLEGRO_VERTEX));

   // vertex buffer, data will be uninitialized
   const void* initial_data_vb = nullptr;
   vertex_buffer = al_create_vertex_buffer(
      vertex_decl,
      initial_data_vb,
      num_vertices,
      ALLEGRO_PRIM_BUFFER_READWRITE
   );

   initialized = true;
   return;
}

int MultiMesh::append(int atlas_item_index_num, float x, float y)
{
   AllegroFlare::TileMaps::MultiMeshUV atlas_item = atlas.get(atlas_item_index_num);
   return append_raw(
      x,
      y,
      atlas_item.infer_width(),
      atlas_item.infer_height(),
      atlas_item.get_u1(),
      atlas_item.get_v1(),
      atlas_item.get_u2(),
      atlas_item.get_v2()
   );
}

int MultiMesh::append_raw(float x, float y, float w, float h, float u1, float v1, float u2, float v2)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TileMaps::MultiMesh::append_raw]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TileMaps::MultiMesh::append_raw]: error: guard \"initialized\" not met");
   }
   ALLEGRO_COLOR color{1, 1, 1, 1};
   ALLEGRO_VERTEX item_vertexes[VERTICES_PER_ITEM] = {
      ALLEGRO_VERTEX{x+0, y+0, 0, u1, v1, color},
      ALLEGRO_VERTEX{x+0, y+h, 0, u1, v2, color},
      ALLEGRO_VERTEX{x+w, y+0, 0, u2, v1, color},
      ALLEGRO_VERTEX{x+w, y+0, 0, u2, v1, color},
      ALLEGRO_VERTEX{x+0, y+h, 0, u1, v2, color},
      ALLEGRO_VERTEX{x+w, y+h, 0, u2, v2, color},
   };

   // lock the vertex buffer
   ALLEGRO_VERTEX* start = (ALLEGRO_VERTEX*)al_lock_vertex_buffer(
      vertex_buffer,
      vertices_in_use,
      VERTICES_PER_ITEM,
      ALLEGRO_LOCK_WRITEONLY
   );

   // fill 6 vertexes @ ind
   for (int i=0; i<VERTICES_PER_ITEM; i++) start[i] = item_vertexes[i];

   // unlock
   al_unlock_vertex_buffer(vertex_buffer);

   // capture the current index of this newly appended item
   int this_item_index = vertices_in_use / VERTICES_PER_ITEM;

   // increase vertices_in_use by 6
   vertices_in_use += VERTICES_PER_ITEM;

   return this_item_index;
}

int MultiMesh::remove(int item_index)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TileMaps::MultiMesh::remove]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TileMaps::MultiMesh::remove]: error: guard \"initialized\" not met");
   }
   // TODO: validate position exists, does not overflow, etc
   if (item_index < 0)
   {
      std::stringstream error_message;
      error_message << "AllegroFlare::TileMaps::MultiMesh::remove() error: "
                    << "The item_index that was passed (" << item_index << ") cannot be less than zero.";
      throw std::runtime_error(error_message.str());
   }
   if (item_index > infer_largest_index_num_in_use())
   {
      std::stringstream error_message;
      error_message << "AllegroFlare::TileMaps::MultiMesh::remove() error: "
                    << "The item_index that was passed (" << item_index << ") cannot be greater than or equal to "
                    << "the largest existing item index (" << infer_largest_index_num_in_use() << ").";
      throw std::runtime_error(error_message.str());
   }

   int item_start_index = item_index * VERTICES_PER_ITEM;
   int length = vertices_in_use - item_start_index; // all the way to the end of vertices_in_use
   bool removed_vertex_is_at_end = (item_start_index == vertices_in_use-VERTICES_PER_ITEM);

   // lock @ index to vertices_in_use
   ALLEGRO_VERTEX* start = (ALLEGRO_VERTEX*)al_lock_vertex_buffer(
      vertex_buffer,
      item_start_index,
      length,
      ALLEGRO_LOCK_READWRITE
   );

   // copy vertexes from end (end-6) into removed position (if not already at end)
   if (!removed_vertex_is_at_end) for (int i=0; i<VERTICES_PER_ITEM; i++)
   {
      start[i] = start[i + length-VERTICES_PER_ITEM];
   }

   // unlock
   al_unlock_vertex_buffer(vertex_buffer);

   // reduce vertices_in_use by 6
   vertices_in_use -= VERTICES_PER_ITEM;
   if (removed_vertex_is_at_end) return item_index;
   return vertices_in_use / VERTICES_PER_ITEM;
}

void MultiMesh::render()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TileMaps::MultiMesh::render]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TileMaps::MultiMesh::render]: error: guard \"initialized\" not met");
   }
   if (vertices_in_use == 0) return;
   al_draw_vertex_buffer(vertex_buffer, texture, 0, vertices_in_use, ALLEGRO_PRIM_TRIANGLE_LIST);
   return;
}


} // namespace TileMaps
} // namespace AllegroFlare


