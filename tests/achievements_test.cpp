


#include <gtest/gtest.h>

#include <AllegroFlare/Achievements.hpp>



using namespace AllegroFlare;



TEST(AchievementsTest, can_be_created_without_arguments)
{
   Achievements achievements;
}



int main(int argc, char **argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}



