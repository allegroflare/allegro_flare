
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_Elements_BaseTest : public ::testing::Test
{};

class AllegroFlare_Elements_BaseTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Elements/Base.hpp>


TEST_F(AllegroFlare_Elements_BaseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::Base text;
}


TEST_F(AllegroFlare_Elements_BaseTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::Base text;
   std::string expected_error_message = "Base::render: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(text.render(), std::runtime_error, expected_error_message);
}


