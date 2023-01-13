
#include <gtest/gtest.h>

#include <AllegroFlare/TileMaps/AutoTile/Filters/Base.hpp>


class FiltersBaseTestClass : public AllegroFlare::TileMaps::AutoTile::Filters::Base
{
public:
   FiltersBaseTestClass()
      : AllegroFlare::TileMaps::AutoTile::Filters::Base("FiltersBaseTestClass")
   {}
};


TEST(AllegroFlare_TileMaps_AutoTile_Filters_BaseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::TileMaps::AutoTile::Filters::Base base;
}


TEST(AllegroFlare_TileMaps_AutoTile_Filters_BaseTest, TYPE__has_the_expected_value)
{
   AllegroFlare::TileMaps::AutoTile::Filters::Base base;
   EXPECT_EQ("Filters/Base", base.get_type());
}


TEST(AllegroFlare_TileMaps_AutoTile_Filters_BaseTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::TileMaps::AutoTile::Filters::Base base;
   EXPECT_EQ(AllegroFlare::TileMaps::AutoTile::Filters::Base::TYPE, base.get_type());
}


TEST(AllegroFlare_TileMaps_AutoTile_Filters_BaseTest, derived_classes_will_have_the_expected_type)
{
   FiltersBaseTestClass test_class;
   EXPECT_EQ("FiltersBaseTestClass", test_class.get_type());
}


