
#include <gtest/gtest.h>

#include <AllegroFlare/Prototypes/MindDive/TunnelTiles/Base.hpp>


class TunnelTilesBaseTestClass : public AllegroFlare::Prototypes::MindDive::TunnelTiles::Base
{
public:
   TunnelTilesBaseTestClass()
      : AllegroFlare::Prototypes::MindDive::TunnelTiles::Base("TunnelTilesBaseTestClass")
   {}
};


TEST(AllegroFlare_Prototypes_MindDive_TunnelTiles_BaseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::MindDive::TunnelTiles::Base base;
}


TEST(AllegroFlare_Prototypes_MindDive_TunnelTiles_BaseTest, TYPE__has_the_expected_value)
{
   AllegroFlare::Prototypes::MindDive::TunnelTiles::Base base;
   EXPECT_EQ("TunnelTiles/Base", base.get_type());
}


TEST(AllegroFlare_Prototypes_MindDive_TunnelTiles_BaseTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Prototypes::MindDive::TunnelTiles::Base base;
   EXPECT_EQ(AllegroFlare::Prototypes::MindDive::TunnelTiles::Base::TYPE, base.get_type());
}


TEST(AllegroFlare_Prototypes_MindDive_TunnelTiles_BaseTest, derived_classes_will_have_the_expected_type)
{
   TunnelTilesBaseTestClass test_class;
   EXPECT_EQ("TunnelTilesBaseTestClass", test_class.get_type());
}


