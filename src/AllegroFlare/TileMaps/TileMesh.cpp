

#include <AllegroFlare/TileMaps/TileMesh.hpp>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
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
   , index_buffer(nullptr)
   , tile_ids({})
   , index_vertices({})
   , h_flipped_tiles({})
   , v_flipped_tiles({})
   , d_flipped_tiles({})
   , num_columns(num_columns)
   , num_rows(num_rows)
   , tile_width(tile_width)
   , tile_height(tile_height)
   , holding_vertex_buffer_update_until_refresh(true)
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


std::vector<int> TileMesh::get_index_vertices() const
{
   return index_vertices;
}


std::set<std::pair<int, int>> TileMesh::get_h_flipped_tiles() const
{
   return h_flipped_tiles;
}


std::set<std::pair<int, int>> TileMesh::get_v_flipped_tiles() const
{
   return v_flipped_tiles;
}


std::set<std::pair<int, int>> TileMesh::get_d_flipped_tiles() const
{
   return d_flipped_tiles;
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
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[TileMesh::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TileMesh::initialize: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[TileMesh::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TileMesh::initialize: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   initialized = true;
   resize(num_columns, num_rows);
   return;
}

void TileMesh::set_num_rows(int num_rows)
{
   if (!((num_rows >= 0)))
   {
      std::stringstream error_message;
      error_message << "[TileMesh::set_num_rows]: error: guard \"(num_rows >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TileMesh::set_num_rows: error: guard \"(num_rows >= 0)\" not met");
   }
   this->num_rows = num_rows;
   if (initialized) resize(num_columns, num_rows);
}

void TileMesh::set_num_columns(int num_columns)
{
   if (!((num_columns >= 0)))
   {
      std::stringstream error_message;
      error_message << "[TileMesh::set_num_columns]: error: guard \"(num_columns >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TileMesh::set_num_columns: error: guard \"(num_columns >= 0)\" not met");
   }
   this->num_columns = num_columns;
   if (initialized) resize(num_columns, num_rows);
}

int TileMesh::remove_tile_xy_from_index(int tile_x, int tile_y)
{
   return remove_vertices_from_index_vertices(vertex_indices_for_tile_xy(tile_x, tile_y));
}

int TileMesh::remove_vertices_from_index_vertices(std::vector<int> vertices_to_remove)
{
   int num_removed = 0;

   for (int i=0; i<index_vertices.size(); i++)
   {
      if (std::find(vertices_to_remove.begin(), vertices_to_remove.end(),
          index_vertices[i]) == vertices_to_remove.end()) continue;

      index_vertices.erase(index_vertices.begin() + i);
      i--; // Adjust index since element was removed
      num_removed++;
   }

   // Completely rebuild the vertex indexes
   if (index_buffer) al_destroy_index_buffer(index_buffer);
   int num_index_vertices = index_vertices.size();
   int index_buffer_int_size = 4; // 4 is the size of a normal "int". If we were to use a "short int", then 2.
   index_buffer = al_create_index_buffer(
         index_buffer_int_size,
         &index_vertices[0],
         index_vertices.size(),
         ALLEGRO_PRIM_BUFFER_DYNAMIC
      );

   return num_removed;
}

std::vector<int> TileMesh::vertex_indices_for_tile_xy(int tile_x, int tile_y)
{
   if (!((tile_x >= 0)))
   {
      std::stringstream error_message;
      error_message << "[TileMesh::vertex_indices_for_tile_xy]: error: guard \"(tile_x >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TileMesh::vertex_indices_for_tile_xy: error: guard \"(tile_x >= 0)\" not met");
   }
   if (!((tile_x < num_columns)))
   {
      std::stringstream error_message;
      error_message << "[TileMesh::vertex_indices_for_tile_xy]: error: guard \"(tile_x < num_columns)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TileMesh::vertex_indices_for_tile_xy: error: guard \"(tile_x < num_columns)\" not met");
   }
   if (!((tile_y >= 0)))
   {
      std::stringstream error_message;
      error_message << "[TileMesh::vertex_indices_for_tile_xy]: error: guard \"(tile_y >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TileMesh::vertex_indices_for_tile_xy: error: guard \"(tile_y >= 0)\" not met");
   }
   if (!((tile_y < num_rows)))
   {
      std::stringstream error_message;
      error_message << "[TileMesh::vertex_indices_for_tile_xy]: error: guard \"(tile_y < num_rows)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TileMesh::vertex_indices_for_tile_xy: error: guard \"(tile_y < num_rows)\" not met");
   }
   // TODO: Test and try using this method
   int first_vertex_index = (tile_x + tile_y * num_columns) * 6;
   return std::vector<int>{
      first_vertex_index+0,
      first_vertex_index+1,
      first_vertex_index+2,
      first_vertex_index+3,
      first_vertex_index+4,
      first_vertex_index+5,
   };
}

