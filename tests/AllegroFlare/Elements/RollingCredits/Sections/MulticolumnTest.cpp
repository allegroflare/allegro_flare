
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/RollingCredits/Sections/Multicolumn.hpp>


TEST(AllegroFlare_Elements_RollingCredits_Sections_MulticolumnTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::RollingCredits::Sections::Multicolumn multicolumn;
}


TEST(AllegroFlare_Elements_RollingCredits_Sections_MulticolumnTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/Elements/RollingCredits/Sections/Multicolumn",
     AllegroFlare::Elements::RollingCredits::Sections::Multicolumn::TYPE
   );
}


TEST(AllegroFlare_Elements_RollingCredits_Sections_MulticolumnTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Elements::RollingCredits::Sections::Multicolumn multicolumn;
   EXPECT_EQ(AllegroFlare::Elements::RollingCredits::Sections::Multicolumn::TYPE, multicolumn.get_type());
}


TEST(AllegroFlare_Elements_RollingCredits_Sections_MulticolumnTest,
   DISABLED__split_into_columns__will_return_the_original_elements_distributed_into_columns)
{
   int num_columns = 3;
   std::vector<std::string> elements = { "foo", "bar", "biz", "baz", "booz", "biz", "borz" };
   std::vector<std::vector<std::string>> expected = {
      { "foo",  "bar" },
      { "biz",  "baz" },
      { "booz", "biz" },
   };
   std::vector<std::vector<std::string>> actual =
      AllegroFlare::Elements::RollingCredits::Sections::Multicolumn::split_into_columns(elements, num_columns);
   EXPECT_EQ(3, actual.size());
   EXPECT_EQ(expected, actual);
}


