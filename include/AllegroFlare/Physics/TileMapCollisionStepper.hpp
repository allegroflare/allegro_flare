#pragma once


#include <AllegroFlare/Physics/AABB2D.hpp>
#include <AllegroFlare/Physics/Int2D.hpp>
#include <AllegroFlare/Physics/TileMapCollisionStepperCollisionInfo.hpp>
#include <AllegroFlare/TileMaps/TileMap.hpp>
#include <utility>
#include <vector>


namespace AllegroFlare
{
   namespace Physics
   {
      class TileMapCollisionStepper
      {
      private:
         AllegroFlare::TileMaps::TileMap<int>* collision_tile_map;
         AllegroFlare::Physics::AABB2D* aabb2d;
         float tile_width;
         float tile_height;
         std::vector<AllegroFlare::Physics::Int2D> get_next_collided_tile_coords(float x=0.0f, float y=0.0f, float velocity=0.0f, float depth_of_body=1.0f, float length_of_edge=1.0f, float tile_length_n=1.0f, float tile_length_m=1.0f);
         int world_coords_to_tile_coords(float world_pos=0.0f, float tile_length=1.0f);
         int world_x_coords_to_tile_coords_x(float world_pos_x=0.0f);
         int world_y_coords_to_tile_coords_y(float world_pos_y=0.0f);

      protected:


      public:
         TileMapCollisionStepper(AllegroFlare::TileMaps::TileMap<int>* collision_tile_map=nullptr, AllegroFlare::Physics::AABB2D* aabb2d=nullptr, float tile_width=16.0f, float tile_height=16.0f);
         ~TileMapCollisionStepper();

         std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo> step();
         bool adjacent_to_bottom_edge(float tile_width=16.0f, float tile_height=16.0f);
         bool adjacent_to_right_edge(float tile_width=16.0f, float tile_height=16.0f);
         bool adjacent_to_top_edge(float tile_width=16.0f, float tile_height=16.0f);
         std::pair<int, int> get_tile_coords_below_left_foot(float x=0.0f, float y=0.0f, float height=1.0f);
         std::pair<int, int> get_tile_coords_below_right_foot(float x=0.0f, float y=0.0f, float width=1.0f, float height=1.0f);
         bool adjacent_to_left_edge(float tile_width=16.0f, float tile_height=16.0f);
         float get_tile_left_edge(float tile_x=0.0f, float tile_width=16.0f);
         float get_tile_right_edge(float tile_x=0.0f, float tile_width=16.0f);
         float get_tile_top_edge(float tile_y=0.0f, float tile_height=16.0f);
         float get_tile_bottom_edge(float tile_y=0.0f, float tile_height=16.0f);
      };
   }
}



