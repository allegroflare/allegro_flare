
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }


#include <AllegroFlare/Elements/Inventory.hpp>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>

#include <chrono>
#include <thread>

class AllegroFlare_Elements_InventoryTest : public ::testing::Test {};
class AllegroFlare_Elements_InventoryWithAllegroRenderingFixtureTest
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


TEST_F(AllegroFlare_Elements_InventoryTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::Inventory inventory;
}


TEST_F(AllegroFlare_Elements_InventoryWithAllegroRenderingFixtureTest, render__does_not_blow_up)
{
   AllegroFlare::Inventory af_inventory;
   AllegroFlare::InventoryIndex index;
   AllegroFlare::Elements::Inventory inventory(&get_font_bin_ref(), &get_bitmap_bin_ref(), &af_inventory, &index);
   inventory.render();
}


TEST_F(AllegroFlare_Elements_InventoryWithAllegroRenderingFixtureTest,
   CAPTURE__render__when_an_item_is_selected__renders_the_details_pane)
{
   AllegroFlare::Inventory af_inventory;
   AllegroFlare::InventoryIndex index = AllegroFlare::InventoryIndex::build_placeholder_inventory_index();
   AllegroFlare::Elements::Inventory inventory(&get_font_bin_ref(), &get_bitmap_bin_ref(), &af_inventory, &index);

   af_inventory.add_item(2);

   inventory.move_cursor_right();
   inventory.move_cursor_right();
   inventory.move_cursor_down();
   inventory.render();

   al_flip_display();
   //sleep_for(1);
}


TEST_F(AllegroFlare_Elements_InventoryWithAllegroRenderingFixtureTest,
   draw_item_selection_cursor__renders_an_animated_style)
{
   AllegroFlare::Inventory af_inventory;
   AllegroFlare::InventoryIndex index = AllegroFlare::InventoryIndex::build_placeholder_inventory_index();
   AllegroFlare::Elements::Inventory inventory(&get_font_bin_ref(), &get_bitmap_bin_ref(), &af_inventory, &index);

   af_inventory.add_item(2);

   //int passes = 60 * 2;
   int passes = 1;
   for (unsigned i=0; i<passes; i++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0.1, 0.1, 0.1, 1.0});
      inventory.draw_item_selection_cursor(1920/2, 1080/2);
      al_flip_display();
      //std::this_thread::sleep_for(std::chrono::milliseconds(1000/60));
   }
}


TEST_F(AllegroFlare_Elements_InventoryWithAllegroRenderingFixtureTest, show__does_a_cool_animation)
{
   AllegroFlare::Inventory af_inventory;
   AllegroFlare::InventoryIndex index = AllegroFlare::InventoryIndex::build_placeholder_inventory_index();
   AllegroFlare::Elements::Inventory inventory(&get_font_bin_ref(), &get_bitmap_bin_ref(), &af_inventory, &index);

   af_inventory.add_item(2);

   //int passes = 60 * 1;
   int passes = 1;
   inventory.show();
   for (unsigned i=0; i<passes; i++)
   {
      inventory.update();

      al_clear_to_color(ALLEGRO_COLOR{0.1, 0.1, 0.1, 1.0});
      //al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
      inventory.render();
      al_flip_display();
      //std::this_thread::sleep_for(std::chrono::milliseconds(1000/60));
   }
}


TEST_F(AllegroFlare_Elements_InventoryWithAllegroRenderingFixtureTest, hide__does_a_cool_animation)
{
   AllegroFlare::Inventory af_inventory;
   AllegroFlare::InventoryIndex index = AllegroFlare::InventoryIndex::build_placeholder_inventory_index();
   AllegroFlare::Elements::Inventory inventory(&get_font_bin_ref(), &get_bitmap_bin_ref(), &af_inventory, &index);

   af_inventory.add_item(2);

   //int passes = 60 * 1;
   int passes = 1;
   inventory.activate();
   inventory.hide();
   for (unsigned i=0; i<passes; i++)
   {
      inventory.update();

      al_clear_to_color(ALLEGRO_COLOR{0.1, 0.1, 0.1, 1.0});
      //al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
      inventory.render();
      al_flip_display();
      //std::this_thread::sleep_for(std::chrono::milliseconds(1000/60));
   }
}


