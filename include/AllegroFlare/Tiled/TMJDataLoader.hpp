#pragma once


#include <AllegroFlare/Tiled/TMJObject.hpp>
#include <AllegroFlare/Tiled/TMJObjectCustomProperties.hpp>
#include <functional>
#include <lib/nlohmann/json.hpp>
#include <map>
#include <set>
#include <string>
#include <tuple>
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
         std::map<std::string, std::vector<int>> tilelayers_tile_data;
         std::string map_class;
         AllegroFlare::Tiled::TMJObjectCustomProperties map_custom_properties;
         std::vector<std::tuple<int, std::string, std::string>> tilesets;
         bool normalize_tile_data_from_tilesets;
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
         std::map<std::string, std::vector<int>> get_tilelayers_tile_data();
         std::string get_map_class();
         AllegroFlare::Tiled::TMJObjectCustomProperties get_map_custom_properties();
         std::vector<std::tuple<int, std::string, std::string>> get_tilesets();
         std::vector<int> get_tilelayer_data_by_name(std::string tilelayer_name="[unset-tilelayer_name]");
         std::vector<std::vector<int>> get_tilelayer_data_by_name_as_2d_vector(std::string tilelayer_name="[unset-tilelayer_name]");
         bool tilelayer_exists(std::string tilelayer_name="[unset-tilelayer_name]");
         bool load();
         static std::string extract_last_fragment(std::string path_string="[unset-string]");
         AllegroFlare::Tiled::TMJObjectCustomProperties attempt_to_extract_custom_properties(nlohmann::json* object_json=nullptr);
         std::vector<int> normalize_tile_data_to_tilesets_firstgids(std::vector<int> data={}, std::set<int> tilesets_firstgids={});
      };
   }
}



