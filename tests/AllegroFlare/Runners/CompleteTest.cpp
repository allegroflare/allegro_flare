
#include <gtest/gtest.h>

#include <AllegroFlare/Runners/Complete.hpp>
#include <AllegroFlare/GameConfigurations/Complete.hpp>
#include <AllegroFlare/Testing/GameConfigurations/Complete/SimpleConfiguration.hpp>


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


TEST(AllegroFlare_Runners_CompleteTest,
   INTERACTIVE__run__will_work_as_expected)
   // TODO: This need to be a timed interactive test
   //DISABLED__INTERACTIVE__run__will_work_as_expected)
{
   // TODO: Update this test to not crash when specific menu options are picked (like start game)
   AllegroFlare::GameConfigurations::Complete *configuration =
      new AllegroFlare::Testing::GameConfigurations::Complete::SimpleConfiguration();
   // TODO: HERE: Make this run:
   AllegroFlare::Runners::Complete::run(configuration, "test");
}



