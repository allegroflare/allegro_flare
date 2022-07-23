
#include <gtest/gtest.h>

#include <AllegroFlare/Prototypes/FixedRoom2D/Entities/Room.hpp>


TEST(AllegroFlare_Prototypes_FixedRoom2D_Entities_RoomTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::FixedRoom2D::Entities::Room room;
}


TEST(AllegroFlare_Prototypes_FixedRoom2D_Entities_RoomTest, run__returns_the_expected_response)
{
   AllegroFlare::Prototypes::FixedRoom2D::Entities::Room room;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, room.run());
}

