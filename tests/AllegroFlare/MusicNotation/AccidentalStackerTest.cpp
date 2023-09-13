
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

   AllegroFlare::MusicNotation::AccidentalStacker accidental_stacker;
   accidental_stacker.solve();

   std::vector<std::pair<AccidentalStacker::AccidentalType, std::pair<int, int>>> expected_stack = {};
   std::vector<std::pair<AccidentalStacker::AccidentalType, std::pair<int, int>>> actual_stack =
      accidental_stacker.get_stack();

   EXPECT_EQ(expected_stack, actual_stack);
}


