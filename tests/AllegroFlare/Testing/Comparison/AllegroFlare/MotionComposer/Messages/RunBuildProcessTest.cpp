
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/Comparison/AllegroFlare/MotionComposer/Messages/RunBuildProcess.hpp>


TEST(AllegroFlare_Testing_Comparison_AllegroFlare_MotionComposer_Messages_RunBuildProcessTest,
   PrintTo__with_an__AllegroFlare_MotionComposer_Messages_RunBuildProcess__will_output_as_expected)
{
   std::stringstream ss;
   AllegroFlare::MotionComposer::Messages::RunBuildProcess object("windows");

   PrintTo(object, &ss);

   std::string expected_output = "RunBuildProcess(platform: \"windows\")";
   std::string actual_output = ss.str();
   EXPECT_EQ(expected_output, actual_output);
}


TEST(AllegroFlare_Testing_Comparison_AllegroFlare_MotionComposer_Messages_RunBuildProcessTest,
   equality_operator__works_with_google_test_EXPECT_statement)
{
   AllegroFlare::MotionComposer::Messages::RunBuildProcess object("windows");
   AllegroFlare::MotionComposer::Messages::RunBuildProcess other_object("windows");

   EXPECT_EQ(object, other_object);
}


