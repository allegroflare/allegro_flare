
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_Elements_HealthBars_ClassicTest : public ::testing::Test
{};

class AllegroFlare_Elements_HealthBars_ClassicTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Elements/HealthBars/Classic.hpp>


TEST_F(AllegroFlare_Elements_HealthBars_ClassicTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::HealthBars::Classic health_bar;
}


TEST_F(AllegroFlare_Elements_HealthBars_ClassicTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::HealthBars::Classic health_bar;
   std::string expected_error_message = "Classic::render: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(health_bar.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Elements_HealthBars_ClassicTestWithAllegroRenderingFixture,
   render__will_draw_the_health_bar_to_the_screen)
{
   AllegroFlare::Elements::HealthBars::Classic health_bar(10, 6);
   health_bar.get_placement_ref().position = {200, 300};
   health_bar.render();
   al_flip_display();
   sleep(1);
   SUCCEED();
}


