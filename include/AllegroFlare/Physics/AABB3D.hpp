#pragma once


#include <AllegroFlare/Physics/AABB3D.hpp>
#include <AllegroFlare/Vec3D.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <vector>


namespace AllegroFlare
{
   namespace Physics
   {
      class AABB3D
      {
      private:
         AllegroFlare::Vec3D min;
         AllegroFlare::Vec3D max;

      protected:


      public:
         std::vector<AllegroFlare::Vec3D> box_corners;
         ALLEGRO_COLOR box_color;
         AABB3D(AllegroFlare::Vec3D min=AllegroFlare::Vec3D(), AllegroFlare::Vec3D max=AllegroFlare::Vec3D());
         ~AABB3D();

         void set_min(AllegroFlare::Vec3D min);
         void set_max(AllegroFlare::Vec3D max);
         AllegroFlare::Vec3D get_min() const;
         AllegroFlare::Vec3D get_max() const;
         void expand(float amount=0.0f);
         bool collides(AllegroFlare::Physics::AABB3D* other=nullptr, AllegroFlare::Vec3D self_offset=AllegroFlare::Vec3D(), AllegroFlare::Vec3D other_offset=AllegroFlare::Vec3D());
         bool collides_with_point(AllegroFlare::Vec3D point=AllegroFlare::Vec3D(), AllegroFlare::Vec3D self_offset=AllegroFlare::Vec3D(), AllegroFlare::Vec3D other_offset=AllegroFlare::Vec3D());
         void draw(ALLEGRO_COLOR color=ALLEGRO_COLOR{1.0f, 1.0f, 0.0f, 1.0f}, AllegroFlare::Vec3D offset=AllegroFlare::Vec3D());
         void calculate_box_corners();
         ALLEGRO_COLOR build_color(float opacity=1.0f);
         std::vector<ALLEGRO_VERTEX> build_line_list_vertices();
         std::vector<ALLEGRO_VERTEX> build_triangle_list_vertices_for_faces();
      };
   }
}



