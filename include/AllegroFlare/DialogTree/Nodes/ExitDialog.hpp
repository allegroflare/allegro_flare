#pragma once


#include <AllegroFlare/DialogTree/Nodes/Base.hpp>


namespace AllegroFlare
{
   namespace DialogTree
   {
      namespace Nodes
      {
         class ExitDialog : public AllegroFlare::DialogTree::Nodes::Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/DialogTree/Nodes/ExitDialog";

         private:

         protected:


         public:
            ExitDialog();
            ~ExitDialog();

         };
      }
   }
}



