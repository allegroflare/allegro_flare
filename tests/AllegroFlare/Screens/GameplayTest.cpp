
#include <gtest/gtest.h>

#include <AllegroFlare/Screens/Gameplay.hpp>
#include <AllegroFlare/Testing/WithAllegroFlareFrameworksFullFixture.hpp>
#include <AllegroFlare/PlayerInputControllers/Generic.hpp>


class AllegroFlare_Screens_GameplayTest : public ::testing::Test {};
class AllegroFlare_Screens_GameplayTestWithAllegroFlareFrameworksFullFixture :
   public AllegroFlare::Testing::WithAllegroFlareFrameworksFullFixture
{};


class MyGameplayScreenTestClass : public AllegroFlare::Screens::Gameplay
{
public:
   AllegroFlare::Vec2D player_position;
   AllegroFlare::PlayerInputControllers::Base* generic_player_input_controller;
   MyGameplayScreenTestClass()
     : player_position()
     , generic_player_input_controller(nullptr)
   {
      auto generic_player_input_controller = new AllegroFlare::PlayerInputControllers::Generic();
      generic_player_input_controller->set_on_time_step_update(
         [this](AllegroFlare::Vec2D value, double time_now, double time_step) {
            player_position.x += value.x; // * 0.1;
            player_position.y += value.y; // * 0.1;
         }
      );
      set_player_input_controller(generic_player_input_controller);
      set_update_strategy(AllegroFlare::Screens::Base::UpdateStrategy::SEPARATE_UPDATE_AND_RENDER_FUNCS);
   }
   ~MyGameplayScreenTestClass()
   {
      delete generic_player_input_controller;
   }
   void primary_render_func() override
   {
      al_clear_to_color(ALLEGRO_COLOR{0.2, 0.2, 0.24, 1.0});
      al_clear_depth_buffer(1);
      al_draw_filled_rectangle(
         player_position.x,
         player_position.y,
         player_position.x+50,
         player_position.y+50,
         ALLEGRO_COLOR{1, 0.4, 0.9, 1.0}
      );
   }
};


TEST_F(AllegroFlare_Screens_GameplayTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Screens::Gameplay gameplay;
}


TEST_F(AllegroFlare_Screens_GameplayTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ("AllegroFlare/Screens/Gameplay", AllegroFlare::Screens::Gameplay::TYPE);
}


TEST_F(AllegroFlare_Screens_GameplayTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Screens::Gameplay gameplay;
   EXPECT_EQ(AllegroFlare::Screens::Gameplay::TYPE, gameplay.get_type());
}


TEST_F(AllegroFlare_Screens_GameplayTestWithAllegroFlareFrameworksFullFixture, will_work_in_a_framework_context)
{
   AllegroFlare::Screens::Gameplay gameplay;
   framework_register_and_activate_screen("gameplay", &gameplay);
   framework_run_loop();
}


TEST_F(AllegroFlare_Screens_GameplayTestWithAllegroFlareFrameworksFullFixture, when_derived__will_work_as_expected)
   // TODO: Make this test more specific
   // TODO: Make this an interactive test
{
   MyGameplayScreenTestClass gameplay;
   framework_register_and_activate_screen("gameplay", &gameplay);
   framework_run_loop();
}


