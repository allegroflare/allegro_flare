
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
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
   EXPECT_THROW_WITH_MESSAGE(health_bar.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Elements_HealthBars_ClassicTestWithAllegroRenderingFixture,
   CAPTURE__render__will_draw_the_health_bar_to_the_screen)
{
   AllegroFlare::Elements::HealthBars::Classic health_bar(10, 6);
   health_bar.get_placement_ref().position = {200, 300};
   health_bar.render();
   al_flip_display();
   //sleep_for(1);
   SUCCEED();
}


TEST_F(AllegroFlare_Elements_HealthBars_ClassicTestWithAllegroRenderingFixture,
   calculate_width__will_return_the_width_of_the_entire_bar_when_rendered)
{
   AllegroFlare::Elements::HealthBars::Classic health_bar(10, 6);
   EXPECT_EQ(24*(10-1)+16, health_bar.calculate_width());

   health_bar.set_bar_spacing(36);
   health_bar.set_bar_width(30);
   EXPECT_EQ(36*(10-1)+30, health_bar.calculate_width());

   health_bar.set_max(1);
   EXPECT_EQ(30, health_bar.calculate_width());

   health_bar.set_max(0);
   EXPECT_EQ(0, health_bar.calculate_width());
}


