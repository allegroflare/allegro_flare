



#include <allegro_flare/programming_language.h>

#include <cstdlib> // for atoi and atof
#include <iostream>
#include <string>
#include <vector>




Variable::Variable(std::string identifier, std::string value, std::string type)
   : identifier(identifier)
   , value(value)
   , type(type)
{}




Variable *VirtualMemory::get_record_by_identifier(std::string identifier) const
{
   for (unsigned i=0; i<variable.size(); i++)
   {
      if (variable[i]->identifier == identifier) return variable[i];
   }
   return NULL;
}




std::string VirtualMemory::get(std::string identifier) const
{
   Variable *var = get_record_by_identifier(identifier);
   if (!var) return "";
   return var->value;
}




int VirtualMemory::get_as_int(std::string identifier) const
{
   return atoi(get(identifier).c_str());
}




float VirtualMemory::get_as_float(std::string identifier) const
{
   return (float)atof(get(identifier).c_str());
}




std::string VirtualMemory::get_as_string(std::string identifier) const
{
   return get(identifier);
}




void VirtualMemory::set(std::string identifier, std::string value)
{
   variable.push_back(new Variable(identifier, value, "string"));
}




bool VirtualMemory::isset(std::string identifier) const
{
   for (unsigned i=0; i<variable.size(); i++)
   {
      if (variable[i]->identifier == identifier) return true;
   }
   return false;
}




std::string VirtualMemory::get_type(std::string identifier) const
{
   Variable *var = get_record_by_identifier(identifier);
   if (!var) return "";
   return var->type;
}




void VirtualMemory::set_type(std::string identifier, std::string type)
{
   Variable *var = get_record_by_identifier(identifier);
   if (var) var->type = type;
}




bool VirtualMemory::has_type(std::string identifier)
{
   return (!(get_type(identifier) == ""));
}




void VirtualMemory::dump()
{
   for (unsigned i=0; i<variable.size(); i++)
   {
      std::cout << variable[i]->identifier << " = " << variable[i]->value << std::endl;
   }
}




