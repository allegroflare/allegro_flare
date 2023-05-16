#pragma once


#include <AllegroFlare/DialogTree/Node.hpp>


namespace AllegroFlare
{
   namespace DialogTree
   {
      class Factory
      {
      private:

      protected:


      public:
         Factory();
         ~Factory();

         AllegroFlare::DialogTree::Node* build_test_tree();
      };
   }
}



