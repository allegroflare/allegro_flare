#pragma once


#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <Tileo/Atlas.hpp>
#include <vector>


class TileMapVertexBufferRenderer
{
private:
   ALLEGRO_VERTEX_BUFFER *vertex_buffer;
   Tileo::Atlas &atlas;
   int width;
   int height;

   ALLEGRO_VERTEX *locked_vertex_buffer_vertex_pos;

   void initialize_or_recreate_vertex_buffer(int length);
   void lock_vertex_buffer(int start, int length);
   ALLEGRO_VERTEX *get_locked_vertex_buffer_vertex_pos();
   void unlock_vertex_buffer();
   void set_tile_uv(int tile_x, int tile_y, int u1, int v1, int u2, int v2);

public:
   TileMapVertexBufferRenderer(Tileo::Atlas &atlas);
   ~TileMapVertexBufferRenderer();

   int get_width();
   int get_height();
   int infer_num_tiles();

   bool set_tile(Tileo::Atlas &atlas, int tile_x, int tile_y, int tile_index);
   void resize(int w, int h, int tile_w, int tile_h);

   void render(int camera_x, int camera_y);
};


