

#include <AllegroFlare/Physics/UnitTileMapCollisionStepper.hpp>

#include <AllegroFlare/Physics/AABB2D.hpp>
#include <AllegroFlare/Physics/TileMapCollisionStepperCollisionInfo.hpp>
#include <cmath>
#include <iostream>
#include <set>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Physics
{


UnitTileMapCollisionStepper::UnitTileMapCollisionStepper(AllegroFlare::TileMaps::TileMap<int>* collision_tile_map, float reposition_offset)
   : collision_tile_map(collision_tile_map)
   , reposition_offset(reposition_offset)
{
}


UnitTileMapCollisionStepper::~UnitTileMapCollisionStepper()
{
}


void UnitTileMapCollisionStepper::set_collision_tile_map(AllegroFlare::TileMaps::TileMap<int>* collision_tile_map)
{
   this->collision_tile_map = collision_tile_map;
}


void UnitTileMapCollisionStepper::set_reposition_offset(float reposition_offset)
{
   this->reposition_offset = reposition_offset;
}


AllegroFlare::TileMaps::TileMap<int>* UnitTileMapCollisionStepper::get_collision_tile_map() const
{
   return collision_tile_map;
}


float UnitTileMapCollisionStepper::get_reposition_offset() const
{
   return reposition_offset;
}


std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo> UnitTileMapCollisionStepper::step(AllegroFlare::Physics::AABB2D* aabb2d)
{
   if (!(collision_tile_map))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Physics::UnitTileMapCollisionStepper::step]: error: guard \"collision_tile_map\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Physics::UnitTileMapCollisionStepper::step]: error: guard \"collision_tile_map\" not met");
   }
   if (!(aabb2d))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Physics::UnitTileMapCollisionStepper::step]: error: guard \"aabb2d\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Physics::UnitTileMapCollisionStepper::step]: error: guard \"aabb2d\" not met");
   }
   return step_internal(aabb2d);
}

std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo> UnitTileMapCollisionStepper::step_with_world_transform(AllegroFlare::Physics::AABB2D* aabb2d, float map_x, float map_y, float tile_width, float tile_height)
{
   if (!(collision_tile_map))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Physics::UnitTileMapCollisionStepper::step_with_world_transform]: error: guard \"collision_tile_map\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Physics::UnitTileMapCollisionStepper::step_with_world_transform]: error: guard \"collision_tile_map\" not met");
   }
   if (!(aabb2d))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Physics::UnitTileMapCollisionStepper::step_with_world_transform]: error: guard \"aabb2d\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Physics::UnitTileMapCollisionStepper::step_with_world_transform]: error: guard \"aabb2d\" not met");
   }
   if (!((tile_width > 0.0f)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Physics::UnitTileMapCollisionStepper::step_with_world_transform]: error: guard \"(tile_width > 0.0f)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Physics::UnitTileMapCollisionStepper::step_with_world_transform]: error: guard \"(tile_width > 0.0f)\" not met");
   }
   if (!((tile_height > 0.0f)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Physics::UnitTileMapCollisionStepper::step_with_world_transform]: error: guard \"(tile_height > 0.0f)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Physics::UnitTileMapCollisionStepper::step_with_world_transform]: error: guard \"(tile_height > 0.0f)\" not met");
   }
   // 1. Transform Down:
   // A) First, find the AABB's position relative to the map's origin (in pixels).
   float aabb_local_x = aabb2d->get_x() - map_x;
   float aabb_local_y = aabb2d->get_y() - map_y;

   // B) Now, scale the local pixel coordinates and dimensions down to unit space.
   AllegroFlare::Physics::AABB2D unit_aabb(
     aabb_local_x / tile_width,
     aabb_local_y / tile_height,
     aabb2d->get_w() / tile_width,
     aabb2d->get_h() / tile_height,
     aabb2d->get_velocity_x() / tile_width,
     aabb2d->get_velocity_y() / tile_height
   );

   // 2. Call the core unit-space step() function.
   std::vector<TileMapCollisionStepperCollisionInfo> result_infos = step_internal(&unit_aabb);

   // 3. Transform Up:
   // A) Scale the final unit-space position up to local pixel coordinates.
   float final_local_x = unit_aabb.get_x() * tile_width;
   float final_local_y = unit_aabb.get_y() * tile_height;

   // B) Translate the local pixel coordinates by the map's position to get the final world coordinates.
   aabb2d->set_x(final_local_x + map_x);
   aabb2d->set_y(final_local_y + map_y);
   aabb2d->set_velocity_x(unit_aabb.get_velocity_x() * tile_width);
   aabb2d->set_velocity_y(unit_aabb.get_velocity_y() * tile_height);

   // 4. Transform the velocities in the collision info back to world space.
   for (auto &info : result_infos)
   {
     info.set_collision_velocity_x(info.get_collision_velocity_x() * tile_width);
     info.set_collision_velocity_y(info.get_collision_velocity_y() * tile_height);
   }

   // 5. Return the collision info.
   return result_infos;
}

