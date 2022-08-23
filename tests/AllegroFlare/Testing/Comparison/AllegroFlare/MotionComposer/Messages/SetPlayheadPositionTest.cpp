
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/Comparison/AllegroFlare/MotionComposer/Messages/SetPlayheadPosition.hpp>


TEST(AllegroFlare_Testing_Comparison_AllegroFlare_MotionComposer_Messages_SetPlayheadPositionTest,
   PrintTo__with_an__AllegroFlare_MotionComposer_Messages_SetPlayheadPosition__will_output_as_expected)
{
   std::stringstream ss;
   AllegroFlare::MotionComposer::Messages::SetPlayheadPosition vec(3.5);

   PrintTo(vec, &ss);

   std::string expected_output = "SetPlayheadPosition(3.5)";
   std::string actual_output = ss.str();
   EXPECT_EQ(expected_output, actual_output);
}


TEST(AllegroFlare_Testing_Comparison_AllegroFlare_MotionComposer_Messages_SetPlayheadPositionTest,
   equality_operator__works_with_google_test_EXPECT_statement)
{
   AllegroFlare::MotionComposer::Messages::SetPlayheadPosition vec(0.5);
   AllegroFlare::MotionComposer::Messages::SetPlayheadPosition other_vec(0.5);

   EXPECT_EQ(vec, other_vec);
}