TEST_F(AllegroFlare_Elements_InventoryWithAllegroRenderingFixtureTest,
   CAPTURE__moving_the_cursor__animates_the_details_pane)
{
   AllegroFlare::Inventory af_inventory;
   AllegroFlare::InventoryIndex index = AllegroFlare::InventoryIndex::build_placeholder_inventory_index();
   AllegroFlare::Elements::Inventory inventory(&get_font_bin_ref(), &get_bitmap_bin_ref(), &af_inventory, &index);

   af_inventory.add_item(1);
   af_inventory.add_item(2);
   af_inventory.add_item(3);
   af_inventory.add_item(4);

   //int passes = 60 * 2;
   int passes = 1;
   inventory.activate();
   float passes_to_move_cursor = 20;
   for (unsigned i=0; i<passes; i++)
   {
      passes_to_move_cursor--;
      if (passes_to_move_cursor < 0)
      {
         passes_to_move_cursor = 40;
         inventory.move_cursor_right();
      }
      inventory.update();

      al_clear_to_color(ALLEGRO_COLOR{0.1, 0.1, 0.11, 1.0});
      inventory.render();
      al_flip_display();
      std::this_thread::sleep_for(std::chrono::milliseconds(1000/60));
   }
}


TEST_F(AllegroFlare_Elements_InventoryTest,
   the_move_cursor_functions_do_not_modify_anything_if_the_inventory_is_inactive)
{
   AllegroFlare::Elements::Inventory inventory;
   inventory.move_cursor_left();
   EXPECT_EQ(0, inventory.get_cursor_x());
   inventory.move_cursor_right();
   EXPECT_EQ(0, inventory.get_cursor_x());
   inventory.move_cursor_up();
   EXPECT_EQ(0, inventory.get_cursor_y());
   inventory.move_cursor_down();
   EXPECT_EQ(0, inventory.get_cursor_y());
}


TEST_F(AllegroFlare_Elements_InventoryTest, move_cursor_left__wraps_the_cursor_when_at_the_edge)
{
   AllegroFlare::Elements::Inventory inventory;
   inventory.activate();
   inventory.move_cursor_left();
   EXPECT_EQ(3, inventory.get_cursor_x());
}


TEST_F(AllegroFlare_Elements_InventoryWithAllegroRenderingFixtureTest,
   move_cursor_right__wraps_the_cursor_when_at_the_edge)
{
   AllegroFlare::Elements::Inventory inventory;
   inventory.activate();
   int num_rows = 4;
   for (unsigned i=0; i<(num_rows-1); i++) inventory.move_cursor_right();

   inventory.move_cursor_right();

   EXPECT_EQ(0, inventory.get_cursor_x());
}


TEST_F(AllegroFlare_Elements_InventoryWithAllegroRenderingFixtureTest,
   move_cursor_up__wraps_the_cursor_when_at_the_edge)
{
   AllegroFlare::Elements::Inventory inventory;
   inventory.activate();
   inventory.move_cursor_up();
   EXPECT_EQ(2, inventory.get_cursor_y());
}


TEST_F(AllegroFlare_Elements_InventoryWithAllegroRenderingFixtureTest,
   move_cursor_down__wraps_the_cursor_when_at_the_edge)
{
   AllegroFlare::Elements::Inventory inventory;
   inventory.activate();
   int num_columns = 3;
   for (unsigned i=0; i<(num_columns-1); i++) inventory.move_cursor_down();

   inventory.move_cursor_down();
   EXPECT_EQ(0, inventory.get_cursor_y());
}


#include <AllegroFlare/Color.hpp>
TEST_F(AllegroFlare_Elements_InventoryWithAllegroRenderingFixtureTest,
   INTERACTIVE__collides__will_return_true_if_the_placement_collides_with_another_placement)
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


