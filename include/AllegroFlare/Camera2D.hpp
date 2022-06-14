#pragma once


#include <AllegroFlare/Placement2D.hpp>


namespace AllegroFlare
{
   class Camera2D : public AllegroFlare::Placement2D
   {
   private:
      float zoom;

   public:
      Camera2D();
      ~Camera2D();

      float get_zoom();
      void set_zoom(float zoom=1.0f);
      void setup_dimentional_projection();
   };
}



