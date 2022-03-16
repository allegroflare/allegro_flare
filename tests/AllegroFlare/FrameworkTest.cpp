
#include <gtest/gtest.h>

#include <AllegroFlare/Framework.hpp>


TEST(AllegroFlare_FrameworkTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Screens screens;
   AllegroFlare::Framework framework(screens);
}



