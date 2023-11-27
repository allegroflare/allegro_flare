
#include <gtest/gtest.h>

#include <AllegroFlare/WorldMaps/Maps/Base.hpp>


class MapsBaseTestClass : public AllegroFlare::WorldMaps::Maps::Base
{
public:
   MapsBaseTestClass()
      : AllegroFlare::WorldMaps::Maps::Base("MapsBaseTestClass")
   {}
};


TEST(AllegroFlare_WorldMaps_Maps_BaseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::WorldMaps::Maps::Base base;
}


TEST(AllegroFlare_WorldMaps_Maps_BaseTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/WorldMaps/Maps/Base",
     AllegroFlare::WorldMaps::Maps::Base::TYPE
   );
}


TEST(AllegroFlare_WorldMaps_Maps_BaseTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::WorldMaps::Maps::Base base;
   EXPECT_EQ(AllegroFlare::WorldMaps::Maps::Base::TYPE, base.get_type());
}


TEST(AllegroFlare_WorldMaps_Maps_BaseTest, derived_classes_will_have_the_expected_type)
{
   MapsBaseTestClass test_class;
   EXPECT_EQ("MapsBaseTestClass", test_class.get_type());
}


