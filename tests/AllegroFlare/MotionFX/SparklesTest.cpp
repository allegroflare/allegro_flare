
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_MotionFX_SparklesTest : public ::testing::Test
{};

class AllegroFlare_MotionFX_SparklesTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/MotionFX/Sparkles.hpp>


TEST_F(AllegroFlare_MotionFX_SparklesTest, can_be_created_without_blowing_up)
{
   AllegroFlare::MotionFX::Sparkles sparkles;
}


TEST_F(AllegroFlare_MotionFX_SparklesTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::MotionFX::Sparkles sparkles;
   std::string expected_error_message =
      "Sparkles::render: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(sparkles.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_MotionFX_SparklesTest, render__before_initialization__raises_an_error)
{
}


TEST_F(AllegroFlare_MotionFX_SparklesTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   AllegroFlare::MotionFX::Sparkles sparkles(&get_font_bin_ref());
   sparkles.initialize();
   sparkles.render();
}


TEST_F(AllegroFlare_MotionFX_SparklesTestWithAllegroRenderingFixture, VISUAL__render__will_render_an_animated_effect)
{
   AllegroFlare::MotionFX::Sparkles sparkles(&get_font_bin_ref(), 1920/2, 1080/2);
   sparkles.initialize();

   int passes = 60 * 3;
   for (int i=0; i<passes; i++)
   {
      sparkles.update();

      clear();
      sparkles.render();
      draw_crosshair(1920/2, 1080/2);
      al_flip_display();
   }
}


