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
         Base();
         virtual ~Base();

         void set_placement(AllegroFlare::Placement2D placement);
         AllegroFlare::Placement2D get_placement() const;
         AllegroFlare::Placement2D &get_placement_ref();
         virtual void render();
      };
   }
}



