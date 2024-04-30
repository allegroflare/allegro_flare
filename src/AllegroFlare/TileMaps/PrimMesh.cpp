

#include <AllegroFlare/TileMaps/PrimMesh.hpp>

#include <iostream> // for set_tile_uv
#include <sstream>


namespace AllegroFlare::TileMaps
{


int PrimMesh::infer_num_vertexes()
{
   return num_columns * num_rows * 6;
}


void PrimMesh::set_tile_uv(int tile_x, int tile_y, int u1, int v1, int u2, int v2)
{
   int id_start = (tile_x * 6) + tile_y * (num_columns*6);
   int &i = id_start;

   vertexes[i+0].u = u1;
   vertexes[i+0].v = v1;

   vertexes[i+1].u = u1;
   vertexes[i+1].v = v2;

   vertexes[i+2].u = u2;
   vertexes[i+2].v = v2;

   vertexes[i+3].u = u2;
   vertexes[i+3].v = v2;

   vertexes[i+4].u = u2;
   vertexes[i+4].v = v1;

   vertexes[i+5].u = u1;
   vertexes[i+5].v = v1;
}


PrimMesh::PrimMesh(AllegroFlare::TileMaps::PrimMeshAtlas *atlas, int num_columns, int num_rows, int tile_width, int tile_height)
   : atlas(atlas)
   , vertexes()
   , tile_ids()
   , num_columns(num_columns)
   , num_rows(num_rows)
   , tile_width(tile_width)
   , tile_height(tile_height)
   , initialized(false)
   , yz_swapped(false)
{
}


PrimMesh::~PrimMesh()
{
}


std::vector<ALLEGRO_VERTEX> &PrimMesh::get_vertexes_ref()
{
   return vertexes;
}


void PrimMesh::initialize()
{
   if (initialized)
   {
      throw std::runtime_error("[AllegroFlare::PrimMesh::initialize()] error: initialized must be false");
   }

   resize(num_columns, num_rows);

   initialized = true;
}


bool PrimMesh::get_initialized()
{
   return initialized;
}


void PrimMesh::resize(int num_columns, int num_rows)
{
   this->num_columns = num_columns;
   this->num_rows = num_rows;

   // resize the vertexes vector
   vertexes.clear();
   tile_ids.clear();
   vertexes.resize(num_columns*num_rows*6);
   tile_ids.resize(num_columns*num_rows);

   // place the vertexes in the mesh
   int num_vertexes = num_columns*num_rows*6;
   for (int v=0; v<num_vertexes; v+=6)
   {
      long tile_num = v / 6;

      int x1 = (tile_num % num_columns);
      int y1 = (tile_num / num_columns);
      int x2 = x1 + 1;
      int y2 = y1 + 1;

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

   // "scale" the vertexes to the tile_w and tile_h and set other default values
   for (int v=0; v<num_vertexes; v++)
   {
      vertexes[v].x *= tile_width;
      vertexes[v].y *= tile_height;
      vertexes[v].z = 0;
      vertexes[v].color = al_map_rgba_f(1, 1, 1, 1);
   }

   if (yz_swapped)
   {
      swap_yz();
      yz_swapped = true; // NOTE: This is a bit of an akward way to re-assign yz_swapped
                         // simply because swap_yz() toggles the yz_swapped value.
   }
}


int PrimMesh::get_num_columns() const
{
   return num_columns;
}


int PrimMesh::get_num_rows() const
{
   return num_rows;
}


int PrimMesh::infer_num_tiles() const
{
   return num_rows * num_columns;
}


void PrimMesh::rescale_tile_dimensions_to(int new_tile_width, int new_tile_height)
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

   for (int v=0; v<infer_num_vertexes(); v++)
   {
      vertexes[v].x = vertexes[v].x / old_tile_width * new_tile_width;
      vertexes[v].y = vertexes[v].y / old_tile_height * new_tile_height;
      vertexes[v].z = vertexes[v].z / old_tile_height * new_tile_height;
   }

   this->tile_width = new_tile_width;
   this->tile_height = new_tile_height;
}


void PrimMesh::set_tile_width(int new_tile_width)
{
   rescale_tile_dimensions_to(new_tile_width, this->tile_height);
}


void PrimMesh::set_tile_height(int new_tile_height)
{
   rescale_tile_dimensions_to(this->tile_width, new_tile_height);
}


int PrimMesh::get_tile_width() const
{
   return tile_width;
}


int PrimMesh::get_tile_height() const
{
   return tile_height;
}


int PrimMesh::get_real_width() const
{
   return num_columns * tile_width;
}


int PrimMesh::get_real_height() const
{
   return num_rows * tile_height;
}


bool PrimMesh::set_tile_id(int tile_x, int tile_y, int tile_id)
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


int PrimMesh::get_tile_id(int tile_x, int tile_y) const
{
   if (tile_x < 0) return 0;
   if (tile_x >= num_columns) return 0;
   if (tile_y < 0) return 0;
   if (tile_y >= num_rows) return 0;

   return tile_ids[tile_x + tile_y * num_columns];
}


std::vector<int> PrimMesh::get_tile_ids() const
{
   return tile_ids;
}


AllegroFlare::TileMaps::PrimMeshAtlas *PrimMesh::get_atlas() const
{
   return atlas;
}


void PrimMesh::set_atlas(AllegroFlare::TileMaps::PrimMeshAtlas *atlas)
{
   this->atlas = atlas;
}


void PrimMesh::swap_yz()
{
   if (!initialized) throw std::runtime_error("[AllegroFlare::PrimMesh::swap_yz] error: must be initialized first");
   for (auto &vertex : vertexes)
   {
      float swap = vertex.y;
      vertex.y = vertex.z;
      vertex.z = swap;
   }

   yz_swapped = !yz_swapped;
}


void PrimMesh::render(bool draw_outline)
{
   if (!initialized) throw std::runtime_error("[AllegroFlare::PrimMesh::render] error: initialized can not be nullptr");
   if (!atlas) throw std::runtime_error("[AllegroFlare::PrimMesh] error: atlas must not be nullptr");

   // TODO: Promote this to a vertex buffer
   al_draw_prim(&vertexes[0], NULL, atlas->get_bitmap(), 0, vertexes.size(), ALLEGRO_PRIM_TRIANGLE_LIST);

   if (draw_outline)
   {
      al_draw_rectangle(0, 0, num_columns * tile_width, num_rows * tile_height, ALLEGRO_COLOR{1, 0, 1, 1}, 2.0);
   }
}

} // namespace AllegroFlare::TileMaps


