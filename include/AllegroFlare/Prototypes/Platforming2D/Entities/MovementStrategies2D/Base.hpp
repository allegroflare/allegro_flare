#pragma once


#include <AllegroFlare/Physics/TileMapCollisionStepperCollisionInfo.hpp>
#include <AllegroFlare/Vec2D.hpp>
#include <vector>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace Platforming2D
      {
         namespace Entities
         {
            namespace MovementStrategies2D
            {
               class Base
               {
               private:

               protected:


               public:
                  Base();
                  virtual ~Base();

                  virtual void initialize();
                  virtual void update();
                  virtual void on_collision_update(AllegroFlare::Vec2D previous_place_position={}, AllegroFlare::Vec2D previous_velocity_position={}, AllegroFlare::Vec2D new_place_position={}, AllegroFlare::Vec2D new_velocity_position={}, std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo>* collision_step_result={}, bool top_edge_is_currently_adjacent_to_wall=false, bool right_edge_is_currently_adjacent_to_wall=false, bool bottom_edge_is_currently_adjacent_to_wall=false, bool left_edge_is_currently_adjacent_to_wall=false);
               };
            }
         }
      }
   }
}



