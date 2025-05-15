#pragma once


#include <AllegroFlare/Camera2D.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <AllegroFlare/Vec2D.hpp>
#include <allegro5/allegro.h>


namespace AllegroFlare
{
   class Camera2D : public AllegroFlare::Placement2D
   {
   public:
      static constexpr int DEFAULT_WIDTH_NUM_UNITS = 1920;
      static constexpr int DEFAULT_HEIGHT_NUM_UNITS = 1080;

   private:
      AllegroFlare::Vec2D zoom;
      int width_num_units;
      int height_num_units;

   protected:


   public:
      Camera2D();
      ~Camera2D();

      void set_width_num_units(int width_num_units);
      void set_height_num_units(int height_num_units);
      AllegroFlare::Vec2D get_zoom() const;
      int get_width_num_units() const;
      int get_height_num_units() const;
      void set_zoom(AllegroFlare::Vec2D zoom=AllegroFlare::Vec2D{1.0f, 1.0f});
      AllegroFlare::Vec2D get_inv_zoom();
      void refresh_zoom_from_scale();
      void setup_dimensional_projection(ALLEGRO_BITMAP* bitmap=nullptr);
      void blend_with_other_camera(AllegroFlare::Camera2D* camera_b=nullptr, float blend_factor=0.0f);
   };
}



