#pragma once


#include <AllegroFlare/Frameworks/Full.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/Screen.hpp>
#include <AllegroFlare/Prototypes/TileDrive/Screen.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <allegro5/allegro.h>


namespace AllegroFlare
{
   namespace Integrations
   {
      class CameraProjectionChanges : public AllegroFlare::Screens::Base
      {
      private:
         AllegroFlare::Frameworks::Full framework;
         AllegroFlare::Prototypes::Platforming2D::Screen platforming_2d_screen;
         AllegroFlare::Prototypes::TileDrive::Screen tile_drive_screen;
         bool initialized;

      protected:


      public:
         CameraProjectionChanges();
         ~CameraProjectionChanges();

         static void callback(ALLEGRO_EVENT* event=nullptr, void* user_data=nullptr);
         void initialize();
         void run();
         void initialize_tile_drive();
         void initialize_platforming_2d();
      };
   }
}



