

#include <AllegroFlare/Prototypes/Platforming2D/EntityCollectionHelper.hpp>

#include <AllegroFlare/Prototypes/Platforming2D/EntityFlagNames.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Prototypes
{
namespace Platforming2D
{


EntityCollectionHelper::EntityCollectionHelper(std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*>* entities)
   : entities(entities)
{
}


EntityCollectionHelper::~EntityCollectionHelper()
{
}


void EntityCollectionHelper::set_entities(std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*>* entities)
{
   this->entities = entities;
}


std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*>* EntityCollectionHelper::get_entities() const
{
   return entities;
}


std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> EntityCollectionHelper::select_collectable_by_player()
{
   if (!(entities))
   {
      std::stringstream error_message;
      error_message << "[EntityCollectionHelper::select_collectable_by_player]: error: guard \"entities\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EntityCollectionHelper::select_collectable_by_player: error: guard \"entities\" not met");
   }
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> result;
   for (auto &entity : (*entities))
   {
      if (entity->exists(COLLECTABLE_BY_PLAYER)) result.push_back(entity);
   }
   return result;
}

std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> EntityCollectionHelper::select_collectable_by_player_on_map(std::string on_map_name)
{
   if (!(entities))
   {
      std::stringstream error_message;
      error_message << "[EntityCollectionHelper::select_collectable_by_player_on_map]: error: guard \"entities\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EntityCollectionHelper::select_collectable_by_player_on_map: error: guard \"entities\" not met");
   }
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> result;
   for (auto &entity : (*entities))
   {
      if (
           entity->exists(COLLECTABLE_BY_PLAYER)
         && entity->exists(ON_MAP_NAME, on_map_name)
      ) result.push_back(entity);
   }
   return result;
}

std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> EntityCollectionHelper::select_collides_with_player()
{
   if (!(entities))
   {
      std::stringstream error_message;
      error_message << "[EntityCollectionHelper::select_collides_with_player]: error: guard \"entities\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EntityCollectionHelper::select_collides_with_player: error: guard \"entities\" not met");
   }
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> result;
   for (auto &entity : (*entities))
   {
      if (entity->exists(COLLIDES_WITH_PLAYER)) result.push_back(entity);
   }
   return result;
}

std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> EntityCollectionHelper::select_goalposts()
{
   if (!(entities))
   {
      std::stringstream error_message;
      error_message << "[EntityCollectionHelper::select_goalposts]: error: guard \"entities\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EntityCollectionHelper::select_goalposts: error: guard \"entities\" not met");
   }
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> result;
   for (auto &entity : (*entities))
   {
      if (entity->exists(TYPE, GOALPOST)) result.push_back(entity);
   }
   return result;
}

std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> EntityCollectionHelper::select_save_points()
{
   if (!(entities))
   {
      std::stringstream error_message;
      error_message << "[EntityCollectionHelper::select_save_points]: error: guard \"entities\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EntityCollectionHelper::select_save_points: error: guard \"entities\" not met");
   }
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> result;
   for (auto &entity : (*entities))
   {
      if (entity->exists(TYPE, SAVE_POINT)) result.push_back(entity);
   }
   return result;
}

std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> EntityCollectionHelper::select_doors()
{
   if (!(entities))
   {
      std::stringstream error_message;
      error_message << "[EntityCollectionHelper::select_doors]: error: guard \"entities\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EntityCollectionHelper::select_doors: error: guard \"entities\" not met");
   }
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> result;
   for (auto &entity : (*entities))
   {
      if (entity->exists(TYPE, DOOR)) result.push_back(entity);
   }
   return result;
}

