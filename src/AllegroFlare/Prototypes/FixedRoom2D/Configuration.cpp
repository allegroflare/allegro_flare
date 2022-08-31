

#include <AllegroFlare/Prototypes/FixedRoom2D/Configuration.hpp>




namespace AllegroFlare
{
namespace Prototypes
{
namespace FixedRoom2D
{


Configuration::Configuration(AllegroFlare::InventoryIndex inventory_index, AllegroFlare::Inventory af_inventory, AllegroFlare::Inventory flags, std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> entity_dictionary, std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Room*> room_dictionary, std::map<std::string, std::string> entity_room_associations, std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Script> script_dictionary)
   : inventory_index(inventory_index)
   , af_inventory(af_inventory)
   , flags(flags)
   , entity_dictionary(entity_dictionary)
   , room_dictionary(room_dictionary)
   , entity_room_associations(entity_room_associations)
   , script_dictionary(script_dictionary)
   , starting_in_room_identifier("[unset-starting_in_room_identifier]")
{
}


Configuration::~Configuration()
{
}


void Configuration::set_inventory_index(AllegroFlare::InventoryIndex inventory_index)
{
   this->inventory_index = inventory_index;
}


void Configuration::set_af_inventory(AllegroFlare::Inventory af_inventory)
{
   this->af_inventory = af_inventory;
}


void Configuration::set_flags(AllegroFlare::Inventory flags)
{
   this->flags = flags;
}


void Configuration::set_entity_dictionary(std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> entity_dictionary)
{
   this->entity_dictionary = entity_dictionary;
}


void Configuration::set_room_dictionary(std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Room*> room_dictionary)
{
   this->room_dictionary = room_dictionary;
}


void Configuration::set_entity_room_associations(std::map<std::string, std::string> entity_room_associations)
{
   this->entity_room_associations = entity_room_associations;
}


void Configuration::set_script_dictionary(std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Script> script_dictionary)
{
   this->script_dictionary = script_dictionary;
}


void Configuration::set_starting_in_room_identifier(std::string starting_in_room_identifier)
{
   this->starting_in_room_identifier = starting_in_room_identifier;
}


AllegroFlare::InventoryIndex Configuration::get_inventory_index() const
{
   return inventory_index;
}


AllegroFlare::Inventory Configuration::get_af_inventory() const
{
   return af_inventory;
}


AllegroFlare::Inventory Configuration::get_flags() const
{
   return flags;
}


std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> Configuration::get_entity_dictionary() const
{
   return entity_dictionary;
}


std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Room*> Configuration::get_room_dictionary() const
{
   return room_dictionary;
}


std::map<std::string, std::string> Configuration::get_entity_room_associations() const
{
   return entity_room_associations;
}


std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Script> Configuration::get_script_dictionary() const
{
   return script_dictionary;
}


std::string Configuration::get_starting_in_room_identifier() const
{
   return starting_in_room_identifier;
}


AllegroFlare::InventoryIndex &Configuration::get_inventory_index_ref()
{
   return inventory_index;
}


AllegroFlare::Inventory &Configuration::get_af_inventory_ref()
{
   return af_inventory;
}


AllegroFlare::Inventory &Configuration::get_flags_ref()
{
   return flags;
}


std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> &Configuration::get_entity_dictionary_ref()
{
   return entity_dictionary;
}


std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Room*> &Configuration::get_room_dictionary_ref()
{
   return room_dictionary;
}


std::map<std::string, std::string> &Configuration::get_entity_room_associations_ref()
{
   return entity_room_associations;
}


std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Script> &Configuration::get_script_dictionary_ref()
{
   return script_dictionary;
}


std::string &Configuration::get_starting_in_room_identifier_ref()
{
   return starting_in_room_identifier;
}




} // namespace FixedRoom2D
} // namespace Prototypes
} // namespace AllegroFlare


