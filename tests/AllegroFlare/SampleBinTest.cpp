
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/SampleBin.hpp>


TEST(AllegroFlare_SampleBinTest, can_be_crated_without_blowing_up)
{
   AllegroFlare::SampleBin sample_bin;
}


TEST(AllegroFlare_SampleBinTest, DISABLED__validate__without_the_acodec_addon_initialized__outputs_an_error)
{
   // TODO investigate why this line does not return the output error regardless if acodec has not be initialized

   al_init();
   AllegroFlare::SampleBin sample_bin;

   testing::internal::CaptureStdout();
   sample_bin.validate();
   std::string output = testing::internal::GetCapturedStdout();
   std::string expected_cerr_output = "[SampleBin::validate] not properly initialized "
                                      "(requires al_init_acodec_addon()).  Will crash probably crash.\n";
   ASSERT_EQ(expected_cerr_output, output);
   al_uninstall_system();
}