void TileMesh::destroy()
{
   if (vertex_buffer) al_destroy_vertex_buffer(vertex_buffer);
   return;
}

void TileMesh::disable_holding_vertex_buffer_update_until_refresh()
{
   // TODO: Test this behavior
   holding_vertex_buffer_update_until_refresh = false;
   return;
}

void TileMesh::resize(int num_columns, int num_rows)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[TileMesh::resize]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TileMesh::resize: error: guard \"initialized\" not met");
   }
   this->num_columns = num_columns;
   this->num_rows = num_rows;

   // resize the vertices vector
   vertices.clear();
   tile_ids.clear();
   vertices.resize(num_columns*num_rows*6);
   tile_ids.resize(num_columns*num_rows);
   index_vertices.clear();
   index_vertices.resize(vertices.size());
   h_flipped_tiles.clear();
   v_flipped_tiles.clear();
   d_flipped_tiles.clear();
   if (vertex_buffer) al_destroy_vertex_buffer(vertex_buffer);
   if (index_buffer) al_destroy_index_buffer(index_buffer);

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

   // Scale the vertices to the tile_w and tile_h and set other default values
   for (int v=0; v<num_vertices; v++)
   {
      vertices[v].x *= tile_width;
      vertices[v].y *= tile_height;
      vertices[v].z = 0;
      vertices[v].color = al_map_rgba_f(1, 1, 1, 1);
   }

   // Create the vertex buffer, duplicate the vertices into it
   vertex_buffer = al_create_vertex_buffer(NULL, &vertices[0], vertices.size(), ALLEGRO_PRIM_BUFFER_DYNAMIC);

   // Build the vertex indexes
   int num_index_vertices = index_vertices.size();
   for (int i=0; i<num_index_vertices; i++) index_vertices[i] = i;
   int index_buffer_int_size = 4; // 4 is the size of a normal "int". If we were to use a "short int", then 2.
   index_buffer = al_create_index_buffer(
         index_buffer_int_size,
         &index_vertices[0],
         index_vertices.size(),
         ALLEGRO_PRIM_BUFFER_DYNAMIC
      );

   vertex_buffer_is_dirty = false;

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
   al_draw_indexed_buffer(
      vertex_buffer,
      atlas->get_bitmap(),
      index_buffer,
      0,
      //vertices.size(),  // vertex_buffer? should be index_buffer?
      index_vertices.size(),  // vertex_buffer? should be index_buffer?
      ALLEGRO_PRIM_TRIANGLE_LIST
   );

   if (draw_outline)
   {
      al_draw_rectangle(0, 0, num_columns * tile_width, num_rows * tile_height, ALLEGRO_COLOR{1, 0, 1, 1}, 2.0);
   }
   return;
}

