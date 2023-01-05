

#include <AllegroFlare/SceneGraph/EntityPool.hpp>

#include <algorithm>


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


bool EntityPool::add(AllegroFlare::SceneGraph::Entities::Base* entity)
{
   entity_pool.push_back(entity);
   return true;
}

bool EntityPool::remove(AllegroFlare::SceneGraph::Entities::Base* entity)
{
   // NOTE: this assumes there is only one instance of the entity
   // TODO: update this std::vector to an std::unordered_set and remove the above comment
   std::vector<AllegroFlare::SceneGraph::Entities::Base*>::iterator it =
      std::find(entity_pool.begin(), entity_pool.end(), entity);
   if (it == entity_pool.end()) return false;
   entity_pool.erase(it);
   return true;
}

bool EntityPool::exists(AllegroFlare::SceneGraph::Entities::Base* entity)
{
   std::vector<AllegroFlare::SceneGraph::Entities::Base*>::iterator it =
      std::find(entity_pool.begin(), entity_pool.end(), entity);
   return (it != entity_pool.end());
}

std::vector<AllegroFlare::SceneGraph::Entities::Base*> EntityPool::select_A(std::string attribute)
{
   std::vector<AllegroFlare::SceneGraph::Entities::Base*> result;
   for (auto &entity : entity_pool)
   {
      if (entity->exists(attribute)) result.push_back(entity);
   }
   return result;
}

std::vector<AllegroFlare::SceneGraph::Entities::Base*> EntityPool::select_B(std::vector<std::string> attributes)
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

std::vector<AllegroFlare::SceneGraph::Entities::Base*> EntityPool::select_C(std::string attribute, std::string parameter)
{
   std::vector<AllegroFlare::SceneGraph::Entities::Base*> result;
   for (auto &entity : entity_pool)
   {
      if (entity->exists(attribute, parameter)) result.push_back(entity);
   }
   return result;
}

std::vector<AllegroFlare::SceneGraph::Entities::Base*> EntityPool::select_D(std::vector<std::pair<std::string, std::string>> attribute_param_pairs)
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

std::vector<AllegroFlare::SceneGraph::Entities::Base*> EntityPool::select_E(std::string attribute, std::vector<std::pair<std::string, std::string>> attribute_param_pairs)
{
   std::vector<AllegroFlare::SceneGraph::Entities::Base*> result;
   for (auto &entity : entity_pool)
   {
      if (!entity->exists(attribute)) continue;
      for (auto &attribute_param_pair : attribute_param_pairs)
      {
         if (!entity->exists(attribute_param_pair.first, attribute_param_pair.second)) continue;
      }
      result.push_back(entity);
   }
   return result;
}

std::vector<AllegroFlare::SceneGraph::Entities::Base*> EntityPool::select_F(std::vector<std::string> attributes, std::vector<std::pair<std::string, std::string>> attribute_param_pairs)
{
   std::vector<AllegroFlare::SceneGraph::Entities::Base*> result;
   for (auto &entity : entity_pool)
   {
      for (auto &attribute : attributes)
      {
         if (!entity->exists(attribute)) continue;
      }
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


