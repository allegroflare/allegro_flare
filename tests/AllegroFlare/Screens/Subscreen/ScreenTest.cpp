
#include <gtest/gtest.h>

#include <AllegroFlare/Screens/Subscreen/Screen.hpp>
#include <AllegroFlare/Testing/WithAllegroFlareFrameworksFullFixture.hpp>
#include <AllegroFlare/Testing/GameConfigurations/Complete/SimpleConfiguration.hpp>
#include <AllegroFlare/Testing/SubscreenElements/Simple.hpp>

class TestGameConfiguration : public AllegroFlare::Testing::GameConfigurations::Complete::SimpleConfiguration
{
public:
   // TODO: Upgrade this out of void* to a level base class (once the upstream design is clear)
   virtual AllegroFlare::Levels::Base *load_level_by_identifier(std::string identifier) override
   {
      // NOTE: Not used in this test
      //RPG::Gameplay::Level *result = new RPG::Gameplay::Level();
      //if (identifier == "test_level")
      //{
         //result->set_background_image_identifier("maps/rpg-fit-backgrounds-x2-01.png");
      //}
      //return result;
      return nullptr;
   }
};


class TestSubscreenWithInputHints : public AllegroFlare::Screens::Subscreen::Screen
{
public:
   virtual void emit_event_to_update_input_hints_bar() override
   {
      get_event_emitter()->emit_set_input_hints_bar_event({{
           "SHIFT", "%SPACE", "%PLUS", "%SPACE", "RIGHT", "%SPACE", "%SLASH", "%SPACE", "LEFT",
              "%SPACER", "LABEL>>", "Next / Previous tab",
           "%SEPARATOR",
           "UP", "%SPACE", "DOWN", "%SPACE", "LEFT", "%SPACE", "RIGHT", "%SPACER", "LABEL>>", "Move cursor",
           "%SEPARATOR",
           "X", "%SPACER", "LABEL>>", "Close Chronicle",
      }});
   }
};



class AllegroFlare_Screens_Subscreen_ScreenTest : public ::testing::Test {};
class AllegroFlare_Screens_Subscreen_ScreenTestWithAllegroFrameworksFullFixture
   : public AllegroFlare::Testing::WithAllegroFlareFrameworksFullFixture
{};


TEST_F(AllegroFlare_Screens_Subscreen_ScreenTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Screens::Subscreen::Screen screen;
}


TEST_F(AllegroFlare_Screens_Subscreen_ScreenTest, TYPE__has_the_expected_value)
{
   //EXPECT_STREQ(
     //"AllegroFlare/Screens/Subscreen/Screen",
     //AllegroFlare::Screens::Subscreen::Screen::TYPE
   //);
}


TEST_F(AllegroFlare_Screens_Subscreen_ScreenTest, type__has_the_expected_value_matching_TYPE)
{
   //AllegroFlare::Screens::Subscreen::Screen screen;
   //EXPECT_EQ(AllegroFlare::Screens::Subscreen::Screen::TYPE, screen.get_type());
}


TEST_F(AllegroFlare_Screens_Subscreen_ScreenTestWithAllegroFrameworksFullFixture,
   CAPTURE__TIMED_INTERACTIVE__will_run_as_expected)
{
   //TestGameConfiguration game_configuration;
   AllegroFlare::Testing::SubscreenElements::Simple subscreen_element;
   subscreen_element.set_bitmap_bin(get_framework_bitmap_bin());
   subscreen_element.set_font_bin(get_framework_font_bin());
   subscreen_element.initialize();

   AllegroFlare::Screens::Subscreen::Screen screen;
   screen.set_event_emitter(get_framework_event_emitter());
   screen.set_bitmap_bin(get_framework_bitmap_bin());
   screen.set_font_bin(get_framework_font_bin());
   screen.set_subscreen_element(&subscreen_element);
   //screen.set_model_bin(get_framework_model_bin());
   //screen.set_game_configuration(&game_configuration),
   screen.initialize();

   framework_register_and_activate_screen("subscreen_screen", &screen);

   //framework_run_loop(3);
}


TEST_F(AllegroFlare_Screens_Subscreen_ScreenTestWithAllegroFrameworksFullFixture,
   CAPTURE__when_override_for_emit_event_to_update_input_hints_bar_is_present__will_render_as_expected)
{
   // TODO: Move this out of a WithAllegroFrameworksFullFixture test
   AllegroFlare::Testing::SubscreenElements::Simple subscreen_element;
   subscreen_element.set_bitmap_bin(get_framework_bitmap_bin());
   subscreen_element.set_font_bin(get_framework_font_bin());
   subscreen_element.initialize();

   TestSubscreenWithInputHints screen;
   screen.set_event_emitter(get_framework_event_emitter());
   screen.set_bitmap_bin(get_framework_bitmap_bin());
   screen.set_font_bin(get_framework_font_bin());
   screen.set_subscreen_element(&subscreen_element);
   //screen.set_model_bin(get_framework_model_bin());
   //screen.set_game_configuration(&game_configuration),
   screen.initialize();

   framework_register_and_activate_screen("subscreen_screen", &screen);

   //framework_run_loop(3);
}


