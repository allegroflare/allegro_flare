

#include <AllegroFlare/TileMaps/TileMesh.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace TileMaps
{


TileMesh::TileMesh(AllegroFlare::TileMaps::PrimMeshAtlas* atlas, int num_columns, int num_rows, int tile_width, int tile_height)
   : atlas(atlas)
   , vertices()
   , vertex_buffer(nullptr)
   , tile_ids({})
   , num_columns(num_columns)
   , num_rows(num_rows)
   , tile_width(tile_width)
   , tile_height(tile_height)
   , holding_vertex_buffer_update_until_refresh(false)
   , vertex_buffer_is_dirty(false)
   , yz_swapped(false)
   , initialized(false)
{
}


TileMesh::~TileMesh()
{
}


void TileMesh::set_atlas(AllegroFlare::TileMaps::PrimMeshAtlas* atlas)
{
   this->atlas = atlas;
}


AllegroFlare::TileMaps::PrimMeshAtlas* TileMesh::get_atlas() const
{
   return atlas;
}


std::vector<int> TileMesh::get_tile_ids() const
{
   return tile_ids;
}


int TileMesh::get_num_columns() const
{
   return num_columns;
}


int TileMesh::get_num_rows() const
{
   return num_rows;
}


int TileMesh::get_tile_width() const
{
   return tile_width;
}


int TileMesh::get_tile_height() const
{
   return tile_height;
}


bool TileMesh::get_holding_vertex_buffer_update_until_refresh() const
{
   return holding_vertex_buffer_update_until_refresh;
}


bool TileMesh::get_vertex_buffer_is_dirty() const
{
   return vertex_buffer_is_dirty;
}


bool TileMesh::get_initialized() const
{
   return initialized;
}


std::vector<ALLEGRO_VERTEX> &TileMesh::get_vertices_ref()
{
   return vertices;
}


void TileMesh::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[TileMesh::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TileMesh::initialize: error: guard \"(!initialized)\" not met");
   }
   // TODO: Guard on al_is_system_installed
   // TODO: Guard on al_is_primitives_addon_initialized

   resize(num_columns, num_rows);

   initialized = true;
   return;
}

void TileMesh::destroy()
{
   if (vertex_buffer) al_destroy_vertex_buffer(vertex_buffer);
   return;
}

void TileMesh::enable_holding_vertex_buffer_update_until_refresh()
{
   holding_vertex_buffer_update_until_refresh = true;
   return;
}

void TileMesh::resize(int num_columns, int num_rows)
{
   this->num_columns = num_columns;
   this->num_rows = num_rows;

   // resize the vertices vector
   vertices.clear();
   tile_ids.clear();
   vertices.resize(num_columns*num_rows*6);
   tile_ids.resize(num_columns*num_rows);

   // place the vertices in the mesh
   int num_vertices = num_columns*num_rows*6;
   for (int v=0; v<num_vertices; v+=6)
   {
      long tile_num = v / 6;

      int x1 = (tile_num % num_columns);
      int y1 = (tile_num / num_columns);
      int x2 = x1 + 1;
      int y2 = y1 + 1;

      vertices[v+0].x = x1;
      vertices[v+0].y = y1;
      vertices[v+1].x = x1;
      vertices[v+1].y = y2;
      vertices[v+2].x = x2;
      vertices[v+2].y = y2;
      vertices[v+3].x = x2;
      vertices[v+3].y = y2;
      vertices[v+4].x = x2;
      vertices[v+4].y = y1;
      vertices[v+5].x = x1;
      vertices[v+5].y = y1;
   }

   // "scale" the vertices to the tile_w and tile_h and set other default values
   for (int v=0; v<num_vertices; v++)
   {
      vertices[v].x *= tile_width;
      vertices[v].y *= tile_height;
      vertices[v].z = 0;
      vertices[v].color = al_map_rgba_f(1, 1, 1, 1);
   }

   // create the vertex buffer;
   if (vertex_buffer) al_destroy_vertex_buffer(vertex_buffer);
   vertex_buffer = al_create_vertex_buffer(NULL, &vertices[0], vertices.size(), ALLEGRO_PRIM_BUFFER_READWRITE);

   if (yz_swapped)
   {
      swap_yz();
      yz_swapped = true; // NOTE: This is a bit of an akward way to re-assign yz_swapped
                         // simply because swap_yz() toggles the yz_swapped value.
   }
   return;
}

