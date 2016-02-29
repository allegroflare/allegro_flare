



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
      return (strcmp(datatype.c_str(), "unbound") != 0);
   }

   bool is_bound_as(std::string datatype)
   {
      return (strcmp(this->datatype.c_str(), datatype.c_str()) == 0);
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
   pull_value(key);
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
   push_value(key);
}




void Attributes::set(std::string key, const char *value)
{
   set(key, std::string(value));
}




void Attributes::set(std::string key, bool value)
{
   int index = __find_or_create_attribute_index(key);
   attributes[index].value = (value ? "true" : "false");
   push_value(key);
}




void Attributes::set(std::string key, float value)
{
   int index = __find_or_create_attribute_index(key);
   attributes[index].value = __tostring(value);
   push_value(key);
}




void Attributes::set(std::string key, double value)
{
   set(key, (float)value);
}




void Attributes::set(std::string key, int value)
{
   int index = __find_or_create_attribute_index(key);
   attributes[index].value = __tostring(value);
   push_value(key);
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
   std::map<std::string, std::string> result;
   for (unsigned i=0; i<attributes.size(); i++)
      result[attributes[i].key] = get(attributes[i].key);
   return result;
}




void Attributes::bind(std::string key, float *var)
{
   bind(key, "float", (void *)var);
}




void Attributes::bind(std::string key, int *var)
{
   bind(key, "int", (void *)var);
}




void Attributes::bind(std::string key, bool *var)
{
   bind(key, "bool", (void *)var);
}




void Attributes::bind(std::string key, std::string *var)
{
   bind(key, "string", (void *)var);
}




bool Attributes::bind(std::string key, std::string datatype, void *var)
{
   int index = __find_or_create_attribute_index(key);
   if (datatype == "int" || datatype == "float" || datatype == "bool" || datatype == "string")
   {
      attributes[index].datatype = datatype;
      attributes[index].bound = var;
      pull_value(key);
      return true;
   }
   else
   {
      // TODO handle created datatypes; throw if type is unrecognized
   }
   return false;
}




bool Attributes::is_bound(std::string key)
{
   int index = __find_attribute_index(key);
   if (index == -1) return false; // TODO possibly throw an error
   return (strcmp(attributes[index].datatype.c_str(), "unbound") != 0);
}




bool Attributes::is_bound_as(std::string key, std::string datatype)
{
   int index = __find_attribute_index(key);
   if (index == -1) return false;
   if (!attributes[index].is_bound() && (datatype == "unbound")) return true;
   return strcmp(attributes[index].datatype.c_str(), datatype.c_str()) == 0;
}




std::string Attributes::get_bound_type(std::string key)
{
   int index = __find_attribute_index(key);
   if (index == -1) return "";
   if (!attributes[index].is_bound()) return "unbound";
   return attributes[index].datatype;
}




bool Attributes::unbind(std::string key)
{
   int index = __find_attribute_index(key);
   if (index == -1 || !attributes[index].is_bound()) return false;
   attributes[index].datatype = "unbound";
   attributes[index].bound = NULL;
   return true;
}




bool Attributes::is_synced(std::string key)
{
   int index = __find_attribute_index(key);
   if (index == -1 || !attributes[index].is_bound())
      return true;
   else if (attributes[index].datatype == "int")
      return attributes[index].value == __tostring(*static_cast<int *>(attributes[index].bound));
   else if (attributes[index].datatype == "float")
      return attributes[index].value == __tostring(*static_cast<float *>(attributes[index].bound));
   else if (attributes[index].datatype == "bool")
      return attributes[index].value == (*static_cast<bool *>(attributes[index].bound) ? "true" : "false");
   else if (attributes[index].datatype == "string")
      return attributes[index].value == (*static_cast<std::string *>(attributes[index].bound));
   //TODO custom datatype or unknown datatype
   return false;
}




bool Attributes::is_unsynced(std::string key)
{
   return !is_synced(key);
}




bool Attributes::push_value(std::string key)
{
   int index = __find_attribute_index(key);
   if (index == -1 || !attributes[index].is_bound())
      return false;
   else if (attributes[index].datatype == "int")
      *static_cast<int *>(attributes[index].bound) = atoi(attributes[index].value.c_str());
   else if (attributes[index].datatype == "float")
      *static_cast<float *>(attributes[index].bound) = atof(attributes[index].value.c_str());
   else if (attributes[index].datatype == "bool")
      *static_cast<bool *>(attributes[index].bound) = (attributes[index].value != "false");
   else if (attributes[index].datatype == "string")
      *static_cast<std::string *>(attributes[index].bound) = attributes[index].value;
   //TODO custom datatype or unknown datatype
   return true;
}




bool Attributes::pull_value(std::string key)
{
   int index = __find_attribute_index(key);
   if (index == -1 || !attributes[index].is_bound())
      return false;
   else if (attributes[index].datatype == "int")
      attributes[index].value = __tostring(*static_cast<int *>(attributes[index].bound));
   else if (attributes[index].datatype == "float")
      attributes[index].value = __tostring(*static_cast<float *>(attributes[index].bound));
   else if (attributes[index].datatype == "bool")
      attributes[index].value = (*static_cast<bool *>(attributes[index].bound) ? "true" : "false");
   else if (attributes[index].datatype == "string")
      attributes[index].value = (*static_cast<std::string *>(attributes[index].bound));
   //TODO custom datatype or unknown datatype
   return true;
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




