#pragma once


#include <AllegroFlare/DialogTree/NodeBank.hpp>
#include <functional>
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
         std::function<bool()> unrecognized_node_type_callback_func;

      protected:


      public:
         NodeBankInferencer(AllegroFlare::DialogTree::NodeBank* node_bank=nullptr);
         ~NodeBankInferencer();

         void set_node_bank(AllegroFlare::DialogTree::NodeBank* node_bank);
         void set_unrecognized_node_type_callback_func(std::function<bool()> unrecognized_node_type_callback_func);
         AllegroFlare::DialogTree::NodeBank* get_node_bank() const;
         std::function<bool()> get_unrecognized_node_type_callback_func() const;
         std::vector<std::string> obtain_list_of_speaking_characters();
         static std::vector<std::string> make_unique_and_retain_ordering(std::vector<std::string> list={});
      };
   }
}



