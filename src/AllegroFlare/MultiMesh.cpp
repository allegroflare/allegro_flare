

#include <AllegroFlare/MultiMesh.hpp>
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


MultiMesh::MultiMesh()
   : vertex_buffer(nullptr)
   , texture(nullptr)
   , num_items(50)
   , vertices_in_use(0)
   , VERTEXES_PER_ITEM(6)
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


ALLEGRO_BITMAP* MultiMesh::get_texture() const
{
   return texture;
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
   ALLEGRO_VERTEX_DECL* decl = al_create_vertex_decl(elems, sizeof(ALLEGRO_VERTEX));

   // vertex buffer, data will be uninitialized
   const void* initial_data_vb = nullptr;
   vertex_buffer = al_create_vertex_buffer(
      decl,
      initial_data_vb,
      num_vertices,
      ALLEGRO_PRIM_BUFFER_READWRITE
   );

   initialized = true;
   return;
}

void MultiMesh::append(float x, float y, float w, float h, float u1, float v1, float u2, float v2)
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "MultiMesh" << "::" << "append" << ": error: " << "guard \"initialized\" not met";
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

void MultiMesh::remove(int item_index)
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "MultiMesh" << "::" << "remove" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   // TODO
   // validate position exists, does not overflow, etc
   int item_start_index = item_index * VERTEXES_PER_ITEM;
   int length = vertices_in_use - item_start_index; // all the way to the end of vertices_in_use

   // lock @ index to vertices_in_use
   ALLEGRO_VERTEX* start = (ALLEGRO_VERTEX*)al_lock_vertex_buffer(
      vertex_buffer,
      item_start_index,
      length,
      ALLEGRO_LOCK_READWRITE
   );

   // copy vertexes from end (end-6) into removed position (if not already at end)
   for (int i=0; i<6; i++) start[i] = start[i + length-6];

   // unlock
   al_unlock_vertex_buffer(vertex_buffer);

   // reduce vertices_in_use by 6
   vertices_in_use -= 6;
   return;
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


