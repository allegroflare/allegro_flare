#pragma once


#include <AllegroFlare/DialogTree/Node.hpp>
#include <AllegroFlare/DialogTree/NodeBank.hpp>
#include <AllegroFlare/DialogTree/NodeOptions/Base.hpp>
#include <AllegroFlare/DialogTree/NodeOptions/ExitDialog.hpp>
#include <AllegroFlare/DialogTree/NodeOptions/GoToNode.hpp>
#include <AllegroFlare/DialogTree/NodeOptions/Node.hpp>
#include <AllegroFlare/YAMLValidator.hpp>
#include <string>
#include <utility>
#include <yaml-cpp/yaml.h>


namespace AllegroFlare
{
   namespace DialogTree
   {
      class YAMLLoader : public AllegroFlare::YAMLValidator
      {
      public:
         static constexpr char* SPEAKER_KEY = (char*)"speaker";
         static constexpr char* PAGES_KEY = (char*)"pages";
         static constexpr char* OPTIONS_KEY = (char*)"options";
         static constexpr char* TEXT_KEY = (char*)"text";
         static constexpr char* TYPE_KEY = (char*)"type";
         static constexpr char* DATA_KEY = (char*)"data";
         static constexpr char* OPTION_TYPE_NODE_KEY = (char*)"node";
         static constexpr char* OPTION_TYPE_GO_TO_NODE_KEY = (char*)"go_to_node";
         static constexpr char* OPTION_TYPE_EXIT_DIALOG_KEY = (char*)"exit_dialog";
         static constexpr char* OPTION_DATA_TARGET_NODE_NAME_KEY = (char*)"target_node_name";

      private:
         AllegroFlare::DialogTree::NodeBank node_bank;
         bool loaded;

      protected:


      public:
         YAMLLoader();
         ~YAMLLoader();

         void load(std::string yaml_as_string="[unset-yaml_as_string]");
         std::pair<std::string, AllegroFlare::DialogTree::Node*> parse_and_create_node(YAML::Node* node_ptr=nullptr);
         AllegroFlare::DialogTree::NodeOptions::Base* parse_and_create_result_option(std::string type="[unset-type]", YAML::Node* data_node_ptr=nullptr);
         AllegroFlare::DialogTree::NodeOptions::ExitDialog* parse_and_create_ExitDialog_option();
         AllegroFlare::DialogTree::NodeOptions::GoToNode* parse_and_create_GoToNode_option(YAML::Node* data_node_ptr=nullptr);
         AllegroFlare::DialogTree::NodeOptions::Node* parse_and_create_Node_option(YAML::Node* data_node_ptr=nullptr);
      };
   }
}



