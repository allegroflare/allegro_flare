#pragma once


#include <AllegroFlare/Screens/Subscreen/Panes/Inventory.hpp>


namespace AllegroFlare
{
   namespace Screens
   {
      namespace Subscreen
      {
         class PaneFactory
         {
         private:

         protected:


         public:
            PaneFactory();
            ~PaneFactory();

            AllegroFlare::Screens::Subscreen::Panes::Inventory* create_inventory_pane();
         };
      }
   }
}



