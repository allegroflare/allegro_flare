
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_Screens_TransitionTest : public ::testing::Test
{};

class AllegroFlare_Screens_TransitionTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Screens/Transition.hpp>


TEST_F(AllegroFlare_Screens_TransitionTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Screens::Transition transition;
}


TEST_F(AllegroFlare_Screens_TransitionTestWithAllegroRenderingFixture, initialize__will_not_blow_up)
{
   AllegroFlare::Screens::Transition transition;
   transition.initialize();
   SUCCEED();
}

