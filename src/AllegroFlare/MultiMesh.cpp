

#include <AllegroFlare/MultiMesh.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{


MultiMesh::MultiMesh(std::size_t num_items)
   : num_items(num_items)
   , vertex_buffer(nullptr)
   , vertex_decl(nullptr)
   , texture(nullptr)
   , vertices_in_use(0)
   , VERTEXES_PER_ITEM(6)
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


void MultiMesh::set_atlas(AllegroFlare::MultiMeshUVAtlas atlas)
{
   if (!((!initialized)))
      {
         std::stringstream error_message;
         error_message << "MultiMesh" << "::" << "set_atlas" << ": error: " << "guard \"(!initialized)\" not met";
         throw std::runtime_error(error_message.str());
      }
   this->atlas = atlas;
   return;
}

void MultiMesh::set_num_items(std::size_t num_items)
{
   if (!((!initialized)))
      {
         std::stringstream error_message;
         error_message << "MultiMesh" << "::" << "set_num_items" << ": error: " << "guard \"(!initialized)\" not met";
         throw std::runtime_error(error_message.str());
      }
   this->num_items = num_items;
   return;
}

void MultiMesh::initialize()
{
   if (!((!initialized)))
      {
         std::stringstream error_message;
         error_message << "MultiMesh" << "::" << "initialize" << ": error: " << "guard \"(!initialized)\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "MultiMesh" << "::" << "initialize" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_primitives_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "MultiMesh" << "::" << "initialize" << ": error: " << "guard \"al_is_primitives_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   int num_vertices = num_items * VERTEXES_PER_ITEM;

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

void MultiMesh::append(int atlas_item_index_num, float x, float y)
{
   AllegroFlare::MultiMeshUV atlas_item = atlas.get(atlas_item_index_num);
   append_raw(
      x,
      y,
      atlas_item.infer_width(),
      atlas_item.infer_height(),
      atlas_item.get_u1(),
      atlas_item.get_v1(),
      atlas_item.get_u2(),
      atlas_item.get_v2()
   );
   return;
}

void MultiMesh::append_raw(float x, float y, float w, float h, float u1, float v1, float u2, float v2)
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "MultiMesh" << "::" << "append_raw" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   ALLEGRO_COLOR color{1, 1, 1, 1};
   ALLEGRO_VERTEX item_vertexes[6] = {
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
      VERTEXES_PER_ITEM,
      ALLEGRO_LOCK_WRITEONLY
   );

   // fill 6 vertexes @ ind
   for (int i=0; i<6; i++) start[i] = item_vertexes[i];

   // unlock
   al_unlock_vertex_buffer(vertex_buffer);

   // increase vertices_in_use by 6
   vertices_in_use += 6;
   return;
}

int MultiMesh::remove(int item_index)
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "MultiMesh" << "::" << "remove" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   // TODO: validate position exists, does not overflow, etc
   int item_start_index = item_index * VERTEXES_PER_ITEM;
   int length = vertices_in_use - item_start_index; // all the way to the end of vertices_in_use
   bool removed_vertex_is_at_end = (item_start_index == vertices_in_use-VERTEXES_PER_ITEM);

   // lock @ index to vertices_in_use
   ALLEGRO_VERTEX* start = (ALLEGRO_VERTEX*)al_lock_vertex_buffer(
      vertex_buffer,
      item_start_index,
      length,
      ALLEGRO_LOCK_READWRITE
   );

   // copy vertexes from end (end-6) into removed position (if not already at end)
   if (!removed_vertex_is_at_end) for (int i=0; i<6; i++) start[i] = start[i + length-VERTEXES_PER_ITEM];

   // unlock
   al_unlock_vertex_buffer(vertex_buffer);

   // reduce vertices_in_use by 6
   vertices_in_use -= 6;
   if (removed_vertex_is_at_end) return item_index;
   return vertices_in_use / VERTEXES_PER_ITEM;
}

void MultiMesh::render()
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "MultiMesh" << "::" << "render" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (vertices_in_use == 0) return;
   al_draw_vertex_buffer(vertex_buffer, texture, 0, vertices_in_use, ALLEGRO_PRIM_TRIANGLE_LIST);
   return;
}
} // namespace AllegroFlare


