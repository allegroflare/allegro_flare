
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>

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
   std::string expected_error_message =
      "Hud::render: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(hud.render(), std::runtime_error, expected_error_message);
}


TEST_F(Wicked_HudTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   Wicked::Hud hud(&get_font_bin_ref());
   hud.render();

   al_flip_display();
   sleep_for(2);
}

