
#include <gtest/gtest.h>

#define EXPECT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_Elements_StopwatchTest : public ::testing::Test
{};

class AllegroFlare_Elements_StopwatchTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Elements/Stopwatch.hpp>


TEST_F(AllegroFlare_Elements_StopwatchTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::Stopwatch stopwatch;
}


TEST_F(AllegroFlare_Elements_StopwatchTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::Stopwatch stopwatch;
   std::string expected_error_message =
      "Stopwatch::render: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(stopwatch.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Elements_StopwatchTest, render__without_font_addon_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::Elements::Stopwatch stopwatch;
   std::string expected_error_message = "Stopwatch::render: error: guard \"al_is_font_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(stopwatch.render(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}


TEST_F(AllegroFlare_Elements_StopwatchTestWithAllegroRenderingFixture, render__without_a_font_bin__will_raise_an_error)
{
   AllegroFlare::Elements::Stopwatch stopwatch;
   std::string expected_error_message = "Stopwatch::render: error: guard \"font_bin\" not met";
   EXPECT_THROW_WITH_MESSAGE(stopwatch.render(), std::runtime_error, expected_error_message);
}


