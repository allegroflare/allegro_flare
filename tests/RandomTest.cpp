
//#include <gtest/gtest.h>
//#include <functional>
//#include <tuple>

//class YourClass {
//public:
    //int add(int a, int b) {
        //return a + b;
    //}

    //double multiply(double a, double b) {
        //return a * b;
    //}

    //std::string concatenate(const std::string& str1, const std::string& str2) {
        //return str1 + str2;
    //}
//};

//class YourClassTest : public ::testing::Test {
//protected:
    //YourClass obj;
//};

//int main(int argc, char **argv) {
    //::testing::InitGoogleTest(&argc, argv);
    //return RUN_ALL_TESTS();
//}

//TEST_F(YourClassTest, MultipleMethodTest) {
    //std::vector<std::pair<std::function<int(const YourClass&, int, int)>, std::tuple<int, int>>> methods_to_test = {
        //{std::mem_fn(&YourClass::add), std::make_tuple(2, 3)},
        //{std::mem_fn(&YourClass::add), std::make_tuple(4, 5)},
        //{std::mem_fn(&YourClass::multiply), std::make_tuple(2.5, 3.5)}
    //};

    //for (const auto& method_to_test : methods_to_test) {
        //auto method_to_call = method_to_test.first;
        //auto args_to_pass = method_to_test.second;

        //int expected_result = 3; // Set your expected result here

        //// Call the method with arguments
        //int actual_result = std::apply([&method_to_call](auto&&... args) {
            //return method_to_call(obj, std::forward<decltype(args)>(args)...);
        //}, args_to_pass);

        //EXPECT_EQ(expected_result, actual_result);
    //}
//}
