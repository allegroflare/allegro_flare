



#include <allegro_flare/attributes.h>




//
//
//
// Internal Definitions
//
//
//




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
   // TODO
   int index = __find_attribute_index(key);
   return (index != -1);
}




bool Attributes::exists(std::string key, std::string value)
{
   // TODO
   return false;
}




bool Attributes::remove(std::string key)
{
   // TODO
   return false;
}




bool Attributes::remove(std::string key, std::string value)
{
   // TODO
   return false;
}




int Attributes::num_attributes()
{
   // TODO
   return 0;
}




std::string Attributes::get(std::string key)
{
   // TODO
   return "";
}




int Attributes::get_as_int(std::string key)
{
   // TODO
   return 0;
}




float Attributes::get_as_float(std::string key)
{
   // TODO
   return 0.0;
}




std::string Attributes::get_as_string(std::string key)
{
   // TODO
   return "";
}




bool Attributes::get_as_bool(std::string key)
{
   // TODO
   return false;
}




bool Attributes::get_as_custom(void *dest, std::string datatype, std::string key)
{
   // TODO
   return false;
}




void Attributes::set(std::string key, std::string value)
{
   // TODO
   int index = __find_or_create_attribute_index(key);
   attributes[index].value = value;
}




void Attributes::set(std::string key, const char *value)
{
   set(key, std::string(value));
}




void Attributes::set(std::string key, bool value)
{
   // TODO
   return;
}




void Attributes::set(std::string key, float value)
{
   // TODO
   return;
}




void Attributes::set(std::string key, int value)
{
   // TODO
   return;
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
   // TODO
   return -1;
}




int Attributes::__find_or_create_attribute_index(std::string key)
{
   for (int i=0; i<attributes.size(); i++)
      if (strcmp(key.c_str(), attributes[i].key.c_str()) == 0) return i;
   attributes.push_back(AttributeRecord(key));
   return attributes.size()-1;
}




