

#include <AllegroFlare/Attributes.hpp>

#include <cstdio>
#include <cstring>
#include <fstream>
#include <sstream>




namespace AllegroFlare
{
   //
   //
   //
   // Internal Definitions
   //
   //
   //




   // Converts a value to a string representation.
//#include <sstream>
   template<class T>
   std::string __tostring(T val)
   {
      std::ostringstream s;
      s << val;
      return s.str();
   }




   Attributes::AttributeRecord::AttributeRecord(std::string key, std::string value)
      : key(key)
      , value(value)
      , datatype("unbound")
      , bound(NULL)
   {}




   bool Attributes::AttributeRecord::is_bound()
   {
      return (strcmp(datatype.c_str(), "unbound") != 0);
   }




   bool Attributes::AttributeRecord::is_bound_as(std::string datatype)
   {
      return (strcmp(this->datatype.c_str(), datatype.c_str()) == 0);
   }




   class DatatypeDefinition
   {
   public:
      std::string identifier;
      bool (*to_val_func)(void *val, std::string str);
      std::string (*to_str_func)(void *val);

      DatatypeDefinition(std::string identifier, bool (*to_val_func)(void *val, std::string str), std::string (*to_str_func)(void *val))
         : identifier(identifier)
         , to_val_func(to_val_func)
         , to_str_func(to_str_func)
      {}

      static std::vector<DatatypeDefinition> definitions;
      static DatatypeDefinition *find_definition(std::string identifier)
      {
         for (auto &definition : definitions)
            if (strcmp(definition.identifier.c_str(), identifier.c_str()) == 0) return &definition;
         return NULL;
      }
   };

   std::vector<DatatypeDefinition> DatatypeDefinition::definitions;




   //
   //
   //
   // Class Instance Functions
   //
   //
   //




   std::vector<std::string> Attributes::denied_custom_types = {"int", "float", "bool", "string"};




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
      pull_value(key);
      return atoi(attributes[index].value.c_str());
   }




   float Attributes::get_as_float(std::string key)
   {
      int index = __find_or_create_attribute_index(key);
      pull_value(key);
      return atof(attributes[index].value.c_str());
   }




   std::string Attributes::get_as_string(std::string key)
   {
      return get(key);
   }




   bool Attributes::get_as_bool(std::string key)
   {
      int index = __find_or_create_attribute_index(key);
      pull_value(key);
      return (strcmp(attributes[index].value.c_str(), "false") != 0);
   }




   bool Attributes::get_as_custom(void *dest, std::string datatype, std::string key)
   {
      int index = __find_or_create_attribute_index(key);
      DatatypeDefinition *datatype_def = DatatypeDefinition::find_definition(datatype);
      if (!datatype_def) return false; // perhaps throw an error here
      pull_value(key);
      return datatype_def->to_val_func(dest, attributes[index].value);
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
      int index = __find_or_create_attribute_index(key);
      DatatypeDefinition *datatype_def = DatatypeDefinition::find_definition(datatype);
      if (!datatype_def) return false; // perhaps throw an error here
      attributes[index].value = datatype_def->to_str_func(value);
      return true;
   }




   bool Attributes::save(std::string filename)
   {
#define DELIMITER ": "

      std::ofstream file;
      file.open(filename);

      for(auto &a : attributes)
         file << a.key << DELIMITER << a.value << std::endl;

      file.close();

      return false;

#undef DELIMITER
   }




   bool Attributes::load(std::string filename)
   {
#define DELIMITER ": "

      std::ifstream file(filename);
      std::string delimiter = DELIMITER;

      for (std::string line; std::getline(file, line); )
      {
         int pos = line.find(delimiter);
         std::string key = line.substr(0, pos);
         std::string value = line.erase(0, pos + delimiter.length());
         set(key, value);
      }

      return false;

#undef DELIMITER
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
      if (datatype == "int" || datatype == "float" || datatype == "bool" || datatype == "string"
            || DatatypeDefinition::find_definition(datatype))
      {
         attributes[index].datatype = datatype;
         attributes[index].bound = var;
         pull_value(key);
         return true;
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
      else
      {
         DatatypeDefinition *datatype_def = DatatypeDefinition::find_definition(attributes[index].datatype);
         if (!datatype_def) return false; // possibly throw an error
         return attributes[index].value == datatype_def->to_str_func(attributes[index].bound);
      }
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
      else
      {
         DatatypeDefinition *datatype_def = DatatypeDefinition::find_definition(attributes[index].datatype);
         if (!datatype_def) return false; // possibly throw an error
         return datatype_def->to_val_func(attributes[index].bound, attributes[index].value);
      }
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
      else
      {
         DatatypeDefinition *datatype_def = DatatypeDefinition::find_definition(attributes[index].datatype);
         if (!datatype_def) return false; // possibly throw an error
         attributes[index].value = datatype_def->to_str_func(attributes[index].bound);
      }
      return true;
   }




   bool Attributes::create_datatype_definition(
         std::string identifier,
         bool (*to_val_func)(void *val, std::string str),
         std::string (*to_str_func)(void *val))
   {
      std::vector<std::string> &denied_types = Attributes::denied_custom_types;
      if (std::find(denied_types.begin(), denied_types.end(), identifier) != denied_types.end()) return false;

      DatatypeDefinition *definition = DatatypeDefinition::find_definition(identifier);
      if (definition) return false;

      DatatypeDefinition::definitions.push_back(DatatypeDefinition(identifier, to_val_func, to_str_func));
      return true;
   }




   bool Attributes::datatype_is_known(std::string datatype)
   {
      return (DatatypeDefinition::find_definition(datatype) != NULL);
   }




   std::vector<std::string> Attributes::get_known_datatypes()
   {
      std::vector<std::string> result = Attributes::denied_custom_types;
      for (unsigned i=0; i<DatatypeDefinition::definitions.size(); i++)
         result.push_back(DatatypeDefinition::definitions[i].identifier);
      std::sort(result.begin(), result.end());
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
}





