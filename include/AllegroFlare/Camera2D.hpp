#pragma once


#include <AllegroFlare/Placement2D.hpp>
#include <allegro5/allegro.h>


namespace AllegroFlare
{
   class Camera2D : public AllegroFlare::Placement2D
   {
   private:
      float zoom;

   protected:


   public:
      Camera2D();
      ~Camera2D();

      float get_zoom() const;
      void set_zoom(float zoom=1.0f);
      void setup_dimentional_projection(ALLEGRO_BITMAP* bitmap=nullptr);
   };
}



