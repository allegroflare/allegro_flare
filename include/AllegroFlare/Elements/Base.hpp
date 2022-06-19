#pragma once


#include <AllegroFlare/ElementID.hpp>
#include <AllegroFlare/Placement2D.hpp>


namespace AllegroFlare
{
   namespace Elements
   {
      class Base : public AllegroFlare::ElementID
      {
      private:
         AllegroFlare::Placement2D placement;

      public:
         Base(AllegroFlare::Placement2D placement={});
         ~Base();

         void set_placement(AllegroFlare::Placement2D placement);
         AllegroFlare::Placement2D get_placement();
         void render();
      };
   }
}



