

#include <AllegroFlare/SceneGraph/EntityPool.hpp>




namespace AllegroFlare
{
namespace SceneGraph
{


EntityPool::EntityPool()
   : entity_pool({})
{
}


EntityPool::~EntityPool()
{
}


std::vector<AllegroFlare::SceneGraph::Entities::Base*> EntityPool::select(std::string attribute)
{
   std::vector<AllegroFlare::SceneGraph::Entities::Base*> result;
   for (auto &entity : entity_pool)
   {
      if (entity->exists(attribute)) result.push_back(entity);
   }
   return result;
}


} // namespace SceneGraph
} // namespace AllegroFlare


