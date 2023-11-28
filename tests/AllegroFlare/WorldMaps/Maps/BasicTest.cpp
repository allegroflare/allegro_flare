
#include <gtest/gtest.h>

#include <AllegroFlare/WorldMaps/Maps/Basic.hpp>
#include <AllegroFlare/WorldMaps/Locations/Base.hpp>


class MyTestLocation : public AllegroFlare::WorldMaps::Locations::Base
{
public:
   float x, y, size;
   MyTestLocation(float x, float y) : x(x), y(y), size(10) {}
   virtual bool collides(float xx, float yy) override {
      xx+=size/2;
      yy+=size/2;
      if (xx < x) return false;
      if (xx > x+size) return false;
      if (yy < y) return false;
      if (yy > y+size) return false;
      return true;
   };
};


class AllegroFlare_WorldMaps_Maps_BasicTest : public ::testing::Test {};
class AllegroFlare_WorldMaps_Maps_BasicTestWithMapFixture : public ::testing::Test
{
public:
   AllegroFlare::WorldMaps::Maps::Basic map;
   virtual void SetUp() override
   {
      ::testing::Test::SetUp();
      map.set_locations({
         { "home",   new MyTestLocation(20, 20) },
         { "office", new MyTestLocation(80, 120) },
         { "store",  new MyTestLocation(-100, -30) },
      });
   }
   virtual void TearDown() override
   {
      for (auto &location : map.get_locations())
      {
         delete location.second;
         location.second = nullptr;
      }
      ::testing::Test::TearDown();
   }
};


TEST_F(AllegroFlare_WorldMaps_Maps_BasicTest, MyTestLocation_collides__has_correct_collision_bounds)
{
   auto location = MyTestLocation(0, 0);

   // Positive collisions
   EXPECT_EQ(true, location.collides(0, 0));
   EXPECT_EQ(true, location.collides(-4.9, 0));
   EXPECT_EQ(true, location.collides(4.9, 0));
   EXPECT_EQ(true, location.collides(0, -4.9));
   EXPECT_EQ(true, location.collides(0, 4.9));

   // Negative collisions
   EXPECT_EQ(false, location.collides(999, 999));
   EXPECT_EQ(false, location.collides(-5.1, 0));
   EXPECT_EQ(false, location.collides(5.1, 0));
   EXPECT_EQ(false, location.collides(0, 5.1));
   EXPECT_EQ(false, location.collides(0, 5.1));
}


TEST_F(AllegroFlare_WorldMaps_Maps_BasicTest, can_be_created_without_blowing_up)
{
   AllegroFlare::WorldMaps::Maps::Basic basic;
}


TEST_F(AllegroFlare_WorldMaps_Maps_BasicTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/WorldMaps/Maps/Basic",
     AllegroFlare::WorldMaps::Maps::Basic::TYPE
   );
}


TEST_F(AllegroFlare_WorldMaps_Maps_BasicTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::WorldMaps::Maps::Basic basic;
   EXPECT_EQ(AllegroFlare::WorldMaps::Maps::Basic::TYPE, basic.get_type());
}


TEST_F(AllegroFlare_WorldMaps_Maps_BasicTest, location_id_at__will_return_the_id_of_the_location_at_that_point)
{
   AllegroFlare::WorldMaps::Maps::Basic basic;
   basic.set_locations({
      { "home",   new MyTestLocation(20, 20) },
      { "office", new MyTestLocation(80, 120) },
      { "store",  new MyTestLocation(-100, -30) },
   });

   EXPECT_EQ("home", basic.location_id_at(20+2, 20+4));
   EXPECT_EQ("office", basic.location_id_at(80-4, 120+2));
   EXPECT_EQ("store", basic.location_id_at(-100-4, -30-4));
}


TEST_F(AllegroFlare_WorldMaps_Maps_BasicTestWithMapFixture,
   primary_point_of_interest_is_set__if_the_primary_point_of_interest_is_not_the_default__returns_true)
{
   // TODO: Add test here
}


