

#include <Tileo/TileMapVertexBufferRenderer.hpp>

#include <iostream> // for set_tile_uv


void TileMapVertexBufferRenderer::initialize_or_recreate_vertex_buffer(int length)
{
   if (vertex_buffer) al_destroy_vertex_buffer(vertex_buffer);
   vertex_buffer = al_create_vertex_buffer(NULL, NULL, length, ALLEGRO_PRIM_BUFFER_STATIC);
   if (!vertex_buffer)
   {
      throw std::runtime_error("TileMapVertexBufferRenderer::lock_vertex_buffer] error: vertex buffer did not lock. " \
                               "The vertex may have already been locked or there was an invalid range passed into the " \
                               "buffer when attempting to lock it.");
   }
}


void TileMapVertexBufferRenderer::lock_vertex_buffer(int start, int length)
{
   locked_vertex_buffer_vertex_pos =
      (ALLEGRO_VERTEX *)al_lock_vertex_buffer(vertex_buffer, start, length, ALLEGRO_LOCK_WRITEONLY);
   if (!locked_vertex_buffer_vertex_pos)
   {
      throw std::runtime_error("[TileMapVertexBufferRenderer::lock_vertex_buffer] error: vertex buffer did not lock. " \
                               "The vertex may have already been locked or there was an invalid range passed into the " \
                               "buffer when attempting to lock it.");
   }
}


void TileMapVertexBufferRenderer::unlock_vertex_buffer()
{
   al_unlock_vertex_buffer(vertex_buffer);
}


ALLEGRO_VERTEX *TileMapVertexBufferRenderer::get_locked_vertex_buffer_vertex_pos()
{
   return locked_vertex_buffer_vertex_pos;
}


void TileMapVertexBufferRenderer::set_tile_uv(int tile_x, int tile_y, int u1, int v1, int u2, int v2)
{
   int index_start = (tile_x * 6) + tile_y * (width*6);

   lock_vertex_buffer(index_start, 6);
   ALLEGRO_VERTEX *vbuff = get_locked_vertex_buffer_vertex_pos();

   vbuff[0].u = u1;
   vbuff[0].v = v1;

   vbuff[1].u = u1;
   vbuff[1].v = v2;

   vbuff[2].u = u2;
   vbuff[2].v = v2;

   vbuff[3].u = u2;
   vbuff[3].v = v2;

   vbuff[4].u = u2;
   vbuff[4].v = v1;

   vbuff[5].u = u1;
   vbuff[5].v = v1;

   unlock_vertex_buffer();
}


TileMapVertexBufferRenderer::TileMapVertexBufferRenderer(Tileo::Atlas &atlas)
   : vertex_buffer(nullptr)
   , atlas(atlas)
   , width(0)
   , height(0)
{
}


TileMapVertexBufferRenderer::~TileMapVertexBufferRenderer()
{
}


int TileMapVertexBufferRenderer::get_width()
{
   return width;
}


int TileMapVertexBufferRenderer::get_height()
{
   return height;
}


int TileMapVertexBufferRenderer::infer_num_tiles()
{
   return width * height;
}


bool TileMapVertexBufferRenderer::set_tile(Tileo::Atlas &atlas, int tile_x, int tile_y, int tile_index)
{
   // if the tile index does not exist in the atlas, break out
   if (tile_index >= (int)atlas.get_tile_index_size()) return false;

   // if the tile_index is a negative number, use the number "0" instead
   // I'm not sure how/why this is the preferred approach.  I think negative numbers
   // should be allowed, any number should be allowed.  So this should be revisited
   if (tile_index < 0) tile_index = 0;

   // transfer the uv coordinates of the from the tile atlas bitmap to the mesh
   // {
      int u1, v1, u2, v2;
      atlas.get_tile_uv(tile_index, &u1, &v1, &u2, &v2);
      set_tile_uv(tile_x, tile_y, u1, v1, u2, v2);
   // }

   return true;
}


void TileMapVertexBufferRenderer::resize(int w, int h, int tile_w, int tile_h)
{
   this->width = w;
   this->height = h;
   int num_vertexes = get_width()*get_height()*6;

   initialize_or_recreate_vertex_buffer(num_vertexes);

   // lock the buffer before writing to it
   lock_vertex_buffer(0, al_get_vertex_buffer_size(vertex_buffer));
   ALLEGRO_VERTEX *vbuff = get_locked_vertex_buffer_vertex_pos();

   // place the vertexes in the mesh
   for (int v=0; v<num_vertexes; v+=6, vbuff+=6)
   {
      long tile_num = v / 6;

      int x1 = (tile_num % get_width());
      int y1 = (tile_num / get_width()); // note the usage of get_width() and not get_height()
      int x2 = x1 + 1;
      int y2 = y1 + 1;

      vbuff[0].x = x1;
      vbuff[0].y = y1;
      vbuff[0].z = 0;
      vbuff[0].color = al_map_rgba_f(1.0f, 1.0f, 1.0f, 1.0f);

      vbuff[1].x = x1;
      vbuff[1].y = y2;
      vbuff[1].z = 0;
      vbuff[1].color = al_map_rgba_f(1.0f, 1.0f, 1.0f, 1.0f);

      vbuff[2].x = x2;
      vbuff[2].y = y2;
      vbuff[2].z = 0;
      vbuff[2].color = al_map_rgba_f(1.0f, 1.0f, 1.0f, 1.0f);

      vbuff[3].x = x2;
      vbuff[3].y = y2;
      vbuff[3].z = 0;
      vbuff[3].color = al_map_rgba_f(1.0f, 1.0f, 1.0f, 1.0f);

      vbuff[4].x = x2;
      vbuff[4].y = y1;
      vbuff[4].z = 0;
      vbuff[4].color = al_map_rgba_f(1.0f, 1.0f, 1.0f, 1.0f);

      vbuff[5].x = x1;
      vbuff[5].y = y1;
      vbuff[5].z = 0;
      vbuff[5].color = al_map_rgba_f(1.0f, 1.0f, 1.0f, 1.0f);
   }

   // unlock our buffer
   unlock_vertex_buffer();
}


void TileMapVertexBufferRenderer::render(int camera_x, int camera_y)
{
   ALLEGRO_TRANSFORM prev, transform;
   al_copy_transform(&prev, al_get_current_transform());
   al_identity_transform(&transform);
   al_translate_transform(&transform, -camera_x, -camera_y);
   al_use_transform(&transform);

   al_draw_vertex_buffer(
      vertex_buffer,
      atlas.get_bitmap(),
      0,
      al_get_vertex_buffer_size(vertex_buffer),
      ALLEGRO_PRIM_TRIANGLE_LIST
      );

   al_use_transform(&prev);
}