void TileMesh::render(bool draw_outline)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[TileMesh::render]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TileMesh::render: error: guard \"initialized\" not met");
   }
   if (!(atlas))
   {
      std::stringstream error_message;
      error_message << "[TileMesh::render]: error: guard \"atlas\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TileMesh::render: error: guard \"atlas\" not met");
   }
   if (!((!vertex_buffer_is_dirty)))
   {
      std::stringstream error_message;
      error_message << "[TileMesh::render]: error: guard \"(!vertex_buffer_is_dirty)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TileMesh::render: error: guard \"(!vertex_buffer_is_dirty)\" not met");
   }
   //if (!initialized) throw std::runtime_error("[AllegroFlare::PrimMesh::render] error: initialized can not be nullptr");
   //if (!atlas) throw std::runtime_error("[AllegroFlare::PrimMesh] error: atlas must not be nullptr");
   //if (

   // TODO: Promote this to a vertex buffer
   //al_draw_prim(&vertices[0], NULL, atlas->get_bitmap(), 0, vertices.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
   al_draw_vertex_buffer(vertex_buffer, atlas->get_bitmap(), 0, vertices.size(), ALLEGRO_PRIM_TRIANGLE_LIST);

   if (draw_outline)
   {
      al_draw_rectangle(0, 0, num_columns * tile_width, num_rows * tile_height, ALLEGRO_COLOR{1, 0, 1, 1}, 2.0);
   }
   return;
}

bool TileMesh::set_tile_id(int tile_x, int tile_y, int tile_id)
{
   if (!atlas) throw std::runtime_error("[AllegroFlare::TileMaps::PrimMesh] error: atlas must not be nullptr");
   if (tile_id >= (int)atlas->get_tile_index_size()) return false;
   if (!initialized) throw std::runtime_error("[AllegroFlare::PrimMesh::set_tile_id] error: must be initialized first");

   // if the tile_id is a negative number, use the number "0" instead
   // I'm not sure how/why this is the preferred approach.  I think negative numbers
   // should be allowed, any number should be allowed.  So this should be revisited
   if (tile_id < 0) tile_id = 0;

   // transfer the uv coordinates of the from the tile atlas bitmap to the mesh
   // {
      int u1, v1, u2, v2;
      atlas->get_tile_uv(tile_id, &u1, &v1, &u2, &v2);
      set_tile_uv(tile_x, tile_y, u1, v1, u2, v2);
   // }

   tile_ids[tile_x + tile_y * num_columns] = tile_id;

   return true;
}

int TileMesh::get_tile_id(int tile_x, int tile_y)
{
   if (tile_x < 0) return 0;
   if (tile_x >= num_columns) return 0;
   if (tile_y < 0) return 0;
   if (tile_y >= num_rows) return 0;

   return tile_ids[tile_x + tile_y * num_columns];
   return 0;
}

void TileMesh::set_tile_uv(int tile_x, int tile_y, int u1, int v1, int u2, int v2)
{
   // NOTE: Should the uv coordinates be floats?
   int tile_index_start = (tile_x * 6) + tile_y * (num_columns*6);
   int &i = tile_index_start;

   // Modify the vertex
   vertices[i+0].u = u1;
   vertices[i+0].v = v1;
   vertices[i+1].u = u1;
   vertices[i+1].v = v2;
   vertices[i+2].u = u2;
   vertices[i+2].v = v2;
   vertices[i+3].u = u2;
   vertices[i+3].v = v2;
   vertices[i+4].u = u2;
   vertices[i+4].v = v1;
   vertices[i+5].u = u1;
   vertices[i+5].v = v1;

   if (holding_vertex_buffer_update_until_refresh)
   {
      vertex_buffer_is_dirty = true;
   }
   else
   {
      // Modify the vertex in the vertex buffer
      ALLEGRO_VERTEX* vertex_buffer_start = (ALLEGRO_VERTEX*)al_lock_vertex_buffer(
         vertex_buffer,
         0,
         infer_num_vertices(), // Consider only locking the region that needs the change
         ALLEGRO_LOCK_WRITEONLY
      );

      vertex_buffer_start[i+0] = vertices[i+0];
      vertex_buffer_start[i+1] = vertices[i+1];
      vertex_buffer_start[i+2] = vertices[i+2];
      vertex_buffer_start[i+3] = vertices[i+3];
      vertex_buffer_start[i+4] = vertices[i+4];
      vertex_buffer_start[i+5] = vertices[i+5];

      al_unlock_vertex_buffer(vertex_buffer);
   }
   return;
}

