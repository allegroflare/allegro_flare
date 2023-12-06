
#include <gtest/gtest.h>

#include <AllegroFlare/WorldMaps/Maps/Basic.hpp>
#include <AllegroFlare/WorldMaps/Locations/Base.hpp>
#include <AllegroFlare/WorldMaps/Locations/Basic.hpp>
#include <AllegroFlare/Testing/ErrorAssertions.hpp>


class MyTestLocation : public AllegroFlare::WorldMaps::Locations::Base
{
public:
   float size;
   MyTestLocation(float x, float y)
      : AllegroFlare::WorldMaps::Locations::Base("MyTestLocation")
      , size(10)
   {
      set_x(x);
      set_y(y);
   }
   virtual bool collides(float xx, float yy) override {
      xx+=size/2;
      yy+=size/2;
      if (xx < get_x()) return false;
      if (xx > get_x()+size) return false;
      if (yy < get_y()) return false;
      if (yy > get_y()+size) return false;
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


AllegroFlare::WorldMaps::Locations::Basic* create_basic_location(std::string name, float x, float y)
{
   AllegroFlare::WorldMaps::Locations::Basic *result = new AllegroFlare::WorldMaps::Locations::Basic(name);
   result->set_x(x);
   result->set_y(y);
   return result;
}


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
   primary_point_of_interest_is_set__if_the_primary_point_of_interest_is_the_default__returns_false)
{
   EXPECT_EQ(false, map.primary_point_of_interest_is_set());
}


TEST_F(AllegroFlare_WorldMaps_Maps_BasicTestWithMapFixture,
   primary_point_of_interest_is_set__if_the_primary_point_of_interest_is_not_the_default__returns_true)
{
   map.set_primary_point_of_interest_identifier("home");
   EXPECT_EQ(true, map.primary_point_of_interest_is_set());
}


TEST_F(AllegroFlare_WorldMaps_Maps_BasicTestWithMapFixture,
   primary_point_of_interest_is_on_map__when_the_primary_point_of_interest_does_not_exist_in_the_locations__returns_false)
{
   map.set_primary_point_of_interest_identifier("a-location-that-does-not-exist");
   EXPECT_EQ(false, map.primary_point_of_interest_is_on_map());
}


TEST_F(AllegroFlare_WorldMaps_Maps_BasicTestWithMapFixture,
   primary_point_of_interest_is_on_map__when_the_primary_point_of_interest_exists_in_the_locations__returns_true)
{
   map.set_primary_point_of_interest_identifier("home");
   EXPECT_EQ(true, map.primary_point_of_interest_is_on_map());
}


TEST_F(AllegroFlare_WorldMaps_Maps_BasicTest,
   infer_location_coordinates__will_return_true_with_the_coordinates_of_a_location)
{
   // TODO: Remove usage of AllegroFlare::WorldMaps::Locations::Basic and use MyTestLocation
   // after moving (x, y) to Locations/Base
   AllegroFlare::WorldMaps::Maps::Basic basic;
   basic.set_locations({
      { "home",   create_basic_location("Home", 20, 20) },
      { "office", create_basic_location("Office", 80, 120) },
      { "store",  create_basic_location("Store", -100, -30) },
   });

   std::pair<bool, std::pair<float, float>> expected_coordinate_result = { true, { 80.0f, 120.0f } };
   EXPECT_EQ(expected_coordinate_result, basic.infer_location_coordinates("office"));
}


TEST_F(AllegroFlare_WorldMaps_Maps_BasicTest,
   infer_location_coordinates__on_a_location_that_does_not_exist__will_return_false_with_placeholder_coordinates)
{
   // TODO: Remove usage of AllegroFlare::WorldMaps::Locations::Basic and use MyTestLocation
   // after moving (x, y) to Locations/Base
   AllegroFlare::WorldMaps::Maps::Basic basic;
   basic.set_locations({
      { "home",   create_basic_location("Home", 20, 20) },
      { "office", create_basic_location("Office", 80, 120) },
      { "store",  create_basic_location("Store", -100, -30) },
   });

   std::pair<bool, std::pair<float, float>> expected_coordinate_result = { false, { 0.0f, 0.0f } };
   EXPECT_EQ(expected_coordinate_result, basic.infer_location_coordinates("a-place-that-does-not-exist"));
}


