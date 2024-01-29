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
         std::vector<AllegroFlare::Physics::Int2D> get_next_collided_tile_coords_1d(float x=0.0f, float y=0.0f, float velocity=0.0f, float depth_of_body=1.0f, float length_of_edge=1.0f, float tile_length_n=1.0f, float tile_length_m=1.0f);
         bool tiles_have_equal_coordinates(AllegroFlare::Physics::Int2D a={0, 0}, AllegroFlare::Physics::Int2D b={0, 0});

      protected:


      public:
         TileMapCollisionStepper(AllegroFlare::TileMaps::TileMap<int>* collision_tile_map=nullptr, AllegroFlare::Physics::AABB2D* aabb2d=nullptr, float tile_width=16.0f, float tile_height=16.0f);
         ~TileMapCollisionStepper();

         void set_collision_tile_map(AllegroFlare::TileMaps::TileMap<int>* collision_tile_map);
         void set_aabb2d(AllegroFlare::Physics::AABB2D* aabb2d);
         void set_tile_width(float tile_width);
         void set_tile_height(float tile_height);
         AllegroFlare::TileMaps::TileMap<int>* get_collision_tile_map() const;
         AllegroFlare::Physics::AABB2D* get_aabb2d() const;
         float get_tile_width() const;
         float get_tile_height() const;
         std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo> step();
         bool adjacent_to_bottom_edge(float tile_width=16.0f, float tile_height=16.0f);
         bool adjacent_to_right_edge(float tile_width=16.0f, float tile_height=16.0f);
         bool adjacent_to_top_edge(float tile_width=16.0f, float tile_height=16.0f);
         std::pair<int, int> get_tile_coords_below_left_foot(float x=0.0f, float y=0.0f, float height=1.0f);
         std::pair<int, int> get_tile_coords_below_right_foot(float x=0.0f, float y=0.0f, float width=1.0f, float height=1.0f);
         bool adjacent_to_left_edge(float tile_width=16.0f, float tile_height=16.0f);
         std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo> get_stepped_tile_collisions(float x=0.0f, float y=0.0f, float velocity_x=0.0f, float velocity_y=0.0f, float width=1.0f, float height=1.0f, float tile_width=1.0f, float tile_height=1.0f);
         std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo> calculate_difference_info(std::vector<AllegroFlare::Physics::Int2D> now_tiles={}, std::vector<AllegroFlare::Physics::Int2D> next_tiles={}, float velocity_x=0.0f, float velocity_y=0.0f);
         std::vector<AllegroFlare::Physics::Int2D> tiles_within_aabb2d(AllegroFlare::Physics::AABB2D aabb2d={});
         std::vector<AllegroFlare::Physics::Int2D> tiles_within(float x=0.0f, float y=0.0f, float width=1.0f, float height=1.0f, float tile_width=1.0f, float tile_height=1.0f);
         static int world_coords_to_tile_coords(float world_pos=0.0f, float tile_length=1.0f);
         int world_x_coords_to_tile_coords_x(float world_pos_x=0.0f);
         int world_y_coords_to_tile_coords_y(float world_pos_y=0.0f);
         float get_tile_left_edge(float tile_x=0.0f, float tile_width=16.0f);
         float get_tile_right_edge(float tile_x=0.0f, float tile_width=16.0f);
         float get_tile_top_edge(float tile_y=0.0f, float tile_height=16.0f);
         float get_tile_bottom_edge(float tile_y=0.0f, float tile_height=16.0f);
      };
   }
}



