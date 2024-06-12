

#include <Wicked/Entities/CollectionHelper.hpp>

#include <Wicked/EntityFlagNames.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Wicked
{
namespace Entities
{


CollectionHelper::CollectionHelper(std::vector<Wicked::Entities::Basic2D*>* entities)
   : entities(entities)
{
}


CollectionHelper::~CollectionHelper()
{
}


void CollectionHelper::set_entities(std::vector<Wicked::Entities::Basic2D*>* entities)
{
   this->entities = entities;
}


std::vector<Wicked::Entities::Basic2D*>* CollectionHelper::get_entities() const
{
   return entities;
}


std::vector<Wicked::Entities::Basic2D*> CollectionHelper::select_collectable_by_player()
{
   if (!(entities))
   {
      std::stringstream error_message;
      error_message << "[Wicked::Entities::CollectionHelper::select_collectable_by_player]: error: guard \"entities\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Wicked::Entities::CollectionHelper::select_collectable_by_player]: error: guard \"entities\" not met");
   }
   std::vector<Wicked::Entities::Basic2D*> result;
   for (auto &entity : (*entities))
   {
      if (entity->exists(COLLECTABLE_BY_PLAYER)) result.push_back(entity);
   }
   return result;
}

std::vector<Wicked::Entities::Basic2D*> CollectionHelper::select_goalposts()
{
   if (!(entities))
   {
      std::stringstream error_message;
      error_message << "[Wicked::Entities::CollectionHelper::select_goalposts]: error: guard \"entities\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Wicked::Entities::CollectionHelper::select_goalposts]: error: guard \"entities\" not met");
   }
   std::vector<Wicked::Entities::Basic2D*> result;
   for (auto &entity : (*entities))
   {
      if (entity->exists(TYPE, GOALPOST)) result.push_back(entity);
   }
   return result;
}

std::vector<Wicked::Entities::Basic2D*> CollectionHelper::select_doors()
{
   if (!(entities))
   {
      std::stringstream error_message;
      error_message << "[Wicked::Entities::CollectionHelper::select_doors]: error: guard \"entities\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Wicked::Entities::CollectionHelper::select_doors]: error: guard \"entities\" not met");
   }
   std::vector<Wicked::Entities::Basic2D*> result;
   for (auto &entity : (*entities))
   {
      if (entity->exists(TYPE, DOOR)) result.push_back(entity);
   }
   return result;
}

std::vector<Wicked::Entities::Basic2D*> CollectionHelper::select_on_map(std::string on_map_name)
{
   if (!(entities))
   {
      std::stringstream error_message;
      error_message << "[Wicked::Entities::CollectionHelper::select_on_map]: error: guard \"entities\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Wicked::Entities::CollectionHelper::select_on_map]: error: guard \"entities\" not met");
   }
   std::vector<Wicked::Entities::Basic2D*> result;
   for (auto &entity : (*entities))
   {
      if (entity->exists(ON_MAP_NAME, on_map_name)) result.push_back(entity);
   }
   return result;
}

WickedDemos::TileMaps::Basic2D* CollectionHelper::find_map_by_name(std::string map_name)
{
   if (!(entities))
   {
      std::stringstream error_message;
      error_message << "[Wicked::Entities::CollectionHelper::find_map_by_name]: error: guard \"entities\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Wicked::Entities::CollectionHelper::find_map_by_name]: error: guard \"entities\" not met");
   }
   //throw std::runtime_error("find_map_by_name not implemented");
   //std::vector<Wicked::Entities::Basic2D*> result;
   for (auto &entity : (*entities))
   {
      if (entity->exists(MAP_NAME, map_name)) return static_cast<WickedDemos::TileMaps::Basic2D*>(entity);
   }
   return nullptr;
}


} // namespace Entities
} // namespace Wicked


