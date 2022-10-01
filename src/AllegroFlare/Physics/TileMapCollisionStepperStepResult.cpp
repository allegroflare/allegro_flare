

#include <AllegroFlare/Physics/TileMapCollisionStepperStepResult.hpp>




namespace AllegroFlare
{
namespace Physics
{


TileMapCollisionStepperStepResult::TileMapCollisionStepperStepResult()
   : subject_position_before({ 0, 0 })
   , subject_velocity_before({ 0, 0 })
   , subject_position_after({ 0, 0 })
   , subject_velocity_after({ 0, 0 })
   , collisions({})
   , subject_was_stopped_by_collision(false)
{
}


TileMapCollisionStepperStepResult::~TileMapCollisionStepperStepResult()
{
}


void TileMapCollisionStepperStepResult::set_subject_position_before(AllegroFlare::Vec2D subject_position_before)
{
   this->subject_position_before = subject_position_before;
}


void TileMapCollisionStepperStepResult::set_subject_velocity_before(AllegroFlare::Vec2D subject_velocity_before)
{
   this->subject_velocity_before = subject_velocity_before;
}


void TileMapCollisionStepperStepResult::set_subject_position_after(AllegroFlare::Vec2D subject_position_after)
{
   this->subject_position_after = subject_position_after;
}


void TileMapCollisionStepperStepResult::set_subject_velocity_after(AllegroFlare::Vec2D subject_velocity_after)
{
   this->subject_velocity_after = subject_velocity_after;
}


void TileMapCollisionStepperStepResult::set_collisions(std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo> collisions)
{
   this->collisions = collisions;
}


void TileMapCollisionStepperStepResult::set_subject_was_stopped_by_collision(bool subject_was_stopped_by_collision)
{
   this->subject_was_stopped_by_collision = subject_was_stopped_by_collision;
}


AllegroFlare::Vec2D TileMapCollisionStepperStepResult::get_subject_position_before() const
{
   return subject_position_before;
}


AllegroFlare::Vec2D TileMapCollisionStepperStepResult::get_subject_velocity_before() const
{
   return subject_velocity_before;
}


AllegroFlare::Vec2D TileMapCollisionStepperStepResult::get_subject_position_after() const
{
   return subject_position_after;
}


AllegroFlare::Vec2D TileMapCollisionStepperStepResult::get_subject_velocity_after() const
{
   return subject_velocity_after;
}


std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo> TileMapCollisionStepperStepResult::get_collisions() const
{
   return collisions;
}


bool TileMapCollisionStepperStepResult::get_subject_was_stopped_by_collision() const
{
   return subject_was_stopped_by_collision;
}


std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo> &TileMapCollisionStepperStepResult::get_collisions_ref()
{
   return collisions;
}




} // namespace Physics
} // namespace AllegroFlare


