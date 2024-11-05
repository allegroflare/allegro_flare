#pragma once


#include <map>
#include <string>


namespace AllegroFlare
{
   namespace Tiled
   {
      class TMJObjectCustomProperties
      {
      private:
         std::map<std::string, std::string> string_properties;
         std::map<std::string, bool> bool_properties;
         std::map<std::string, int> int_properties;
         std::map<std::string, float> float_properties;
         std::map<std::string, std::string> color_properties;
         void throw_if_key_already_exists(std::string key="[unset-key]", std::string while_in_method_name="[unset-location]");
         void throw_if_key_does_not_exist(std::string key="[unset-key]", std::string while_in_method_name="[unset-location]");

      protected:


      public:
         TMJObjectCustomProperties();
         ~TMJObjectCustomProperties();

         void set_string_properties(std::map<std::string, std::string> string_properties);
         void set_bool_properties(std::map<std::string, bool> bool_properties);
         void set_int_properties(std::map<std::string, int> int_properties);
         void set_float_properties(std::map<std::string, float> float_properties);
         void set_color_properties(std::map<std::string, std::string> color_properties);
         std::map<std::string, std::string> get_string_properties() const;
         std::map<std::string, bool> get_bool_properties() const;
         std::map<std::string, int> get_int_properties() const;
         std::map<std::string, float> get_float_properties() const;
         std::map<std::string, std::string> get_color_properties() const;
         std::string get_keys_in_list();
         bool empty();
         void clear();
         void add_string(std::string name="[unset-name]", std::string value="[unset-value]");
         void add_bool(std::string name="[unset-name]", bool value=false);
         void add_float(std::string name="[unset-name]", float value=0.0f);
         void add_int(std::string name="[unset-name]", int value=0);
         void add_color(std::string name="[unset-name]", std::string value="[unset-value]");
         std::string get_string(std::string name="[unset-name]");
         bool get_bool(std::string name="[unset-name]");
         float get_float(std::string name="[unset-name]");
         int get_int(std::string name="[unset-name]");
         std::string get_color(std::string name="[unset-name]");
         std::string get_type(std::string name="[unset-name]");
         bool exists(std::string name="[unset-name]");
         bool is_float(std::string name="[unset-name]");
         bool is_bool(std::string name="[unset-name]");
         bool is_int(std::string name="[unset-name]");
         bool is_string(std::string name="[unset-name]");
         bool is_color(std::string name="[unset-name]");
      };
   }
}



