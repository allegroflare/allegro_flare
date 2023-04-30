
#include <gtest/gtest.h>

#include <AllegroFlare/Routers/Standard.hpp>


TEST(AllegroFlare_Routers_StandardTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Routers::Standard standard;
}


TEST(AllegroFlare_Routers_StandardTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/Routers/Standard",
     AllegroFlare::Routers::Standard::TYPE
   );
}


TEST(AllegroFlare_Routers_StandardTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Routers::Standard standard;
   EXPECT_EQ(AllegroFlare::Routers::Standard::TYPE, standard.get_type());
}


