
#include <gtest/gtest.h>

#include <AllegroFlare/Display.hpp>


TEST(AllegroFlare_DisplayTest, DISABLED__can_be_created_without_blowing_up)
{
   // TODO: Rework AllegroFlare/Display and prevent this test from failing. This will require a
   // general overhaul of pieces that use Display, which expect to create the display on instanciation.
   AllegroFlare::Display display;
}


TEST(AllegroFlare_DisplayTest, can_be_created_without_blowing_up)
{
   al_init();
   AllegroFlare::Display display;
   al_uninstall_system();
}


