
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_Elements_HealthBars_HeartsTest : public ::testing::Test
{};

class AllegroFlare_Elements_HealthBars_HeartsTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Elements/HealthBars/Hearts.hpp>


TEST_F(AllegroFlare_Elements_HealthBars_HeartsTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::HealthBars::Hearts health_bar;
}


TEST_F(AllegroFlare_Elements_HealthBars_HeartsTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::HealthBars::Hearts health_bar;
   std::string expected_error_message = "Hearts::render: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(health_bar.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Elements_HealthBars_HeartsTest, render__without_font_addon_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::Elements::HealthBars::Hearts health_bar;
   std::string expected_error_message = "Hearts::render: error: guard \"al_is_font_addon_initialized()\" not met";
   ASSERT_THROW_WITH_MESSAGE(health_bar.render(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}


TEST_F(AllegroFlare_Elements_HealthBars_HeartsTest, render__without_ttf_addon_initialized__raises_an_error)
{
   al_init();
   al_init_font_addon();
   AllegroFlare::Elements::HealthBars::Hearts health_bar;
   std::string expected_error_message = "Hearts::render: error: guard \"al_is_ttf_addon_initialized()\" not met";
   ASSERT_THROW_WITH_MESSAGE(health_bar.render(), std::runtime_error, expected_error_message);
   al_shutdown_ttf_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_Elements_HealthBars_HeartsTestWithAllegroRenderingFixture,
   render__will_draw_the_health_bar_to_the_screen)
{
   AllegroFlare::Elements::HealthBars::Hearts health_bar(&get_font_bin_ref(), 10, 6);
   health_bar.get_placement_ref().position = {200, 300};
   health_bar.render();
   al_flip_display();
   sleep(1);
   SUCCEED();
}

