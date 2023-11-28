#include <gtest/gtest.h>

#define EXPECT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_Elements_WorldMapViewerTest : public ::testing::Test {};
class AllegroFlare_Elements_WorldMapViewerTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Elements/WorldMapViewer.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();


TEST_F(AllegroFlare_Elements_WorldMapViewerTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::WorldMapViewer crime_summary;
}


//TEST_F(AllegroFlare_Elements_WorldMapViewerTest, TYPE__has_the_expected_value)
//{
   //AllegroFlare::Elements::WorldMapViewer crime_summary;
   //EXPECT_EQ("WorldMapViewer", crime_summary.get_type());
//}


//TEST_F(AllegroFlare_Elements_WorldMapViewerTest, type__has_the_expected_value_matching_TYPE)
//{
   //AllegroFlare::Elements::WorldMapViewer crime_summary;
   //EXPECT_EQ(AllegroFlare::Elements::WorldMapViewer::TYPE, crime_summary.get_type());
//}


TEST_F(AllegroFlare_Elements_WorldMapViewerTest, initialize__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::WorldMapViewer crime_summary;
   std::string expected_error_message =
      "WorldMapViewer::initialize: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(crime_summary.initialize(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Elements_WorldMapViewerTest, initialize__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::Elements::WorldMapViewer crime_summary;
   std::string expected_error_message =
      "WorldMapViewer::initialize: error: guard \"al_is_primitives_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(crime_summary.initialize(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}


TEST_F(AllegroFlare_Elements_WorldMapViewerTest, initialize__without_font_addon_initialized__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   AllegroFlare::Elements::WorldMapViewer crime_summary;
   std::string expected_error_message =
      "WorldMapViewer::initialize: error: guard \"al_is_font_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(crime_summary.initialize(), std::runtime_error, expected_error_message);
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_Elements_WorldMapViewerTest, initialize__without_ttf_addon_initialized__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   AllegroFlare::Elements::WorldMapViewer crime_summary;
   std::string expected_error_message =
      "WorldMapViewer::initialize: error: guard \"al_is_ttf_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(crime_summary.initialize(), std::runtime_error, expected_error_message);
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_Elements_WorldMapViewerTest, initialize__without_a_bitmap_bin__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   al_init_ttf_addon();
   AllegroFlare::Elements::WorldMapViewer crime_summary;
   std::string expected_error_message =
      "WorldMapViewer::initialize: error: guard \"bitmap_bin\" not met";
   EXPECT_THROW_WITH_MESSAGE(crime_summary.initialize(), std::runtime_error, expected_error_message);
   al_shutdown_font_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_Elements_WorldMapViewerTest, initialize__without_a_font_bin__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   al_init_ttf_addon();
   AllegroFlare::BitmapBin bitmap_bin;
   AllegroFlare::Elements::WorldMapViewer crime_summary(&bitmap_bin);
   std::string expected_error_message =
      "WorldMapViewer::initialize: error: guard \"font_bin\" not met";
   EXPECT_THROW_WITH_MESSAGE(crime_summary.initialize(), std::runtime_error, expected_error_message);
   al_shutdown_font_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_Elements_WorldMapViewerTestWithAllegroRenderingFixture,
   render__before_initialization__witl_throw_an_error)
{
   AllegroFlare::Elements::WorldMapViewer crime_summary(&get_bitmap_bin_ref(), &get_font_bin_ref());
   std::string expected_error_message =
      "WorldMapViewer::render: error: guard \"initialized\" not met";
   EXPECT_THROW_WITH_MESSAGE(crime_summary.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Elements_WorldMapViewerTestWithAllegroRenderingFixture,
   CAPTURE__render__when_there_are_no_pages__will_render_an_empty_text)
{
   get_bitmap_bin_ref().set_full_path("/Users/markoates/Repos/AllegroFlare/bin/data/bitmaps");
   AllegroFlare::Elements::WorldMapViewer crime_summary(&get_bitmap_bin_ref(), &get_font_bin_ref());
   crime_summary.initialize();
   crime_summary.render();
   al_flip_display();
   //sleep_for(1);
}


TEST_F(AllegroFlare_Elements_WorldMapViewerTestWithAllegroRenderingFixture,
   set_pages__will_set_the_pages)
{
   // TODO
}


TEST_F(AllegroFlare_Elements_WorldMapViewerTestWithAllegroRenderingFixture,
   set_pages__will_reset_the_document_camera_to_the_initial_zoom_and_position)
{
   // TODO
}


TEST_F(AllegroFlare_Elements_WorldMapViewerTestWithAllegroRenderingFixture,
   set_pages__will_fit_and_position_pages)
{
   // TODO
}


TEST_F(AllegroFlare_Elements_WorldMapViewerTestWithAllegroRenderingFixture, CAPTURE__render__will_not_blow_up)
{
   get_bitmap_bin_ref().set_full_path("/Users/markoates/Repos/AllegroFlare/bin/data/bitmaps");
   AllegroFlare::Elements::WorldMapViewer crime_summary(&get_bitmap_bin_ref(), &get_font_bin_ref());
   crime_summary.set_pages({
      { "crime-summary-pages-p1-01.png" },
      { "crime-summary-pages-p2-01.png" },
      { "crime-summary-pages-p3-01.png" },
   });
   crime_summary.initialize();
   clear();
   crime_summary.render();
   al_flip_display();
}


TEST_F(AllegroFlare_Elements_WorldMapViewerTestWithAllegroRenderingFixture,
   CAPTURE__VISUAL__page_next__will_move_to_the_next_page)
{
   get_bitmap_bin_ref().set_full_path("/Users/markoates/Repos/AllegroFlare/bin/data/bitmaps");
   AllegroFlare::Elements::WorldMapViewer crime_summary(&get_bitmap_bin_ref(), &get_font_bin_ref());
   crime_summary.set_pages({
      { "crime-summary-pages-p1-02.png" },
      { "crime-summary-pages-p2-02.png" },
      { "crime-summary-pages-p3-02.png" },
   });
   crime_summary.initialize();

   int page_flips = 4;
   for (int i=0; i<page_flips; i++)
   {
      clear();
      crime_summary.render();
      al_flip_display();
      sleep_for(0.01);

      crime_summary.page_next();
   }
}


TEST_F(AllegroFlare_Elements_WorldMapViewerTestWithAllegroRenderingFixture,
   CAPTURE__VISUAL__page_previous__will_move_to_the_previous_page)
{
   get_bitmap_bin_ref().set_full_path("/Users/markoates/Repos/AllegroFlare/bin/data/bitmaps");
   AllegroFlare::Elements::WorldMapViewer crime_summary(&get_bitmap_bin_ref(), &get_font_bin_ref());
   crime_summary.set_pages({
      { "crime-summary-pages-p1-02.png" },
      { "crime-summary-pages-p2-02.png" },
      { "crime-summary-pages-p3-02.png" },
   });
   crime_summary.initialize();

   int page_flips = 4;
   for (int i=0; i<page_flips; i++)
   {
      clear();
      crime_summary.render();
      al_flip_display();
      sleep_for(0.01);

      crime_summary.page_previous();
   }
}


TEST_F(AllegroFlare_Elements_WorldMapViewerTestWithAllegroRenderingFixture,
   CAPTURE__VISUAL__step_zoom_in__will_zoom_in_the_camera_by_one_step__and_loop_back_when_at_the_edge)
{
   get_bitmap_bin_ref().set_full_path("/Users/markoates/Repos/AllegroFlare/bin/data/bitmaps");
   AllegroFlare::Elements::WorldMapViewer crime_summary(&get_bitmap_bin_ref(), &get_font_bin_ref());
   crime_summary.set_pages({
      { "crime-summary-pages-p1-02.png" },
      { "crime-summary-pages-p2-02.png" },
      { "crime-summary-pages-p3-02.png" },
   });
   crime_summary.initialize();

   int zooms = 5;
   for (int i=0; i<zooms; i++)
   {
      crime_summary.step_zoom_in();
      crime_summary.update();

      clear();
      crime_summary.render();
      al_flip_display();
      sleep_for(0.01);
   }
}


TEST_F(AllegroFlare_Elements_WorldMapViewerTestWithAllegroRenderingFixture,
   CAPTURE__VISUAL__step_zoom_out__will_zoom_out_the_camera_by_one_step__and_loop_back_when_at_the_edge)
{
   get_bitmap_bin_ref().set_full_path("/Users/markoates/Repos/AllegroFlare/bin/data/bitmaps");
   AllegroFlare::Elements::WorldMapViewer crime_summary(&get_bitmap_bin_ref(), &get_font_bin_ref());
   crime_summary.set_pages({
      { "crime-summary-pages-p1-02.png" },
      { "crime-summary-pages-p2-02.png" },
      { "crime-summary-pages-p3-02.png" },
   });
   crime_summary.initialize();

   int zooms = 6;
   for (int i=0; i<zooms; i++)
   {
      crime_summary.step_zoom_out();
      crime_summary.update();

      clear();
      crime_summary.render();
      al_flip_display();
      sleep_for(0.01);
   }
}


TEST_F(AllegroFlare_Elements_WorldMapViewerTestWithAllegroRenderingFixture,
   CAPTURE__VISUAL__if_the_display_dimensions_are_different_from_virtual_dimensions_of_1920x1080__will_clip_properly)
{
   // TODO
}