bool TileMesh::set_tile_id(int tile_x, int tile_y, int tile_id, bool flip_h, bool flip_v, bool flip_d)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[TileMesh::set_tile_id]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TileMesh::set_tile_id: error: guard \"initialized\" not met");
   }
   if (!(atlas))
   {
      std::stringstream error_message;
      error_message << "[TileMesh::set_tile_id]: error: guard \"atlas\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TileMesh::set_tile_id: error: guard \"atlas\" not met");
   }
   if (tile_id >= (int)atlas->get_tile_index_size()) return false;

   // if the tile_id is a negative number, use the number "0" instead
   // I'm not sure how/why this is the preferred approach.  I think negative numbers
   // should be allowed, any number should be allowed.  So this should be revisited
   if (tile_id < 0) tile_id = 0;

   int u1, v1, u2, v2;
   atlas->get_tile_uv(tile_id, &u1, &v1, &u2, &v2);

   // HACK
   {
      bool diagonal_will_do_the_h_flip = (flip_h && !flip_v && flip_d);
      bool diagonal_will_do_the_v_flip = (!flip_h && flip_v && flip_d);
      bool diagonal_will_do_the_flip = diagonal_will_do_the_h_flip || diagonal_will_do_the_v_flip;

      if (diagonal_will_do_the_flip)
      {
         v_flip_vertices(&u1, &v1, &u2, &v2);
         h_flip_vertices(&u1, &v1, &u2, &v2);
      }
   }


   if (flip_h)
   {
      h_flip_vertices(&u1, &v1, &u2, &v2);
      h_flipped_tiles.insert({tile_x, tile_y});
   }
   else
   {
      h_flipped_tiles.erase({tile_x, tile_y});
   }
   if (flip_v)
   {
      v_flip_vertices(&u1, &v1, &u2, &v2);
      v_flipped_tiles.insert({tile_x, tile_y});
   }
   else
   {
      v_flipped_tiles.erase({tile_x, tile_y});
   }
   if (flip_d)
   {
      d_flipped_tiles.insert({tile_x, tile_y});
   }
   else
   {
      d_flipped_tiles.erase({tile_x, tile_y});
   }

   set_tile_uv(tile_x, tile_y, u1, v1, u2, v2, flip_d);

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
}

std::tuple<bool, bool, bool> TileMesh::get_tile_flip(int tile_x, int tile_y)
{
   if (tile_x < 0) return { false, false, false };
   if (tile_x >= num_columns) return { false, false, false };
   if (tile_y < 0) return { false, false, false };
   if (tile_y >= num_rows) return { false, false, false };

   // TODO: Add is_d_flipped to result
   bool is_h_flipped = h_flipped_tiles.find({ tile_x, tile_y }) != h_flipped_tiles.end();
   bool is_v_flipped = v_flipped_tiles.find({ tile_x, tile_y }) != v_flipped_tiles.end();
   bool is_d_flipped = d_flipped_tiles.find({ tile_x, tile_y }) != d_flipped_tiles.end();

   return { is_h_flipped, is_v_flipped, is_d_flipped };
}

void TileMesh::h_flip_vertices(int* u1, int* v1, int* u2, int* v2)
{
   if (!(u1))
   {
      std::stringstream error_message;
      error_message << "[TileMesh::h_flip_vertices]: error: guard \"u1\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TileMesh::h_flip_vertices: error: guard \"u1\" not met");
   }
   if (!(v1))
   {
      std::stringstream error_message;
      error_message << "[TileMesh::h_flip_vertices]: error: guard \"v1\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TileMesh::h_flip_vertices: error: guard \"v1\" not met");
   }
   if (!(u2))
   {
      std::stringstream error_message;
      error_message << "[TileMesh::h_flip_vertices]: error: guard \"u2\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TileMesh::h_flip_vertices: error: guard \"u2\" not met");
   }
   if (!(v2))
   {
      std::stringstream error_message;
      error_message << "[TileMesh::h_flip_vertices]: error: guard \"v2\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TileMesh::h_flip_vertices: error: guard \"v2\" not met");
   }
   // NOTE: Should the uv coordinates be floats?
   int swap = *u1;
   *u1 = *u2;
   *u2 = swap;
   return;
}

