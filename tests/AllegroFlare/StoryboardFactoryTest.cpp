
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_StoryboardFactoryTest : public ::testing::Test
{};

class AllegroFlare_StoryboardFactoryTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/StoryboardFactory.hpp>


TEST_F(AllegroFlare_StoryboardFactoryTest, can_be_created_without_blowing_up)
{
   AllegroFlare::StoryboardFactory storyboard_factory;
}


TEST_F(AllegroFlare_StoryboardFactoryTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::StoryboardFactory storyboard_factory;
   std::string expected_error_message =
      "StoryboardFactory::render: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(storyboard_factory.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_StoryboardFactoryTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   AllegroFlare::StoryboardFactory storyboard_factory;
   storyboard_factory.render();
   SUCCEED();
}

