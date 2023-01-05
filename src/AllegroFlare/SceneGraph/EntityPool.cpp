

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

std::vector<AllegroFlare::SceneGraph::Entities::Base*> EntityPool::select(std::vector<std::string> attributes)
{
   std::vector<AllegroFlare::SceneGraph::Entities::Base*> result;
   for (auto &entity : entity_pool)
   {
      for (auto &attribute : attributes)
      {
         if (!entity->exists(attribute)) continue;
      }
      result.push_back(entity);
   }
   return result;
}

std::vector<AllegroFlare::SceneGraph::Entities::Base*> EntityPool::select(std::string attribute, std::string parameter)
{
   std::vector<AllegroFlare::SceneGraph::Entities::Base*> result;
   for (auto &entity : entity_pool)
   {
      if (entity->exists(attribute, parameter)) result.push_back(entity);
   }
   return result;
}

std::vector<AllegroFlare::SceneGraph::Entities::Base*> EntityPool::select(std::vector<std::pair<std::string, std::string>> attribute_param_pairs)
{
   std::vector<AllegroFlare::SceneGraph::Entities::Base*> result;
   for (auto &entity : entity_pool)
   {
      for (auto &attribute_param_pair : attribute_param_pairs)
      {
         if (!entity->exists(attribute_param_pair.first, attribute_param_pair.second)) continue;
      }
      result.push_back(entity);
   }
   return result;
}


} // namespace SceneGraph
} // namespace AllegroFlare


