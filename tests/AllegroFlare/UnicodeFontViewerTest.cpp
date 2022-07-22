
#include <gtest/gtest.h>

#define EXPECT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_UnicodeFontViewerTest : public ::testing::Test
{};

class AllegroFlare_UnicodeFontViewerTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/UnicodeFontViewer.hpp>


TEST_F(AllegroFlare_UnicodeFontViewerTest, can_be_created_without_blowing_up)
{
   AllegroFlare::UnicodeFontViewer unicode_font_viewer;
}


TEST_F(AllegroFlare_UnicodeFontViewerTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::UnicodeFontViewer unicode_font_viewer;
   std::string expected_error_message =
      "UnicodeFontViewer::render: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(unicode_font_viewer.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_UnicodeFontViewerTest, render__without_font_addon_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::UnicodeFontViewer unicode_font_viewer;
   std::string expected_error_message =
      "UnicodeFontViewer::render: error: guard \"al_is_font_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(unicode_font_viewer.render(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}


TEST_F(AllegroFlare_UnicodeFontViewerTest, render__without_ttf_addon_initialized__raises_an_error)
{
   al_init();
   al_init_font_addon();
   AllegroFlare::UnicodeFontViewer unicode_font_viewer;
   std::string expected_error_message =
      "UnicodeFontViewer::render: error: guard \"al_is_ttf_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(unicode_font_viewer.render(), std::runtime_error, expected_error_message);
   al_shutdown_font_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_UnicodeFontViewerTest, render__without_a_font_bin__raises_an_error)
{
   al_init();
   al_init_font_addon();
   al_init_ttf_addon();
   AllegroFlare::UnicodeFontViewer unicode_font_viewer;
   std::string expected_error_message =
      "UnicodeFontViewer::render: error: guard \"font_bin\" not met";
   EXPECT_THROW_WITH_MESSAGE(unicode_font_viewer.render(), std::runtime_error, expected_error_message);
   al_shutdown_ttf_addon();
   al_shutdown_font_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_UnicodeFontViewerTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();
   AllegroFlare::UnicodeFontViewer unicode_font_viewer(&font_bin, "Bravura.otf", 0x1D100);

   al_clear_to_color({0});

   unicode_font_viewer.render();

   al_flip_display();
   sleep(1);

   SUCCEED();
}


