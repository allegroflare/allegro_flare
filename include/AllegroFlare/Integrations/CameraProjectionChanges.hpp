#pragma once


#include <AllegroFlare/Frameworks/Full.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/Screen.hpp>


namespace AllegroFlare
{
   namespace Integrations
   {
      class CameraProjectionChanges
      {
      private:
         AllegroFlare::Frameworks::Full framework;
         AllegroFlare::Prototypes::Platforming2D::Screen platforming_2d;

      protected:


      public:
         CameraProjectionChanges();
         ~CameraProjectionChanges();

         void initialize();
         void initialize_tile_drive();
         void initialize_platforming_2d();
      };
   }
}