std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo> UnitTileMapCollisionStepper::step_internal(AllegroFlare::Physics::AABB2D* aabb2d)
{
   if (!(collision_tile_map))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Physics::UnitTileMapCollisionStepper::step_internal]: error: guard \"collision_tile_map\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Physics::UnitTileMapCollisionStepper::step_internal]: error: guard \"collision_tile_map\" not met");
   }
   if (!(aabb2d))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Physics::UnitTileMapCollisionStepper::step_internal]: error: guard \"aabb2d\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Physics::UnitTileMapCollisionStepper::step_internal]: error: guard \"aabb2d\" not met");
   }
   //this->aabb2d = aabb2d;

   std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo> result_infos;
   AllegroFlare::Physics::AABB2D &obj = *aabb2d;
   AllegroFlare::TileMaps::TileMap<int> &map = *collision_tile_map;

   // collect the position before any alterations
   AllegroFlare::Physics::AABB2D obj_before = obj;

   // test horizontal first
   std::vector<AllegroFlare::Physics::Int2D> horizontal_collided_blocks = get_next_collided_tile_coords_1d(
         obj.get_x(), obj.get_y(), obj.get_velocity_x(), obj.get_w(), obj.get_h()
   );

   // react to the collision here:
   if (!horizontal_collided_blocks.empty())
   {
      for (AllegroFlare::Physics::Int2D &t : horizontal_collided_blocks)
      {
         //int tile_value = map.get_tile(t.get_x(), t.get_y());
         int tile_value = get_tile_or_fallback(t.get_x(), t.get_y(), 0);

         if (tile_value == 1) // tile is solid
         {
            if (obj.get_velocity_x() > 0) // Moving to the right
            {
               result_infos.push_back(
                  AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo(
                     AllegroFlare::Physics::Int2D(t.get_x(), t.get_y()),
                     tile_value,
                     obj.get_velocity_x(),
                     obj.get_velocity_y(),
                     true,
                     AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::EVENT_COLLIDED_AGAINST,
                     AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::CollidingBlockEdge::EDGE_LEFT
                  )
               );

               obj.set_right_edge(get_tile_left_edge(t.get_x()) - reposition_offset); //0.0001);
               obj.set_velocity_x(0.0);
            }
            else if (obj.get_velocity_x() < 0) // Moving to the left
            {
               result_infos.push_back(
                  AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo(
                     AllegroFlare::Physics::Int2D(t.get_x(), t.get_y()),
                     tile_value,
                     obj.get_velocity_x(),
                     obj.get_velocity_y(),
                     true,
                     AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::EVENT_COLLIDED_AGAINST,
                     AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::CollidingBlockEdge::EDGE_RIGHT
                  )
               );

               obj.set_left_edge(get_tile_right_edge(t.get_x()) + reposition_offset); //0.0001);
               obj.set_velocity_x(0.0);
            }
         }
         else // tile is not solid (aka, "1")
         {
            // do nothing (this result is handled later in the function)
         }
      }
   }

   obj.set_x(obj.get_x() + obj.get_velocity_x());

   // test vertical second
   std::vector<AllegroFlare::Physics::Int2D> vertical_collided_blocks = get_next_collided_tile_coords_1d(
      obj.get_y(), obj.get_x(), obj.get_velocity_y(), obj.get_h(), obj.get_w()
   );

   for(AllegroFlare::Physics::Int2D &tile_coord : vertical_collided_blocks) tile_coord.rotate();
   if (!vertical_collided_blocks.empty())
   {
      for (AllegroFlare::Physics::Int2D &t : vertical_collided_blocks)
      {
         int tile_value = map.get_tile_or_fallback(t.get_x(), t.get_y(), 0);

         if (tile_value == 1) // tile is solid
         {
            if (obj.get_velocity_y() > 0) // Moving down
            {
               result_infos.push_back(
                  AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo(
                     AllegroFlare::Physics::Int2D(t.get_x(), t.get_y()),
                     tile_value,
                     obj.get_velocity_x(),
                     obj.get_velocity_y(),
                     true,
                     AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::EVENT_COLLIDED_AGAINST,
                     AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::CollidingBlockEdge::EDGE_TOP
                  )
               );

               obj.set_bottom_edge(get_tile_top_edge(t.get_y()) - reposition_offset); //0.0001);
               obj.set_velocity_y(0.0);
            }
            else if (obj.get_velocity_y() < 0) // Moving up
            {
               result_infos.push_back(
                  AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo(
                     AllegroFlare::Physics::Int2D(t.get_x(), t.get_y()),
                     tile_value,
                     obj.get_velocity_x(),
                     obj.get_velocity_y(),
                     true,
                     AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::EVENT_COLLIDED_AGAINST,
                     AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::CollidingBlockEdge::EDGE_BOTTOM
                  )
               );

               obj.set_top_edge(get_tile_bottom_edge(t.get_y()) + reposition_offset); //0.0001);
               obj.set_velocity_y(0.0);
            }
         }
         else // tile is not solid (aka, "1")
         {
            // do nothing (this result is handled later in the function)
         }
      }
   }
   obj.set_y(obj.get_y() + obj.get_velocity_y());


   AllegroFlare::Physics::AABB2D obj_after = obj;

   // collect the "now_tiles" and "next_tiles" and calculate the difference information
   std::vector<AllegroFlare::Physics::Int2D> now_tiles = tiles_within_aabb2d(&obj_before);
   std::vector<AllegroFlare::Physics::Int2D> next_tiles = tiles_within_aabb2d(&obj_after);
   std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo> difference_infos =
      calculate_difference_info(now_tiles, next_tiles, obj_before.get_velocity_x(), obj_before.get_velocity_y());

   // append the difference_infos to the result
   result_infos.insert(result_infos.end(), difference_infos.begin(), difference_infos.end());

   return result_infos;
}