AllegroFlare::Prototypes::Platforming2D::Entities::Doors::Basic2D* EntityCollectionHelper::find_door_by_tmj_object_id(int tmj_object_id)
{
   if (!(entities))
   {
      std::stringstream error_message;
      error_message << "[EntityCollectionHelper::find_door_by_tmj_object_id]: error: guard \"entities\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EntityCollectionHelper::find_door_by_tmj_object_id: error: guard \"entities\" not met");
   }
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   //std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> result;
   for (auto &entity : (*entities))
   {
      if (
               entity->exists(TYPE, DOOR)
            && entity->exists(TMJ_OBJECT_ID)
            && (entity->get_as_int(TMJ_OBJECT_ID) == tmj_object_id)
            //&& entity->is_type(...) // TODO: Consider validating entity type as Doors::Basic2D::TYPE
         )
      {
         return static_cast<AllegroFlare::Prototypes::Platforming2D::Entities::Doors::Basic2D*>(entity);
      }
   }
   return nullptr;
}

AllegroFlare::Prototypes::Platforming2D::Entities::Doors::Basic2D* EntityCollectionHelper::find_door_by_target_door_name(std::string target_door_name)
{
   if (!(entities))
   {
      std::stringstream error_message;
      error_message << "[EntityCollectionHelper::find_door_by_target_door_name]: error: guard \"entities\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EntityCollectionHelper::find_door_by_target_door_name: error: guard \"entities\" not met");
   }
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   //std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> result;
   for (auto &entity : (*entities))
   {
      if (
               entity->exists(TYPE, DOOR)
            && entity->exists(TMJ_OBJECT_NAME, target_door_name)
            //&& entity->is_type(...) // TODO: Consider validating entity type as Doors::Basic2D::TYPE
         )
      {
         return static_cast<AllegroFlare::Prototypes::Platforming2D::Entities::Doors::Basic2D*>(entity);
      }
   }
   return nullptr;
}

std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> EntityCollectionHelper::select_on_map(std::string on_map_name)
{
   if (!(entities))
   {
      std::stringstream error_message;
      error_message << "[EntityCollectionHelper::select_on_map]: error: guard \"entities\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EntityCollectionHelper::select_on_map: error: guard \"entities\" not met");
   }
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> result;
   for (auto &entity : (*entities))
   {
      if (entity->exists(ON_MAP_NAME, on_map_name)) result.push_back(entity);
   }
   return result;
}

std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> EntityCollectionHelper::select_on_map_y_sorted(std::string on_map_name)
{
   if (!(entities))
   {
      std::stringstream error_message;
      error_message << "[EntityCollectionHelper::select_on_map_y_sorted]: error: guard \"entities\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EntityCollectionHelper::select_on_map_y_sorted: error: guard \"entities\" not met");
   }
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;
   using AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D;

   std::vector<Basic2D*> result;
   for (auto &entity : (*entities))
   {
      if (entity->exists(ON_MAP_NAME, on_map_name)) result.push_back(entity);
   }

   // TODO: see if there is a better way to do this without using "get_place_ref()", maybe a comparison
   // operator on the class.
   std::sort(result.begin(), result.end(),[](Basic2D *a, Basic2D *b)
         { return a->get_place_ref().position.y < b->get_place_ref().position.y; }
      );

   return result;
}

AllegroFlare::Prototypes::Platforming2D::Entities::TileMaps::Basic2D* EntityCollectionHelper::find_map_by_name(std::string map_name)
{
   if (!(entities))
   {
      std::stringstream error_message;
      error_message << "[EntityCollectionHelper::find_map_by_name]: error: guard \"entities\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EntityCollectionHelper::find_map_by_name: error: guard \"entities\" not met");
   }
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   //throw std::runtime_error("find_map_by_name not implemented");
   //std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> result;
   for (auto &entity : (*entities))
   {
      if (entity->exists(MAP_NAME, map_name))
      {
         return static_cast<AllegroFlare::Prototypes::Platforming2D::Entities::TileMaps::Basic2D*>(entity);
      }
   }
   return nullptr;
}


} // namespace Platforming2D
} // namespace Prototypes
} // namespace AllegroFlare


