

#include <AllegroFlare/TileMaps/MultiMeshUVAtlas.hpp>

#include <iostream>
#include <sstream>


namespace AllegroFlare
{
namespace TileMaps
{


MultiMeshUVAtlas::MultiMeshUVAtlas(std::map<int, AllegroFlare::TileMaps::MultiMeshUV> index)
   : index(index)
{
}


MultiMeshUVAtlas::~MultiMeshUVAtlas()
{
}


void MultiMeshUVAtlas::set_index(std::map<int, AllegroFlare::TileMaps::MultiMeshUV> index)
{
   this->index = index;
}


std::map<int, AllegroFlare::TileMaps::MultiMeshUV> MultiMeshUVAtlas::get_index() const
{
   return index;
}


void MultiMeshUVAtlas::add(int index_num, float u1, float v1, float u2, float v2)
{
   index[index_num] = AllegroFlare::TileMaps::MultiMeshUV(u1, v1, u2, v2);
   return;
}

bool MultiMeshUVAtlas::exists(int index_num)
{
   return (index.count(index_num) == 1);
}

AllegroFlare::TileMaps::MultiMeshUV MultiMeshUVAtlas::get(int index_num)
{
   if (!exists(index_num))
   {
      std::stringstream error_message;
      error_message << "AllegroFlare::TileMaps::MultiMeshUVAtlas::get error: "
                    << "Item does not exist at index_num " << index_num << ". Returning a default MultiMeshUV.";
      std::cout << error_message.str() << std::endl;
      return AllegroFlare::TileMaps::MultiMeshUV();
   }
   return index[index_num];
}


} // namespace TileMaps
} // namespace AllegroFlare


