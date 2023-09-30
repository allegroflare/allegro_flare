#pragma once


#include <AllegroFlare/DialogTree/NodeBank.hpp>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace DialogTree
   {
      class NodeBankInferencer
      {
      private:
         AllegroFlare::DialogTree::NodeBank* node_bank;

      protected:


      public:
         NodeBankInferencer(AllegroFlare::DialogTree::NodeBank* node_bank=nullptr);
         ~NodeBankInferencer();

         void set_node_bank(AllegroFlare::DialogTree::NodeBank* node_bank);
         AllegroFlare::DialogTree::NodeBank* get_node_bank() const;
         std::vector<std::string> obtain_list_of_speaking_characters();
         static std::vector<std::string> make_unique_and_retain_ordering(std::vector<std::string> list={});
      };
   }
}



