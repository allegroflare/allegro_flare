
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


