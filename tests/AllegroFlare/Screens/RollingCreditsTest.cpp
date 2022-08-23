
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_Screens_RollingCreditsTest : public ::testing::Test
{};

class AllegroFlare_Screens_RollingCreditsTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Screens/RollingCredits.hpp>


TEST_F(AllegroFlare_Screens_RollingCreditsTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Screens::RollingCredits rolling_credits;
}


TEST_F(AllegroFlare_Screens_RollingCreditsTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Screens::RollingCredits rolling_credits;
   std::string expected_error_message =
      "RollingCredits::render: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(rolling_credits.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Screens_RollingCreditsTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   AllegroFlare::Screens::RollingCredits rolling_credits;
   rolling_credits.render();
   SUCCEED();
}