bool UnitTileMapCollisionStepper::adjacent_to_bottom_edge(AllegroFlare::Physics::AABB2D* aabb2d)
{
   if (!(collision_tile_map))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Physics::UnitTileMapCollisionStepper::adjacent_to_bottom_edge]: error: guard \"collision_tile_map\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Physics::UnitTileMapCollisionStepper::adjacent_to_bottom_edge]: error: guard \"collision_tile_map\" not met");
   }
   if (!(aabb2d))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Physics::UnitTileMapCollisionStepper::adjacent_to_bottom_edge]: error: guard \"aabb2d\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Physics::UnitTileMapCollisionStepper::adjacent_to_bottom_edge]: error: guard \"aabb2d\" not met");
   }
   AllegroFlare::Physics::AABB2D &obj = *aabb2d;

   std::vector<AllegroFlare::Physics::Int2D> tiles = get_next_collided_tile_coords_1d(
      obj.get_y(),
      obj.get_x(),
      reposition_offset*2,
      obj.get_h(),
      obj.get_w()
   );
   if (tiles.empty()) return false;

   for (auto &t : tiles)
   {
      t.rotate();
      //if (collision_tile_map->get_tile(t.get_x(), t.get_y()) == 1) return true;
      if (get_tile_or_fallback(t.get_x(), t.get_y(), 0) == 1) return true;
   }
   return false;
}

bool UnitTileMapCollisionStepper::adjacent_to_right_edge(AllegroFlare::Physics::AABB2D* aabb2d)
{
   if (!(collision_tile_map))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Physics::UnitTileMapCollisionStepper::adjacent_to_right_edge]: error: guard \"collision_tile_map\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Physics::UnitTileMapCollisionStepper::adjacent_to_right_edge]: error: guard \"collision_tile_map\" not met");
   }
   if (!(aabb2d))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Physics::UnitTileMapCollisionStepper::adjacent_to_right_edge]: error: guard \"aabb2d\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Physics::UnitTileMapCollisionStepper::adjacent_to_right_edge]: error: guard \"aabb2d\" not met");
   }
   AllegroFlare::Physics::AABB2D &obj = *aabb2d;

   std::vector<AllegroFlare::Physics::Int2D> tiles = get_next_collided_tile_coords_1d(
      obj.get_x(),
      obj.get_y(),
      reposition_offset * 2,
      obj.get_w(),
      obj.get_h()
   );
   if (tiles.empty()) return false;

   for (auto &t : tiles)
   {
      //t.rotate();
      //if (collision_tile_map->get_tile(t.get_x(), t.get_y()) == 1) return true;
      if (get_tile_or_fallback(t.get_x(), t.get_y(), 0) == 1) return true;
   }
   return false;
}

