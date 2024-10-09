
#include <gtest/gtest.h>

#include <AllegroFlare/CollisionObservers/Simple.hpp>


TEST(AllegroFlare_CollisionObservers_SimpleTest, can_be_created_without_blowing_up)
{
   AllegroFlare::CollisionObservers::Simple simple;
}


/*
   // Test collisions
   std::set<void*> collidables;
   auto &boxes = frustum_viewer.get_boxes_ref();
   for (auto &box : boxes) { if (box.collides_with_player) collidables.insert(&box); }
   collision_observer.set_subject(player_box);
   collision_observer.set_collidables(collidables);
   collision_observer.set_on_test_collide([](void* subject, void* collidable) -> bool {
      return static_cast<TileFPS::Box*>(collidable)->collides(static_cast<TileFPS::Box*>(subject));
   });
   collision_observer.process();

   // Process "entered" collisions
   for (auto &entered : collision_observer.get_entered())
   {
      handle_player_box_box_collision(
         player_box, 
         static_cast<TileFPS::Box*>(entered)
      );
   }
*/


