#pragma once


#include <allegro5/allegro.h>
#include <set>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace Platforming2D
      {
         class TMJDataLoader
         {
         public:
            static constexpr ALLEGRO_COLOR DEFAULT_BACKGROUND_COLOR = ALLEGRO_COLOR{0.086f, 0.086f, 0.114f, 1.0f};

         private:
            std::string filename;
            int num_columns;
            int num_rows;
            int tile_width;
            int tile_height;
            int layer_num_columns;
            int layer_num_rows;
            std::vector<int> layer_tile_data;
            bool foreground_tilelayer_exists;
            int foreground_tilelayer_num_columns;
            int foreground_tilelayer_num_rows;
            std::vector<int> foreground_tilelayer_tile_data;
            bool background_tilelayer_exists;
            int background_tilelayer_num_columns;
            int background_tilelayer_num_rows;
            std::vector<int> background_tilelayer_tile_data;
            int collision_layer_num_columns;
            int collision_layer_num_rows;
            std::vector<int> collision_layer_tile_data;
            ALLEGRO_COLOR background_color;
            bool normalize_tile_data_from_tilesets;
            bool reduce_any_non_zero_collision_layer_data_to_1;
            bool loaded;
            static bool file_exists(std::string filename="[unset-filename]");

         protected:


         public:
            TMJDataLoader(std::string filename="filename-not-set.tmj");
            ~TMJDataLoader();

            bool get_loaded() const;
            int get_num_columns();
            int get_num_rows();
            int get_tile_width();
            int get_tile_height();
            int get_layer_num_columns();
            int get_layer_num_rows();
            std::vector<int> get_layer_tile_data();
            bool get_foreground_tilelayer_exists();
            int get_foreground_tilelayer_num_columns();
            int get_foreground_tilelayer_num_rows();
            std::vector<int> get_foreground_tilelayer_tile_data();
            bool get_background_tilelayer_exists();
            int get_background_tilelayer_num_columns();
            int get_background_tilelayer_num_rows();
            std::vector<int> get_background_tilelayer_tile_data();
            int get_collision_layer_num_columns();
            int get_collision_layer_num_rows();
            std::vector<int> get_collision_layer_tile_data();
            ALLEGRO_COLOR get_background_color();
            bool load();
            std::vector<int> normalize_tile_data_to_tilesets_firstgids(std::vector<int> data={}, std::set<int> tilesets_firstgids={});
         };
      }
   }
}