void TileMesh::v_flip_vertices(int* u1, int* v1, int* u2, int* v2)
{
   if (!(u1))
   {
      std::stringstream error_message;
      error_message << "[TileMesh::v_flip_vertices]: error: guard \"u1\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TileMesh::v_flip_vertices: error: guard \"u1\" not met");
   }
   if (!(v1))
   {
      std::stringstream error_message;
      error_message << "[TileMesh::v_flip_vertices]: error: guard \"v1\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TileMesh::v_flip_vertices: error: guard \"v1\" not met");
   }
   if (!(u2))
   {
      std::stringstream error_message;
      error_message << "[TileMesh::v_flip_vertices]: error: guard \"u2\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TileMesh::v_flip_vertices: error: guard \"u2\" not met");
   }
   if (!(v2))
   {
      std::stringstream error_message;
      error_message << "[TileMesh::v_flip_vertices]: error: guard \"v2\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TileMesh::v_flip_vertices: error: guard \"v2\" not met");
   }
   // NOTE: Should the uv coordinates be floats?
   int swap = *v1;
   *v1 = *v2;
   *v2 = swap;
   return;
}

void TileMesh::set_tile_uv(int tile_x, int tile_y, int u1, int v1, int u2, int v2, bool diagonal_flip)
{
   // NOTE: Should the uv coordinates be floats?
   int tile_index_start = (tile_x * 6) + tile_y * (num_columns*6);
   int &i = tile_index_start;

   if (diagonal_flip)
   {
      // NOTE: The vertices are woven in the following order:
      //   triangle 1: top left, bottom left, bottom right
      //   triangle 2: bottom right, top right, top left

      vertices[i+0].u = u1;
      vertices[i+0].v = v1;
      vertices[i+1].u = u2;
      vertices[i+1].v = v1;
      vertices[i+2].u = u2;
      vertices[i+2].v = v2;

      vertices[i+3].u = u2;
      vertices[i+3].v = v2;
      vertices[i+4].u = u1;
      vertices[i+4].v = v2;
      vertices[i+5].u = u1;
      vertices[i+5].v = v1;
   }
   else
   {
      // NOTE: The vertices are woven in the following order:
      //   triangle 1: top left, bottom left, bottom right
      //   triangle 2: bottom right, top right, top left

      // Triangle 1:
      vertices[i+0].u = u1;
      vertices[i+0].v = v1;
      vertices[i+1].u = u1;
      vertices[i+1].v = v2;
      vertices[i+2].u = u2;
      vertices[i+2].v = v2;

      // Triangle 2:
      vertices[i+3].u = u2;
      vertices[i+3].v = v2;
      vertices[i+4].u = u2;
      vertices[i+4].v = v1;
      vertices[i+5].u = u1;
      vertices[i+5].v = v1;
   }

   if (holding_vertex_buffer_update_until_refresh)
   {
      vertex_buffer_is_dirty = true;
   }
   else
   {
      // Upate the vertex in the vertex buffer
      // TODO: Consider only locking the region that needs the change
      refresh_vertex_buffer();
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

   for (int v=0; v<num_vertices; v++)
   {
      vertices[v].x = vertices[v].x / old_tile_width * new_tile_width;
      vertices[v].y = vertices[v].y / old_tile_height * new_tile_height;
      vertices[v].z = vertices[v].z / old_tile_height * new_tile_height;
   }

   if (holding_vertex_buffer_update_until_refresh) vertex_buffer_is_dirty = true;
   else refresh_vertex_buffer();

   this->tile_width = new_tile_width;
   this->tile_height = new_tile_height;
   return;
}

void TileMesh::set_tile_width(int new_tile_width)
{
   if (!initialized)
   {
      this->tile_width = new_tile_width;
   }
   else
   {
      rescale_tile_dimensions_to(new_tile_width, this->tile_height);
   }
   return;
}

void TileMesh::set_tile_height(int new_tile_height)
{
   if (!initialized)
   {
      this->tile_height = new_tile_height;
   }
   else
   {
      rescale_tile_dimensions_to(this->tile_width, new_tile_height);
   }
   return;
}

int TileMesh::get_real_width()
{
   // TODO: This should be a float?
   return num_columns * tile_width;
}

int TileMesh::get_real_height()
{
   // TODO: This should be a float?
   return num_rows * tile_height;
}

void TileMesh::swap_yz()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[TileMesh::swap_yz]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TileMesh::swap_yz: error: guard \"initialized\" not met");
   }
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


