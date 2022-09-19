

#include <Tileo/Mesh.hpp>

#include <iostream> // for set_tile_uv


namespace Tileo
{

void Mesh::set_tile_uv(int tile_x, int tile_y, int u1, int v1, int u2, int v2)
{
   int id_start = (tile_x * 6) + tile_y * (num_columns*6);
   int &i = id_start;

   //ALLEGRO_VERTEX *vbuff =
   //   (ALLEGRO_VERTEX *)al_lock_vertex_buffer(vertex_buffer, id_start, 6, ALLEGRO_LOCK_WRITEONLY);
   //if (!vbuff) std::cout << "could not lock vertex buffer" << std::endl;

   if (use_primitive) vertexes[i+0].u = u1;
   if (use_primitive) vertexes[i+0].v = v1;
   //vbuff[0].u = u1;
   //vbuff[0].v = v1;

   if (use_primitive) vertexes[i+1].u = u1;
   if (use_primitive) vertexes[i+1].v = v2;
   //vbuff[1].u = u1;
   //vbuff[1].v = v2;

   if (use_primitive) vertexes[i+2].u = u2;
   if (use_primitive) vertexes[i+2].v = v2;
   //vbuff[2].u = u2;
   //vbuff[2].v = v2;

   if (use_primitive) vertexes[i+3].u = u2;
   if (use_primitive) vertexes[i+3].v = v2;
   //vbuff[3].u = u2;
   //vbuff[3].v = v2;

   if (use_primitive) vertexes[i+4].u = u2;
   if (use_primitive) vertexes[i+4].v = v1;
   //vbuff[4].u = u2;
   //vbuff[4].v = v1;

   if (use_primitive) vertexes[i+5].u = u1;
   if (use_primitive) vertexes[i+5].v = v1;
   //vbuff[5].u = u1;
   //vbuff[5].v = v1;

   //al_unlock_vertex_buffer(vertex_buffer);
}


Mesh::Mesh(Tileo::Atlas *atlas, int num_columns, int num_rows, int tile_width, int tile_height)
   : atlas(atlas)
   , vertex_buffer(nullptr)
   , vertexes()
   , tile_ids()
   //, atlas_bitmap(atlas_bitmap)
   , num_columns(num_columns)
   , num_rows(num_rows)
   , tile_width(tile_width)
   , tile_height(tile_height)
   , use_primitive(true)
   , initialized(false)
{
}


Mesh::~Mesh()
{
}


std::vector<ALLEGRO_VERTEX> &Mesh::get_vertexes_ref()
{
   return vertexes;
}


void Mesh::initialize()
{
   if (initialized)
   {
      throw std::runtime_error("[Tileo::Mesh::initialize()] error: initialized must be false");
      //return false
   }

   resize(num_columns, num_rows);

   // set as initialized
   initialized = true;
}


void Mesh::resize(int num_columns, int num_rows)
{
   this->num_columns = num_columns;
   this->num_rows = num_rows;
   //num_columns = w;
   //num_rows = h;

   //if (initialized)
   //{
      //throw std::runtime_error("[Tileo::Mesh] error: initialized must be false");
      ////return false
   //}

   // resize the vertexes vector
   vertexes.clear();
   tile_ids.clear();
   if (use_primitive) vertexes.resize(num_columns*num_rows*6);
   tile_ids.resize(num_columns*num_rows);

   // create a vertex_buffer
   if (vertex_buffer) al_destroy_vertex_buffer(vertex_buffer);
   vertex_buffer = al_create_vertex_buffer(NULL, NULL, num_columns*num_rows*6, ALLEGRO_PRIM_BUFFER_STATIC);
   if (!vertex_buffer) std::cout << "There was an error creating the vertex buffer" << std::endl;

   // lock the buffer before writing to it
   int vertex_buffer_size = al_get_vertex_buffer_size(vertex_buffer);
   ALLEGRO_VERTEX *vbuff_begin =
      (ALLEGRO_VERTEX *)al_lock_vertex_buffer(vertex_buffer, 0, vertex_buffer_size, ALLEGRO_LOCK_WRITEONLY);
   if (!vbuff_begin) std::cout << "There was an error locking the vertex buffer" << std::endl;

   // place the vertexes in the mesh
   ALLEGRO_VERTEX *vbuff = vbuff_begin;
   int v = 0;
   int num_vertexes = num_columns*num_rows*6;
   for (; v<num_vertexes; v+=6, vbuff+=6)
   {
      long tile_num = v / 6;

      int x1 = (tile_num % num_columns);
      int y1 = (tile_num / num_columns);
      int x2 = x1 + 1;
      int y2 = y1 + 1;

      if (use_primitive) vertexes[v+0].x = x1;
      if (use_primitive) vertexes[v+0].y = y1;
      vbuff[0].x = x1;
      vbuff[0].y = y1;

      if (use_primitive) vertexes[v+1].x = x1;
      if (use_primitive) vertexes[v+1].y = y2;
      vbuff[1].x = x1;
      vbuff[1].y = y2;

      if (use_primitive) vertexes[v+2].x = x2;
      if (use_primitive) vertexes[v+2].y = y2;
      vbuff[2].x = x2;
      vbuff[2].y = y2;

      if (use_primitive) vertexes[v+3].x = x2;
      if (use_primitive) vertexes[v+3].y = y2;
      vbuff[3].x = x2;
      vbuff[3].y = y2;

      if (use_primitive) vertexes[v+4].x = x2;
      if (use_primitive) vertexes[v+4].y = y1;
      vbuff[4].x = x2;
      vbuff[4].y = y1;

      if (use_primitive) vertexes[v+5].x = x1;
      if (use_primitive) vertexes[v+5].y = y1;
      vbuff[5].x = x1;
      vbuff[5].y = y1;
   }

   // "scale" the vertexes to the tile_w and tile_h
   // and set other default values
   vbuff = vbuff_begin;
   v = 0;
   for (; v<num_vertexes; v++, vbuff++)
   {
      if (use_primitive) vertexes[v].x *= tile_width;
      if (use_primitive) vertexes[v].y *= tile_height;
      if (use_primitive) vertexes[v].z = 0;
      if (use_primitive) vertexes[v].color = al_map_rgba_f(1, 1, 1, 1);
      vbuff[0].x *= tile_width;
      vbuff[0].y *= tile_height;
      vbuff[0].z = 0;
      vbuff[0].color = al_map_rgba_f(1, 1, 1, 1);//color::mix(color::white, random_color(), 0.5);
   }

   // unlock our buffer
   al_unlock_vertex_buffer(vertex_buffer);

   // set as initialized
   //initialized = true;
}


int Mesh::get_num_columns() const
{
   return num_columns;
}


int Mesh::get_num_rows() const
{
   return num_rows;
}


int Mesh::get_tile_width() const
{
   return tile_width;
}


int Mesh::get_tile_height() const
{
   return tile_height;
}


int Mesh::get_real_width() const
{
   return num_columns * tile_width;
}


int Mesh::get_real_height() const
{
   return num_rows * tile_height;
}


bool Mesh::set_tile(int tile_x, int tile_y, int tile_id)
{
   std::cout
      << "[Tileo::Mesh:set_tile] DEPRECATION WARNING: "
      << "set_tile() is deprecated. use set_tile_id instead, which is identical in signature and behavior."
      << std::endl;
   return set_tile_id(tile_x, tile_y, tile_id);
}


bool Mesh::set_tile_id(int tile_x, int tile_y, int tile_id)
{
   if (!atlas) throw std::runtime_error("[Tileo::Mesh] error: atlas must not be nullptr");
   // if the tile index does not exist in the atlas, break out
   if (tile_id >= (int)atlas->get_tile_index_size()) return false;

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


int Mesh::get_tile_id(int tile_x, int tile_y) const
{
   if (tile_x < 0) return 0;
   if (tile_x >= num_columns) return 0;
   if (tile_y < 0) return 0;
   if (tile_y >= num_rows) return 0;

   return tile_ids[tile_x + tile_y * num_columns];
}


std::vector<int> Mesh::get_tile_ids() const
{
   return tile_ids;
}


Tileo::Atlas *Mesh::get_atlas() const
{
   return atlas;
}


 //void Mesh::set_atlas_bitmap(ALLEGRO_BITMAP *atlas_bitmap)
 //{
 //   this->atlas_bitmap = atlas_bitmap;
 //}



void Mesh::render(bool draw_frame) //int camera_x, int camera_y)
{
   if (!initialized) throw std::runtime_error("[Tileo::Mesh;:render] error: initialized can not be nullptr");
   if (!atlas) throw std::runtime_error("[Tileo::Mesh] error: atlas must not be nullptr");


   //return;

   //std::vector<ALLEGRO_VERTEX> vertexes = {
   //   ALLEGRO_VERTEX{ 0, 0, 0, ALLEGRO_COLOR{1, 0, 0, 1}, 0, 0 },
   //};



   al_draw_prim(&vertexes[0], NULL, atlas->get_bitmap(), 0, vertexes.size(), ALLEGRO_PRIM_TRIANGLE_LIST);

   //al_draw_prim(&vertexes[0], NULL, bmp, 0, vertexes.size(), ALLEGRO_PRIM_TRIANGLE_LIST);

   //ALLEGRO_TRANSFORM prev, transform;

   //al_draw_vertex_buffer(
   //   vertex_buffer,
   //   atlas->get_bitmap(),
   //   0,
   //   al_get_vertex_buffer_size(vertex_buffer),
   //   ALLEGRO_PRIM_TRIANGLE_LIST);

   // TODO: assuming a tile_width and a tile_height of 16
   //float tile_width = 16;
   //float tile_height = 16;
   if (draw_frame)
   {
      al_draw_rectangle(0, 0, num_columns * tile_width, num_rows * tile_height, ALLEGRO_COLOR{1, 0, 1, 1}, 2.0);
   }
}

} // Tileo


