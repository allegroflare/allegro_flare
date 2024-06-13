

#include <AllegroFlare/Prototypes/FixedRoom2D/ConfigurationLoader.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Prototypes
{
namespace FixedRoom2D
{


ConfigurationLoader::ConfigurationLoader(AllegroFlare::Prototypes::FixedRoom2D::Configuration* source_configuration, AllegroFlare::InventoryIndex* destination_inventory_index, AllegroFlare::Inventory* destination_af_inventory, AllegroFlare::Inventory* destination_flags, std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>* destination_entity_dictionary, std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Room*>* destination_room_dictionary, std::map<std::string, std::string>* destination_entity_room_associations, std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Script>* destination_script_dictionary, std::string* destination_starting_room_identifier)
   : source_configuration(source_configuration)
   , destination_inventory_index(destination_inventory_index)
   , destination_af_inventory(destination_af_inventory)
   , destination_flags(destination_flags)
   , destination_entity_dictionary(destination_entity_dictionary)
   , destination_room_dictionary(destination_room_dictionary)
   , destination_entity_room_associations(destination_entity_room_associations)
   , destination_script_dictionary(destination_script_dictionary)
   , destination_starting_room_identifier(destination_starting_room_identifier)
{
}


ConfigurationLoader::~ConfigurationLoader()
{
}


void ConfigurationLoader::set_source_configuration(AllegroFlare::Prototypes::FixedRoom2D::Configuration* source_configuration)
{
   this->source_configuration = source_configuration;
}


void ConfigurationLoader::set_destination_inventory_index(AllegroFlare::InventoryIndex* destination_inventory_index)
{
   this->destination_inventory_index = destination_inventory_index;
}


void ConfigurationLoader::set_destination_af_inventory(AllegroFlare::Inventory* destination_af_inventory)
{
   this->destination_af_inventory = destination_af_inventory;
}


void ConfigurationLoader::set_destination_flags(AllegroFlare::Inventory* destination_flags)
{
   this->destination_flags = destination_flags;
}


void ConfigurationLoader::set_destination_entity_dictionary(std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>* destination_entity_dictionary)
{
   this->destination_entity_dictionary = destination_entity_dictionary;
}


void ConfigurationLoader::set_destination_room_dictionary(std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Room*>* destination_room_dictionary)
{
   this->destination_room_dictionary = destination_room_dictionary;
}


void ConfigurationLoader::set_destination_entity_room_associations(std::map<std::string, std::string>* destination_entity_room_associations)
{
   this->destination_entity_room_associations = destination_entity_room_associations;
}


void ConfigurationLoader::set_destination_script_dictionary(std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Script>* destination_script_dictionary)
{
   this->destination_script_dictionary = destination_script_dictionary;
}


void ConfigurationLoader::set_destination_starting_room_identifier(std::string* destination_starting_room_identifier)
{
   this->destination_starting_room_identifier = destination_starting_room_identifier;
}


AllegroFlare::Prototypes::FixedRoom2D::Configuration* ConfigurationLoader::get_source_configuration() const
{
   return source_configuration;
}


AllegroFlare::InventoryIndex* ConfigurationLoader::get_destination_inventory_index() const
{
   return destination_inventory_index;
}


AllegroFlare::Inventory* ConfigurationLoader::get_destination_af_inventory() const
{
   return destination_af_inventory;
}


AllegroFlare::Inventory* ConfigurationLoader::get_destination_flags() const
{
   return destination_flags;
}


std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>* ConfigurationLoader::get_destination_entity_dictionary() const
{
   return destination_entity_dictionary;
}


std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Room*>* ConfigurationLoader::get_destination_room_dictionary() const
{
   return destination_room_dictionary;
}


std::map<std::string, std::string>* ConfigurationLoader::get_destination_entity_room_associations() const
{
   return destination_entity_room_associations;
}


std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Script>* ConfigurationLoader::get_destination_script_dictionary() const
{
   return destination_script_dictionary;
}


std::string* ConfigurationLoader::get_destination_starting_room_identifier() const
{
   return destination_starting_room_identifier;
}


bool ConfigurationLoader::load_from_source_configuration()
{
   if (!(source_configuration))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::ConfigurationLoader::load_from_source_configuration]: error: guard \"source_configuration\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::ConfigurationLoader::load_from_source_configuration]: error: guard \"source_configuration\" not met");
   }
   *destination_inventory_index = source_configuration->get_inventory_index_ref();
   *destination_af_inventory = source_configuration->get_af_inventory();
   *destination_room_dictionary = source_configuration->get_room_dictionary();
   *destination_entity_dictionary = source_configuration->get_entity_dictionary();
   *destination_entity_room_associations = source_configuration->get_entity_room_associations();
   *destination_script_dictionary = source_configuration->get_script_dictionary();
   *destination_starting_room_identifier = source_configuration->get_starting_room_identifier();
   return true;
}


} // namespace FixedRoom2D
} // namespace Prototypes
} // namespace AllegroFlare


