#pragma once


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
         private:
            std::string filename;
            int num_columns;
            int num_rows;
            int tile_width;
            int tile_height;
            int layer_num_columns;
            int layer_num_rows;
            std::vector<int> layer_tile_data;
            int collision_layer_num_columns;
            int collision_layer_num_rows;
            std::vector<int> collision_layer_tile_data;
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
            int get_collision_layer_num_columns();
            int get_collision_layer_num_rows();
            std::vector<int> get_collision_layer_tile_data();
            bool load();
         };
      }
   }
}



