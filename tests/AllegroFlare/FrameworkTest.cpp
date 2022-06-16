

#include <gtest/gtest.h>

#define EXPECT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }


#include <AllegroFlare/Framework.hpp>


TEST(AllegroFlare_FrameworkTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Framework framework;
}


TEST(AllegroFlare_FrameworkTest, run_loop__without_screens__will_throw_an_error)
{
   AllegroFlare::Framework framework;
   std::string expected_error_message = "Framework::run_loop: error: screens cannot be nullptr";
   EXPECT_THROW_WITH_MESSAGE(framework.run_loop(), std::runtime_error, expected_error_message);
}


TEST(AllegroFlare_FrameworkTest, initialize__will_initialize_the_audio_controller)
{
   AllegroFlare::Framework framework;
   AllegroFlare::AudioController &audio_controller = framework.get_audio_controller_ref();
   ASSERT_EQ(false, audio_controller.get_initialized());

   framework.initialize();

   ASSERT_EQ(true, audio_controller.get_initialized());
}


TEST(AllegroFlare_FrameworkTest, initialize_with_display__will_create_a_display_with_the_expected_dimentions)
{
   AllegroFlare::Framework framework;

   framework.initialize_with_display();

   ALLEGRO_DISPLAY *current_al_display = al_get_current_display();
   ASSERT_NE(nullptr, current_al_display);

   AllegroFlare::Display *primary_framework_display = framework.get_primary_display();
   ASSERT_NE(nullptr, primary_framework_display);

   EXPECT_EQ(current_al_display, primary_framework_display->al_display);
   EXPECT_EQ(1920, primary_framework_display->get_width());
   EXPECT_EQ(1080, primary_framework_display->get_height());
}


