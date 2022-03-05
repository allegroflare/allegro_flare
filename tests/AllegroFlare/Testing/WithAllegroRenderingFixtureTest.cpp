
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class TestClassFor_AllegroFlare_Testing_WithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture{};


TEST_F(TestClassFor_AllegroFlare_Testing_WithAllegroRenderingFixture,
   get_test_name__will_return_the_name_of_the_test)
{
   std::string expected_test_name = "get_test_name__will_return_the_name_of_the_test";
   EXPECT_EQ(expected_test_name, get_test_name());
}


TEST_F(TestClassFor_AllegroFlare_Testing_WithAllegroRenderingFixture,
   get_test_suite_name__will_return_the_name_of_the_test)
{
   std::string expected_test_name = "TestClassFor_AllegroFlare_Testing_WithAllegroRenderingFixture";
   EXPECT_EQ(expected_test_name, get_test_suite_name());
}


