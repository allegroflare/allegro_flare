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
      class UnitTileMapCollisionStepper
      {
      public:
         static constexpr float DEFAULT_REPOSITION_OFFSET = 0.00097656;

      private:
         AllegroFlare::TileMaps::TileMap<int>* collision_tile_map;
         float reposition_offset;
         std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo> step_internal(AllegroFlare::Physics::AABB2D* aabb2d=nullptr);
         bool tiles_have_equal_coordinates(AllegroFlare::Physics::Int2D a={0, 0}, AllegroFlare::Physics::Int2D b={0, 0});

      protected:


      public:
         UnitTileMapCollisionStepper(AllegroFlare::TileMaps::TileMap<int>* collision_tile_map=nullptr, float reposition_offset=DEFAULT_REPOSITION_OFFSET);
         ~UnitTileMapCollisionStepper();

         void set_collision_tile_map(AllegroFlare::TileMaps::TileMap<int>* collision_tile_map);
         void set_reposition_offset(float reposition_offset);
         AllegroFlare::TileMaps::TileMap<int>* get_collision_tile_map() const;
         float get_reposition_offset() const;
         std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo> step(AllegroFlare::Physics::AABB2D* aabb2d=nullptr);
         std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo> step_with_world_transform(AllegroFlare::Physics::AABB2D* aabb2d=nullptr, float map_x=0.0f, float map_y=0.0f, float tile_width=16.0f, float tile_height=16.0f);
         bool adjacent_to_bottom_edge(AllegroFlare::Physics::AABB2D* aabb2d=nullptr);
         bool adjacent_to_right_edge(AllegroFlare::Physics::AABB2D* aabb2d=nullptr);
         bool adjacent_to_top_edge(AllegroFlare::Physics::AABB2D* aabb2d=nullptr);
         bool adjacent_to_left_edge(AllegroFlare::Physics::AABB2D* aabb2d=nullptr);
         std::pair<int, int> get_tile_coords_below_left_foot(float x=0.0f, float y=0.0f, float height=1.0f);
         std::pair<int, int> get_tile_coords_below_right_foot(float x=0.0f, float y=0.0f, float width=1.0f, float height=1.0f);
         static std::vector<AllegroFlare::Physics::Int2D> get_next_collided_tile_coords_1d(float x=0.0f, float y=0.0f, float velocity=0.0f, float depth_of_body=1.0f, float length_of_edge=1.0f);
         std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo> get_stepped_tile_collisions(float x=0.0f, float y=0.0f, float velocity_x=0.0f, float velocity_y=0.0f, float width=1.0f, float height=1.0f);
         std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo> calculate_difference_info(std::vector<AllegroFlare::Physics::Int2D> now_tiles={}, std::vector<AllegroFlare::Physics::Int2D> next_tiles={}, float velocity_x=0.0f, float velocity_y=0.0f);
         static std::vector<AllegroFlare::Physics::Int2D> tiles_within_aabb2d(AllegroFlare::Physics::AABB2D* aabb2d=nullptr);
         static std::vector<AllegroFlare::Physics::Int2D> tiles_within(float x=0.0f, float y=0.0f, float width=1.0f, float height=1.0f);
         static int unit_space_to_tile_coord(float unit_pos=0.0f);
         float get_tile_left_edge(float tile_x=0.0f);
         float get_tile_right_edge(float tile_x=0.0f);
         float get_tile_top_edge(float tile_y=0.0f);
         float get_tile_bottom_edge(float tile_y=0.0f);
         int get_tile_or_fallback(int tile_x=0, int tile_y=0, int fallback=0);
      };
   }
}