bool UnitTileMapCollisionStepper::adjacent_to_top_edge(AllegroFlare::Physics::AABB2D* aabb2d)
{
   if (!(collision_tile_map))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Physics::UnitTileMapCollisionStepper::adjacent_to_top_edge]: error: guard \"collision_tile_map\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Physics::UnitTileMapCollisionStepper::adjacent_to_top_edge]: error: guard \"collision_tile_map\" not met");
   }
   if (!(aabb2d))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Physics::UnitTileMapCollisionStepper::adjacent_to_top_edge]: error: guard \"aabb2d\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Physics::UnitTileMapCollisionStepper::adjacent_to_top_edge]: error: guard \"aabb2d\" not met");
   }
   AllegroFlare::Physics::AABB2D &obj = *aabb2d;

   std::vector<AllegroFlare::Physics::Int2D> tiles = get_next_collided_tile_coords_1d(
      obj.get_y(),
      obj.get_x(),
      -reposition_offset * 2,
      obj.get_h(),
      obj.get_w()
   );
   if (tiles.empty()) return false;

   for (auto &t : tiles)
   {
      t.rotate();
      //if (collision_tile_map->get_tile(t.get_x(), t.get_y()) == 1) return true;
      if (get_tile_or_fallback(t.get_x(), t.get_y(), 0) == 1) return true;
   }
   return false;
}

bool UnitTileMapCollisionStepper::adjacent_to_left_edge(AllegroFlare::Physics::AABB2D* aabb2d)
{
   if (!(collision_tile_map))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Physics::UnitTileMapCollisionStepper::adjacent_to_left_edge]: error: guard \"collision_tile_map\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Physics::UnitTileMapCollisionStepper::adjacent_to_left_edge]: error: guard \"collision_tile_map\" not met");
   }
   if (!(aabb2d))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Physics::UnitTileMapCollisionStepper::adjacent_to_left_edge]: error: guard \"aabb2d\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Physics::UnitTileMapCollisionStepper::adjacent_to_left_edge]: error: guard \"aabb2d\" not met");
   }
   AllegroFlare::Physics::AABB2D &obj = *aabb2d;

   std::vector<AllegroFlare::Physics::Int2D> tiles = get_next_collided_tile_coords_1d(
      obj.get_x(),
      obj.get_y(),
      -reposition_offset*2,
      obj.get_w(),
      obj.get_h()
   );
   if (tiles.empty()) return false;

   for (auto &t : tiles)
   {
      //t.rotate();
      //if (collision_tile_map->get_tile(t.get_x(), t.get_y()) == 1) return true;
      if (get_tile_or_fallback(t.get_x(), t.get_y(), 0) == 1) return true;
   }
   return false;
}

std::pair<int, int> UnitTileMapCollisionStepper::get_tile_coords_below_left_foot(float x, float y, float height)
{
   std::pair<int, int> result{
      unit_space_to_tile_coord(x),
      unit_space_to_tile_coord(y + height + reposition_offset*2) // 0.0001f)
   };
   return result;
}

std::pair<int, int> UnitTileMapCollisionStepper::get_tile_coords_below_right_foot(float x, float y, float width, float height)
{
   std::pair<int, int> result{
      unit_space_to_tile_coord(x + width),
      unit_space_to_tile_coord(y + height + reposition_offset*2) // 0.0001f)
   };
   return result;
}

