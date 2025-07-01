
#include <gtest/gtest.h>

#include <AllegroFlare/Screens/Gameplay.hpp>
#include <AllegroFlare/Testing/WithAllegroFlareFrameworksFullFixture.hpp>
#include <AllegroFlare/PlayerInputControllers/Generic.hpp>


/*
  - name: get_any_font
    type: ALLEGRO_FONT*
    parameters:
      - name: size
        type: int
        default_argument: -30
    guards: [ (size != 0) ]
    body: |
      std::stringstream ss;
      ss << "Inter-Regular.ttf " << size;
      return font_bin.auto_get(ss.str());
*/


class AllegroFlare_Screens_GameplayTest : public ::testing::Test {};
class AllegroFlare_Screens_GameplayTestWithAllegroFlareFrameworksFullFixture :
   public AllegroFlare::Testing::WithAllegroFlareFrameworksFullFixture
{};


class MyGameplayScreenTestClass : public AllegroFlare::Screens::Gameplay
{
public:
   ALLEGRO_FONT *font;
   AllegroFlare::Vec2D player_position;
   AllegroFlare::PlayerInputControllers::Base* generic_player_input_controller;
   MyGameplayScreenTestClass(ALLEGRO_FONT *font=nullptr)
     : font(font)
     , player_position()
     , generic_player_input_controller(nullptr)
   {
      auto generic_player_input_controller = new AllegroFlare::PlayerInputControllers::Generic();
      generic_player_input_controller->set_on_time_step_update(
         [this](AllegroFlare::Vec2D value, double time_now, double time_step) {
            player_position.x += value.x * time_step * 100; // 100 pixels per second?
            player_position.y += value.y * time_step * 100; // 100 pixels per second?
         }
      );
      generic_player_input_controller->set_on_joy_button_pressed(
         [](int button_num) {
            std::cout << "button " << button_num << " pressed." << std::endl;
         }
      );
      set_player_input_controller(generic_player_input_controller);
      set_update_strategy(AllegroFlare::Screens::Base::UpdateStrategy::SEPARATE_UPDATE_AND_RENDER_FUNCS);
      set_timer_strategy(AllegroFlare::Screens::Gameplay::TimerStrategy::TIMER_STRATEGY_ATOMIC_TIME_STEP);
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

      if (font)
      {
         std::stringstream ss;
         ss << get_game_world_step_timer_ref().get_last_time_step__num_steps_taken() << std::endl;
         ss << get_game_world_step_timer_ref().get_last_time_step__excess_steps_not_taken() << std::endl;
/*
  - name: last_time_step__time_remaining_to_next_step
    type: double
    init_with: 0
    getter: true

  - name: last_time_step__num_steps_taken
    type: int
    init_with: 0
    getter: true

  - name: last_time_step__excess_steps_not_taken
    type: int
    init_with: 0
    getter: true

  - name: last_time_step__total_accumulated_time
    type: double
    init_with: 0
    getter: true

  - name: last_time_step__total_accumulated_time_target
    type: double
    init_with: 0
    getter: true
*/
         //ss << game_world_step_timer.get_
         al_draw_multiline_text(font, ALLEGRO_COLOR{1, 1, 1, 1}, 1920/2, 30, 800, 30, ALLEGRO_ALIGN_CENTER, ss.str().c_str());
      }
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
   framework_run_loop(1);
}


TEST_F(AllegroFlare_Screens_GameplayTestWithAllegroFlareFrameworksFullFixture,
   FOCUS__when_derived__will_work_as_expected)
   // TODO: Make this test more specific
   // TODO: Make this an interactive test
{
   std::stringstream ss;
   ss << "Inter-Regular.ttf " << 28;
   ALLEGRO_FONT *f = get_framework_font_bin()->auto_get(ss.str());

   MyGameplayScreenTestClass gameplay(f);
   gameplay.get_game_world_step_timer_ref().start();
   framework_register_and_activate_screen("gameplay", &gameplay);
   framework_run_loop(20);
}


TEST_F(AllegroFlare_Screens_GameplayTestWithAllegroFlareFrameworksFullFixture, suspend_gameplay__will_not_blow_up)
   // TODO: Make this test more specific
   // TODO: Make this an interactive test
{
   MyGameplayScreenTestClass gameplay;
   framework_register_and_activate_screen("gameplay", &gameplay);
   gameplay.suspend_gameplay();

   //framework_run_loop();
}


TEST_F(AllegroFlare_Screens_GameplayTestWithAllegroFlareFrameworksFullFixture,
   resume_suspended_gameplay__after__suspend_gameplay__will_not_blow_up)
{
   MyGameplayScreenTestClass gameplay;
   framework_register_and_activate_screen("gameplay", &gameplay);

   gameplay.suspend_gameplay();
   gameplay.resume_suspended_gameplay();
}


