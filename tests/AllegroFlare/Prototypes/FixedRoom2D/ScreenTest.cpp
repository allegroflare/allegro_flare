
#include <gtest/gtest.h>

#include <AllegroFlare/Prototypes/FixedRoom2D/Screen.hpp>

#include <AllegroFlare/Testing/WithAllegroFlareFrameworksFullFixture.hpp>
#include <AllegroFlare/Elements/Backgrounds/ClearToColor.hpp>

class AllegroFlare_Prototypes_FixedRoom2D_ScreenTest : public ::testing::Test {};
class AllegroFlare_Prototypes_FixedRoom2D_ScreenTestWithAllegroFrameworksFullFixture :
   public AllegroFlare::Testing::WithAllegroFlareFrameworksFullFixture
{};



TEST_F(AllegroFlare_Prototypes_FixedRoom2D_ScreenTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::FixedRoom2D::Screen screen;
}


TEST_F(AllegroFlare_Prototypes_FixedRoom2D_ScreenTestWithAllegroFrameworksFullFixture,
   CAPTURE__TIMED_INTERACTIVE__will_run_as_expected)
{
   // TODO: Figure out why this test *not* working as expected
   //AllegroFlare::Elements::Backgrounds::ClearToColor background;

   AllegroFlare::Prototypes::FixedRoom2D::Screen screen;
   screen.set_event_emitter(get_framework_event_emitter());
   screen.set_bitmap_bin(get_framework_bitmap_bin());
   screen.set_font_bin(get_framework_font_bin());
   //screen.set_background(&background);
   screen.initialize();

   framework_register_and_activate_screen("subscreen_screen", &screen);

   framework_run_loop(3);
}