void TileMesh::refresh_vertex_buffer()
{
   int num_vertices = infer_num_vertices();
   ALLEGRO_VERTEX* vertex_buffer_start = (ALLEGRO_VERTEX*)al_lock_vertex_buffer(
      vertex_buffer,
      0,
      num_vertices,
      ALLEGRO_LOCK_WRITEONLY
   );

   for (int v=0; v<num_vertices; v++) vertex_buffer_start[v] = vertices[v];

   al_unlock_vertex_buffer(vertex_buffer);

   vertex_buffer_is_dirty = false;
   return;
}

int TileMesh::infer_num_vertices()
{
   return num_columns * num_rows * 6;
}

int TileMesh::infer_num_tiles()
{
   return num_rows * num_columns;
}

void TileMesh::rescale_tile_dimensions_to(int new_tile_width, int new_tile_height)
{
   int old_tile_width = this->tile_width;
   int old_tile_height = this->tile_height;

   if (new_tile_width <= 0 || new_tile_height <= 0)
   {
      // TODO: test this assertion
      std::stringstream error_message;
      error_message << "AllegroFlare::TileMaps::PrimMesh::rescale_tile_dimensions_to: error: "
                    << "new_tile_width and/or new_tile_height cannot be less than or equal to zero.";
      throw std::runtime_error(error_message.str());
   }

   int num_vertices = infer_num_vertices();
   //ALLEGRO_VERTEX* vertex_buffer_start = (ALLEGRO_VERTEX*)al_lock_vertex_buffer(
      //vertex_buffer,
      //0,
      //num_vertices,
      //ALLEGRO_LOCK_WRITEONLY
   //);

   for (int v=0; v<num_vertices; v++)
   {
      vertices[v].x = vertices[v].x / old_tile_width * new_tile_width;
      vertices[v].y = vertices[v].y / old_tile_height * new_tile_height;
      vertices[v].z = vertices[v].z / old_tile_height * new_tile_height;

      //vertex_buffer_start[v] = vertices[v];
   }

   //al_unlock_vertex_buffer(vertex_buffer);

   if (holding_vertex_buffer_update_until_refresh) vertex_buffer_is_dirty = true;
   else refresh_vertex_buffer();

   this->tile_width = new_tile_width;
   this->tile_height = new_tile_height;
   return;
}

void TileMesh::set_tile_width(int new_tile_width)
{
   rescale_tile_dimensions_to(new_tile_width, this->tile_height);
   return;
}

void TileMesh::set_tile_height(int new_tile_height)
{
   rescale_tile_dimensions_to(this->tile_width, new_tile_height);
   return;
}

int TileMesh::get_real_width()
{
   // TODO: This should be a float?
   return num_columns * tile_width;
   return 0;
}

int TileMesh::get_real_height()
{
   // TODO: This should be a float?
   return num_rows * tile_height;
   return 0;
}

void TileMesh::swap_yz()
{
   if (!initialized) throw std::runtime_error("[AllegroFlare::PrimMesh::swap_yz] error: must be initialized first");


   for (auto &vertex : vertices)
   {
      float swap = vertex.y;
      vertex.y = vertex.z;
      vertex.z = swap;
   }

   // Modify the vertex in the vertex buffer
   if (holding_vertex_buffer_update_until_refresh) vertex_buffer_is_dirty = true;
   else refresh_vertex_buffer();

   yz_swapped = !yz_swapped;
   return;
}


} // namespace TileMaps
} // namespace AllegroFlare