std::vector<AllegroFlare::Physics::Int2D> UnitTileMapCollisionStepper::get_next_collided_tile_coords_1d(float x, float y, float velocity, float depth_of_body, float length_of_edge)
{
   std::vector<AllegroFlare::Physics::Int2D> collided_tiles;

   if (velocity > 0) x += depth_of_body;

   int now = unit_space_to_tile_coord(x); //TileMap::world_to_tile(x);
   int next = unit_space_to_tile_coord(x + velocity); //TileMap::world_to_tile(x + velocity);

   if (now != next)
   {
      // new tiles have been entered
      int start_y = unit_space_to_tile_coord(y); //TileMap::world_to_tile(y);
      float inset_y = std::fmod(std::fmod(y, 1.0) + 1.0, 1.0); // handles negative y
      int num_tiles_along_edge = std::max(1, (int)std::ceil((length_of_edge + inset_y) / 1.0));
      collided_tiles.reserve(num_tiles_along_edge);

      // add a list of tiles to the thing
      for (int i=0; i<num_tiles_along_edge; i++)
      {
         collided_tiles.push_back(AllegroFlare::Physics::Int2D(next, start_y+i));
      }
   }

   return collided_tiles;
}

std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo> UnitTileMapCollisionStepper::get_stepped_tile_collisions(float x, float y, float velocity_x, float velocity_y, float width, float height)
{
   std::vector<AllegroFlare::Physics::Int2D> now_tiles = tiles_within(x, y, width, height);
   std::vector<AllegroFlare::Physics::Int2D> next_tiles = tiles_within(
      x+velocity_x,
      y+velocity_y,
      width+velocity_x,
      height+velocity_y
   );
   return calculate_difference_info(now_tiles, next_tiles, velocity_x, velocity_y);
}

std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo> UnitTileMapCollisionStepper::calculate_difference_info(std::vector<AllegroFlare::Physics::Int2D> now_tiles, std::vector<AllegroFlare::Physics::Int2D> next_tiles, float velocity_x, float velocity_y)
{
   std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo> result;

   std::vector<AllegroFlare::Physics::Int2D> stayed_on_tiles;

   std::set<int> next_tile_indexes_to_remove;
   std::set<int> now_tile_indexes_to_remove;

   for (int i=0; i<next_tiles.size(); i++)
   {
      for (int j=0; j<now_tiles.size(); j++)
      {
         if (tiles_have_equal_coordinates(next_tiles[i], now_tiles[j]))
         {
            // add them to the stayed_on_tiles
            stayed_on_tiles.push_back(now_tiles[j]);

            // remove this tile from both sets
            next_tile_indexes_to_remove.insert(i);
            now_tile_indexes_to_remove.insert(j);
         }
      }
   }

   // remove the indexes from the set
   for (int i=next_tile_indexes_to_remove.size()-1; i>=0; i--)
   {
      int index_to_remove = *std::next(next_tile_indexes_to_remove.begin(), i);
      next_tiles.erase(next_tiles.begin() + index_to_remove);
   }
   for (int i=now_tile_indexes_to_remove.size()-1; i>=0; i--)
   {
      int index_to_remove = *std::next(now_tile_indexes_to_remove.begin(), i);
      now_tiles.erase(now_tiles.begin() + index_to_remove);
   }

   // aggrigate the results
   std::vector<AllegroFlare::Physics::Int2D> &entered_tiles = next_tiles;
   std::vector<AllegroFlare::Physics::Int2D> &exited_tiles = now_tiles;

   // aggrigate the result (EVENT_STAYED_ON)
   for (auto &stayed_on_tile : stayed_on_tiles)
   {
      result.push_back(AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo(
         stayed_on_tile,
         //collision_tile_map ? collision_tile_map->get_tile(stayed_on_tile.get_x(), stayed_on_tile.get_y()) : -999,
         collision_tile_map ? get_tile_or_fallback(stayed_on_tile.get_x(), stayed_on_tile.get_y(), -1) : -999,
         velocity_x,
         velocity_y,
         false,
         AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::EVENT_STAYED_ON
      ));
   }

   // aggrigate the result (EVENT_ENTERED)
   for (auto &entered_tile : entered_tiles)
   {
      result.push_back(AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo(
         entered_tile,
         //collision_tile_map ? collision_tile_map->get_tile(entered_tile.get_x(), entered_tile.get_y()) : -999,
         collision_tile_map ? get_tile_or_fallback(entered_tile.get_x(), entered_tile.get_y(), -1) : -999,
         //get_tile_value_or_fallback(entered_tile.get_x(), entered_tile.get_y(), -999),
         velocity_x,
         velocity_y,
         false,
         AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::EVENT_ENTERED
      ));
   }

   // aggrigate the result (EVENT_EXITED)
   for (auto &exited_tile : exited_tiles)
   {
      result.push_back(AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo(
         exited_tile,
         //collision_tile_map ? collision_tile_map->get_tile(exited_tile.get_x(), exited_tile.get_y()) : -999,
         //get_tile_value_or_fallback(exited_tile.get_x(), exited_tile.get_y(), -999),
         collision_tile_map ? get_tile_or_fallback(exited_tile.get_x(), exited_tile.get_y(), -1) : -999,
         velocity_x,
         velocity_y,
         false,
         AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::EVENT_EXITED
      ));
   }

   return result;
}

