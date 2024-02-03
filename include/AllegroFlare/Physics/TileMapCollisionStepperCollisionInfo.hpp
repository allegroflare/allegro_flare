#pragma once


#include <AllegroFlare/Physics/Int2D.hpp>
#include <AllegroFlare/Physics/TileMapCollisionStepperCollisionInfo.hpp>
#include <string>


namespace AllegroFlare
{
   namespace Physics
   {
      class TileMapCollisionStepperCollisionInfo
      {
      public:
         static constexpr int EVENT_UNDEFINED = 1;
         static constexpr int EVENT_ENTERED = 2;
         static constexpr int EVENT_EXITED = 3;
         static constexpr int EVENT_COLLIDED_AGAINST = 4;
         static constexpr int EVENT_STAYED_ON = 5;

      public:

         enum CollidingBlockEdge
         {
            EDGE_UNDEFINED = 0,
            EDGE_TOP,
            EDGE_RIGHT,
            EDGE_BOTTOM,
            EDGE_LEFT,
         };
      private:
         AllegroFlare::Physics::Int2D collided_tile_coordinate;
         int tile_value;
         float collision_velocity_x;
         float collision_velocity_y;
         bool stopped_by_this_collision;
         int event;
         AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::CollidingBlockEdge collided_against_block_edge;

      protected:


      public:
         TileMapCollisionStepperCollisionInfo(AllegroFlare::Physics::Int2D collided_tile_coordinate={ -1, -1 }, int tile_value=0, float collision_velocity_x=0, float collision_velocity_y=0, bool stopped_by_this_collision=false, int event=EVENT_UNDEFINED, AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::CollidingBlockEdge collided_against_block_edge=CollidingBlockEdge::EDGE_UNDEFINED);
         ~TileMapCollisionStepperCollisionInfo();

         void set_collided_tile_coordinate(AllegroFlare::Physics::Int2D collided_tile_coordinate);
         void set_tile_value(int tile_value);
         void set_collision_velocity_x(float collision_velocity_x);
         void set_collision_velocity_y(float collision_velocity_y);
         void set_stopped_by_this_collision(bool stopped_by_this_collision);
         void set_event(int event);
         void set_collided_against_block_edge(AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::CollidingBlockEdge collided_against_block_edge);
         AllegroFlare::Physics::Int2D get_collided_tile_coordinate() const;
         int get_tile_value() const;
         float get_collision_velocity_x() const;
         float get_collision_velocity_y() const;
         bool get_stopped_by_this_collision() const;
         int get_event() const;
         AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::CollidingBlockEdge get_collided_against_block_edge() const;
         bool is_tile_value(int tile_value=-999);
         bool is_event(int event=EVENT_UNDEFINED);
         bool infer_is_a_ground_land();
         static std::string build_event_name(int event=0);
         bool collided_block_edge_is_left_edge();
         bool collided_block_edge_is_right_edge();
         bool collided_block_edge_is_top_edge();
         bool collided_block_edge_is_bottom_edge();
         static std::string build_collided_block_edge_name(AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::CollidingBlockEdge event=CollidingBlockEdge::EDGE_UNDEFINED);
      };
   }
}



