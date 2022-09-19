#pragma once



#include <Tileo/TileIndexInfo.hpp>
#include <allegro5/allegro.h>
#include <string>
#include <vector>


namespace Tileo
{
   class Atlas
   {
   private:
      ALLEGRO_BITMAP *bitmap;
      std::string bitmap_filename;
      int tile_width;
      int tile_height;
      int tile_spacing;
      std::vector<Tileo::TileIndexInfo> tile_index;

   public:
      Atlas();
      ~Atlas();

      void clear();

      void duplicate_bitmap_and_load(ALLEGRO_BITMAP *source_bitmap, int tile_width, int tile_height, int spacing=0);

      std::string get_bitmap_filename() const;
      int get_tile_width() const;
      int get_tile_height() const;
      int get_tile_spacing() const;

      void set_bitmap_filename(std::string bitmap_filename="unset-bitmap-filename.png");
      void set_tile_width(int tile_width); // TODO: important, the mesh needs to be refreshed if these are changed
      void set_tile_height(int tile_height);
      void set_tile_spacing(int tile_spacing);

      ALLEGRO_BITMAP *get_bitmap();
      int get_tile_index_size();
      int get_bitmap_width();
      int get_bitmap_height();

      void draw_tile_to_atlas(ALLEGRO_BITMAP *tile, int tile_num, ALLEGRO_COLOR color=al_map_rgba_f(1, 1, 1, 1));
      bool get_tile_uv(int index_num, int *u1, int *v1, int *u2, int *v2);
      bool get_tile_uv(int index_num, float *u1, float *v1, float *u2, float *v2);
      ALLEGRO_BITMAP *get_bitmap(int index_num);

      std::vector<Tileo::TileIndexInfo> get_tile_index();
   };
}


