#pragma once


#include <AllegroFlare/Tiled/TMJObject.hpp>
#include <functional>
#include <map>
#include <set>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace Tiled
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
         int collision_layer_num_columns;
         int collision_layer_num_rows;
         std::vector<int> collision_layer_tile_data;
         std::map<std::string, std::vector<int>> tilelayers_tile_data;
         bool normalize_tile_data_from_tilesets;
         bool reduce_any_non_zero_collision_layer_data_to_1;
         bool loaded;
         std::vector<AllegroFlare::Tiled::TMJObject> objects;
         static bool file_exists(std::string filename="[unset-filename]");

      protected:


      public:
         TMJDataLoader(std::string filename="filename-not-set.tmj");
         ~TMJDataLoader();

         bool get_loaded() const;
         std::vector<AllegroFlare::Tiled::TMJObject> get_objects() const;
         std::vector<AllegroFlare::Tiled::TMJObject> &get_objects_ref();
         void for_each_object(std::function<void(AllegroFlare::Tiled::TMJObject*, void*)> function={}, void* user_data=nullptr);
         void set_filename(std::string filename="[unset-filename]");
         int get_num_columns();
         int get_num_rows();
         int get_tile_width();
         int get_tile_height();
         int get_layer_num_columns();
         int get_layer_num_rows();
         int get_collision_layer_num_columns();
         int get_collision_layer_num_rows();
         std::vector<int> get_collision_layer_tile_data();
         std::map<std::string, std::vector<int>> get_tilelayers_tile_data();
         bool tilelayer_exists(std::string tilelayer_name="[unset-tilelayer_name]");
         bool load();
         std::vector<int> normalize_tile_data_to_tilesets_firstgids(std::vector<int> data={}, std::set<int> tilesets_firstgids={});
      };
   }
}



