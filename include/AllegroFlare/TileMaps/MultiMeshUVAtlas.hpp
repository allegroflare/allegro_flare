#pragma once


#include <AllegroFlare/TileMaps/MultiMeshUV.hpp>
#include <map>


namespace AllegroFlare
{
   namespace TileMaps
   {
      class MultiMeshUVAtlas
      {
      private:
         std::map<int, AllegroFlare::TileMaps::MultiMeshUV> index;

      protected:


      public:
         MultiMeshUVAtlas(std::map<int, AllegroFlare::TileMaps::MultiMeshUV> index={});
         ~MultiMeshUVAtlas();

         void set_index(std::map<int, AllegroFlare::TileMaps::MultiMeshUV> index);
         std::map<int, AllegroFlare::TileMaps::MultiMeshUV> get_index() const;
         void add(int index_num=0, float u1=0.0f, float v1=0.0f, float u2=1.0f, float v2=1.0f);
         bool exists(int index_num=0);
         AllegroFlare::TileMaps::MultiMeshUV get(int index_num=0);
      };
   }
}



