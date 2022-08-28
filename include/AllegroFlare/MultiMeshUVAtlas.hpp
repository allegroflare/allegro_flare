#pragma once


#include <AllegroFlare/MultiMeshUV.hpp>
#include <map>


namespace AllegroFlare
{
   class MultiMeshUVAtlas
   {
   private:
      std::map<int, AllegroFlare::MultiMeshUV> index;

   public:
      MultiMeshUVAtlas(std::map<int, AllegroFlare::MultiMeshUV> index={});
      ~MultiMeshUVAtlas();

      void set_index(std::map<int, AllegroFlare::MultiMeshUV> index);
      std::map<int, AllegroFlare::MultiMeshUV> get_index() const;
      void add(int index_num=0, float u1=0.0f, float v1=0.0f, float u2=1.0f, float v2=1.0f);
      bool exists(int index_num=0);
      AllegroFlare::MultiMeshUV get(int index_num=0);
   };
}