std::vector<AllegroFlare::Physics::Int2D> UnitTileMapCollisionStepper::tiles_within_aabb2d(AllegroFlare::Physics::AABB2D* aabb2d)
{
   if (!(aabb2d))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Physics::UnitTileMapCollisionStepper::tiles_within_aabb2d]: error: guard \"aabb2d\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Physics::UnitTileMapCollisionStepper::tiles_within_aabb2d]: error: guard \"aabb2d\" not met");
   }
   return tiles_within(aabb2d->get_x(), aabb2d->get_y(), aabb2d->get_w(), aabb2d->get_h());
}

std::vector<AllegroFlare::Physics::Int2D> UnitTileMapCollisionStepper::tiles_within(float x, float y, float width, float height)
{
   if (!((width >= 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Physics::UnitTileMapCollisionStepper::tiles_within]: error: guard \"(width >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Physics::UnitTileMapCollisionStepper::tiles_within]: error: guard \"(width >= 0)\" not met");
   }
   if (!((height >= 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Physics::UnitTileMapCollisionStepper::tiles_within]: error: guard \"(height >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Physics::UnitTileMapCollisionStepper::tiles_within]: error: guard \"(height >= 0)\" not met");
   }
   std::vector<AllegroFlare::Physics::Int2D> result_tiles;

   int left_tile_x = unit_space_to_tile_coord(x);
   int top_tile_y = unit_space_to_tile_coord(y);
   int right_tile_x = unit_space_to_tile_coord(x+width);
   int bottom_tile_y = unit_space_to_tile_coord(y+height);

   for (int tile_y = top_tile_y; tile_y <= bottom_tile_y; tile_y++)
      for (int tile_x = left_tile_x; tile_x <= right_tile_x; tile_x++)
      {
         result_tiles.push_back(AllegroFlare::Physics::Int2D(tile_x, tile_y));
      }

   return result_tiles;
}

bool UnitTileMapCollisionStepper::tiles_have_equal_coordinates(AllegroFlare::Physics::Int2D a, AllegroFlare::Physics::Int2D b)
{
   return (a.get_x() == b.get_x() && a.get_y() == b.get_y());
}

int UnitTileMapCollisionStepper::unit_space_to_tile_coord(float unit_pos)
{
   return static_cast<int>(std::floor(unit_pos));
}

float UnitTileMapCollisionStepper::get_tile_left_edge(float tile_x)
{
   return tile_x;
}

float UnitTileMapCollisionStepper::get_tile_right_edge(float tile_x)
{
   return (tile_x+1);
}

float UnitTileMapCollisionStepper::get_tile_top_edge(float tile_y)
{
   return tile_y;
}

float UnitTileMapCollisionStepper::get_tile_bottom_edge(float tile_y)
{
   return (tile_y+1);
}

int UnitTileMapCollisionStepper::get_tile_or_fallback(int tile_x, int tile_y, int fallback)
{
   if (!(collision_tile_map))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Physics::UnitTileMapCollisionStepper::get_tile_or_fallback]: error: guard \"collision_tile_map\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Physics::UnitTileMapCollisionStepper::get_tile_or_fallback]: error: guard \"collision_tile_map\" not met");
   }
   return collision_tile_map->get_tile_or_fallback(tile_x, tile_y, fallback);
   // Check if the tile coordinates are within the map's bounds
   //if (tile_x >= 0 && tile_x < collision_tile_map->get_num_columns()
    //&& tile_y >= 0 && tile_y < collision_tile_map->get_num_rows())
   //{
       //return collision_tile_map->get_tile(tile_x, tile_y);
   //}
   //return fallback;
}


} // namespace Physics
} // namespace AllegroFlare


