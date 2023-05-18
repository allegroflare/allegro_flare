#pragma once


#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>


namespace AllegroFlare
{
   class YAMLValidator
   {
   private:
      static std::string join(std::vector<std::string> tokens={}, std::string delimiter=", ");
      static std::string quote_and_escape_inner_quotes(std::string subject="[unset-subject]");
      static std::string replace(std::string subject="[unset-subject]", std::string search="[unset-search]", std::string replace="[unset-replace]");

   protected:


   public:
      YAMLValidator();
      ~YAMLValidator();

      static bool validate_presence_of_key(YAML::Node node={}, std::string key="[unset-key]", bool throw_on_error=true);
      static bool validate_node_type(YAML::Node node={}, std::string key="[unset-key]", YAML::NodeType::value expected_type=YAML::NodeType::Undefined, bool throw_on_error=true);
      static bool validate_node_is_one_of_type(YAML::Node node={}, std::string key="[unset-key]", std::vector<YAML::NodeType::value> possible_valid_types={}, bool throw_on_error=true);
      static bool validate_node_has_unsigned_int_value(YAML::Node node={}, std::string key="[unset-key]");
      static bool validate_elements_are_unique(std::vector<std::string> elements={});
      static std::string yaml_node_type_as_string(YAML::NodeType::value node_type=YAML::NodeType::Undefined);
      static bool validate_unique_all_upper_identifiers(YAML::Node items={});
      static std::string get_type_string(YAML::Node* node_ptr=nullptr);
      static std::vector<std::string> extract_sequence_as_string_array(YAML::Node source={});
   };
}



