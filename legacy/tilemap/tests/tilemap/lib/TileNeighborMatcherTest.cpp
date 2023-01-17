

#include <gtest/gtest.h>

#include <tilemap/lib/TileNeighborMatcher.hpp>


TEST(TileNeighborMatcherTest, can_be_created_without_arguments)
{
   TileNeighborMatcher filter_matcher;
}


TEST(TileNeighborMatcherTest, match__returns_true_when_given_a_tile_context_and_a_filter_matches)
{
   TileNeighborMatcher filter_matcher;

   int my_tile_context_matrix[3][3] = { { 12, 32,  8 },
                                        { 32, 32, 11 },
                                        { 12,  7,  8 } };

   ASSERT_TRUE(filter_matcher.match(filter_matcher.bottom_right, 32, my_tile_context_matrix));
}


TEST(TileNeighborMatcherTest, match__returns_false_when_given_a_tile_context_and_a_filter_does_not_match)
{
   TileNeighborMatcher filter_matcher;

   int my_tile_context_matrix[3][3] = { { 12, 32,  8 },
                                        { 32, 32, 32 },
                                        { 12,  7,  8 } };

   ASSERT_FALSE(filter_matcher.match(filter_matcher.bottom_right, 32, my_tile_context_matrix));
}


TEST(TileNeighborMatcherTest, match__with_a_matcher_matrix_values_of_0_allows_any_tile)
{
   TileNeighborMatcher filter_matcher;

   int matcher[3][3] = { { 0, 0, 0 },
                         { 0, 0, 0 },
                         { 0, 0, 0 } };

   int my_tile_context_matrix[3][3] = { { 12, 35, 56 },
                                        { 78, 90, 12 },
                                        { 34, 56, 78 } };

   ASSERT_TRUE(filter_matcher.match(matcher, 90, my_tile_context_matrix));
   ASSERT_TRUE(filter_matcher.match(matcher, 0, my_tile_context_matrix));
   ASSERT_TRUE(filter_matcher.match(matcher, 999, my_tile_context_matrix));
}


TEST(TileNeighborMatcherTest, match__with_a_matcher_matrix_values_of_1_must_match_the_expected_tiles)
{
   TileNeighborMatcher filter_matcher;

   int matcher[3][3] = { { 1, 0, 0 },
                         { 0, 1, 0 },
                         { 0, 0, 1 } };

   int my_tile_context_matrix[3][3] = { {  9, 35, 56 },
                                        { 78,  9, 12 },
                                        { 34, 56,  9 } };

   ASSERT_TRUE(filter_matcher.match(matcher,  9, my_tile_context_matrix));
   ASSERT_FALSE(filter_matcher.match(matcher, 0, my_tile_context_matrix));
   ASSERT_FALSE(filter_matcher.match(matcher, 12, my_tile_context_matrix));
}


TEST(TileNeighborMatcherTest, match__with_a_matcher_matrix_values_of_2_must_mismatch_the_expected_tiles)
{
   TileNeighborMatcher filter_matcher;

   int matcher[3][3] = { { 2, 0, 0 },
                         { 0, 2, 0 },
                         { 0, 0, 2 } };

   int my_tile_context_matrix[3][3] = { { 16, 35, 56 },
                                        { 78, 16, 12 },
                                        { 34, 56, 16 } };

   ASSERT_FALSE(filter_matcher.match(matcher, 16, my_tile_context_matrix));
   ASSERT_TRUE(filter_matcher.match(matcher, 999, my_tile_context_matrix));
   ASSERT_TRUE(filter_matcher.match(matcher,  12, my_tile_context_matrix));
}


int main(int argc, char **argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}


