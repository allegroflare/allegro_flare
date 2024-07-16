
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
      inventory.draw_item_selection_cursor();
      al_flip_display();
      //std::this_thread::sleep_for(std::chrono::milliseconds(1000/60));
   }
}


TEST_F(AllegroFlare_Elements_InventoryWithAllegroRenderingFixtureTest, render__does_not_blow_up)
{
   AllegroFlare::Inventory af_inventory;
   AllegroFlare::InventoryIndex index;
   AllegroFlare::Elements::Inventory inventory(&get_font_bin_ref(), &get_bitmap_bin_ref(), &af_inventory, &index);
   inventory.render();
}


TEST_F(AllegroFlare_Elements_InventoryWithAllegroRenderingFixtureTest,
   infer_item_boxes_width__returns_the_width_of_the_item_boxes_not_including_a_margin)
{
   // TODO
}


TEST_F(AllegroFlare_Elements_InventoryWithAllegroRenderingFixtureTest,
   infer_item_boxes_height__returns_the_height_of_the_item_boxes_not_including_a_margin)
{
   // TODO
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
   CAPTURE__render__with_non_default_design_configuration__will_render_as_expected)
{
   AllegroFlare::Inventory af_inventory;
   AllegroFlare::InventoryIndex index = AllegroFlare::InventoryIndex::build_placeholder_inventory_index();
   AllegroFlare::Elements::Inventory inventory(&get_font_bin_ref(), &get_bitmap_bin_ref(), &af_inventory, &index);
   af_inventory.add_items({ 1, 2, 3, 4 });

   // setup a custom configuration
   inventory.get_place_ref().size.x = 1920 - 180;
   inventory.get_place_ref().size.y = 1080 - 250;
   inventory.set_num_columns(4);
   inventory.set_num_rows(4);
   inventory.set_inventory_items_box_size_x(134);
   inventory.set_inventory_items_box_size_y(160);
   inventory.set_inventory_items_box_gutter_x(20);
   inventory.set_inventory_items_box_gutter_y(24);
   inventory.set_inventory_items_left_padding(20.0);
   inventory.set_inventory_items_top_padding(60.0);
   inventory.set_show_title_text(false);
   inventory.set_show_backframe(false);
   inventory.set_show_background(true);

   // TODO: ellaborate here

   inventory.activate();
   inventory.render();

   al_flip_display();
   //sleep_for(1);
}


TEST_F(AllegroFlare_Elements_InventoryWithAllegroRenderingFixtureTest,
   show__does_a_cool_animation)
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


TEST_F(AllegroFlare_Elements_InventoryWithAllegroRenderingFixtureTest,
   hide__does_a_cool_animation)
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
   set_num_rows__with_a_value_less_than_or_equal_to_zero__will_raise_an_exception)
{
   // TODO
}


TEST_F(AllegroFlare_Elements_InventoryWithAllegroRenderingFixtureTest,
   set_num_rows__will_set_the_number_of_rows)
{
   // TODO
}


TEST_F(AllegroFlare_Elements_InventoryWithAllegroRenderingFixtureTest,
   set_num_rows__will_reposition_the_cursor_to_0x_0y)
{
   // TODO
}

TEST_F(AllegroFlare_Elements_InventoryWithAllegroRenderingFixtureTest,
   set_num_rows__will_set_the_item_in_the_details_pane)
{
   // TODO
}


TEST_F(AllegroFlare_Elements_InventoryWithAllegroRenderingFixtureTest,
   set_num_columns__with_a_value_less_than_or_equal_to_zero__will_raise_an_exception)
{
   // TODO
}


TEST_F(AllegroFlare_Elements_InventoryWithAllegroRenderingFixtureTest,
   set_num_columns__will_set_the_number_of_columns)
{
   // TODO
}


TEST_F(AllegroFlare_Elements_InventoryWithAllegroRenderingFixtureTest,
   set_num_columns__will_reposition_the_cursor_to_0x_0y)
{
   // TODO
}

TEST_F(AllegroFlare_Elements_InventoryWithAllegroRenderingFixtureTest,
   set_num_columns__will_set_the_item_in_the_details_pane)
{
   // TODO
}


TEST_F(AllegroFlare_Elements_InventoryWithAllegroRenderingFixtureTest,
   moving_the_cursor__will_set_the_item_in_details_pane)
{
   // TODO
}


TEST_F(AllegroFlare_Elements_InventoryWithAllegroRenderingFixtureTest,
   moving_the_cursor__will_set_the_item_in_details_pane_at_to_the_current_time)
{
   // TODO
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
   inventory.disable_sound();
   inventory.activate();
   inventory.move_cursor_left();
   EXPECT_EQ(3, inventory.get_cursor_x());
}


