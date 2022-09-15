
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }


#include <Wicked/Inventory.hpp>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>

#include <chrono>
#include <thread>
static void SHOW_RENDER(int seconds=1)
{
   al_flip_display(); std::this_thread::sleep_for(std::chrono::seconds(seconds));
}
//static void SLEEP_FOR_VIEW(int milliseconds=1000/60) { std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds)); }
static void SLEEP_FOR_VIEW(int milliseconds=0)
{
   std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

static void SKIP_FOR_FASTER_BUILD()
{
   GTEST_SKIP() << "Test is skipped for a faster build";
}


//bool diabled_for_a_faster_build = true;


class Wicked_InventoryTest : public ::testing::Test {};
class Wicked_InventoryWithAllegroRenderingFixtureTest : public AllegroFlare::Testing::WithAllegroRenderingFixture {};


TEST_F(Wicked_InventoryTest, can_be_created_without_blowing_up)
{
   Wicked::Inventory inventory;
}


TEST_F(Wicked_InventoryWithAllegroRenderingFixtureTest, render__does_not_blow_up)
{
   AllegroFlare::Inventory af_inventory;
   Wicked::Inventory inventory(&get_font_bin_ref(), &get_bitmap_bin_ref(), &af_inventory);
   inventory.render();
}


TEST_F(Wicked_InventoryWithAllegroRenderingFixtureTest, render__displays_the_inventory_window)
{
   GTEST_SKIP();

   AllegroFlare::Inventory af_inventory;
   Wicked::Inventory inventory(&get_font_bin_ref(), &get_bitmap_bin_ref(), &af_inventory);
   inventory.render();
   SHOW_RENDER();
}


TEST_F(Wicked_InventoryWithAllegroRenderingFixtureTest, render__when_an_item_is_selected__renders_the_details_pane)
{
   GTEST_SKIP();

   AllegroFlare::Inventory af_inventory;
   af_inventory.add_item(2);
   Wicked::Inventory inventory(&get_font_bin_ref(), &get_bitmap_bin_ref(), &af_inventory);
   inventory.move_cursor_right();
   inventory.move_cursor_right();
   inventory.move_cursor_down();
   inventory.render();
   SHOW_RENDER();
}


TEST_F(Wicked_InventoryWithAllegroRenderingFixtureTest, draw_item_selection_cursor__renders_an_animated_style)
{
   GTEST_SKIP();

   AllegroFlare::Inventory af_inventory;
   af_inventory.add_item(2);
   Wicked::Inventory inventory(&get_font_bin_ref(), &get_bitmap_bin_ref(), &af_inventory);
   int passes = 60 * 2;
   //int passes = 0;
   for (unsigned i=0; i<passes; i++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0.1, 0.1, 0.1, 1.0});
      inventory.draw_item_selection_cursor(1920/2, 1080/2);
      al_flip_display();
      SLEEP_FOR_VIEW();
   }
}

TEST_F(Wicked_InventoryWithAllegroRenderingFixtureTest, show__does_a_cool_animation)
{
   GTEST_SKIP();

   AllegroFlare::Inventory af_inventory;
   af_inventory.add_item(2);
   Wicked::Inventory inventory(&get_font_bin_ref(), &get_bitmap_bin_ref(), &af_inventory);
   int passes = 60 * 1;
   //int passes = 0;
   inventory.show();
   for (unsigned i=0; i<passes; i++)
   {
      inventory.update();

      al_clear_to_color(ALLEGRO_COLOR{0.1, 0.1, 0.1, 1.0});
      //al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
      inventory.render();
      al_flip_display();
      SLEEP_FOR_VIEW();
   }
}

TEST_F(Wicked_InventoryWithAllegroRenderingFixtureTest, hide__does_a_cool_animation)
{
   GTEST_SKIP();

   AllegroFlare::Inventory af_inventory;
   af_inventory.add_item(2);
   Wicked::Inventory inventory(&get_font_bin_ref(), &get_bitmap_bin_ref(), &af_inventory);
   int passes = 60 * 1;
   //int passes = 0;
   inventory.activate();
   inventory.hide();
   for (unsigned i=0; i<passes; i++)
   {
      inventory.update();

      al_clear_to_color(ALLEGRO_COLOR{0.1, 0.1, 0.1, 1.0});
      //al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
      inventory.render();
      al_flip_display();
      SLEEP_FOR_VIEW();
   }
}

TEST_F(Wicked_InventoryWithAllegroRenderingFixtureTest, moving_the_cursor__animates_the_details_pane)
{
   GTEST_SKIP();

   AllegroFlare::Inventory af_inventory;
   af_inventory.add_item(2);
   af_inventory.add_item(1);
   Wicked::Inventory inventory(&get_font_bin_ref(), &get_bitmap_bin_ref(), &af_inventory);
   int passes = 60 * 3;
   //int passes = 0;
   inventory.activate();
   float passes_to_move_cursor = 20;
   for (unsigned i=0; i<passes; i++)
   {
      passes_to_move_cursor--;
      if (passes_to_move_cursor < 0)
      {
         passes_to_move_cursor = 70;
         inventory.move_cursor_right();
      }
      inventory.update();

      al_clear_to_color(ALLEGRO_COLOR{0.1, 0.1, 0.1, 1.0});
      //al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
      inventory.render();
      al_flip_display();
      SLEEP_FOR_VIEW();
   }
}

TEST_F(Wicked_InventoryTest, the_move_cursor_functions_do_not_modify_anything_if_the_inventory_is_inactive)
{
   GTEST_SKIP();

   Wicked::Inventory inventory;
   inventory.move_cursor_left();
   EXPECT_EQ(0, inventory.get_cursor_x());
   inventory.move_cursor_right();
   EXPECT_EQ(0, inventory.get_cursor_x());
   inventory.move_cursor_up();
   EXPECT_EQ(0, inventory.get_cursor_y());
   inventory.move_cursor_down();
   EXPECT_EQ(0, inventory.get_cursor_y());
}

TEST_F(Wicked_InventoryTest, move_cursor_left__wraps_the_cursor_when_at_the_edge)
{
   GTEST_SKIP();

   Wicked::Inventory inventory;
   inventory.activate();
   inventory.move_cursor_left();
   EXPECT_EQ(3, inventory.get_cursor_x());
}

TEST_F(Wicked_InventoryWithAllegroRenderingFixtureTest, move_cursor_right__wraps_the_cursor_when_at_the_edge)
{
   GTEST_SKIP();

   Wicked::Inventory inventory;
   inventory.activate();
   int num_rows = 4;
   for (unsigned i=0; i<(num_rows-1); i++) inventory.move_cursor_right();

   inventory.move_cursor_right();

   EXPECT_EQ(0, inventory.get_cursor_x());
}

TEST_F(Wicked_InventoryWithAllegroRenderingFixtureTest, move_cursor_up__wraps_the_cursor_when_at_the_edge)
{
   GTEST_SKIP();

   Wicked::Inventory inventory;
   inventory.activate();
   inventory.move_cursor_up();
   EXPECT_EQ(2, inventory.get_cursor_y());
}

TEST_F(Wicked_InventoryWithAllegroRenderingFixtureTest, move_cursor_down__wraps_the_cursor_when_at_the_edge)
{
   GTEST_SKIP();

   Wicked::Inventory inventory;
   inventory.activate();
   int num_rows = 3;
   for (unsigned i=0; i<(num_rows-1); i++) inventory.move_cursor_down();

   inventory.move_cursor_down();
   EXPECT_EQ(0, inventory.get_cursor_y());
}



