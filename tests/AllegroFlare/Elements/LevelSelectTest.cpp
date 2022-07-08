
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }


#include <AllegroFlare/Elements/LevelSelect.hpp>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>

#include <chrono>
#include <thread>
static void SHOW_RENDER(int seconds=1) { al_flip_display(); std::this_thread::sleep_for(std::chrono::seconds(seconds)); }
#include <AllegroFlare/EventNames.hpp>

class AllegroFlare_Elements_LevelSelectTest : public ::testing::Test {};
class AllegroFlare_Elements_LevelSelectWithAllegroRenderingFixtureTest : public AllegroFlare::Testing::WithAllegroRenderingFixture {};


TEST_F(AllegroFlare_Elements_LevelSelectTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::LevelSelect level_select;
}


TEST_F(AllegroFlare_Elements_LevelSelectTest, DISABLED__TODOs)
{
   // assert errors thrown
   // assert event emitted
}


TEST_F(AllegroFlare_Elements_LevelSelectWithAllegroRenderingFixtureTest, render__does_not_blow_up)
{
   AllegroFlare::EventEmitter event_emitter;
   AllegroFlare::Elements::LevelSelect level_select(&event_emitter, &get_font_bin_ref());
   level_select.render();
}


TEST_F(AllegroFlare_Elements_LevelSelectWithAllegroRenderingFixtureTest, render__displays_the_level_select_window)
{
   AllegroFlare::EventEmitter event_emitter;
   std::vector<std::pair<std::string, std::string>> levels_list = {
      { "1", "1" },
      { "2", "2" },
      { "3", "3" },
      { "4", "4" },
      { "5", "5" },
      { "6", "6" },
      { "7", "7" },
      { "8", "8" },
      { "9", "9" },
   };
   AllegroFlare::Elements::LevelSelect level_select(&event_emitter, &get_font_bin_ref(), levels_list);
   level_select.render();
   //SHOW_RENDER();
}


TEST_F(AllegroFlare_Elements_LevelSelectWithAllegroRenderingFixtureTest,
   DISABLED__draw_selection_cursor__renders_an_animated_style)
{
   AllegroFlare::EventEmitter event_emitter;
   std::vector<std::pair<std::string, std::string>> levels_list;
   AllegroFlare::Elements::LevelSelect level_select(&event_emitter, &get_font_bin_ref(), levels_list);
   int passes = 60 * 2;
   //int passes = 0;
   for (int i=0; i<passes; i++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0.1, 0.1, 0.1, 1.0});
      level_select.draw_selection_cursor(1920/2, 1080/2);
      al_flip_display();
      std::this_thread::sleep_for(std::chrono::milliseconds(1000/60));
   }
}


TEST_F(AllegroFlare_Elements_LevelSelectTest, move_cursor_left__wraps_the_cursor_when_at_the_edge)
{
   AllegroFlare::Elements::LevelSelect level_select;
   level_select.move_cursor_left();
   EXPECT_EQ(level_select.get_num_columns()-1, level_select.get_cursor_x());
}


TEST_F(AllegroFlare_Elements_LevelSelectWithAllegroRenderingFixtureTest,
   move_cursor_right__wraps_the_cursor_when_at_the_edge)
{
   AllegroFlare::Elements::LevelSelect level_select;
   int num_columns = level_select.get_num_columns();
   for (int i=0; i<(num_columns-1); i++) level_select.move_cursor_right();

   level_select.move_cursor_right();

   EXPECT_EQ(0, level_select.get_cursor_x());
}


TEST_F(AllegroFlare_Elements_LevelSelectWithAllegroRenderingFixtureTest,
   move_cursor_up__wraps_the_cursor_when_at_the_edge)
{
   AllegroFlare::Elements::LevelSelect level_select;
   level_select.move_cursor_up();
   EXPECT_EQ(2, level_select.get_cursor_y());
}


TEST_F(AllegroFlare_Elements_LevelSelectWithAllegroRenderingFixtureTest,
   move_cursor_down__wraps_the_cursor_when_at_the_edge)
{
   AllegroFlare::Elements::LevelSelect level_select;
   int num_rows = level_select.get_num_rows();
   for (int i=0; i<(num_rows-1); i++) level_select.move_cursor_down();

   level_select.move_cursor_down();
   EXPECT_EQ(0, level_select.get_cursor_y());
}


TEST_F(AllegroFlare_Elements_LevelSelectTest,
   DISABLED__activate_selected_menu_option__without_an_event_emitter__will_throw_an_error)
{
   // TODO
}


TEST_F(AllegroFlare_Elements_LevelSelectTest,
   DISABLED__activate_selected_menu_option__with_an_empty_list_of_levels__will_output_an_error_message)
{
   // TODO
}


TEST_F(AllegroFlare_Elements_LevelSelectTest,
   DISABLED__activate_selected_menu_option__with_a_selection_that_is_empty__will_output_an_error_message)
{
   // TODO
}


TEST_F(AllegroFlare_Elements_LevelSelectWithAllegroRenderingFixtureTest,
   DISABLED__activate_selected_menu_option__will_emit_an_ALLEGRO_FLARE_EVENT_SELECT_LEVEL_witH_the_expected_values)
{
   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
   AllegroFlare::EventEmitter event_emitter;
   event_emitter.initialize();
   al_register_event_source(event_queue, &event_emitter.get_event_source_ref());
   std::vector<std::pair<std::string, std::string>> levels_list = {
      { "Sunny Meadow",   "level1" },
      { "Watery Willows", "level2" },
      { "Fluffy Forest",  "level3" },
      { "Heated Desert",  "level4" },
   };
   AllegroFlare::Elements::LevelSelect level_select(&event_emitter, &get_font_bin_ref(), levels_list);

   level_select.activate_selected_menu_option();

   ALLEGRO_EVENT event;
   ASSERT_EQ(true, al_peek_next_event(event_queue, &event));
   std::string *value = nullptr;

   EXPECT_EQ(ALLEGRO_FLARE_EVENT_SELECT_LEVEL, event.any.type);
   ASSERT_NE(nullptr, (void *)event.user.data1);
   EXPECT_NE("level1", *(std::string*)(void*)event.user.data1);

   delete value;
}


