
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Logger.hpp>


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
   std::string expected_error_message = AllegroFlare::Logger::build_guard_error_message(
      "AllegroFlare::MotionFX::Sparkles2::render",
      "al_is_system_installed()"
   );
   EXPECT_THROW_WITH_MESSAGE(sparkles2.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_MotionFX_Sparkles2TestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   AllegroFlare::MotionFX::Sparkles2 sparkles2(&get_bitmap_bin_ref());
   sparkles2.initialize();
   sparkles2.render();
   SUCCEED();
}


TEST_F(AllegroFlare_MotionFX_Sparkles2TestWithAllegroRenderingFixture,
   VISUAL__render__will_render_an_animated_effect)
{
   AllegroFlare::MotionFX::Sparkles2 sparkles2(&get_bitmap_bin_ref(), 1920/2, 1080/2);
   sparkles2.initialize();

   int passes = 60 * 2.5;
   for (int pass=0; pass<passes; pass++)
   {
      sparkles2.set_time(pass * 1.0/60.0); // 60 fps

      clear();
      sparkles2.render();
      draw_crosshair(1920/2, 1080/2);
      al_flip_display();
   }
}


