
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/CustomComparison.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>

#include <AllegroFlare/Placement2D.hpp>

#include <AllegroFlare/Color.hpp>
#include <allegro5/allegro_primitives.h>
#include <AllegroFlare/Testing/Rulers.hpp>


class AllegroFlare_Placement2DTest : public ::testing::Test
{};

class AllegroFlare_Placement2DWithAllegroRenderingFixtureTest
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


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


TEST_F(AllegroFlare_Placement2DTest, assignment_operator__will_work_as_expected)
{
   AllegroFlare::Placement2D placement_1;
   placement_1.position = { 7, 21 };
   placement_1.size = { 11, 13 };
   placement_1.align = { 73, 79 }; // TODO: Use a more realistic number for this test data
   placement_1.scale = { 7, 3 };
   placement_1.anchor = { 0.125, 0.875 };
   placement_1.flip = { true, true };
   placement_1.rotation = { 0.75 };

   AllegroFlare::Placement2D placement_2 = placement_1;

   EXPECT_EQ(placement_2.position, placement_1.position);
   EXPECT_EQ(placement_2.size, placement_1.size);
   EXPECT_EQ(placement_2.align, placement_1.align);
   EXPECT_EQ(placement_2.scale, placement_1.scale);
   EXPECT_EQ(placement_2.anchor, placement_1.anchor);
   //EXPECT_EQ(placement_2.flip, placement_1.flip ); // TODO: Add comparison for this value
   EXPECT_EQ(placement_2.rotation, placement_1.rotation);
}


TEST_F(AllegroFlare_Placement2DTest, scale_to_fit_width__will_modify_the_scale_to_fit_the_width)
{
   //void scale_to_fit_width(float target_width);
   // TODO: Add test
}


TEST_F(AllegroFlare_Placement2DTest, scale_to_fit_height__will_modify_the_scale_to_fit_the_height)
{
   //void scale_to_fit_height(float target_height);
   // TODO: Add test
}


TEST_F(AllegroFlare_Placement2DTest, scale_to_fit_width_or_height__will_modify_the_scale_to_fit_the_width_or_height)
{
   //void scale_to_fit_width_or_height(float target_width, float target_height);
   // TODO: Add test
}


TEST_F(AllegroFlare_Placement2DTest, scale_to_fill_width_or_height__will_modify_the_scale_to_fill_the_width_or_height)
{
   //void scale_to_fit_width_or_height(float target_width, float target_height);
   // TODO: Add test
}


TEST_F(AllegroFlare_Placement2DWithAllegroRenderingFixtureTest,
   CAPTURE__VISUAL__blend__will_interpolate_between_two_placements)
{
   AllegroFlare::Placement2D placement1;
   placement1.position = {200, 1080/2};
   placement1.size = {80, 80};
   placement1.rotation = -0.1;
   placement1.scale = { 1.0f, 1.0f };
   placement1.align = { 0.0f, 0.5f };

   AllegroFlare::Placement2D placement2;
   placement2.position = {1920-200, 1080/2};
   placement2.size = {100, 200};
   placement2.rotation = 0.2;
   placement2.scale = { 1.5f, 1.5f };
   placement2.align = { 0.75f, 0.5f };

   int num_blends = 5;
   for(int i=0; i<=num_blends; i++)
   {
      float interpolation = (float)i / (float)num_blends;
      AllegroFlare::Placement2D placement = AllegroFlare::Placement2D::blend(placement1, placement2, interpolation);

      placement.draw_box(ALLEGRO_COLOR{1, 1, 1, 1}, true);

      // Draw the center of body
      // TODO: Move this to another test, this current test is not related to center of body
      AllegroFlare::Vec2D center_of_body_coordinate = placement.get_center_of_body_coordinate();
      draw_crosshair(center_of_body_coordinate.x, center_of_body_coordinate.y);
   }
   al_flip_display();
   al_rest(1);
}


