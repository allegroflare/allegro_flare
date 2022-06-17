

#include <gtest/gtest.h>

#define EXPECT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }


#include <AllegroFlare/Framework.hpp>


TEST(AllegroFlare_FrameworkTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Framework framework;
}


TEST(AllegroFlare_FrameworkTest, run_loop__without_screens__will_throw_an_error)
{
   AllegroFlare::Framework framework;
   std::string expected_error_message = "Framework::run_loop: error: screens cannot be nullptr";
   EXPECT_THROW_WITH_MESSAGE(framework.run_loop(), std::runtime_error, expected_error_message);
}


