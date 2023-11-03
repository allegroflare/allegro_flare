#pragma once


#include <AllegroFlare/DialogTree/Nodes/Base.hpp>
#include <cstdint>
#include <map>
#include <set>
#include <string>


namespace AllegroFlare
{
   namespace DialogTree
   {
      class NodeBank
      {
      private:
         std::map<std::string, AllegroFlare::DialogTree::Nodes::Base*> nodes;

      protected:


      public:
         NodeBank();
         ~NodeBank();

         void set_nodes(std::map<std::string, AllegroFlare::DialogTree::Nodes::Base*> nodes);
         std::map<std::string, AllegroFlare::DialogTree::Nodes::Base*> &get_nodes_ref();
         uint32_t num_nodes();
         void add_node(std::string name="[unset-name]", AllegroFlare::DialogTree::Nodes::Base* node=nullptr);
         void replace_node(std::string name="[unset-name]", AllegroFlare::DialogTree::Nodes::Base* node=nullptr);
         bool node_exists_by_name(std::string name="[unset-name]");
         AllegroFlare::DialogTree::Nodes::Base* find_node_by_name(std::string name="[unset-name]");
         void delete_all_nodes_and_clear();
         void merge(AllegroFlare::DialogTree::NodeBank* other_node_bank=nullptr);
         std::set<std::string> find_shared_node_names(AllegroFlare::DialogTree::NodeBank* other_node_bank=nullptr);
      };
   }
}



