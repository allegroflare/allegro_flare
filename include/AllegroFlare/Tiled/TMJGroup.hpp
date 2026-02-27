#pragma once


#include <AllegroFlare/Tiled/TMJObject.hpp>
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
         std::map<std::string, std::vector<int>> tilelayers_tile_data;
         std::vector<AllegroFlare::Tiled::TMJObject> objects;
         TMJGroup(int id=0, std::string name="[unset-name]", float offset_x=0.0f, float offset_y=0.0f);
         ~TMJGroup();

      };
   }
}



