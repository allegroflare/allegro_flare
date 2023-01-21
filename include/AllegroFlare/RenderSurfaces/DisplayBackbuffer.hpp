#pragma once


#include <AllegroFlare/RenderSurfaces/Base.hpp>
#include <allegro5/allegro.h>


namespace AllegroFlare
{
   namespace RenderSurfaces
   {
      class DisplayBackbuffer : public AllegroFlare::RenderSurfaces::Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/RenderSurfaces/DisplayBackbuffer";

      private:
         ALLEGRO_DISPLAY* display;
         ALLEGRO_BITMAP* display_backbuffer;
         bool initialized;

      protected:


      public:
         DisplayBackbuffer(ALLEGRO_DISPLAY* display=nullptr);
         virtual ~DisplayBackbuffer();

         ALLEGRO_DISPLAY* get_display() const;
         ALLEGRO_BITMAP* get_display_backbuffer() const;
         void set_display(ALLEGRO_DISPLAY* display=nullptr);
         void initialize();
         virtual bool set_as_target() override;
      };
   }
}



