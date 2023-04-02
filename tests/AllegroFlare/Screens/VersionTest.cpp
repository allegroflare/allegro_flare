
#include <gtest/gtest.h>

#include <AllegroFlare/Screens/Version.hpp>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Testing/WithAllegroFlareFrameworksFullFixture.hpp>
//#include <AllegroFlare/Frameworks/Full.hpp>

class AllegroFlare_Screens_VersionTest : public ::testing::Test {};
class AllegroFlare_Screens_VersionTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};
class AllegroFlare_Screens_VersionTestWithAllegroFrameworksFullFixture
   : public AllegroFlare::Testing::WithAllegroFlareFrameworksFullFixture
{};



TEST_F(AllegroFlare_Screens_VersionTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Screens::Version version;
}


TEST_F(AllegroFlare_Screens_VersionTest, TYPE__has_the_expected_value)
{
   AllegroFlare::Screens::Version version;
   EXPECT_EQ("AllegroFlare/Screens/Version", version.get_type());
}


TEST_F(AllegroFlare_Screens_VersionTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Screens::Version version;
   EXPECT_EQ(AllegroFlare::Screens::Version::TYPE, version.get_type());
}


TEST_F(AllegroFlare_Screens_VersionTestWithAllegroFrameworksFullFixture,
   TIMED_INTERACTIVE__will_run_as_expected)
{
   AllegroFlare::Screens::Version version;
   version.set_event_emitter(get_framework_event_emitter());
   version.set_bitmap_bin(get_framework_bitmap_bin());
   version.set_font_bin(get_framework_font_bin());
   version.set_model_bin(get_framework_model_bin());
   version.initialize();

   framework_register_and_activate_screen("version", &version);

   framework_run_loop(3);
}


TEST_F(AllegroFlare_Screens_VersionTestWithAllegroFrameworksFullFixture,
   DISABLED__pressing_any_key__will_emit_the_game_event_name_to_emit_on_exit)
{
   // TODO
}


