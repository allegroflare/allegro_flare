
#include <gtest/gtest.h>

#include <AllegroFlare/Runners/Complete.hpp>


TEST(AllegroFlare_Runners_CompleteTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Runners::Complete complete;
}


TEST(AllegroFlare_Runners_CompleteTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/Runners/Complete",
     AllegroFlare::Runners::Complete::TYPE
   );
}


TEST(AllegroFlare_Runners_CompleteTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Runners::Complete complete;
   EXPECT_EQ(AllegroFlare::Runners::Complete::TYPE, complete.get_type());
}


