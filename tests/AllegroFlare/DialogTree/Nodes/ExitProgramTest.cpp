
#include <gtest/gtest.h>

#include <AllegroFlare/DialogTree/Nodes/ExitProgram.hpp>


TEST(AllegroFlare_DialogTree_Nodes_ExitProgramTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogTree::Nodes::ExitProgram exit_program;
}


TEST(AllegroFlare_DialogTree_Nodes_ExitProgramTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/DialogTree/Nodes/ExitProgram",
     AllegroFlare::DialogTree::Nodes::ExitProgram::TYPE
   );
}


TEST(AllegroFlare_DialogTree_Nodes_ExitProgramTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::DialogTree::Nodes::ExitProgram exit_program;
   EXPECT_EQ(AllegroFlare::DialogTree::Nodes::ExitProgram::TYPE, exit_program.get_type());
}


