
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
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
   EXPECT_THROW_WITH_MESSAGE(text.render(), std::runtime_error, expected_error_message);
}


