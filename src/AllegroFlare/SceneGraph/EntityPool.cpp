

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


void EntityPool::set_entity_pool(std::unordered_set<AllegroFlare::SceneGraph::Entities::Base*> entity_pool)
{
   this->entity_pool = entity_pool;
}


std::unordered_set<AllegroFlare::SceneGraph::Entities::Base*> EntityPool::get_entity_pool() const
{
   return entity_pool;
}


std::unordered_set<AllegroFlare::SceneGraph::Entities::Base*> &EntityPool::get_entity_pool_ref()
{
   return entity_pool;
}


bool EntityPool::add(AllegroFlare::SceneGraph::Entities::Base* entity)
{
   entity_pool.insert(entity);
}

bool EntityPool::add(std::vector<AllegroFlare::SceneGraph::Entities::Base*> entities)
{
   entity_pool.insert(entities.begin(), entities.end());
}

bool EntityPool::remove(AllegroFlare::SceneGraph::Entities::Base* entity)
{
   int num_erased = entity_pool.erase(entity);
   return (bool)num_erased;
}

bool EntityPool::exists(AllegroFlare::SceneGraph::Entities::Base* entity)
{
   return (entity_pool.count(entity) > 0);
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
         if (!entity->exists(attribute)) goto loop_next;
      }
      result.push_back(entity);

      loop_next:;
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


