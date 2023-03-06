
#include <gtest/gtest.h>

#include <AllegroFlare/VirtualControllers/GenericController.hpp>


TEST(AllegroFlare_VirtualControllers_GenericControllerTest, can_be_created_without_blowing_up)
{
   AllegroFlare::VirtualControllers::GenericController generic_controller;
}


TEST(AllegroFlare_VirtualControllers_GenericControllerTest, TYPE__has_the_expected_value)
{
   AllegroFlare::VirtualControllers::GenericController generic_controller;
   EXPECT_EQ("AllegroFlare/VirtualControllers/GenericController", generic_controller.get_type());
}


TEST(AllegroFlare_VirtualControllers_GenericControllerTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::VirtualControllers::GenericController generic_controller;
   EXPECT_EQ(AllegroFlare::VirtualControllers::GenericController::TYPE, generic_controller.get_type());
}


