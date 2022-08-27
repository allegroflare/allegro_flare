

#include <AllegroFlare/MultiMeshUVAtlas.hpp>



namespace AllegroFlare
{


MultiMeshUVAtlas::MultiMeshUVAtlas(std::map<int, AllegroFlare::MultiMeshUV> index)
   : index(index)
{
}


MultiMeshUVAtlas::~MultiMeshUVAtlas()
{
}


void MultiMeshUVAtlas::set_index(std::map<int, AllegroFlare::MultiMeshUV> index)
{
   this->index = index;
}


std::map<int, AllegroFlare::MultiMeshUV> MultiMeshUVAtlas::get_index() const
{
   return index;
}


} // namespace AllegroFlare


