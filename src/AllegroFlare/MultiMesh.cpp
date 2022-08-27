

#include <AllegroFlare/MultiMesh.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{


MultiMesh::MultiMesh()
   : vertex_buffer(nullptr)
   , index_buffer(nullptr)
   , indexes_in_use(0)
   , initialized(false)
{
}


MultiMesh::~MultiMesh()
{
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
   int num_elements = 50;
   int num_vertices = num_elements * 6;

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

   // index buffer, data will be uninitialized
   // size of the buffer is 2, which is a short, limiting the size to a certain amount (TODO, figure out amount)
   const void* initial_data_ib = nullptr;
   index_buffer = al_create_index_buffer(
      sizeof(short),
      initial_data_ib,
      num_vertices,
      ALLEGRO_PRIM_BUFFER_READWRITE
   );

   initialized = true;
   return;
}

void MultiMesh::append(float x, float y, float w, float h)
{
   // TODO
   return;
}

void MultiMesh::remove(int at_index)
{
   // TODO
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
   //int al_draw_indexed_buffer(ALLEGRO_VERTEX_BUFFER* vertex_buffer,
      //ALLEGRO_BITMAP* texture, ALLEGRO_INDEX_BUFFER* index_buffer,
      //int start, int end, int type)
   return;
}
} // namespace AllegroFlare


