
#include <gtest/gtest.h>

#include <AllegroFlare/Prototypes/FixedRoom2D/RoomDictionary.hpp>


TEST(AllegroFlare_Prototypes_FixedRoom2D_RoomDictionaryTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::FixedRoom2D::RoomDictionary room_dictionary;
}


TEST(AllegroFlare_Prototypes_FixedRoom2D_RoomDictionaryTest, run__returns_the_expected_response)
{
   AllegroFlare::Prototypes::FixedRoom2D::RoomDictionary room_dictionary;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, room_dictionary.run());
}

