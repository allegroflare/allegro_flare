#pragma once


#include <AllegroFlare/Physics/AABB2D.hpp>
#include <AllegroFlare/Vec2D.hpp>


namespace AllegroFlare
{
   namespace Physics
   {
      class AABB2D
      {
      private:
         float x;
         float y;
         float w;
         float h;
         float velocity_x;
         float velocity_y;

      protected:


      public:
         AABB2D(float x=0.0f, float y=0.0f, float w=0.0f, float h=0.0f, float velocity_x=0.0f, float velocity_y=0.0f);
         ~AABB2D();

         void set_x(float x);
         void set_y(float y);
         void set_w(float w);
         void set_h(float h);
         void set_velocity_x(float velocity_x);
         void set_velocity_y(float velocity_y);
         float get_x() const;
         float get_y() const;
         float get_w() const;
         float get_h() const;
         float get_velocity_x() const;
         float get_velocity_y() const;
         float get_left_edge();
         float get_right_edge();
         float get_top_edge();
         float get_bottom_edge();
         void set_left_edge(float x=0.0f);
         void set_right_edge(float x=0.0f);
         void set_top_edge(float y=0.0f);
         void set_bottom_edge(float y=0.0f);
         bool collides(AllegroFlare::Physics::AABB2D* other=nullptr, AllegroFlare::Vec2D self_offset=AllegroFlare::Vec2D(), AllegroFlare::Vec2D other_offset=AllegroFlare::Vec2D());
         bool collides_with_point(AllegroFlare::Vec2D position={});
      };
   }
}



