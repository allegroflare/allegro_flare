#pragma once


#include <AllegroFlare/DialogTree/NodeBank.hpp>


namespace AllegroFlare
{
   namespace DialogTree
   {
      class NodeBankFactory
      {
      private:

      protected:


      public:
         NodeBankFactory();
         ~NodeBankFactory();

         static AllegroFlare::DialogTree::NodeBank build_common_system_dialogs_node_bank();
      };
   }
}



