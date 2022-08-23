
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/RollingCredits/Sections/Header.hpp>


TEST(AllegroFlare_Elements_RollingCredits_Sections_HeaderTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::RollingCredits::Sections::Header header;
}


TEST(AllegroFlare_Elements_RollingCredits_Sections_HeaderTest, has_the_expected_type)
{
   AllegroFlare::Elements::RollingCredits::Sections::Header header;
   EXPECT_EQ("Header", header.get_type());
}


