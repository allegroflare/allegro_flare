#pragma once


#include <AllegroFlare/DialogTree/Node.hpp>
#include <AllegroFlare/DialogTree/NodeOptions/Base.hpp>
#include <AllegroFlare/YAMLValidator.hpp>
#include <string>
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
         static constexpr char* OPTION_TYPE_GO_TO_NODE_KEY = (char*)"go_to_node";
         static constexpr char* OPTION_TYPE_EXIT_DIALOG_KEY = (char*)"exit_dialog";

      private:

      protected:


      public:
         YAMLLoader();
         ~YAMLLoader();

         AllegroFlare::DialogTree::Node* load(std::string yaml_as_string="");
         AllegroFlare::DialogTree::NodeOptions::Base* parse_and_create_result_option(std::string type="[unset-type]", YAML::Node* data_node_ptr=nullptr);
      };
   }
}



