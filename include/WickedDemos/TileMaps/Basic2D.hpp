#pragma once


#include <AllegroFlare/TileMaps/Basic2D.hpp>
#include <Wicked/Entities/Basic2D.hpp>


namespace WickedDemos
{
   namespace TileMaps
   {
      class Basic2D : public Wicked::Entities::Basic2D, public AllegroFlare::TileMaps::Basic2D
      {
      private:

      protected:


      public:
         Basic2D();
         ~Basic2D();

      };
   }
}



