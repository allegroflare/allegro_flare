
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


TEST(AllegroFlare_TileMaps_AutoTile_Filters_BaseTest,
   iterate_through_input_and_apply_to_result_if_match__with_out_of_bounds_match_type_of_\
OUT_OF_BOUNDS_MATCH_TYPE_POSITIVE__will_work_as_expected)
{
   // TODO
}


TEST(AllegroFlare_TileMaps_AutoTile_Filters_BaseTest,
   iterate_through_input_and_apply_to_result_if_match__with_out_of_bounds_match_type_of_\
OUT_OF_BOUNDS_MATCH_TYPE_NEGATIVE__will_work_as_expected)
{
   // TODO
}


TEST(AllegroFlare_TileMaps_AutoTile_Filters_BaseTest,
   iterate_through_input_and_apply_to_result_if_match__with_out_of_bounds_match_type_of_\
OUT_OF_BOUNDS_MATCH_TYPE_EXTRUDED_EDGE__will_work_as_expected)
{
   // TODO
}


TEST(AllegroFlare_TileMaps_AutoTile_Filters_BaseTest,
   matrix_matches__with_out_of_bounds_match_type_of__OUT_OF_BOUNDS_MATCH_TYPE_POSITIVE__will_work_as_expected)
{
   // TODO
}


TEST(AllegroFlare_TileMaps_AutoTile_Filters_BaseTest,
   matrix_matches__with_out_of_bounds_match_type_of__OUT_OF_BOUNDS_MATCH_TYPE_NEGATIVE__will_work_as_expected)
{
   // TODO
}


TEST(AllegroFlare_TileMaps_AutoTile_Filters_BaseTest,
   matrix_matches__with_out_of_bounds_match_type_of_OUT_OF_BOUNDS_MATCH_TYPE_EXTRUDED_EDGE__will_work_as_expected)
{
   // TODO
}


