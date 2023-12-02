
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <AllegroFlare/AllegroContributorsList.hpp>


TEST(AllegroFlare_AllegroContributorsListTest, can_be_created_without_blowing_up)
{
   AllegroFlare::AllegroContributorsList allegro_contributors_list;
}


TEST(AllegroFlare_AllegroContributorsListTest, build_allegro_5_contributors_list__returns_the_expected_number_of_names)
{
   std::vector<std::string> list = AllegroFlare::AllegroContributorsList::build_allegro_5_contributors_list();
   EXPECT_EQ(93, list.size());
}


TEST(AllegroFlare_AllegroContributorsListTest, build_allegro_5_contributors_list__contains_expected_names)
{
   std::vector<std::string> list = AllegroFlare::AllegroContributorsList::build_allegro_5_contributors_list();
   std::vector<std::string> some_expected_names = {
      "Martijn van Iersel",
      "Matthew Leverton",
      "SiegeLord",
      "Mark Oates",
      "Rodolfo Lam",
   };
   for (auto &some_expected_name : some_expected_names)
   {
      EXPECT_THAT(list, ::testing::Contains(some_expected_name));
   }
}


