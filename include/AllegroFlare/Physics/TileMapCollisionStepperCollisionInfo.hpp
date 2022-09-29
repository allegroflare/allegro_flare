#pragma once


#include <AllegroFlare/Physics/Int2D.hpp>


namespace AllegroFlare
{
   namespace Physics
   {
      class TileMapCollisionStepperCollisionInfo
      {
      private:
         AllegroFlare::Physics::Int2D collided_tile_coordinate;
         int tile_value;
         float collision_velocity_x;
         float collision_velocity_y;
         bool stopped_by_this_collision;

      protected:


      public:
         TileMapCollisionStepperCollisionInfo(AllegroFlare::Physics::Int2D collided_tile_coordinate={ -1, -1 }, int tile_value=0, float collision_velocity_x=0, float collision_velocity_y=0, bool stopped_by_this_collision=false);
         ~TileMapCollisionStepperCollisionInfo();

         void set_collided_tile_coordinate(AllegroFlare::Physics::Int2D collided_tile_coordinate);
         void set_tile_value(int tile_value);
         void set_collision_velocity_x(float collision_velocity_x);
         void set_collision_velocity_y(float collision_velocity_y);
         void set_stopped_by_this_collision(bool stopped_by_this_collision);
         AllegroFlare::Physics::Int2D get_collided_tile_coordinate() const;
         int get_tile_value() const;
         float get_collision_velocity_x() const;
         float get_collision_velocity_y() const;
         bool get_stopped_by_this_collision() const;
      };
   }
}



