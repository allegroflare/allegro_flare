
#include <gtest/gtest.h>

#include <AllegroFlare/Screens/Subscreen/PaneFactory.hpp>


TEST(AllegroFlare_Screens_Subscreen_PaneFactoryTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Screens::Subscreen::PaneFactory pane_factory;
}


TEST(AllegroFlare_Screens_Subscreen_PaneFactoryTest, run__returns_the_expected_response)
{
   AllegroFlare::Screens::Subscreen::PaneFactory pane_factory;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, pane_factory.run());
}


