
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
   AllegroFlare::Elements::HealthBars::Classic classic;
}


TEST_F(AllegroFlare_Elements_HealthBars_ClassicTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::HealthBars::Classic classic;
   std::string expected_error_message =
      "Classic::render: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(classic.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Elements_HealthBars_ClassicTestWithAllegroRenderingFixture,
   render__without_a_font_bin__will_throw_an_error)
{
   AllegroFlare::Elements::HealthBars::Classic classic;
   std::string expected_error_message = "Classic::obtain_font: error: guard \"font_bin\" not met";
   ASSERT_THROW_WITH_MESSAGE(classic.render(), std::runtime_error, expected_error_message);
   //AllegroFlare::Elements::HealthBars::Classic classic;
   //classic.render();
   //al_flip_display();
   //sleep(2);
   //SUCCEED();
}


TEST_F(AllegroFlare_Elements_HealthBars_ClassicTestWithAllegroRenderingFixture,
   render__will_draw_the_text_to_the_screen)
{
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();
   AllegroFlare::Elements::HealthBars::Classic classic(&font_bin);
   classic.render();
   al_flip_display();
   sleep(1);
   SUCCEED();
}


