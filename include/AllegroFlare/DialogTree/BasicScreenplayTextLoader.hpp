#pragma once


#include <AllegroFlare/DialogTree/NodeBank.hpp>
#include <AllegroFlare/DialogTree/NodeOptions/GoToNode.hpp>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace DialogTree
   {
      class BasicScreenplayTextLoader
      {
      private:
         std::string text;
         AllegroFlare::DialogTree::NodeBank node_bank;
         bool loaded;

      protected:


      public:
         BasicScreenplayTextLoader(std::string text="[unset-text]");
         ~BasicScreenplayTextLoader();

         bool get_loaded() const;
         void set_text(std::string text="[unset-text]");
         AllegroFlare::DialogTree::NodeBank get_node_bank();
         void load_file(std::string filename="[unset-filename]");
         const AllegroFlare::DialogTree::NodeBank& load();
         AllegroFlare::DialogTree::NodeOptions::GoToNode* create_GoToNode_option(std::string node_target_name="[unset-node_target_name]");
         static std::vector<std::string> split(std::string input="[unset-input]", std::string delimiter="__");
      };
   }
}



