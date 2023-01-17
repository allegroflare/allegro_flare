

#include <tilemap/lib/NextCollidingTilesCalculator.hpp>

#include <cmath>


static vec2i world_to_tile_coordinates(float world_x, float world_y)
{
   return vec2i(world_x/16, world_y/16);
}


NextCollidingTilesCalculator::NextCollidingTilesCalculator(axis_t axis, float element_x, float element_y, float element_w, float element_h, float element_velocity_x, float element_velocity_y)
   : axis(axis)
   , element_x(element_x)
   , element_y(element_y)
   , element_w(element_w)
   , element_h(element_h)
   , element_velocity_x(element_velocity_x)
   , element_velocity_y(element_velocity_y)
{
}


NextCollidingTilesCalculator::~NextCollidingTilesCalculator()
{
}


std::vector<vec2i> NextCollidingTilesCalculator::next_colliding_tiles()
{
   std::vector<vec2i> result_tiles;


   float velocity_amt = element_velocity_x; // * timestep;
   float now_x = element_x;
   float next_x = element_x + velocity_amt;
   float next_y = element_y;
   float size_of_body = element_w;
   float length_of_edge = element_h;
   float cursor_step_amt = 16;






   if (axis == Y_AXIS)
   {
      velocity_amt = element_velocity_y; // * timestep;
      now_x = element_y;
      next_x = element_y + velocity_amt;
      next_y = element_x;
      size_of_body = element_h;
      length_of_edge = element_w;
   }






   // if moving right, test along the right edge
   float padding = 0.0001;
   if (velocity_amt > 0.0) // moving right
   {
      now_x += size_of_body - padding;
      next_x += size_of_body - padding;
   }
   else
   {
      now_x += padding;
      next_x += padding;
   }

   int column_x_now = now_x / 16;
   int column_x_next = next_x / 16;

   float remainder_y = fmod(next_y, 16.0);

   if (column_x_now != column_x_next)
   {
      int num_passes = std::ceil((length_of_edge + remainder_y) / 16);
      float step_cursor = 0;

      result_tiles.reserve(num_passes);
      vec2i collided_tile;

      for (unsigned i=0; i<num_passes; i++)
      {
         if (axis == X_AXIS) collided_tile = world_to_tile_coordinates(next_x, next_y + step_cursor);
         else if (axis == Y_AXIS) collided_tile = world_to_tile_coordinates(next_y + step_cursor, next_x);

         result_tiles.push_back(collided_tile);

         step_cursor += cursor_step_amt;
      }
   }


   return result_tiles;
}


