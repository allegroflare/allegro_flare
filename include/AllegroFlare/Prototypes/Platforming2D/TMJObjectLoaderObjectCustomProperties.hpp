#pragma once


#include <map>
#include <string>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace Platforming2D
      {
         class TMJObjectLoaderObjectCustomProperties
         {
         private:
            std::map<std::string, std::string> string_properties;
            std::map<std::string, bool> bool_properties;
            std::map<std::string, int> int_properties;
            std::map<std::string, float> float_properties;

         protected:


         public:
            TMJObjectLoaderObjectCustomProperties();
            ~TMJObjectLoaderObjectCustomProperties();

            void set_string_properties(std::map<std::string, std::string> string_properties);
            void set_bool_properties(std::map<std::string, bool> bool_properties);
            void set_int_properties(std::map<std::string, int> int_properties);
            void set_float_properties(std::map<std::string, float> float_properties);
            std::map<std::string, std::string> get_string_properties() const;
            std::map<std::string, bool> get_bool_properties() const;
            std::map<std::string, int> get_int_properties() const;
            std::map<std::string, float> get_float_properties() const;
            void add(std::string name="[unset-name]", std::string value="[unset-value]");
            void add(std::string name="[unset-name]", float value=0.0f);
            void add(std::string name="[unset-name]", int value=0);
            void add(std::string name="[unset-name]", bool value=false);
            void add_string(std::string name="[unset-name]", std::string value="[unset-value]");
            void add_bool(std::string name="[unset-name]", bool value=false);
            void add_float(std::string name="[unset-name]", float value=0.0f);
            void add_int(std::string name="[unset-name]", int value=0);
            std::string get_string(std::string name="[unset-name]");
            bool get_bool(std::string name="[unset-name]");
            float get_float(std::string name="[unset-name]");
            int get_int(std::string name="[unset-name]");
            std::string get_type(std::string name="[unset-name]");
            bool exists(std::string name="[unset-name]");
         };
      }
   }
}



