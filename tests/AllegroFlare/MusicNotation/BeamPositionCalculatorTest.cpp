
#include <gtest/gtest.h>

#include <AllegroFlare/MusicNotation/BeamPositionCalculator.hpp>


class AllegroFlare_MusicNotation_BeamPositionCalculatorTest : public ::testing::Test
{
public:
   std::vector<std::pair<float, int>> build_staff_positions()
   {
      std::vector<std::pair<float, int>> result = {
         // { } // TODO: Add some test data
      };
      return result;
   }
};


TEST_F(AllegroFlare_MusicNotation_BeamPositionCalculatorTest, can_be_created_without_blowing_up)
{
   AllegroFlare::MusicNotation::BeamPositionCalculator beam_position_calculator;
}


TEST_F(AllegroFlare_MusicNotation_BeamPositionCalculatorTest,
   get_min_staff_position__will_return_the_minimum_staff_position_among_the_notehead_staff_positions)
{
   std::vector<std::pair<float, int>> staff_positions = build_staff_positions();
   AllegroFlare::MusicNotation::BeamPositionCalculator beam_position_calculator(staff_positions);
}


