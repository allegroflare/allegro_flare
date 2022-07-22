
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
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
   ASSERT_THROW_WITH_MESSAGE(unicode_font_viewer.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_UnicodeFontViewerTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   AllegroFlare::UnicodeFontViewer unicode_font_viewer;
   unicode_font_viewer.render();
   SUCCEED();
}

