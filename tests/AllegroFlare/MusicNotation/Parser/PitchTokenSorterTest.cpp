
#include <gtest/gtest.h>

#include <AllegroFlare/MusicNotation/Parser/PitchTokenSorter.hpp>

#include <AllegroFlare/Testing/Comparison/AllegroFlare/MusicNotation/Parser/PitchToken.hpp>


TEST(AllegroFlare_MusicNotation_Parser_PitchTokenSorterTest, can_be_created_without_blowing_up)
{
   AllegroFlare::MusicNotation::Parser::PitchTokenSorter pitch_token_sorter;
}


TEST(AllegroFlare_MusicNotation_Parser_PitchTokenSorterTest,
   sort_unique_desc__will_return_the_pitches_as_unique_elements_in_descending_order)
{
   std::vector<AllegroFlare::MusicNotation::Parser::PitchToken> pitches = {
      { 0,  0, false },
      { 3,  0, false },
      { -7, 0, false },
      { 0,  0, false },
      { -7, 0, false },
      { 2,  0, false },
      { -5, 0, false },
      { 0, -1, false },
   };
   AllegroFlare::MusicNotation::Parser::PitchTokenSorter pitch_token_sorter(pitches);
   std::vector<AllegroFlare::MusicNotation::Parser::PitchToken> expected_pitches = {
      { 3,   0, false },
      { 2,   0, false },
      { 0,   0, false },
      { 0,  -1, false },
      { -5,  0, false },
      { -7,  0, false },
   };
   std::vector<AllegroFlare::MusicNotation::Parser::PitchToken> actual_pitches = pitch_token_sorter.sort_unique_desc();
   EXPECT_EQ(expected_pitches, actual_pitches);
}


