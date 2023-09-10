
#include <gtest/gtest.h>

#include <AllegroFlare/MusicNotation/BeamPositionCalculator.hpp>


class AllegroFlare_MusicNotation_BeamPositionCalculatorTest : public ::testing::Test
{
public:
   std::vector<std::pair<float, int>> build_staff_positions()
   {
      std::vector<std::pair<float, int>> result = {
          { 0.0,    1 },
          { 20.0,   3 },
          { 40.0,  -3 },
          { 70.0,  -4 },
          { 90.0,   2 },
      };
      return result;
   }
};


TEST_F(AllegroFlare_MusicNotation_BeamPositionCalculatorTest, can_be_created_without_blowing_up)
{
   AllegroFlare::MusicNotation::BeamPositionCalculator beam_position_calculator;
}


TEST_F(AllegroFlare_MusicNotation_BeamPositionCalculatorTest,
   get_first_staff_position__will_return_the_staff_position_of_the_first_notehead_staff_position)
{
   std::vector<std::pair<float, int>> staff_positions = build_staff_positions();
   AllegroFlare::MusicNotation::BeamPositionCalculator beam_position_calculator(staff_positions);
   EXPECT_EQ(1, beam_position_calculator.get_first_staff_position());
}


TEST_F(AllegroFlare_MusicNotation_BeamPositionCalculatorTest,
   get_last_staff_position__will_return_the_staff_position_of_the_last_notehead_staff_position)
{
   std::vector<std::pair<float, int>> staff_positions = build_staff_positions();
   AllegroFlare::MusicNotation::BeamPositionCalculator beam_position_calculator(staff_positions);
   EXPECT_EQ(2, beam_position_calculator.get_last_staff_position());
}


TEST_F(AllegroFlare_MusicNotation_BeamPositionCalculatorTest,
   get_min_staff_position__will_return_the_minimum_staff_position_among_the_notehead_staff_positions)
{
   std::vector<std::pair<float, int>> staff_positions = build_staff_positions();
   AllegroFlare::MusicNotation::BeamPositionCalculator beam_position_calculator(staff_positions);
   EXPECT_EQ(-4, beam_position_calculator.get_min_staff_position());
}


TEST_F(AllegroFlare_MusicNotation_BeamPositionCalculatorTest,
   get_max_staff_position__will_return_the_maximum_staff_position_among_the_notehead_staff_positions)
{
   std::vector<std::pair<float, int>> staff_positions = build_staff_positions();
   AllegroFlare::MusicNotation::BeamPositionCalculator beam_position_calculator(staff_positions);
   EXPECT_EQ(3, beam_position_calculator.get_max_staff_position());
}


