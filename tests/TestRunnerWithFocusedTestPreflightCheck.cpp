
#include <allegro5/allegro.h>

#include <gtest/gtest.h>

// look here for extending google test to handle events
// https://github.com/google/googletest/blob/main/docs/advanced.md#extending-googletest-by-handling-test-events

//class MinimalistPrinter : public testing::EmptyTestEventListener {
 //// Called before a test starts.
 //void OnTestStart(const testing::TestInfo& test_info) override {
   //printf("*** Test %s.%s starting.\n",
          //test_info.test_suite_name(), test_info.name());
 //}

 //// Called after a failed assertion or a SUCCESS().
 //void OnTestPartResult(const testing::TestPartResult& test_part_result) override {
   //printf("%s in %s:%d\n%s\n",
          //test_part_result.failed() ? "*** Failure" : "Success",
          //test_part_result.file_name(),
          //test_part_result.line_number(),
          //test_part_result.summary());
 //}

 //// Called after a test ends.
 //void OnTestEnd(const testing::TestInfo& test_info) override {
   //printf("*** Test %s.%s ending.\n",
          //test_info.test_suite_name(), test_info.name());
 //}
//};



#include <iostream>
#include <string>

int first_non_uppercase_letter_or_underscore(std::string input) {
    for (int i = 0; i < input.size(); i++) {
        if (!isupper(input[i]) && input[i] != '_') {
            return i;
        }
    }
    return -1;
}



#include <iostream>
#include <string>

bool contains_FOCUS(std::string input) {
    return input.find("FOCUS__") != std::string::npos;
}



std::stringstream cout_buffer;
std::streambuf* prevcoutbuf = nullptr;
std::string captured_cout = ""; 

void start_capture()
{
   std::streambuf* prevcoutbuf = std::cout.rdbuf(cout_buffer.rdbuf());
}

void restore_capture()
{
   std::string captured_cout = cout_buffer.str();
   std::cout.rdbuf(prevcoutbuf);
}

std::string get_cout_capture()
{
   return captured_cout;
}




#define GTEST_DEFAULT_FILTER_FLAG "*"


int main(int argc, char **argv)
{
   int test_result = -1;
   ::testing::InitGoogleTest(&argc, argv);




   std::string initial_filter_flag = ::testing::GTEST_FLAG(filter);




   ::testing::GTEST_FLAG(filter) = "*FOCUS__*"; //"TestCaseOne.*:TestCaseTwo.Test5:TestCaseTen.Test3";


   /*

   //NOTE: The default GTEST_FLAG is "*"
   if (initial_filter_flag != GTEST_DEFAULT_FILTER_FLAG)
   {
      std::cout << "[tests/TestRunner::main] INFO: Gtest is being run with a flag \"" << initial_filter_flag << "\"." << std::endl;
   }

   //std::cout << ::testing::GTEST_FLAG(filter) << std::endl;
   //std::cout << ::testing::GTEST_FLAG(filter) << std::endl;
   //std::cout << ::testing::GTEST_FLAG(filter) << std::endl;

   // NOTE: this will override gtest flag
   ::testing::GTEST_FLAG(filter) = "*FOCUS__*"; //"TestCaseOne.*:TestCaseTwo.Test5:TestCaseTen.Test3";
   //std::string RUN_ALL_TESTS();

   ::testing::GTEST_FLAG(list_tests) = true;

   start_capture();
   test_result = RUN_ALL_TESTS();
   restore_capture();

   if (test_result != 0)
   {
      throw std::runtime_error("[tests/TestRunner::main]: error: When attempting to capture test names, "
                               "RUN_ALL_TESTS() returned an unexpected response.");
   }

   std::cout << get_cout_capture() << std::endl;
   ::testing::GTEST_FLAG(list_tests) = false;

   ::testing::GTEST_FLAG(filter) = initial_filter_flag;

   */



   //// Gets hold of the event listener list.
   //testing::TestEventListeners& listeners =
      //testing::UnitTest::GetInstance()->listeners();
   //// Adds a listener to the end.  googletest takes the ownership.
   //listeners.Append(new MinimalistPrinter);

   test_result = RUN_ALL_TESTS();

   return test_result;
}



