

#include <AllegroFlare/Prototypes/FixedRoom2D/Configuration.hpp>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace Prototypes
{
namespace FixedRoom2D
{


Configuration::Configuration(AllegroFlare::InventoryIndex* inventory_index, AllegroFlare::Inventory* af_inventory, AllegroFlare::Inventory* flags, std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>* entity_dictionary, std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Room*>* room_dictionary, std::map<std::string, std::string>* entity_room_associations, std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Script>* script_dictionary)
   : inventory_index(inventory_index)
   , af_inventory(af_inventory)
   , flags(flags)
   , entity_dictionary(entity_dictionary)
   , room_dictionary(room_dictionary)
   , entity_room_associations(entity_room_associations)
   , script_dictionary(script_dictionary)
{
}


Configuration::~Configuration()
{
}


void Configuration::set_inventory_index(AllegroFlare::InventoryIndex* inventory_index)
{
   this->inventory_index = inventory_index;
}


void Configuration::set_af_inventory(AllegroFlare::Inventory* af_inventory)
{
   this->af_inventory = af_inventory;
}


void Configuration::set_flags(AllegroFlare::Inventory* flags)
{
   this->flags = flags;
}


void Configuration::set_entity_dictionary(std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>* entity_dictionary)
{
   this->entity_dictionary = entity_dictionary;
}


void Configuration::set_room_dictionary(std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Room*>* room_dictionary)
{
   this->room_dictionary = room_dictionary;
}


void Configuration::set_entity_room_associations(std::map<std::string, std::string>* entity_room_associations)
{
   this->entity_room_associations = entity_room_associations;
}


void Configuration::set_script_dictionary(std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Script>* script_dictionary)
{
   this->script_dictionary = script_dictionary;
}


AllegroFlare::InventoryIndex* Configuration::get_inventory_index()
{
   return inventory_index;
}


AllegroFlare::Inventory* Configuration::get_af_inventory()
{
   return af_inventory;
}


AllegroFlare::Inventory* Configuration::get_flags()
{
   return flags;
}


std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>* Configuration::get_entity_dictionary()
{
   return entity_dictionary;
}


std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Room*>* Configuration::get_room_dictionary()
{
   return room_dictionary;
}


std::map<std::string, std::string>* Configuration::get_entity_room_associations()
{
   return entity_room_associations;
}


std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Script>* Configuration::get_script_dictionary()
{
   return script_dictionary;
}


bool Configuration::load_original_gametest_default()
{
   if (!(inventory_index))
      {
         std::stringstream error_message;
         error_message << "Configuration" << "::" << "load_original_gametest_default" << ": error: " << "guard \"inventory_index\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(af_inventory))
      {
         std::stringstream error_message;
         error_message << "Configuration" << "::" << "load_original_gametest_default" << ": error: " << "guard \"af_inventory\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(flags))
      {
         std::stringstream error_message;
         error_message << "Configuration" << "::" << "load_original_gametest_default" << ": error: " << "guard \"flags\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(entity_dictionary))
      {
         std::stringstream error_message;
         error_message << "Configuration" << "::" << "load_original_gametest_default" << ": error: " << "guard \"entity_dictionary\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(room_dictionary))
      {
         std::stringstream error_message;
         error_message << "Configuration" << "::" << "load_original_gametest_default" << ": error: " << "guard \"room_dictionary\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(entity_room_associations))
      {
         std::stringstream error_message;
         error_message << "Configuration" << "::" << "load_original_gametest_default" << ": error: " << "guard \"entity_room_associations\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(script_dictionary))
      {
         std::stringstream error_message;
         error_message << "Configuration" << "::" << "load_original_gametest_default" << ": error: " << "guard \"script_dictionary\" not met";
         throw std::runtime_error(error_message.str());
      }
   return true;
}
} // namespace FixedRoom2D
} // namespace Prototypes
} // namespace AllegroFlare


