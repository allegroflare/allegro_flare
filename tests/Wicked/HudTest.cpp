
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Logger.hpp>

class Wicked_HudTest : public ::testing::Test
{};

class Wicked_HudTestWithAllegroRenderingFixture : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <Wicked/Hud.hpp>


TEST_F(Wicked_HudTest, can_be_created_without_blowing_up)
{
   Wicked::Hud hud;
}


TEST_F(Wicked_HudTest, render__without_allegro_initialized__raises_an_error)
{
   Wicked::Hud hud;
   std::string expected_error_message = AllegroFlare::Logger::build_guard_error_message(
      "Wicked::Hud::render",
      "al_is_system_installed()"
   );
   EXPECT_THROW_WITH_MESSAGE(hud.render(), std::runtime_error, expected_error_message);
}


TEST_F(Wicked_HudTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   Wicked::Hud hud(&get_font_bin_ref());
   hud.render();

   al_flip_display();
   sleep_for(2);
}

