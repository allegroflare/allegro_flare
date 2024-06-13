

#include <AllegroFlare/Prototypes/FixedRoom2D/EntityCollectionHelper.hpp>

#include <AllegroFlare/Prototypes/FixedRoom2D/Entities/Base.hpp>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Prototypes
{
namespace FixedRoom2D
{


EntityCollectionHelper::EntityCollectionHelper(std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>* entity_dictionary, std::map<std::string, std::string>* entity_room_associations)
   : entity_dictionary(entity_dictionary)
   , entity_room_associations(entity_room_associations)
{
}


EntityCollectionHelper::~EntityCollectionHelper()
{
}


void EntityCollectionHelper::set_entity_dictionary(std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>* entity_dictionary)
{
   this->entity_dictionary = entity_dictionary;
}


void EntityCollectionHelper::set_entity_room_associations(std::map<std::string, std::string>* entity_room_associations)
{
   this->entity_room_associations = entity_room_associations;
}


std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>* EntityCollectionHelper::get_entity_dictionary() const
{
   return entity_dictionary;
}


std::map<std::string, std::string>* EntityCollectionHelper::get_entity_room_associations() const
{
   return entity_room_associations;
}


std::vector<AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> EntityCollectionHelper::select_all_in_room_ordered_by_id(std::string room_name)
{
   if (!(entity_dictionary))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper::select_all_in_room_ordered_by_id]: error: guard \"entity_dictionary\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper::select_all_in_room_ordered_by_id]: error: guard \"entity_dictionary\" not met");
   }
   std::vector<std::string> entity_names_in_room = select_all_entity_names_in_room_name(room_name);
   std::vector<AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> entities =
      get_entities_by_entity_names(entity_names_in_room);
   return order_by_id(entities);
}

std::vector<AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> EntityCollectionHelper::select_all()
{
   if (!(entity_dictionary))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper::select_all]: error: guard \"entity_dictionary\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper::select_all]: error: guard \"entity_dictionary\" not met");
   }
   std::vector<AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> result;
   for (auto &entity : *entity_dictionary) { result.push_back(entity.second); }
   return result;
}

std::string EntityCollectionHelper::find_dictionary_name_of_entity_that_cursor_is_now_over()
{
   if (!(entity_dictionary))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper::find_dictionary_name_of_entity_that_cursor_is_now_over]: error: guard \"entity_dictionary\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper::find_dictionary_name_of_entity_that_cursor_is_now_over]: error: guard \"entity_dictionary\" not met");
   }
   for (auto &entity : *entity_dictionary)
   {
      if (entity.second->get_cursor_is_over()) return entity.first;
   }
   return "";
}

AllegroFlare::Prototypes::FixedRoom2D::Entities::Base* EntityCollectionHelper::find_entity_by_dictionary_name(std::string dictionary_listing_name)
{
   if (!(entity_dictionary))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper::find_entity_by_dictionary_name]: error: guard \"entity_dictionary\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper::find_entity_by_dictionary_name]: error: guard \"entity_dictionary\" not met");
   }
   std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>::iterator it =
      entity_dictionary->find(dictionary_listing_name);
   if (it == entity_dictionary->end()) return nullptr;
   return it->second;
}

std::vector<AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> EntityCollectionHelper::order_by_id(std::vector<AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> entities_to_order)
{
   std::vector<AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> result;
   std::map<int, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> as_ids;

   for (auto &entity : entities_to_order)
   {
      if (!entity) continue;
      as_ids[entity->get_id()] = entity;
   }

   for (auto &entity : as_ids)
   {
      result.push_back(entity.second);
   }
   return result;
}

std::vector<AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> EntityCollectionHelper::get_entities_by_entity_names(std::vector<std::string> entity_dictionary_names)
{
   if (!(entity_dictionary))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper::get_entities_by_entity_names]: error: guard \"entity_dictionary\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper::get_entities_by_entity_names]: error: guard \"entity_dictionary\" not met");
   }
   std::vector<AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> result;
   for (auto &entity_dictionary_name : entity_dictionary_names)
   {
      AllegroFlare::Prototypes::FixedRoom2D::Entities::Base* found_entity =
         find_entity_by_dictionary_name(entity_dictionary_name);

      if (!found_entity)
      {
         std::cout << "[FixedRoom2D::EntityCollectionHelper::get_entities_from_entity_names]: warning: The provided "
                   << "entity name \"" << entity_dictionary_name << "\" does not have a listing. Ignoring."
                   << std::endl;
      }
      else
      {
         result.push_back(found_entity);
      }
   }
   return result;
}

std::vector<std::string> EntityCollectionHelper::select_all_entity_names_in_room_name(std::string room_name)
{
   if (!(entity_room_associations))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper::select_all_entity_names_in_room_name]: error: guard \"entity_room_associations\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper::select_all_entity_names_in_room_name]: error: guard \"entity_room_associations\" not met");
   }
   std::vector<std::string> result;
   for (auto &entity_room_association : (*entity_room_associations))
   {
      if (entity_room_association.second == room_name) result.push_back(entity_room_association.first);
   }
   return result;
}


} // namespace FixedRoom2D
} // namespace Prototypes
} // namespace AllegroFlare


