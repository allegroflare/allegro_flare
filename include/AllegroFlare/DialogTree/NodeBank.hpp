#pragma once


#include <AllegroFlare/DialogTree/Node.hpp>
#include <cstdint>
#include <map>
#include <string>


namespace AllegroFlare
{
   namespace DialogTree
   {
      class NodeBank
      {
      private:
         std::map<std::string, AllegroFlare::DialogTree::Node*> nodes;

      protected:


      public:
         NodeBank();
         ~NodeBank();

         void set_nodes(std::map<std::string, AllegroFlare::DialogTree::Node*> nodes);
         uint32_t num_nodes();
         void add_node(std::string name="[unset-name]", AllegroFlare::DialogTree::Node* node=nullptr);
         bool node_exists_by_name(std::string name="[unset-name]");
         AllegroFlare::DialogTree::Node* find_node_by_name(std::string name="[unset-name]");
      };
   }
}



