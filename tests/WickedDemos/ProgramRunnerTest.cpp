
#include <gtest/gtest.h>

#include <WickedDemos/ProgramRunner.hpp>

TEST(WickedDemos_ProgramRunnerTest, can_be_created_without_blowing_up)
{
   WickedDemos::ProgramRunner program_runner;
}

TEST(WickedDemos_ProgramRunnerTest, run__returns_the_expected_response)
{
   WickedDemos::ProgramRunner program_runner;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, program_runner.run());
}
