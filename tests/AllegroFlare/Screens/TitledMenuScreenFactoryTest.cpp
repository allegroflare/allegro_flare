
#include <gtest/gtest.h>

#include <AllegroFlare/Screens/TitledMenuScreenFactory.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_Screens_TitledMenuScreenFactoryTestWithAllegroRenderingFixture :
   public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


TEST(AllegroFlare_Screens_TitledMenuScreenFactoryTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Screens::TitledMenuScreenFactory titled_menu_screen_factory;
}


TEST_F(AllegroFlare_Screens_TitledMenuScreenFactoryTestWithAllegroRenderingFixture,
   CAPTURE__create_standard_pause_screen__will_create_a_valid_pause_screen_with_the_expected_properties)
{
   auto screen = AllegroFlare::Screens::TitledMenuScreen::create_standard_pause_screen(
      get_data_folder_path(),
      "NAME OF GAME   v0.2.81"
   );

   screen->reveal();
   screen->render();

   al_flip_display();
   al_rest(0.25);

   screen->destroy();
   SUCCEED();
}


TEST_F(AllegroFlare_Screens_TitledMenuScreenFactoryTestWithAllegroRenderingFixture,
   CAPTURE__create_standard_title_screen__will_create_a_valid_pause_screen_with_the_expected_properties)
{
   auto screen = AllegroFlare::Screens::TitledMenuScreen::create_standard_title_screen(
      get_data_folder_path(),
      "Title of Game",
      "© Copyright 2025       clubcatt.com      v0.1.17"
   );

   screen->reveal();
   screen->render();

   al_flip_display();
   al_rest(0.25);

   screen->destroy();
   SUCCEED();
}


TEST_F(AllegroFlare_Screens_TitledMenuScreenFactoryTestWithAllegroRenderingFixture,
   CAPTURE__create_standard_game_won_screen__will_create_a_valid_pause_screen_with_the_expected_properties)
{
   auto screen = AllegroFlare::Screens::TitledMenuScreen::create_standard_game_won_screen(
      get_data_folder_path()
   );

   screen->reveal();
   screen->render();

   al_flip_display();
   al_rest(0.25);

   screen->destroy();
   SUCCEED();
}


TEST_F(AllegroFlare_Screens_TitledMenuScreenFactoryTestWithAllegroRenderingFixture,
   CAPTURE__create_standard_game_over_screen__will_create_a_valid_pause_screen_with_the_expected_properties)
{
   auto screen = AllegroFlare::Screens::TitledMenuScreen::create_standard_game_over_screen(
      get_data_folder_path()
   );

   screen->reveal();
   screen->render();

   al_flip_display();
   al_rest(0.25);

   screen->destroy();
   SUCCEED();
}


