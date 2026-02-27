#pragma once


#include <AllegroFlare/Tiled/TMJObject.hpp>
#include <functional>
#include <map>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace Tiled
   {
      class TMJGroup
      {
      private:

      protected:


      public:
         int id;
         std::string name;
         float offset_x;
         float offset_y;
         int num_rows;
         int num_columns;
         std::map<std::string, std::vector<int>> tilelayers_tile_data;
         std::vector<AllegroFlare::Tiled::TMJObject> objects;
         TMJGroup();
         ~TMJGroup();

         void for_each_object(std::function<void(AllegroFlare::Tiled::TMJObject*, void*)> function={}, void* user_data=nullptr);
         std::vector<int> get_tilelayer_data_by_name(std::string tilelayer_name="[unset-tilelayer_name]");
         std::vector<std::vector<int>> get_tilelayer_data_by_name_as_2d_vector(std::string tilelayer_name="[unset-tilelayer_name]");
         bool tilelayer_exists(std::string tilelayer_name="[unset-tilelayer_name]");
      };
   }
}



