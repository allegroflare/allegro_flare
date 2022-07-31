

#include <AllegroFlare/Prototypes/FixedRoom2D/EntityCollectionHelper.hpp>
#include <stdexcept>
#include <sstream>
#include <map>
#include <AllegroFlare/Prototypes/FixedRoom2D/Entities/Base.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <map>
#include <AllegroFlare/Prototypes/FixedRoom2D/Entities/Base.hpp>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace Prototypes
{
namespace FixedRoom2D
{


EntityCollectionHelper::EntityCollectionHelper(std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>* entity_dictionary)
   : entity_dictionary(entity_dictionary)
{
}


EntityCollectionHelper::~EntityCollectionHelper()
{
}


void EntityCollectionHelper::set_entity_dictionary(std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>* entity_dictionary)
{
   this->entity_dictionary = entity_dictionary;
}


std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>* EntityCollectionHelper::get_entity_dictionary()
{
   return entity_dictionary;
}


std::vector<AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> EntityCollectionHelper::select_all_in_room(std::string room_name)
{
   if (!(entity_dictionary))
      {
         std::stringstream error_message;
         error_message << "EntityCollectionHelper" << "::" << "select_all_in_room" << ": error: " << "guard \"entity_dictionary\" not met";
         throw std::runtime_error(error_message.str());
      }
   std::vector<AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> result;
   for (auto &entity : *entity_dictionary)
   {
      // if entity has the attribute, include it in the result
   }
   return result;
}

std::vector<AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> EntityCollectionHelper::select_all_unordered()
{
   if (!(entity_dictionary))
      {
         std::stringstream error_message;
         error_message << "EntityCollectionHelper" << "::" << "select_all_unordered" << ": error: " << "guard \"entity_dictionary\" not met";
         throw std::runtime_error(error_message.str());
      }
   std::vector<AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> result;
   for (auto &entity : *entity_dictionary)
   {
      result.push_back(entity.second);
   }
   return result;
}

std::string EntityCollectionHelper::find_dictionary_name_of_entity_that_cursor_is_now_over()
{
   if (!(entity_dictionary))
      {
         std::stringstream error_message;
         error_message << "EntityCollectionHelper" << "::" << "find_dictionary_name_of_entity_that_cursor_is_now_over" << ": error: " << "guard \"entity_dictionary\" not met";
         throw std::runtime_error(error_message.str());
      }
   for (auto &entity : *entity_dictionary)
   {
      if (entity.second->get_cursor_is_over()) return entity.first;
   }
   return "";
}

AllegroFlare::Prototypes::FixedRoom2D::Entities::Base* EntityCollectionHelper::find_by_dictionary_listing_name(std::string dictionary_listing_name)
{
   if (!(entity_dictionary))
      {
         std::stringstream error_message;
         error_message << "EntityCollectionHelper" << "::" << "find_by_dictionary_listing_name" << ": error: " << "guard \"entity_dictionary\" not met";
         throw std::runtime_error(error_message.str());
      }
   std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>::iterator it =
      entity_dictionary->find(dictionary_listing_name);
   if (it == entity_dictionary->end()) return nullptr;
   return it->second;
}

std::vector<AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> EntityCollectionHelper::select_all_ordered_by_id(std::string room_name)
{
   if (!(entity_dictionary))
      {
         std::stringstream error_message;
         error_message << "EntityCollectionHelper" << "::" << "select_all_ordered_by_id" << ": error: " << "guard \"entity_dictionary\" not met";
         throw std::runtime_error(error_message.str());
      }
   std::vector<AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> result;
   std::map<int, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> as_ids;

   for (auto &entity : *entity_dictionary)
   {
      as_ids[entity.second->get_id()] = entity.second;
   }

   for (auto &entity : as_ids)
   {
      result.push_back(entity.second);
   }
   return result;
}
} // namespace FixedRoom2D
} // namespace Prototypes
} // namespace AllegroFlare


