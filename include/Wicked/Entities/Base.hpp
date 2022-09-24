#pragma once


#include <AllegroFlare/ElementID.hpp>


namespace Wicked
{
   namespace Entities
   {
      class Base : public AllegroFlare::ElementID
      {
      private:
         AllegroFlare::ElementID* parent;

      protected:


      public:
         Base(AllegroFlare::ElementID* parent=nullptr);
         virtual ~Base();

         virtual void update();
         virtual void draw();
      };
   }
}



