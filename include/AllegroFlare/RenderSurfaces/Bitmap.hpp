#pragma once


#define ALLEGRO_UNSTABLE // for al_get_new_bitmap_samples

#include <AllegroFlare/RenderSurfaces/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace RenderSurfaces
   {
      class Bitmap : public AllegroFlare::RenderSurfaces::Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/RenderSurfaces/Bitmap";

      private:
         ALLEGRO_BITMAP* surface;
         ALLEGRO_COLOR clear_color;
         ALLEGRO_STATE previous_state;
         bool surface_is_setup;

      public:
         Bitmap();
         ~Bitmap();

         void setup_surface(int w, int h, int multisamples=0, int depth=0);
         virtual bool set_as_target() override;
         void restore_previous_target();

         void set_clear_color(ALLEGRO_COLOR clear_color);
         ALLEGRO_COLOR get_clear_color();

         virtual ALLEGRO_BITMAP *obtain_surface() override;
         virtual int get_width() override;
         virtual int get_height() override;
      };
   }
}



