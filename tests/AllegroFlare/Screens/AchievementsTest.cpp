
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_Screens_AchievementsTest : public ::testing::Test
{};

class AllegroFlare_Screens_AchievementsTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Screens/Achievements.hpp>


TEST_F(AllegroFlare_Screens_AchievementsTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Screens::Achievements achievements;
}


TEST_F(AllegroFlare_Screens_AchievementsTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Screens::Achievements achievements;
   std::string expected_error_message =
      "Achievements::render: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(achievements.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Screens_AchievementsTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   AllegroFlare::Screens::Achievements achievements(&get_font_bin_ref());
   achievements.render();
   SUCCEED();
}

