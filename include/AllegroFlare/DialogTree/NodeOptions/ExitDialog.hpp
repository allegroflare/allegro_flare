#pragma once


#include <AllegroFlare/DialogTree/NodeOptions/Base.hpp>


namespace AllegroFlare
{
   namespace DialogTree
   {
      namespace NodeOptions
      {
         class ExitDialog : public AllegroFlare::DialogTree::NodeOptions::Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/DialogTree/NodeOptions/ExitDialog";

         private:

         protected:


         public:
            ExitDialog();
            ~ExitDialog();

         };
      }
   }
}



