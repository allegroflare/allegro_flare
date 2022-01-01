
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/FontBin.hpp>


TEST(AllegroFlare_FontBinTest, can_be_crated_without_blowing_up)
{
   AllegroFlare::FontBin sample_bin;
}


TEST(AllegroFlare_FontBinTest, validate__without_the_font_addon_initialized__outputs_an_error)
{
   AllegroFlare::FontBin sample_bin;

   testing::internal::CaptureStdout();
   sample_bin.validate();
   std::string output = testing::internal::GetCapturedStdout();
   std::string expected_cout_output = "\x1B[1;31m"
                                      "[FontBin::validate] not properly initialized "
                                      "(requires al_init_font_addon()).  Will crash probably crash."
                                      "\x1B[0m"
                                      "\n";
   ASSERT_EQ(expected_cout_output, output);
}


TEST(AllegroFlare_FontBinTest, validate__without_the_ttf_addon_initialized__outputs_an_error)
{
   al_init();
   al_init_font_addon();
   AllegroFlare::FontBin sample_bin;

   testing::internal::CaptureStdout();
   sample_bin.validate();
   std::string output = testing::internal::GetCapturedStdout();
   std::string expected_cout_output ="\x1B[1;31m"
                                      "[FontBin::validate] not properly initialized "
                                      "(requires al_init_ttf_addon()).  Will crash probably crash."
                                      "\x1B[0m"
                                      "\n";
   ASSERT_EQ(expected_cout_output, output);
   al_uninstall_system();
}


