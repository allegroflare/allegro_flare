



#include <allegro_flare/attributes.h>




//
//
//
// Internal Definitions
//
//
//



// Converts a value to a string representation.
#include <sstream>
template<class T>
std::string __tostring(T val)
{
	std::ostringstream s;
	s << val;
	return s.str();
}




class Attributes::AttributeRecord
{
public:
   std::string key;
   std::string value;
   std::string datatype;
   void *bound;

   AttributeRecord(std::string key, std::string value="")
      : key(key)
      , value(value)
      , datatype("unbound")
      , bound(NULL)
   {}

   bool is_bound()
   {
      // TODO
      return false;
   }

   bool is_bound_as(std::string datatype)
   {
      // TODO
      return false;
   }
};




class DatatypeDefinition
{
public:
   std::string identifier;
   bool (*to_val_func)(void *val, std::string str);
   std::string (*to_str_func)(void *val);

   DatatypeDefinition(std::string identifier,
      bool (*to_val_func)(void *val, std::string str),
      std::string (*to_str_func)(void *val))
      : identifier(identifier)
      , to_val_func(to_val_func)
      , to_str_func(to_str_func)
   {}

   static std::vector<DatatypeDefinition> definitions;
   static DatatypeDefinition *find_definition(std::string identifier)
   {
      // TODO
      return NULL;
   }
};




//
//
//
// Class Instance Functions
//
//
//




Attributes::Attributes()
{
}




Attributes::~Attributes()
{
}




bool Attributes::exists(std::string key)
{
   int index = __find_attribute_index(key);
   return (index != -1);
}




bool Attributes::exists(std::string key, std::string value)
{
   int index = __find_attribute_index(key, value);
   return (index != -1);
}




bool Attributes::remove(std::string key)
{
   int index = __find_attribute_index(key);
   if (index == -1) return false;

   attributes.erase(attributes.begin() + index);
   return true;
}




bool Attributes::remove(std::string key, std::string value)
{
   int index = __find_attribute_index(key);
   if (index == -1) return false;

   attributes.erase(attributes.begin() + index);
   return true;
}




int Attributes::num_attributes()
{
   return attributes.size();
}




std::string Attributes::get(std::string key)
{
   int index = __find_or_create_attribute_index(key);
   return attributes[index].value;
}




int Attributes::get_as_int(std::string key)
{
   int index = __find_or_create_attribute_index(key);
   return atoi(attributes[index].value.c_str());
}




float Attributes::get_as_float(std::string key)
{
   int index = __find_or_create_attribute_index(key);
   return atof(attributes[index].value.c_str());
}




std::string Attributes::get_as_string(std::string key)
{
   return get(key);
}




bool Attributes::get_as_bool(std::string key)
{
   int index = __find_or_create_attribute_index(key);
   return (strcmp(attributes[index].value.c_str(), "false") != 0);
}




bool Attributes::get_as_custom(void *dest, std::string datatype, std::string key)
{
   // TODO
   return false;
}




void Attributes::set(std::string key, std::string value)
{
   int index = __find_or_create_attribute_index(key);
   attributes[index].value = value;
}




void Attributes::set(std::string key, const char *value)
{
   set(key, std::string(value));
}




void Attributes::set(std::string key, bool value)
{
   int index = __find_or_create_attribute_index(key);
   attributes[index].value = (value ? "true" : "false");
}




void Attributes::set(std::string key, float value)
{
   int index = __find_or_create_attribute_index(key);
   attributes[index].value = __tostring(value);
}




void Attributes::set(std::string key, double value)
{
   set(key, (float)value);
}




void Attributes::set(std::string key, int value)
{
   int index = __find_or_create_attribute_index(key);
   attributes[index].value = __tostring(value);
}




bool Attributes::set(std::string key, std::string datatype, void *value)
{
   // TODO
   return false;
}




bool Attributes::save(std::string filename)
{
   // TODO
   return false;
}




bool Attributes::load(std::string filename)
{
   // TODO
   return false;
}




std::map<std::string, std::string> Attributes::get_copy()
{
   // TODO
   std::map<std::string, std::string> result;
   return result;
}




bool bind(std::string key, float *var)
{
   // TODO
   return false;
}




bool bind(std::string key, int *var)
{
   // TODO
   return false;
}




bool bind(std::string key, bool *var)
{
   // TODO
   return false;
}




bool bind(std::string key, std::string *var)
{
   // TODO
   return false;
}




bool bind(std::string key, std::string datatype, void *var)
{
   // TODO
   return false;
}




bool Attributes::is_bound(std::string key)
{
   // TODO
   return false;
}




std::string Attributes::get_bound_type(std::string key)
{
   // TODO
   return "";
}




bool Attributes::unbind(std::string key)
{
   // TODO
   return false;
}




bool Attributes::is_unsynced(std::string key)
{
   // TODO
   return false;
}




bool Attributes::push_value(std::string key)
{
   // TODO
   return false;
}




bool Attributes::pull_value(std::string key)
{
   // TODO
   return false;
}




void Attributes::create_datatype_definition(
   std::string datatype_identifier,
   bool (*to_val_func)(void *val, std::string str),
   std::string (*to_str_func)(void *val))
{
   // TODO
   return;
}




std::vector<std::string> Attributes::get_known_datatypes()
{
   // TODO
   std::vector<std::string> result;
   return result;
}




int Attributes::__find_attribute_index(std::string key)
{
   for (int i=0; i<attributes.size(); i++)
      if (strcmp(key.c_str(), attributes[i].key.c_str()) == 0) return i;
   return -1;
}




int Attributes::__find_attribute_index(std::string key, std::string value)
{
   for (int i=0; i<attributes.size(); i++)
      if ((strcmp(key.c_str(), attributes[i].key.c_str()) == 0)
         && (strcmp(value.c_str(), attributes[i].value.c_str()) == 0))
         return i;
   return -1;
}




int Attributes::__find_or_create_attribute_index(std::string key)
{
   for (int i=0; i<attributes.size(); i++)
      if (strcmp(key.c_str(), attributes[i].key.c_str()) == 0) return i;
   attributes.push_back(AttributeRecord(key));
   return attributes.size()-1;
}




