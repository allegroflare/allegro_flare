#include <allegro5/allegro.h>
#include <gtest/gtest.h>

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

bool contains_FOCUS(std::string input) {
    return input.find("FOCUS__") != std::string::npos;
}

std::stringstream cout_buffer;
std::streambuf* prevcoutbuf = nullptr;
std::string captured_cout = ""; 

void start_capture() {
    prevcoutbuf = std::cout.rdbuf(cout_buffer.rdbuf());
}

void restore_capture() {
    captured_cout = cout_buffer.str();
    std::cout.rdbuf(prevcoutbuf);
}

std::string get_cout_capture() {
    return captured_cout;
}

int main(int argc, char **argv) {
    int test_result = -1;
    ::testing::InitGoogleTest(&argc, argv);

    bool runAllTests = true;

    // Check if any test contains FOCUS__
    // List all tests without running them
    ::testing::UnitTest& unitTest = *::testing::UnitTest::GetInstance();
    for (int i = 0; i < unitTest.total_test_case_count(); i++) {
        const ::testing::TestCase* testCase = unitTest.GetTestCase(i);
        for (int j = 0; j < testCase->total_test_count(); j++) {
            const ::testing::TestInfo* testInfo = testCase->GetTestInfo(j);
            std::string testName = std::string(testInfo->test_suite_name()) + "." + testInfo->name();
            if (contains_FOCUS(testName)) {
                runAllTests = false;
                break;
            }
        }
        if (!runAllTests) {
            break;
        }
    }

    if (runAllTests) {
        std::cout << "No tests contain FOCUS__. Running all tests.\n";
    } else {
        std::cout << "At least one test contains FOCUS__. Running only focused tests.\n";
        ::testing::GTEST_FLAG(filter) = "*FOCUS__*";
    }

    test_result = RUN_ALL_TESTS();

    return test_result;
}
