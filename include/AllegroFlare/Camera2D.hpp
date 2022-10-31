#pragma once


#include <AllegroFlare/Placement2D.hpp>
#include <AllegroFlare/Vec2D.hpp>
#include <allegro5/allegro.h>


namespace AllegroFlare
{
   class Camera2D : public AllegroFlare::Placement2D
   {
   private:
      AllegroFlare::Vec2D zoom;

   protected:


   public:
      Camera2D();
      ~Camera2D();

      AllegroFlare::Vec2D get_zoom() const;
      void set_zoom(AllegroFlare::Vec2D zoom={1.0f, 1.0f});
      AllegroFlare::Vec2D get_inv_zoom();
      void setup_dimentional_projection(ALLEGRO_BITMAP* bitmap=nullptr);
   };
}



