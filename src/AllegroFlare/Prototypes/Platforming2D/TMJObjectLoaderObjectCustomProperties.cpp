

#include <AllegroFlare/Prototypes/Platforming2D/TMJObjectLoaderObjectCustomProperties.hpp>




namespace AllegroFlare
{
namespace Prototypes
{
namespace Platforming2D
{


TMJObjectLoaderObjectCustomProperties::TMJObjectLoaderObjectCustomProperties()
   : string_properties({})
   , bool_properties({})
   , int_properties({})
   , float_properties({})
{
}


TMJObjectLoaderObjectCustomProperties::~TMJObjectLoaderObjectCustomProperties()
{
}


void TMJObjectLoaderObjectCustomProperties::set_string_properties(std::map<std::string, std::string> string_properties)
{
   this->string_properties = string_properties;
}


void TMJObjectLoaderObjectCustomProperties::set_bool_properties(std::map<std::string, bool> bool_properties)
{
   this->bool_properties = bool_properties;
}


void TMJObjectLoaderObjectCustomProperties::set_int_properties(std::map<std::string, int> int_properties)
{
   this->int_properties = int_properties;
}


void TMJObjectLoaderObjectCustomProperties::set_float_properties(std::map<std::string, float> float_properties)
{
   this->float_properties = float_properties;
}


std::map<std::string, std::string> TMJObjectLoaderObjectCustomProperties::get_string_properties() const
{
   return string_properties;
}


std::map<std::string, bool> TMJObjectLoaderObjectCustomProperties::get_bool_properties() const
{
   return bool_properties;
}


std::map<std::string, int> TMJObjectLoaderObjectCustomProperties::get_int_properties() const
{
   return int_properties;
}


std::map<std::string, float> TMJObjectLoaderObjectCustomProperties::get_float_properties() const
{
   return float_properties;
}


void TMJObjectLoaderObjectCustomProperties::add(std::string name, std::string value)
{
   // TODO: Check for duplicate or overwrite
   string_properties[name] = value;
}

void TMJObjectLoaderObjectCustomProperties::add(std::string name, float value)
{
   // TODO: Check for duplicate or overwrite
   float_properties[name] = value;
}

void TMJObjectLoaderObjectCustomProperties::add(std::string name, int value)
{
   // TODO: Check for duplicate or overwrite
   float_properties[name] = value;
}

void TMJObjectLoaderObjectCustomProperties::add(std::string name, bool value)
{
   // TODO: Check for duplicate or overwrite
   bool_properties[name] = value;
}

void TMJObjectLoaderObjectCustomProperties::add_string(std::string name, std::string value)
{
   // TODO: Check for duplicate or overwrite
   string_properties[name] = value;
}

void TMJObjectLoaderObjectCustomProperties::add_bool(std::string name, bool value)
{
   // TODO: Check for duplicate or overwrite
   bool_properties[name] = value;
}

void TMJObjectLoaderObjectCustomProperties::add_float(std::string name, float value)
{
   // TODO: Check for duplicate or overwrite
   float_properties[name] = value;
}

void TMJObjectLoaderObjectCustomProperties::add_int(std::string name, int value)
{
   // TODO: Check for duplicate or overwrite
   int_properties[name] = value;
}

std::string TMJObjectLoaderObjectCustomProperties::get_string(std::string name)
{
   // TODO: Check for existence
   return string_properties[name];
}

bool TMJObjectLoaderObjectCustomProperties::get_bool(std::string name)
{
   // TODO: Check for existence
   return bool_properties[name];
}

float TMJObjectLoaderObjectCustomProperties::get_float(std::string name)
{
   // TODO: Check for existence
   return float_properties[name];
}

int TMJObjectLoaderObjectCustomProperties::get_int(std::string name)
{
   // TODO: Check for existence
   return int_properties[name];
}

std::string TMJObjectLoaderObjectCustomProperties::get_type(std::string name)
{
   // TODO: Check for duplicate or overwrite
   if (float_properties.find(name) != float_properties.end()) return "float";
   if (int_properties.find(name) != int_properties.end()) return "int";
   if (bool_properties.find(name) != bool_properties.end()) return "bool";
   if (string_properties.find(name) != string_properties.end()) return "string";
   return "[ERROR-does_not_exist]";
}

bool TMJObjectLoaderObjectCustomProperties::exists(std::string name)
{
   // TODO: Check for duplicate or overwrite
   if (float_properties.find(name) != float_properties.end()) return true;
   if (int_properties.find(name) != int_properties.end()) return true;
   if (bool_properties.find(name) != bool_properties.end()) return true;
   if (string_properties.find(name) != string_properties.end()) return true;
   return false;
}

bool TMJObjectLoaderObjectCustomProperties::is_float(std::string name)
{
   // TODO: Conaider checking for existence first
   if (float_properties.find(name) != float_properties.end()) return true;
   return false;
}

bool TMJObjectLoaderObjectCustomProperties::is_bool(std::string name)
{
   // TODO: Conaider checking for existence first
   if (bool_properties.find(name) != bool_properties.end()) return true;
   return false;
}

bool TMJObjectLoaderObjectCustomProperties::is_int(std::string name)
{
   // TODO: Conaider checking for existence first
   if (int_properties.find(name) != int_properties.end()) return true;
   return false;
}

bool TMJObjectLoaderObjectCustomProperties::is_string(std::string name)
{
   // TODO: Conaider checking for existence first
   if (string_properties.find(name) != string_properties.end()) return true;
   return false;
}


} // namespace Platforming2D
} // namespace Prototypes
} // namespace AllegroFlare


