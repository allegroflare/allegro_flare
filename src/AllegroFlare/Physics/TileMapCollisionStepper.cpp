

#include <AllegroFlare/Physics/TileMapCollisionStepper.hpp>

#include <AllegroFlare/Physics/AABB2D.hpp>
#include <AllegroFlare/Physics/TileMapCollisionStepperCollisionInfo.hpp>
#include <AllegroFlare/Testing/Comparison/AllegroFlare/Physics/Int2D.hpp>
#include <cmath>
#include <set>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Physics
{


TileMapCollisionStepper::TileMapCollisionStepper(AllegroFlare::TileMaps::TileMap<int>* collision_tile_map, AllegroFlare::Physics::AABB2D* aabb2d, float tile_width, float tile_height)
   : collision_tile_map(collision_tile_map)
   , aabb2d(aabb2d)
   , tile_width(tile_width)
   , tile_height(tile_height)
{
}


TileMapCollisionStepper::~TileMapCollisionStepper()
{
}


std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo> TileMapCollisionStepper::step()
{
   if (!(collision_tile_map))
   {
      std::stringstream error_message;
      error_message << "TileMapCollisionStepper" << "::" << "step" << ": error: " << "guard \"collision_tile_map\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(aabb2d))
   {
      std::stringstream error_message;
      error_message << "TileMapCollisionStepper" << "::" << "step" << ": error: " << "guard \"aabb2d\" not met";
      throw std::runtime_error(error_message.str());
   }
   // NEXT: TODO: include EVENT_ENTERED, EVENT_EXITED, EVENT_STAYED_ON, EVENT_COLLIDED_AGAINST to the
   // CollisionInfo result data

   std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo> result_infos;
   AllegroFlare::Physics::AABB2D &obj = *aabb2d;
   AllegroFlare::TileMaps::TileMap<int> &map = *collision_tile_map;

   // collect the position before any alterations
   AllegroFlare::Physics::AABB2D obj_before = obj;

   // test horizontal first
   std::vector<AllegroFlare::Physics::Int2D> horizontal_collided_blocks = get_next_collided_tile_coords_1d(
         obj.get_x(), obj.get_y(), obj.get_velocity_x(), obj.get_w(), obj.get_h(), tile_width, tile_height
   );

   // react to the collision here:
   if (!horizontal_collided_blocks.empty())
   {
      for (AllegroFlare::Physics::Int2D &t : horizontal_collided_blocks)
      {
         int tile_value = map.get_tile(t.get_x(), t.get_y());

         if (tile_value == 1) // tile is solid
         {
            if (obj.get_velocity_x() > 0)
            {
               result_infos.push_back(
                  AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo(
                     AllegroFlare::Physics::Int2D(t.get_x(), t.get_y()),
                     tile_value,
                     obj.get_velocity_x(),
                     obj.get_velocity_y(),
                     true,
                     // NEXT: TODO: ensure this is correct and calcualte "entered", "exited" and "stayed_on" tiles
                     AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::EVENT_COLLIDED_AGAINST
                  )
               );

               obj.set_right_edge(get_tile_left_edge(t.get_x(), tile_width) - 0.0001);
               obj.set_velocity_x(0.0);
            }
            else if (obj.get_velocity_x() < 0)
            {
               result_infos.push_back(
                  AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo(
                     AllegroFlare::Physics::Int2D(t.get_x(), t.get_y()),
                     tile_value,
                     obj.get_velocity_x(),
                     obj.get_velocity_y(),
                     true,
                     // NEXT: TODO: ensure this is correct and calcualte "entered", "exited" and "stayed_on" tiles
                     AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::EVENT_COLLIDED_AGAINST
                  )
               );

               obj.set_left_edge(get_tile_right_edge(t.get_x(), tile_width) + 0.0001);
               obj.set_velocity_x(0.0);
            }
         }
         else // tile is not solid (aka, "1")
         {
            result_infos.push_back(
               AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo(
                  AllegroFlare::Physics::Int2D(t.get_x(), t.get_y()),
                  tile_value,
                  obj.get_velocity_x(),
                  obj.get_velocity_y(),
                  false,
                  // NEXT: TODO: ensure this is correct and calcualte "entered", "exited" and "stayed_on" tiles
                  AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::EVENT_ENTERED
               )
            );
         }
      }
   }

   obj.set_x(obj.get_x() + obj.get_velocity_x());

   // test vertical second
   std::vector<AllegroFlare::Physics::Int2D> vertical_collided_blocks = get_next_collided_tile_coords_1d(
      obj.get_y(), obj.get_x(), obj.get_velocity_y(), obj.get_h(), obj.get_w(), tile_height, tile_width
   );
   for(AllegroFlare::Physics::Int2D &tile_coord : vertical_collided_blocks) tile_coord.rotate();
   if (!vertical_collided_blocks.empty())
   {
      for (AllegroFlare::Physics::Int2D &t : vertical_collided_blocks)
      {
         int tile_value = map.get_tile(t.get_x(), t.get_y());

         if (tile_value == 1) // tile is solid
         {
            if (obj.get_velocity_y() > 0)
            {
               result_infos.push_back(
                  AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo(
                     AllegroFlare::Physics::Int2D(t.get_x(), t.get_y()),
                     tile_value,
                     obj.get_velocity_x(),
                     obj.get_velocity_y(),
                     true,
                     // NEXT: TODO: ensure this is correct and calcualte "entered", "exited" and "stayed_on" tiles
                     AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::EVENT_COLLIDED_AGAINST
                  )
               );

               obj.set_bottom_edge(get_tile_top_edge(t.get_y(), tile_height) - 0.0001);
               obj.set_velocity_y(0.0);
            }
            else if (obj.get_velocity_y() < 0)
            {
               result_infos.push_back(
                  AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo(
                     AllegroFlare::Physics::Int2D(t.get_x(), t.get_y()),
                     tile_value,
                     obj.get_velocity_x(),
                     obj.get_velocity_y(),
                     true,
                  // NEXT: TODO: ensure this is correct and calcualte "entered", "exited" and "stayed_on" tiles
                     AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::EVENT_COLLIDED_AGAINST
                  )
               );

               obj.set_top_edge(get_tile_bottom_edge(t.get_y(), tile_height) + 0.0001);
               obj.set_velocity_y(0.0);
            }
         }
         else // tile is not solid (aka, "1")
         {
            result_infos.push_back(
               AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo(
                  AllegroFlare::Physics::Int2D(t.get_x(), t.get_y()),
                  tile_value,
                  obj.get_velocity_x(),
                  obj.get_velocity_y(),
                  false,
                  // NEXT: TODO: ensure this is correct and calcualte "entered", "exited" and "stayed_on" tiles
                  AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::EVENT_ENTERED
               )
            );
         }
      }
   }
   obj.set_y(obj.get_y() + obj.get_velocity_y());


   AllegroFlare::Physics::AABB2D obj_after = obj;



   return result_infos;
}

bool TileMapCollisionStepper::adjacent_to_bottom_edge(float tile_width, float tile_height)
{
   if (!(collision_tile_map))
   {
      std::stringstream error_message;
      error_message << "TileMapCollisionStepper" << "::" << "adjacent_to_bottom_edge" << ": error: " << "guard \"collision_tile_map\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(aabb2d))
   {
      std::stringstream error_message;
      error_message << "TileMapCollisionStepper" << "::" << "adjacent_to_bottom_edge" << ": error: " << "guard \"aabb2d\" not met";
      throw std::runtime_error(error_message.str());
   }
   AllegroFlare::Physics::AABB2D &obj = *aabb2d;

   std::vector<AllegroFlare::Physics::Int2D> tiles = get_next_collided_tile_coords_1d(
      obj.get_y(),
      obj.get_x(),
      0.0004,
      obj.get_h(),
      obj.get_w(),
      tile_height,
      tile_width
   );
   if (tiles.empty()) return false;

   for (auto &t : tiles)
   {
      t.rotate();
      if (collision_tile_map->get_tile(t.get_x(), t.get_y()) == 1) return true;
   }
   return false;
}

bool TileMapCollisionStepper::adjacent_to_right_edge(float tile_width, float tile_height)
{
   if (!(collision_tile_map))
   {
      std::stringstream error_message;
      error_message << "TileMapCollisionStepper" << "::" << "adjacent_to_right_edge" << ": error: " << "guard \"collision_tile_map\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(aabb2d))
   {
      std::stringstream error_message;
      error_message << "TileMapCollisionStepper" << "::" << "adjacent_to_right_edge" << ": error: " << "guard \"aabb2d\" not met";
      throw std::runtime_error(error_message.str());
   }
   AllegroFlare::Physics::AABB2D &obj = *aabb2d;

   std::vector<AllegroFlare::Physics::Int2D> tiles = get_next_collided_tile_coords_1d(
      obj.get_x(),
      obj.get_y(),
      0.0004,
      obj.get_w(),
      obj.get_h(),
      tile_width,
      tile_height
   );
   if (tiles.empty()) return false;

   for (auto &t : tiles)
   {
      //t.rotate();
      if (collision_tile_map->get_tile(t.get_x(), t.get_y()) == 1) return true;
   }
   return false;
}

bool TileMapCollisionStepper::adjacent_to_top_edge(float tile_width, float tile_height)
{
   if (!(collision_tile_map))
   {
      std::stringstream error_message;
      error_message << "TileMapCollisionStepper" << "::" << "adjacent_to_top_edge" << ": error: " << "guard \"collision_tile_map\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(aabb2d))
   {
      std::stringstream error_message;
      error_message << "TileMapCollisionStepper" << "::" << "adjacent_to_top_edge" << ": error: " << "guard \"aabb2d\" not met";
      throw std::runtime_error(error_message.str());
   }
   AllegroFlare::Physics::AABB2D &obj = *aabb2d;

   std::vector<AllegroFlare::Physics::Int2D> tiles = get_next_collided_tile_coords_1d(
      obj.get_y(),
      obj.get_x(),
      -0.0004,
      obj.get_h(),
      obj.get_w(),
      tile_height,
      tile_width
   );
   if (tiles.empty()) return false;

   for (auto &t : tiles)
   {
      t.rotate();
      if (collision_tile_map->get_tile(t.get_x(), t.get_y()) == 1) return true;
   }
   return false;
}

std::pair<int, int> TileMapCollisionStepper::get_tile_coords_below_left_foot(float x, float y, float height)
{
   std::pair<int, int> result{
      world_x_coords_to_tile_coords_x(x),
      world_y_coords_to_tile_coords_y(y+height+0.0001f)
   };
   return result;
}

std::pair<int, int> TileMapCollisionStepper::get_tile_coords_below_right_foot(float x, float y, float width, float height)
{
   std::pair<int, int> result{
      world_x_coords_to_tile_coords_x(x+width),
      world_y_coords_to_tile_coords_y(y+height+0.0001f)
   };
   return result;
}

bool TileMapCollisionStepper::adjacent_to_left_edge(float tile_width, float tile_height)
{
   if (!(collision_tile_map))
   {
      std::stringstream error_message;
      error_message << "TileMapCollisionStepper" << "::" << "adjacent_to_left_edge" << ": error: " << "guard \"collision_tile_map\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(aabb2d))
   {
      std::stringstream error_message;
      error_message << "TileMapCollisionStepper" << "::" << "adjacent_to_left_edge" << ": error: " << "guard \"aabb2d\" not met";
      throw std::runtime_error(error_message.str());
   }
   AllegroFlare::Physics::AABB2D &obj = *aabb2d;

   std::vector<AllegroFlare::Physics::Int2D> tiles = get_next_collided_tile_coords_1d(
      obj.get_x(),
      obj.get_y(),
      -0.0004,
      obj.get_w(),
      obj.get_h(),
      tile_height,
      tile_width
   );
   if (tiles.empty()) return false;

   for (auto &t : tiles)
   {
      //t.rotate();
      if (collision_tile_map->get_tile(t.get_x(), t.get_y()) == 1) return true;
   }
   return false;
}

std::vector<AllegroFlare::Physics::Int2D> TileMapCollisionStepper::get_next_collided_tile_coords_1d(float x, float y, float velocity, float depth_of_body, float length_of_edge, float tile_length_n, float tile_length_m)
{
   std::vector<AllegroFlare::Physics::Int2D> collided_tiles;

   if (velocity > 0) x += depth_of_body;

   int now = world_coords_to_tile_coords(x, tile_length_n); //TileMap::world_to_tile(x);
   int next = world_coords_to_tile_coords(x + velocity, tile_length_n); //TileMap::world_to_tile(x + velocity);

   if (now != next)
   {
      // new tiles have been entered
      int start_y = world_coords_to_tile_coords(y, tile_length_m); //TileMap::world_to_tile(y);
      float inset_y = std::fmod(y, tile_length_m); // fmod(y, 16.0);
      int num_tiles_along_edge = std::max(1, (int)std::ceil((length_of_edge + inset_y) / tile_length_m));
      collided_tiles.reserve(num_tiles_along_edge);

      // add a list of tiles to the thing
      for (int i=0; i<num_tiles_along_edge; i++)
      {
         collided_tiles.push_back(AllegroFlare::Physics::Int2D(next, start_y+i));
      }
   }

   return collided_tiles;
}

std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo> TileMapCollisionStepper::get_stepped_tile_collisions(float x, float y, float velocity_x, float velocity_y, float width, float height, float tile_width, float tile_height)
{
   std::vector<AllegroFlare::Physics::Int2D> now_tiles = tiles_within(x, y, width, height, tile_width, tile_height);
   std::vector<AllegroFlare::Physics::Int2D> next_tiles = tiles_within(
      x+velocity_x,
      y+velocity_y,
      width+velocity_x,
      height+velocity_y,
      tile_width,
      tile_height
   );
   return calculate_difference_info(now_tiles, next_tiles, velocity_x, velocity_y);
}

std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo> TileMapCollisionStepper::calculate_difference_info(std::vector<AllegroFlare::Physics::Int2D> now_tiles, std::vector<AllegroFlare::Physics::Int2D> next_tiles, float velocity_x, float velocity_y)
{
   std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo> result;

   std::vector<AllegroFlare::Physics::Int2D> stayed_on_tiles;
   //std::vector<AllegroFlare::Physics::Int2D> &entered_tiles = next_tiles;
   //std::vector<AllegroFlare::Physics::Int2D> &exited_tiles = now_tiles;

   std::set<int> next_tile_indexes_to_remove;
   std::set<int> now_tile_indexes_to_remove;

   for (int i=0; i<next_tiles.size(); i++)
   {
      for (int j=0; j<now_tiles.size(); j++)
      //for (auto &now_tile : now_tiles)
      {
         if (next_tiles[i] == now_tiles[j])
         {
            // add them to the stayed_on_tiles
            stayed_on_tiles.push_back(now_tiles[j]);

            // remove this tile from both sets
            next_tile_indexes_to_remove.insert(i);
            now_tile_indexes_to_remove.insert(j);
         }
      }
   }

   //std::cout << "next tiles count: " << next_tiles.size() << std::endl;
   //std::cout << "now tiles count: " << now_tiles.size() << std::endl;
   //std::cout << "next tiles to remove count: " << next_tile_indexes_to_remove.size() << std::endl;
   //std::cout << "now tiles to remove count: " << now_tile_indexes_to_remove.size() << std::endl;

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
         collision_tile_map ? collision_tile_map->get_tile(stayed_on_tile.get_x(), stayed_on_tile.get_y()) : -999,
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
         collision_tile_map ? collision_tile_map->get_tile(entered_tile.get_x(), entered_tile.get_y()) : -999,
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
         collision_tile_map ? collision_tile_map->get_tile(exited_tile.get_x(), exited_tile.get_y()) : -999,
         velocity_x,
         velocity_y,
         false,
         AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::EVENT_EXITED
      ));
   }

   return result;
}

std::vector<AllegroFlare::Physics::Int2D> TileMapCollisionStepper::tiles_within(float x, float y, float width, float height, float tile_width, float tile_height)
{
   if (!((width >= 0)))
   {
      std::stringstream error_message;
      error_message << "TileMapCollisionStepper" << "::" << "tiles_within" << ": error: " << "guard \"(width >= 0)\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!((height >= 0)))
   {
      std::stringstream error_message;
      error_message << "TileMapCollisionStepper" << "::" << "tiles_within" << ": error: " << "guard \"(height >= 0)\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!((tile_width > 0.0f)))
   {
      std::stringstream error_message;
      error_message << "TileMapCollisionStepper" << "::" << "tiles_within" << ": error: " << "guard \"(tile_width > 0.0f)\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!((tile_height > 0.0f)))
   {
      std::stringstream error_message;
      error_message << "TileMapCollisionStepper" << "::" << "tiles_within" << ": error: " << "guard \"(tile_height > 0.0f)\" not met";
      throw std::runtime_error(error_message.str());
   }
   std::vector<AllegroFlare::Physics::Int2D> result_tiles;

   int left_tile_x = world_coords_to_tile_coords(x, tile_width);
   int top_tile_y = world_coords_to_tile_coords(y, tile_height);
   int right_tile_x = world_coords_to_tile_coords(x+width, tile_width);
   int bottom_tile_y = world_coords_to_tile_coords(y+height, tile_height);

   for (int tile_y = top_tile_y; tile_y <= bottom_tile_y; tile_y++)
      for (int tile_x = left_tile_x; tile_x <= right_tile_x; tile_x++)
      {
         result_tiles.push_back(AllegroFlare::Physics::Int2D(tile_x, tile_y));
      }

   return result_tiles;
}

int TileMapCollisionStepper::world_coords_to_tile_coords(float world_pos, float tile_length)
{
   return (int)(world_pos / tile_length);
}

int TileMapCollisionStepper::world_x_coords_to_tile_coords_x(float world_pos_x)
{
   return (int)(world_pos_x / tile_width);
}

int TileMapCollisionStepper::world_y_coords_to_tile_coords_y(float world_pos_y)
{
   return (int)(world_pos_y / tile_height);
}

float TileMapCollisionStepper::get_tile_left_edge(float tile_x, float tile_width)
{
   return tile_x * tile_width;
}

float TileMapCollisionStepper::get_tile_right_edge(float tile_x, float tile_width)
{
   return (tile_x+1) * tile_width;
}

float TileMapCollisionStepper::get_tile_top_edge(float tile_y, float tile_height)
{
   return tile_y * tile_height;
}

float TileMapCollisionStepper::get_tile_bottom_edge(float tile_y, float tile_height)
{
   return (tile_y+1) * tile_height;
}


} // namespace Physics
} // namespace AllegroFlare


