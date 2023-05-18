

#include <AllegroFlare/YAMLValidator.hpp>

#include <AllegroFlare/Logger.hpp>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <unordered_set>


namespace AllegroFlare
{


YAMLValidator::YAMLValidator()
{
}


YAMLValidator::~YAMLValidator()
{
}


bool YAMLValidator::validate_presence_of_key(YAML::Node node, std::string key, bool throw_on_error)
{
   // TODO: test this function
   if (node[key]) return true;

   if (throw_on_error)
   {
      std::stringstream error_message;
      error_message << "[YAMLValidator::validate_presence_of_key]: error: "
                    << "expecting to find node \"" << key << "\" but it is not present.";
      throw std::runtime_error(error_message.str());
   }
   return false;
}

bool YAMLValidator::validate_node_type(YAML::Node node, std::string key, YAML::NodeType::value expected_type, bool throw_on_error)
{
   if (node[key].Type() == expected_type) return true;

   // TODO: test these validators
   if (throw_on_error)
   {
      std::string name_of_type = yaml_node_type_as_string(expected_type);
      std::stringstream error_message;
      error_message << "[YAMLValidator::validate_node_type]: error: "
                    << "expecting to find node \"" << key << "\" as a \"" << name_of_type << "\", "
                    << "but it is a \"" << node[key] << "\".";
      throw std::runtime_error(error_message.str());
   }
   return false;
}

bool YAMLValidator::validate_node_has_unsigned_int_value(YAML::Node node, std::string key)
{
   if (!node[key].IsScalar()) return false;

   std::string str = node[key].as<std::string>();

   if (str.empty())
   {
      // An empty string is not a valid numerical string.
      return false;
   }
   else if (str[0] == '0')
   {
      // A numerical string cannot start with 0 unless it is only 0.
      if (str.length() == 1) return true;
      return false;
   }
   for (const char c : str) {
      if (!isdigit(c)) {
        // If any character is not a digit, then the string is not a valid numerical string.
        return false;
      }
   }

   return true;
}

bool YAMLValidator::validate_elements_are_unique(std::vector<std::string> elements)
{
   // TODO: test this function
   std::unordered_set<std::string> unique_set;
   for (const auto& element : elements)
   {
      if (!unique_set.insert(element).second)
      {
          return false;
      }
   }
   return true;
}

std::string YAMLValidator::yaml_node_type_as_string(YAML::NodeType::value node_type)
{
   // TODO: test this function
   switch(node_type)
   {
      case YAML::NodeType::Null: return "Null"; break;
      case YAML::NodeType::Scalar: return "Scalar"; break;
      case YAML::NodeType::Sequence: return "Sequence"; break;
      case YAML::NodeType::Map: return "Map"; break;
      case YAML::NodeType::Undefined: return "Undefined"; break;
      default: {
         std::stringstream error_message;
         error_message << "[YAMLValidator::yaml_node_type_as_string]: error: "
                       << "Unhandled case for type \"" << node_type << "\"";
         throw std::runtime_error(error_message.str());
      } break;
   }
   return "";
}

bool YAMLValidator::validate_unique_all_upper_identifiers(YAML::Node items)
{
   // TODO: add exception messages to areas with return false
   if (!items.IsSequence())
   {
      std::string node_type_as_string = yaml_node_type_as_string(items["items"].Type());
      std::stringstream error_message;
      error_message
        << "Expecting node \"items\" to be a \"Sequence\" but it was a \""
        << node_type_as_string
        << "\".";

        AllegroFlare::Logger::throw_error(
        "YAMLValidator::validate_unique_all_upper_identifiers",
        error_message.str()
      );

      return false;
   }

   // Check that each string in the list meets the requirements
   for (const auto& item : items) {
      if (!item.IsScalar()) {
         return false;
      }

      const std::string& str = item.as<std::string>();
      if (str.empty() || !std::isupper(str[0])) {
         return false;
      }

      for (char c : str) {
         if (!std::isalnum(c) && c != '_') {
           return false;
         }
      }

      if (std::any_of(str.begin() + 1, str.end(), [](char c) { return std::isdigit(c); })) {
         return false;
      }
    }

    // All checks passed
    return true;
}

std::string YAMLValidator::get_type_string(YAML::Node* node_ptr)
{
   if (!(node_ptr))
   {
      std::stringstream error_message;
      error_message << "[YAMLValidator::get_type_string]: error: guard \"node_ptr\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("YAMLValidator::get_type_string: error: guard \"node_ptr\" not met");
   }
   // TODO: Test this function
   YAML::Node &node = (*node_ptr);

   switch (node.Type())
   {
      case YAML::NodeType::Null: return "Null"; break;
      case YAML::NodeType::Scalar: return "Scalar"; break;
      case YAML::NodeType::Sequence: return "Sequence"; break;
      case YAML::NodeType::Map: return "Map"; break;
      case YAML::NodeType::Undefined: return "Undefined"; break;
   }

   std::stringstream error_message;
   error_message << "Unrecognized YAML::NodeType \"" << node.Type() << "\" on node.Type().";

   AllegroFlare::Logger::throw_error(
     "YAMLValidator::get_type_string",
     error_message.str()
   );

   return "[ERROR-get_type_string_result]";
}

std::vector<std::string> YAMLValidator::extract_sequence_as_string_array(YAML::Node source)
{
   // TODO: Test this function
   // TODO: Rename this function
   std::string this_func_name = "extract_sequence_as_string_array";
   std::vector<std::string> result;

   for (YAML::const_iterator it=source.begin(); it!=source.end(); ++it)
   {
      if (!it->IsScalar())
      {
         AllegroFlare::Logger::throw_error(
           "YAMLValidator::extract_sequence_as_string_array",
           "Unexpected sequence element, expected to be of a YAML Scalar."
         );
      }
      result.push_back(it->as<std::string>());
   }

   return result;
}


} // namespace AllegroFlare


