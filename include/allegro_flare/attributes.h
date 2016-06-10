#ifndef __AF_ATTRIBUTES_HEADER
#define __AF_ATTRIBUTES_HEADER




#include <map>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>




class Attributes
{
private:
   class AttributeRecord
   {
   public:
      std::string key;
      std::string value;
      std::string datatype;
      void *bound;

      AttributeRecord(std::string key, std::string value="");
      bool is_bound();
      bool is_bound_as(std::string datatype);
   };

   std::vector<AttributeRecord> attributes;

public:
   Attributes();
   ~Attributes();


   //
   // Checking the presence of attributes
   //

   // Returns true if the matching key or key/value pair exists
   bool exists(std::string key);
   bool exists(std::string key, std::string value);

   // Removes the key-value pair from the attributes (if it exists)
   bool remove(std::string key);
   bool remove(std::string key, std::string value);

   // Return the number of attributes that currently exist
   int num_attributes();


   //
   // Getting / Setting Values
   //

   // Set the value of the attribute
   void set(std::string key, std::string value="");
   void set(std::string key, const char *value);
   void set(std::string key, bool value);
   void set(std::string key, float value);
   void set(std::string key, double value); // will downcast to float
   void set(std::string key, int value);

   // Set the value of the attribute using a custom datatype
   bool set(std::string key, std::string datatype, void *value);

   // Return the value of the attribute formatted as a std::string
   std::string get(std::string key);

   // Return the value of the attribute as an int
   int get_as_int(std::string key);

   // Return the value of the attribute as a float
   float get_as_float(std::string key);

   // Return the value of the attribute as a std::string datatype
   std::string get_as_string(std::string key);

   // Returns the value of the attribute as a bool.
   // A value that is anything other than "false" will evaluate to true.
   bool get_as_bool(std::string key);

   // Gets the value of the attribute as a custom datatype and assigns it to dest
   bool get_as_custom(void *dest, std::string datatype, std::string key);


   //
   // Storing and retrieving the attributes
   //

   // Save all the key-value pairs to a text file
   bool save(std::string filename);

   // Load all the key-value pairs from a text file
   bool load(std::string filename);

   // Get a copy of the entire set of key-value pairs
   std::map<std::string, std::string> get_copy();


   //
   // Binding to actual C/C++ variables
   //

   // Bind a variable to the attribute.  Binding will cause the variable to be
   // updated anytime the attribute is modified.
   void bind(std::string key, float *var);
   void bind(std::string key, int *var);
   void bind(std::string key, bool *var);
   void bind(std::string key, std::string *var);
   bool bind(std::string key, std::string datatype, void *var);

   // Returns true if the attribute is currently bound to a variable
   bool is_bound(std::string key);

   // Returns true if the attribute is currently bound to a variable matching the datatype
   bool is_bound_as(std::string key, std::string datatype);

   // Get the datatype of the variable that the attribute is currently bounded to.
   // Possible return values are "string", "int", "float", "bool", "unbound",
   // or any custom datatype that has been defined with create_datatype_definition()
   std::string get_bound_type(std::string key);

   // Unbind the attriute from its currently bound variable if one is currently bound
   bool unbind(std::string key);

   // Returns true if the attribute and its bound variable have the same value
   bool is_synced(std::string key);

   // Returns true if the attribute and its bound variable do not have the same value
   bool is_unsynced(std::string key);

   // Refresh the attribute to match the current value of its bound variable
   bool push_value(std::string key);

   // Refresh the bound variable to match the value of the attribute
   bool pull_value(std::string key);


   //
   // Binding to a custom datatype
   //

   // Create a definition for a datatype so it can be bound to an attribute
   static bool create_datatype_definition(std::string datatype_identifier,
                                          bool (*to_val_func)(void *val, std::string str),
                                          std::string (*to_str_func)(void *val));

   // Returns true if the datatype has a known definition
   static bool datatype_is_known(std::string datatype);

   // Return a vector containing string names for all recognized datatypes
   static std::vector<std::string> get_known_datatypes();

private:
   static std::vector<std::string> denied_custom_types;

   int __find_attribute_index(std::string key);
   int __find_attribute_index(std::string key, std::string value);
   int __find_or_create_attribute_index(std::string key);
};




#endif
