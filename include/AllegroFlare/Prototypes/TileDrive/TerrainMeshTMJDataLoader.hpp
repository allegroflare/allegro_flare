#pragma once


#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace TileDrive
      {
         class TerrainMeshTMJDataLoader
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
            std::vector<int> collision_layer_tile_data;
            bool collision_layer_present;
            bool loaded;
            static bool file_exists(std::string filename="[unset-filename]");

         protected:


         public:
            TerrainMeshTMJDataLoader(std::string filename="filename-not-set.tmj");
            ~TerrainMeshTMJDataLoader();

            bool get_loaded() const;
            int get_num_columns();
            int get_num_rows();
            int get_tile_width();
            int get_tile_height();
            int get_layer_num_columns();
            int get_layer_num_rows();
            std::vector<int> get_layer_tile_data();
            std::vector<int> get_collision_layer_tile_data();
            bool get_collision_layer_present();
            bool load();
         };
      }
   }
}



