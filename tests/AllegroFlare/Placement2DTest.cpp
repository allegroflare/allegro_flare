
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/CustomComparison.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_Placement2DTest : public ::testing::Test
{};

class AllegroFlare_Placement2DWithAllegroRenderingFixtureTest
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};



#include <AllegroFlare/Placement2D.hpp>

#include <AllegroFlare/Color.hpp>


TEST_F(AllegroFlare_Placement2DTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Placement2D placement;
}


TEST_F(AllegroFlare_Placement2DTest,
   transform_coordinates__will_transform_a_list_of_vec2d_coordinates_into_the_placement)
{
   AllegroFlare::Placement2D placement;
   placement.position = {10, 27};
   std::vector<AllegroFlare::Vec2D> coordinates = { { 0, 0 }, { 10, 27 }, { 32, 64 } };

   placement.transform_coordinates(&coordinates);

   std::vector<AllegroFlare::Vec2D> expected_transformed_coordinates = { { -10, -27 }, { 0, 0 }, { 22, 37 } };

   EXPECT_EQ(expected_transformed_coordinates, coordinates);
}


TEST_F(AllegroFlare_Placement2DTest,
   place_coordinates__will_place_a_list_of_vec2d_coordinates_into_the_placement)
{
   AllegroFlare::Placement2D placement;
   placement.position = {10, 27};
   std::vector<AllegroFlare::Vec2D> coordinates = { { 0, 0 }, { 10, 27 }, { 32, 64 } };

   placement.place_coordinates(&coordinates);

   std::vector<AllegroFlare::Vec2D> expected_transformed_coordinates = { { 10, 27 }, { 20, 54 }, { 42, 91 } };

   EXPECT_EQ(expected_transformed_coordinates, coordinates);
}


TEST_F(AllegroFlare_Placement2DWithAllegroRenderingFixtureTest,
   collides__will_return_true_if_the_placement_collides_with_another_placement)
{
   AllegroFlare::Placement2D placement_a(400, 300, 100, 100);
   placement_a.rotation = 0.01f;

   AllegroFlare::Placement2D placement_b(700, 400, 150, 140);
   placement_b.rotation = 0.02f;

   al_install_keyboard();
   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
   ALLEGRO_TIMER *primary_timer = al_create_timer(ALLEGRO_BPS_TO_SECS(60));
   al_register_event_source(event_queue, al_get_timer_event_source(primary_timer));
   al_register_event_source(event_queue, al_get_keyboard_event_source());

   AllegroFlare::Placement2D *targeted_placement = &placement_a;

   al_start_timer(primary_timer);
   bool abort = false;
   while(!abort)
   {
      ALLEGRO_EVENT current_event;
      al_wait_for_event(event_queue, &current_event);
      switch(current_event.type)
      {
         case ALLEGRO_EVENT_TIMER:
         {
            al_clear_to_color(AllegroFlare::Color::Nothing);
            bool collides = placement_a.collide(placement_b);
            ALLEGRO_COLOR collides_color = AllegroFlare::Color::Red;
            placement_a.draw_box(collides ? collides_color : AllegroFlare::color::mintcream, false);
            placement_b.draw_box(collides ? collides_color : AllegroFlare::color::lightcyan, false);
            al_flip_display();
         }
         break;

         case ALLEGRO_EVENT_KEY_CHAR:
         {
            switch(current_event.keyboard.keycode)
            {
               case ALLEGRO_KEY_TAB: // toggle between the two placements
                  if (targeted_placement == &placement_a) targeted_placement = &placement_b;
                  else targeted_placement = &placement_a;
               break;

               case ALLEGRO_KEY_R: // rotate the current targeted placement
                  targeted_placement->rotation += 0.1f;
               break;

               case ALLEGRO_KEY_RIGHT: // move the current targeted placement to the right
                  targeted_placement->position.x += 10.0f;
               break;

               case ALLEGRO_KEY_LEFT: // move the current targeted placement to the left
                  targeted_placement->position.x -= 10.0f;
               break;

               case ALLEGRO_KEY_UP: // move the current targeted placement up
                  targeted_placement->position.y -= 10.0f;
               break;

               case ALLEGRO_KEY_DOWN: // move the current targeted placement down
                  targeted_placement->position.y += 10.0f;
               break;

               case ALLEGRO_KEY_PAD_PLUS: // increase the targeted placement scale
                  targeted_placement->scale.x += 0.1f;
                  targeted_placement->scale.y += 0.1f;
               break;

               case ALLEGRO_KEY_PAD_MINUS: // decrease the targeted placement scale
                  targeted_placement->scale.x -= 0.1f;
                  targeted_placement->scale.y -= 0.1f;
               break;

               case ALLEGRO_KEY_ESCAPE:
                  abort = true;
               break;
            }
         }
         break;
      }
   }

   al_destroy_timer(primary_timer);
   //al_destroy_r(timer);
}


