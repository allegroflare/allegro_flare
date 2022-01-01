
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/BitmapBin.hpp>


TEST(AllegroFlare_BitmapBinTest, can_be_crated_without_blowing_up)
{
   AllegroFlare::BitmapBin sample_bin;
}


TEST(AllegroFlare_BitmapBinTest, validate__without_the_image_addon_initialized__outputs_an_error)
{
   AllegroFlare::BitmapBin sample_bin;

   testing::internal::CaptureStdout();
   sample_bin.validate();
   std::string output = testing::internal::GetCapturedStdout();
   std::string expected_cerr_output = "\x1B[1;31m"
                                      "[BitmapBin::validate] not properly initialized "
                                      "(requires al_init_image_addon()).  Will crash probably crash."
                                      "\x1B[0m"
                                      "\n";
   ASSERT_EQ(expected_cerr_output, output);
}


