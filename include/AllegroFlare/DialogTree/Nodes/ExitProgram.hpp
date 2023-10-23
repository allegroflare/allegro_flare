#pragma once


#include <AllegroFlare/DialogTree/Nodes/Base.hpp>


namespace AllegroFlare
{
   namespace DialogTree
   {
      namespace Nodes
      {
         class ExitProgram : public AllegroFlare::DialogTree::Nodes::Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/DialogTree/Nodes/ExitProgram";

         private:

         protected:


         public:
            ExitProgram();
            ~ExitProgram();

         };
      }
   }
}



