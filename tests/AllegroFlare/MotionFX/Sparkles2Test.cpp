
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_MotionFX_Sparkles2Test : public ::testing::Test
{};

class AllegroFlare_MotionFX_Sparkles2TestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/MotionFX/Sparkles2.hpp>


TEST_F(AllegroFlare_MotionFX_Sparkles2Test, can_be_created_without_blowing_up)
{
   AllegroFlare::MotionFX::Sparkles2 sparkles2;
}


TEST_F(AllegroFlare_MotionFX_Sparkles2Test, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::MotionFX::Sparkles2 sparkles2;
   std::string expected_error_message =
      "Sparkles2::render: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(sparkles2.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_MotionFX_Sparkles2TestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   AllegroFlare::MotionFX::Sparkles2 sparkles2;
   sparkles2.initialize();
   sparkles2.render();
   SUCCEED();
}


TEST_F(AllegroFlare_MotionFX_Sparkles2TestWithAllegroRenderingFixture,
   DISABLED__VISUAL__render__will_render_an_animated_effect)
{
   AllegroFlare::MotionFX::Sparkles2 sparkles2(&get_font_bin_ref(), 1920/2, 1080/2);
   sparkles2.initialize();

   int passes = 60 * 3;
   for (int i=0; i<passes; i++)
   {
      sparkles2.update();

      clear();
      sparkles2.render();
      draw_crosshair(1920/2, 1080/2);
      al_flip_display();
   }
}

