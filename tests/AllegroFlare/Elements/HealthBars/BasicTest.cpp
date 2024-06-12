
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_Elements_HealthBars_BasicTest : public ::testing::Test
{};

class AllegroFlare_Elements_HealthBars_BasicTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Elements/HealthBars/Basic.hpp>


TEST_F(AllegroFlare_Elements_HealthBars_BasicTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::HealthBars::Basic health_bar;
}


TEST_F(AllegroFlare_Elements_HealthBars_BasicTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::HealthBars::Basic health_bar;
   std::string expected_error_message = "Basic::render: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(health_bar.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Elements_HealthBars_BasicTestWithAllegroRenderingFixture,
   CAPTURE__render__will_draw_the_health_bar_to_the_screen)
{
   AllegroFlare::Elements::HealthBars::Basic health_bar(0.6);
   health_bar.get_placement_ref().position = {200, 300};
   health_bar.render();
   al_flip_display();
   //sleep_for(1);
   SUCCEED();
}

