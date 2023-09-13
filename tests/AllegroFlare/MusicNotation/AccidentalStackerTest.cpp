
#include <gtest/gtest.h>

#include <AllegroFlare/MusicNotation/AccidentalStacker.hpp>


const bool operator==(
      const AllegroFlare::MusicNotation::AccidentalStacker::AccidentalType &a1,
      const AllegroFlare::MusicNotation::AccidentalStacker::AccidentalStacker::AccidentalType &a2
   )
{
   return ((int)a1 == (int)a2);
}


TEST(AllegroFlare_MusicNotation_AccidentalStackerTest, can_be_created_without_blowing_up)
{
   AllegroFlare::MusicNotation::AccidentalStacker accidental_stacker;
}


TEST(AllegroFlare_MusicNotation_AccidentalStackerTest, solve__will_not_blow_up)
{
   AllegroFlare::MusicNotation::AccidentalStacker accidental_stacker;
   accidental_stacker.solve();
}


TEST(AllegroFlare_MusicNotation_AccidentalStackerTest, solve__will_generate_the_expected_stack)
{
   using namespace AllegroFlare::MusicNotation;
   std::vector<AllegroFlare::MusicNotation::Parser::PitchToken> pitches = {
      { 3  , -1, false },
      { 3+7, -1, false },
      { 5,    1, false },
      { 8,    0, true  },
   };

   AllegroFlare::MusicNotation::AccidentalStacker accidental_stacker(pitches);
   accidental_stacker.solve();

   std::vector<std::pair<AccidentalStacker::AccidentalType, std::pair<int, int>>> expected_stack = {
      { AccidentalStacker::AccidentalType::FLAT,    { 0,  3+7 } },
      { AccidentalStacker::AccidentalType::FLAT,    { 0,  3   } },
      { AccidentalStacker::AccidentalType::SHARP,   { -1, 5   } },
      { AccidentalStacker::AccidentalType::NATURAL, { -2, 8   } },
   };
   std::vector<std::pair<AccidentalStacker::AccidentalType, std::pair<int, int>>> actual_stack =
      accidental_stacker.get_stack();

   EXPECT_EQ(expected_stack, actual_stack);
}


