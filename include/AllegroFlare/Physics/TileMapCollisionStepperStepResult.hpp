#pragma once


#include <AllegroFlare/Physics/TileMapCollisionStepperCollisionInfo.hpp>
#include <AllegroFlare/Vec2D.hpp>
#include <vector>


namespace AllegroFlare
{
   namespace Physics
   {
      class TileMapCollisionStepperStepResult
      {
      private:
         AllegroFlare::Vec2D subject_position_before;
         AllegroFlare::Vec2D subject_velocity_before;
         AllegroFlare::Vec2D subject_position_after;
         AllegroFlare::Vec2D subject_velocity_after;
         std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo> collisions;
         bool subject_was_stopped_by_collision;

      protected:


      public:
         TileMapCollisionStepperStepResult();
         ~TileMapCollisionStepperStepResult();

         void set_subject_position_before(AllegroFlare::Vec2D subject_position_before);
         void set_subject_velocity_before(AllegroFlare::Vec2D subject_velocity_before);
         void set_subject_position_after(AllegroFlare::Vec2D subject_position_after);
         void set_subject_velocity_after(AllegroFlare::Vec2D subject_velocity_after);
         void set_collisions(std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo> collisions);
         void set_subject_was_stopped_by_collision(bool subject_was_stopped_by_collision);
         AllegroFlare::Vec2D get_subject_position_before() const;
         AllegroFlare::Vec2D get_subject_velocity_before() const;
         AllegroFlare::Vec2D get_subject_position_after() const;
         AllegroFlare::Vec2D get_subject_velocity_after() const;
         std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo> get_collisions() const;
         bool get_subject_was_stopped_by_collision() const;
         std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo> &get_collisions_ref();
         bool subject_entered_tile_value(int tile_value=0);
         bool subject_is_still_on_or_was_previously_on_tile_value(int tile_value=0);
      };
   }
}



