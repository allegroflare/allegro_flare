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
   };
}



