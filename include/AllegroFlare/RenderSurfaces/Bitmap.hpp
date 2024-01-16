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
         int surface_width;
         int surface_height;
         int multisamples;
         int depth;
         bool min_linear;
         bool mag_linear;
         bool no_preserve_texture;
         bool initialized;

      public:
         Bitmap(int surface_width=0, int surface_height=0, int multisamples=0, int depth=0);
         ~Bitmap();

         void set_surface_width(int surface_width);
         void set_surface_height(int surface_height);
         void set_multisamples(int multisamples);
         void set_depth(int depth);
         void set_min_linear(bool min_linear);
         void set_mag_linear(bool mag_linear);
         void set_no_preserve_texture(bool no_preserve_texture);

         void initialize();
         void setup_surface(int surface_width, int surface_height, int multisamples=0, int depth=0);
         void setup_surface_with_settings_that_match_display(
            ALLEGRO_DISPLAY* display,
            int surface_width,
            int surface_height
         );
         virtual bool set_as_target() override;
         void restore_previous_target();

         void set_clear_color(ALLEGRO_COLOR clear_color);
         ALLEGRO_COLOR get_clear_color();

         virtual ALLEGRO_BITMAP *obtain_surface() override;
         virtual void clear_surface() override;
         virtual int get_width() override;
         virtual int get_height() override;
      };
   }
}



