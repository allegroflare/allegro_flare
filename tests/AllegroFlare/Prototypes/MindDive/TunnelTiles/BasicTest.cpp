
#include <gtest/gtest.h>

#include <AllegroFlare/Prototypes/MindDive/TunnelTiles/Basic.hpp>


TEST(AllegroFlare_Prototypes_MindDive_TunnelTiles_BasicTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::MindDive::TunnelTiles::Basic basic;
}


TEST(AllegroFlare_Prototypes_MindDive_TunnelTiles_BasicTest, TYPE__has_the_expected_value)
{
   AllegroFlare::Prototypes::MindDive::TunnelTiles::Basic basic;
   EXPECT_EQ("TunnelTiles/Basic", basic.get_type());
}


TEST(AllegroFlare_Prototypes_MindDive_TunnelTiles_BasicTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Prototypes::MindDive::TunnelTiles::Basic basic;
   EXPECT_EQ(AllegroFlare::Prototypes::MindDive::TunnelTiles::Basic::TYPE, basic.get_type());
}