TEST_F(AllegroFlare_Elements_InventoryWithAllegroRenderingFixtureTest,
   move_cursor_right__wraps_the_cursor_when_at_the_edge)
{
   AllegroFlare::Elements::Inventory inventory;
   inventory.disable_sound();
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
   inventory.disable_sound();
   inventory.activate();
   inventory.move_cursor_up();
   EXPECT_EQ(2, inventory.get_cursor_y());
}


TEST_F(AllegroFlare_Elements_InventoryWithAllegroRenderingFixtureTest,
   move_cursor_down__wraps_the_cursor_when_at_the_edge)
{
   AllegroFlare::Elements::Inventory inventory;
   inventory.disable_sound();
   inventory.activate();
   int num_columns = 3;
   for (unsigned i=0; i<(num_columns-1); i++) inventory.move_cursor_down();

   inventory.move_cursor_down();
   EXPECT_EQ(0, inventory.get_cursor_y());
}


#include <AllegroFlare/EventNames.hpp>
TEST_F(AllegroFlare_Elements_InventoryWithAllegroRenderingFixtureTest,
   FOCUS__CAPTURE__TIMED_INTERACTIVE__will_work_as_expected)
{
   al_install_keyboard();
   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
   ALLEGRO_TIMER *primary_timer = al_create_timer(ALLEGRO_BPS_TO_SECS(60));
   AllegroFlare::EventEmitter event_emitter;
   event_emitter.initialize();
   al_register_event_source(event_queue, al_get_timer_event_source(primary_timer));
   al_register_event_source(event_queue, al_get_keyboard_event_source());
   al_register_event_source(event_queue, &event_emitter.get_event_source_ref());

   AllegroFlare::Inventory af_inventory;
   AllegroFlare::InventoryIndex index = AllegroFlare::InventoryIndex::build_placeholder_inventory_index();
   AllegroFlare::Elements::Inventory inventory(
      &get_font_bin_ref(),
      &get_bitmap_bin_ref(),
      &af_inventory,
      &index,
      nullptr,
      &event_emitter
   );

   // NOTE: Items are added out of order
   af_inventory.add_item(4);
   af_inventory.add_item(1);
   //af_inventory.add_item(3);
   //af_inventory.add_item(3);
   //af_inventory.add_item(3);
   af_inventory.add_item(2);
   //af_inventory.add_item(3);
   //af_inventory.add_item(4);

   float duration_to_auto_abort_sec = 6;
   bool auto_abort_halted = false;
   ALLEGRO_FONT *prompt_font = get_user_prompt_font();

   al_start_timer(primary_timer);
   bool abort = false;
   while(!abort)
   {
      double time_now = al_get_time();
      ALLEGRO_EVENT current_event;
      al_wait_for_event(event_queue, &current_event);
      switch(current_event.type)
      {
         case ALLEGRO_EVENT_TIMER:
         {
            // Update
            inventory.update();
            if (!auto_abort_halted && (time_now >= duration_to_auto_abort_sec)) abort = true;

            // Render
            clear();
            inventory.render();
            if (!auto_abort_halted)
            {
               int seconds_left = (int)(duration_to_auto_abort_sec - time_now) + 1;
               al_draw_textf(prompt_font, ALLEGRO_COLOR{0.3, 0.3, 0.3, 1}, 30, 1080-60, ALLEGRO_ALIGN_LEFT, "Interactive "
                  "test will auto-close in %d seconds. Otherwise press any key.", seconds_left);
            }
            al_flip_display();
         }
         break;

         case ALLEGRO_FLARE_EVENT_PLAY_SOUND_EFFECT:
         {
            std::cout << "[AllegroFlare_Elements_InventoryWithAllegroRenderingFixtureTest]: INFO: "
                      << "Play sound effect event was emitted. "
                      << std::endl;
         }

         case ALLEGRO_EVENT_KEY_CHAR:
         {
            if (!auto_abort_halted) auto_abort_halted = true;

            switch(current_event.keyboard.keycode)
            {
               case ALLEGRO_KEY_A:
                  inventory.activate();
               break;

               case ALLEGRO_KEY_D:
                  inventory.deactivate();
               break;

               case ALLEGRO_KEY_S:
                  inventory.show();
               break;

               case ALLEGRO_KEY_H:
                  inventory.hide();
               break;

               case ALLEGRO_KEY_T:
                  inventory.toggle_show_hide();
               break;

               case ALLEGRO_KEY_UP:
                  inventory.move_cursor_up();
               break;

               case ALLEGRO_KEY_DOWN:
                  inventory.move_cursor_down();
               break;

               case ALLEGRO_KEY_LEFT:
                  inventory.move_cursor_left();
               break;

               case ALLEGRO_KEY_RIGHT:
                  inventory.move_cursor_right();
               break;

               case ALLEGRO_KEY_ESCAPE:
                  abort = true;
               break;
            }
         }
         break;
      }
   }

   al_unregister_event_source(event_queue, &event_emitter.get_event_source_ref());
   al_destroy_timer(primary_timer);
}


