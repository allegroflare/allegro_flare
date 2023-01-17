

#include <gtest/gtest.h>

#include <tilemap/lib/NextCollidingTilesCalculator.hpp>


TEST(NextCollidingTilesCalculatorTest, can_be_created_without_arguments)
{
   //NextCollidingTilesCalculator calculator;
}


TEST(NextCollidingTilesCalculatorTest, next_colliding_tiles__returns_a_list_of_tiles_that_are_expected_to_collide_in_the_next_step_along_the_x_axis)
{
   NextCollidingTilesCalculator calculator(NextCollidingTilesCalculator::X_AXIS, 0, 0, 16, 16, 8, 0);

   std::vector<vec2i> expected_result_tiles = { { 1, 0 } };
   std::vector<vec2i> returned_result_tiles = calculator.next_colliding_tiles();

   ASSERT_EQ(expected_result_tiles, returned_result_tiles);
}


int main(int argc, char **argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}


