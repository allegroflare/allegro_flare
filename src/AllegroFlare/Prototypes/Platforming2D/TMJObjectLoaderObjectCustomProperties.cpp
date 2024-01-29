

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


} // namespace Platforming2D
} // namespace Prototypes
} // namespace AllegroFlare


