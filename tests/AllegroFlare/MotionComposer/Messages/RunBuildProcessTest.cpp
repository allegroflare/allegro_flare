
#include <gtest/gtest.h>

#include <AllegroFlare/MotionComposer/Messages/RunBuildProcess.hpp>


TEST(AllegroFlare_MotionComposer_Messages_RunBuildProcessTest, can_be_created_without_blowing_up)
{
   AllegroFlare::MotionComposer::Messages::RunBuildProcess run_build_process;
}


TEST(AllegroFlare_MotionComposer_Messages_RunBuildProcessTest, TYPE__has_the_expected_value)
{
   AllegroFlare::MotionComposer::Messages::RunBuildProcess run_build_process;
   EXPECT_EQ("Messages/RunBuildProcess", run_build_process.get_type());
}


TEST(AllegroFlare_MotionComposer_Messages_RunBuildProcessTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::MotionComposer::Messages::RunBuildProcess run_build_process;
   EXPECT_EQ(AllegroFlare::MotionComposer::Messages::RunBuildProcess::TYPE, run_build_process.get_type());
}


