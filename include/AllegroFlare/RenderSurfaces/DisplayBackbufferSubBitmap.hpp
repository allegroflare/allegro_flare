#pragma once


#include <AllegroFlare/RenderSurfaces/Base.hpp>
#include <allegro5/allegro.h>


namespace AllegroFlare
{
   namespace RenderSurfaces
   {
      class DisplayBackbufferSubBitmap : public AllegroFlare::RenderSurfaces::Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/RenderSurfaces/DisplayBackbufferSubBitmap";

      private:
         ALLEGRO_DISPLAY* display;
         ALLEGRO_BITMAP* display_backbuffer_sub_bitmap;
         bool initialized;

      protected:


      public:
         DisplayBackbufferSubBitmap(ALLEGRO_DISPLAY* display=nullptr);
         virtual ~DisplayBackbufferSubBitmap();

         ALLEGRO_DISPLAY* get_display() const;
         ALLEGRO_BITMAP* get_display_backbuffer_sub_bitmap() const;
         void set_display(ALLEGRO_DISPLAY* display=nullptr);
         void initialize();
         virtual bool set_as_target() override;
      };
   }
}