TEST_F(AllegroFlare_Placement2DWithAllegroRenderingFixtureTest,
   // TODO: Make this TIMED_INTERACTIVE
   DISABLED__INTERACTIVE__collide_as_if__will_check_pixel_perfect_collision_as_if_the_subject_under_placement_is_a_bitmap)
{
   ALLEGRO_BITMAP *bitmap_a = get_bitmap_bin_ref()["monoplex-1.png"];
   ALLEGRO_BITMAP *bitmap_b = get_bitmap_bin_ref()["rooster_cat_grid.png"];

   AllegroFlare::Placement2D placement_a(400, 300, al_get_bitmap_width(bitmap_a), al_get_bitmap_height(bitmap_a));
   placement_a.rotation = 0.01f;

   AllegroFlare::Placement2D placement_b(700, 400, al_get_bitmap_width(bitmap_b), al_get_bitmap_height(bitmap_b));
   placement_b.rotation = 0.02f;

   al_install_keyboard();
   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
   ALLEGRO_TIMER *primary_timer = al_create_timer(ALLEGRO_BPS_TO_SECS(60));
   al_register_event_source(event_queue, al_get_timer_event_source(primary_timer));
   al_register_event_source(event_queue, al_get_keyboard_event_source());

   AllegroFlare::Placement2D *targeted_placement = &placement_a;

   float cursor_x = 1920/2;
   float cursor_y = 1080/2;

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
            bool collides_a = placement_a.collide_as_if(bitmap_a, cursor_x, cursor_y);
            bool collides_b = placement_b.collide_as_if(bitmap_b, cursor_x, cursor_y);

            al_clear_to_color(AllegroFlare::Color::Nothing);

            ALLEGRO_COLOR collides_color = AllegroFlare::Color::Red;

            placement_a.start_transform();
            al_draw_bitmap(bitmap_a, 0, 0, 0);
            placement_a.restore_transform();
            placement_a.draw_box(collides_a ? collides_color : AllegroFlare::color::mintcream, false);

            placement_b.start_transform();
            al_draw_bitmap(bitmap_b, 0, 0, 0);
            placement_b.restore_transform();
            placement_b.draw_box(collides_b ? collides_color : AllegroFlare::color::lightcyan, false);

            // draw the "cursor"
            al_draw_rectangle(cursor_x-3, cursor_y-3, cursor_x+3, cursor_y+3, ALLEGRO_COLOR{1, 1, 1, 1}, 2.0);

            al_flip_display();
         }
         break;

         case ALLEGRO_EVENT_KEY_CHAR:
         {
            switch(current_event.keyboard.keycode)
            {
               case ALLEGRO_KEY_TAB: // toggle between the two placements
                  if (targeted_placement == &placement_a) targeted_placement = &placement_b;
                  else if (targeted_placement == &placement_b) targeted_placement = &placement_a;
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


TEST_F(AllegroFlare_Placement2DWithAllegroRenderingFixtureTest,
   // TODO: Make this TIMED_INTERACTIVE
   //INTERACTIVE__collides__will_return_true_if_the_placement_collides_with_another_placement)
   DISABLED__INTERACTIVE__collides__will_return_true_if_the_placement_collides_with_another_placement)
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


TEST_F(AllegroFlare_Placement2DWithAllegroRenderingFixtureTest,
   // TODO: Make this TIMED_INTERACTIVE
   //INTERACTIVE__get_nthmost_coordinates__will_return_the_coordinates_of_the_placement)
   DISABLED__INTERACTIVE__get_nthmost_coordinates__will_return_the_coordinates_of_the_placement)
{
   AllegroFlare::Placement2D placement_a(400, 300, 100, 100);
   placement_a.rotation = 0.1f;
   placement_a.scale = { 2.0f, 2.0f };

   //AllegroFlare::Placement2D placement_b(700, 400, 150, 140);
   //placement_b.rotation = 0.02f;

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
            //bool collides = placement_a.collide(placement_b);
            ALLEGRO_COLOR collides_color = AllegroFlare::Color::Red;
            placement_a.draw_box(AllegroFlare::color::mintcream, false);

            float leftmost_coordinate = placement_a.get_leftmost_coordinate();
            float rightmost_coordinate = placement_a.get_rightmost_coordinate();
            float topmost_coordinate = placement_a.get_topmost_coordinate();
            float bottommost_coordinate = placement_a.get_bottommost_coordinate();
            AllegroFlare::Vec2D center_of_body_coordinate = placement_a.get_center_of_body_coordinate();

            al_draw_line(leftmost_coordinate, 0, leftmost_coordinate, 1080, ALLEGRO_COLOR{1, 0.4, 0.4, 1.0}, 2.0);
            al_draw_line(rightmost_coordinate, 0, rightmost_coordinate, 1080, ALLEGRO_COLOR{0.4, 0.4, 1.0, 1.0}, 2.0);
            al_draw_line(0, topmost_coordinate, 1920, topmost_coordinate, ALLEGRO_COLOR{0.4, 1.0, 0.4, 1.0}, 2.0);
            al_draw_line(0, bottommost_coordinate, 1920, bottommost_coordinate, ALLEGRO_COLOR{1.0, 1.0, 0.4, 1.0}, 2.0);

            draw_crosshair(center_of_body_coordinate.x, center_of_body_coordinate.y);

            std::tuple<float, float, float, float> edges = placement_a.get_outermost_coordinates_trbl();

            al_draw_rectangle(
               std::get<3>(edges), // left
               std::get<0>(edges), // top
               std::get<1>(edges), // right
               std::get<2>(edges), // bottom
               ALLEGRO_COLOR{0.5, 0.9, 1.0, 1.0},
               4.0
            );

            //placement_b.draw_box(collides ? collides_color : AllegroFlare::color::lightcyan, false);
            al_flip_display();
         }
         break;

         case ALLEGRO_EVENT_KEY_CHAR:
         {
            switch(current_event.keyboard.keycode)
            {
               //case ALLEGRO_KEY_TAB: // toggle between the two placements
                  //if (targeted_placement == &placement_a) targeted_placement = &placement_b;
                  //else targeted_placement = &placement_a;
               //break;

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


TEST_F(AllegroFlare_Placement2DWithAllegroRenderingFixtureTest,
   // TODO: Make this TIMED_INTERACTIVE
   DISABLED__INTERACTIVE__set_nthmost_coordinates__will_move_the_placement_so_the_nthmost_coordinate_is_palced_there)
   //INTERACTIVE__set_nthmost_coordinates__will_move_the_placement_so_the_nthmost_coordinate_is_palced_there)
{
   AllegroFlare::Placement2D placement_a(400, 300, 100, 100);
   placement_a.rotation = 0.1f;
   placement_a.scale = { 2.0f, 2.0f };

   //AllegroFlare::Placement2D placement_b(700, 400, 150, 140);
   //placement_b.rotation = 0.02f;

   al_install_keyboard();
   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
   ALLEGRO_TIMER *primary_timer = al_create_timer(ALLEGRO_BPS_TO_SECS(60));
   al_register_event_source(event_queue, al_get_timer_event_source(primary_timer));
   al_register_event_source(event_queue, al_get_keyboard_event_source());

   AllegroFlare::Placement2D *targeted_placement = &placement_a;
   float my_x_cursor = 1920/3;
   float my_y_cursor = 1080/3;
   float my_cursor_speed = 17.1;

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
            //bool collides = placement_a.collide(placement_b);
            ALLEGRO_COLOR collides_color = AllegroFlare::Color::Red;
            placement_a.draw_box(AllegroFlare::color::mintcream, false);

            //float leftmost_coordinate = placement_a.get_leftmost_coordinate();
            //float rightmost_coordinate = placement_a.get_rightmost_coordinate();
            //float topmost_coordinate = placement_a.get_topmost_coordinate();
            //float bottommost_coordinate = placement_a.get_bottommost_coordinate();

            al_draw_line(my_x_cursor, 0, my_x_cursor, 1080, ALLEGRO_COLOR{1, 0.4, 0.4, 1.0}, 2.0);
            al_draw_line(0, my_y_cursor, 1920, my_y_cursor, ALLEGRO_COLOR{0.4, 0.4, 1.0, 1.0}, 2.0);
            //al_draw_line(rightmost_coordinate, 0, rightmost_coordinate, 1080, ALLEGRO_COLOR{0.4, 0.4, 1.0, 1.0}, 2.0);
            //al_draw_line(0, topmost_coordinate, 1920, topmost_coordinate, ALLEGRO_COLOR{0.4, 1.0, 0.4, 1.0}, 2.0);
            //al_draw_line(0, bottommost_coordinate, 1920, bottommost_coordinate, ALLEGRO_COLOR{1.0, 1.0, 0.4, 1.0}, 2.0);

            //std::tuple<float, float, float, float> edges = placement_a.get_outermost_coordinates_trbl();

            //al_draw_rectangle(
               //std::get<3>(edges), // left
               //std::get<0>(edges), // top
               //std::get<1>(edges), // right
               //std::get<2>(edges), // bottom
               //ALLEGRO_COLOR{0.5, 0.9, 1.0, 1.0},
               //4.0
            //);

            //placement_b.draw_box(collides ? collides_color : AllegroFlare::color::lightcyan, false);
            al_flip_display();
         }
         break;

         case ALLEGRO_EVENT_KEY_CHAR:
         {
            switch(current_event.keyboard.keycode)
            {
               //case ALLEGRO_KEY_TAB: // toggle between the two placements
                  //if (targeted_placement == &placement_a) targeted_placement = &placement_b;
                  //else targeted_placement = &placement_a;
               //break;

               case ALLEGRO_KEY_1: // Place the placement's top-most coordinate to the current cursor placement
                  targeted_placement->set_topmost_coordinate(my_y_cursor);
               break;

               case ALLEGRO_KEY_2: // Place the placement's right-most coordinate to the current cursor placement
                  targeted_placement->set_rightmost_coordinate(my_x_cursor);
               break;

               case ALLEGRO_KEY_3: // Place the placement's bottom-most coordinate to the current cursor placement
                  targeted_placement->set_bottommost_coordinate(my_y_cursor);
               break;

               case ALLEGRO_KEY_4: // Place the placement's left-most coordinate to the current cursor placement
                  targeted_placement->set_leftmost_coordinate(my_x_cursor);
               break;

               case ALLEGRO_KEY_TAB: // rotate the current targeted placement
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

               case ALLEGRO_KEY_PAD_6: // increase the targeted placement scale
                  my_x_cursor += my_cursor_speed;
                  if (my_x_cursor > 1920 - 10) my_x_cursor = 1920 - 10;
               break;

               case ALLEGRO_KEY_PAD_4: // increase the targeted placement scale
                  my_x_cursor -= my_cursor_speed;
                  if (my_x_cursor < 10) my_x_cursor = 10;
               break;

               case ALLEGRO_KEY_PAD_8: // increase the targeted placement scale
                  my_y_cursor -= my_cursor_speed;
                  if (my_y_cursor < 10) my_y_cursor = 10;
               break;

               case ALLEGRO_KEY_PAD_2: // increase the targeted placement scale
                  my_y_cursor += my_cursor_speed;
                  if (my_y_cursor > 1080 - 10) my_y_cursor = 1080 - 10;
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


