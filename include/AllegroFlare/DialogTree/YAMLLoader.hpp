#pragma once


#include <AllegroFlare/DialogTree/NodeBank.hpp>
#include <AllegroFlare/DialogTree/NodeOptions/Base.hpp>
#include <AllegroFlare/DialogTree/NodeOptions/ExitDialog.hpp>
#include <AllegroFlare/DialogTree/NodeOptions/GoToNode.hpp>
#include <AllegroFlare/DialogTree/Nodes/MultipageWithOptions.hpp>
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
         static constexpr char* NAME_KEY = (char*)"name";
         static constexpr char* SPEAKER_KEY = (char*)"speaker";
         static constexpr char* PAGES_KEY = (char*)"pages";
         static constexpr char* OPTIONS_KEY = (char*)"options";
         static constexpr char* TEXT_KEY = (char*)"text";
         static constexpr char* TYPE_KEY = (char*)"type";
         static constexpr char* DATA_KEY = (char*)"data";
         static constexpr char* OPTION_TYPE_GO_TO_NODE_KEY = (char*)"go_to_node";
         static constexpr char* OPTION_TYPE_EXIT_DIALOG_KEY = (char*)"exit_dialog";
         static constexpr char* OPTION_DATA_TARGET_NODE_NAME_KEY = (char*)"target_node_name";
         static constexpr char* MULTIPAGE_WITH_OPTIONS_KEY = (char*)"multipage_with_options";

      private:
         AllegroFlare::DialogTree::NodeBank node_bank;
         bool loaded;

      protected:


      public:
         YAMLLoader();
         ~YAMLLoader();

         bool get_loaded() const;
         AllegroFlare::DialogTree::NodeBank get_node_bank();
         void load_file(std::string filename="[unset-filename]");
         void load(std::string yaml_as_string="[unset-yaml_as_string]");
         std::pair<std::string, AllegroFlare::DialogTree::Nodes::MultipageWithOptions*> parse_and_create_MultipageWithOptions_node(YAML::Node* node_ptr=nullptr);
         AllegroFlare::DialogTree::NodeOptions::Base* parse_and_create_result_option(std::string type="[unset-type]", YAML::Node* data_node_ptr=nullptr);
         AllegroFlare::DialogTree::NodeOptions::ExitDialog* parse_and_create_ExitDialog_option();
         AllegroFlare::DialogTree::NodeOptions::GoToNode* parse_and_create_GoToNode_option(YAML::Node* data_node_ptr=nullptr);
      };
   }
}



