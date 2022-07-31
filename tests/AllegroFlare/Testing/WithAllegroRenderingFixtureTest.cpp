
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


TEST_F(TestClassFor_AllegroFlare_Testing_WithAllegroRenderingFixture,
   will_set_the_window_title_to_the_test_suite_name_and_test_name)
{
   // NOTE: cannot currently test this, Allegro5 does not currently have a al_get_window_title() feature
}


TEST_F(TestClassFor_AllegroFlare_Testing_WithAllegroRenderingFixture,
   with_a_test_name_prefixed_with_CAPTURE__will_save_a_screenshot_of_the_backbuffer_during_teardown)
{
   // NOTE: cannot currently test this, assertion would need to happen after teardown
}


