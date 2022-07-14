
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


#include <AllegroFlare/Screens/Transition.hpp>


#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/TransitionFX/Base.hpp>

class TestScreenA : public AllegroFlare::Screens::Base
{
public:
   ALLEGRO_COLOR background_color;
   TestScreenA() : AllegroFlare::Screens::Base(), background_color(AllegroFlare::Color::Red) {}
   void primary_timer_func() override { al_clear_to_color(background_color); }
};

class TestScreenB : public AllegroFlare::Screens::Base
{
public:
   ALLEGRO_COLOR background_color;
   TestScreenB() : AllegroFlare::Screens::Base(), background_color(AllegroFlare::Color::Green) {}
   void primary_timer_func() override { al_clear_to_color(background_color); }
};

class TestTransitionFX : public AllegroFlare::TransitionFX::Base
{
public:
   TestTransitionFX() : AllegroFlare::TransitionFX::Base() {}
};


class AllegroFlare_Screens_TransitionTest : public ::testing::Test
{};

class AllegroFlare_Screens_TransitionTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};



TEST_F(AllegroFlare_Screens_TransitionTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Screens::Transition transition;
}


TEST_F(AllegroFlare_Screens_TransitionTestWithAllegroRenderingFixture, initialize__will_not_blow_up)
{
   AllegroFlare::Screens::Transition transition;
   transition.initialize();
   SUCCEED();
}


TEST_F(AllegroFlare_Screens_TransitionTestWithAllegroRenderingFixture, primary_timer_func__will_not_blow_up)
{
   AllegroFlare::EventEmitter event_emitter;
   TestScreenA *test_screen_a = new TestScreenA;
   TestScreenB *test_screen_b = new TestScreenB;
   TestTransitionFX *test_transition_fx = new TestTransitionFX;
   test_transition_fx->initialize();
   
   AllegroFlare::Screens::Transition transition(&event_emitter, test_screen_a, test_screen_b, test_transition_fx);
   transition.initialize();

   for (int i=0; i<120; i++)
   {
      transition.primary_timer_func();
      al_flip_display();
   }

   delete test_transition_fx;
   delete test_screen_b;
   delete test_screen_a;
}


TEST_F(AllegroFlare_Screens_TransitionTestWithAllegroRenderingFixture,
   primary_timer_func__when_the_transition_fx_becomes_finished__marks_the_transition_as_finished)
{
   // TODO
}


TEST_F(AllegroFlare_Screens_TransitionTestWithAllegroRenderingFixture,
   primary_timer_func__when_the_transition_fx_becomes_finished__emit_an_event_with_the_expected_param_value)
{
   // TODO
}


