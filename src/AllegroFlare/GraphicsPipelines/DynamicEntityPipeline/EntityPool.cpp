

#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/EntityPool.hpp>




namespace AllegroFlare
{
namespace GraphicsPipelines
{
namespace DynamicEntityPipeline
{


EntityPool::EntityPool()
   : entity_pool({})
{
}


EntityPool::~EntityPool()
{
}


void EntityPool::set_entity_pool(std::unordered_set<AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base*> entity_pool)
{
   this->entity_pool = entity_pool;
}


std::unordered_set<AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base*> EntityPool::get_entity_pool() const
{
   return entity_pool;
}


std::unordered_set<AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base*> &EntityPool::get_entity_pool_ref()
{
   return entity_pool;
}


int EntityPool::num_elements()
{
   // TODO: Test this function
   return entity_pool.size();
}

bool EntityPool::add(AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base* entity)
{
   // TODO: consider checking for duplicates
   entity_pool.insert(entity);
   return true;
}

bool EntityPool::add(std::vector<AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base*> entities)
{
   // TODO: consider checking for duplicates
   entity_pool.insert(entities.begin(), entities.end());
   return true;
}

bool EntityPool::remove(AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base* entity)
{
   int num_erased = entity_pool.erase(entity);
   return (bool)num_erased;
}

int EntityPool::remove(std::vector<AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base*> entities)
{
   int num_erased = 0;
   for (auto &entity : entities)
   {
      num_erased += entity_pool.erase(entity);
   }
   return num_erased;
}

bool EntityPool::exists(AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base* entity)
{
   return (entity_pool.count(entity) > 0);
}

AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base* EntityPool::find_with_attribute(std::string attribute)
{
   // TODO: Test this function
   for (auto &entity : entity_pool) if (entity->exists(attribute)) return entity;
   return nullptr;
}

std::vector<AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base*> EntityPool::find_all_with_attribute(std::string attribute)
{
   // TODO: Test this
   std::vector<AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base*> result;
   for (auto &entity : entity_pool)
   {
      if (entity->exists(attribute)) result.push_back(entity);
   }
   return result;
}

std::vector<AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base*> EntityPool::select_A(std::string attribute)
{
   // TODO: Replace collers of "select_A" to use "find_all_with_attributes" and remove this method
   // TODO: Test this
   return find_all_with_attribute(attribute);
}

std::vector<AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base*> EntityPool::select_B(std::vector<std::string> attributes)
{
   std::vector<AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base*> result;
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

std::vector<AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base*> EntityPool::select_C(std::string attribute, std::string parameter)
{
   std::vector<AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base*> result;
   for (auto &entity : entity_pool)
   {
      if (entity->exists(attribute, parameter)) result.push_back(entity);
   }
   return result;
}

std::vector<AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base*> EntityPool::select_D(std::vector<std::pair<std::string, std::string>> attribute_param_pairs)
{
   // TODO: add test

   std::vector<AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base*> result;
   for (auto &entity : entity_pool)
   {
      for (auto &attribute_param_pair : attribute_param_pairs)
      {
         if (!entity->exists(attribute_param_pair.first, attribute_param_pair.second)) goto loop_next2;
      }
      result.push_back(entity);

      loop_next2:;
   }
   return result;
}

std::vector<AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base*> EntityPool::select_E(std::string attribute, std::vector<std::pair<std::string, std::string>> attribute_param_pairs)
{
   std::vector<AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base*> result;
   for (auto &entity : entity_pool)
   {
      if (!entity->exists(attribute)) goto loop_next3;
      for (auto &attribute_param_pair : attribute_param_pairs)
      {
         if (!entity->exists(attribute_param_pair.first, attribute_param_pair.second)) goto loop_next3;
      }
      result.push_back(entity);

      loop_next3:;
   }
   return result;
}

std::vector<AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base*> EntityPool::select_F(std::vector<std::string> attributes, std::vector<std::pair<std::string, std::string>> attribute_param_pairs)
{
   // TODO: add test

   std::vector<AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base*> result;
   for (auto &entity : entity_pool)
   {
      for (auto &attribute : attributes)
      {
         if (!entity->exists(attribute)) goto loop_next4;
      }
      for (auto &attribute_param_pair : attribute_param_pairs)
      {
         if (!entity->exists(attribute_param_pair.first, attribute_param_pair.second)) goto loop_next4;
      }
      result.push_back(entity);

      loop_next4:;
   }
   return result;
}


} // namespace DynamicEntityPipeline
} // namespace GraphicsPipelines
} // namespace AllegroFlare


