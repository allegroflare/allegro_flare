#include <gtest/gtest.h>

#define EXPECT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_Elements_ScoreTest : public ::testing::Test {};
class AllegroFlare_Elements_ScoreTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Elements/Score.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();


TEST_F(AllegroFlare_Elements_ScoreTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::Score score;
}


TEST_F(AllegroFlare_Elements_ScoreTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::Score score;
   std::string expected_error_message =
      "Score::render: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(score.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Elements_ScoreTest, render__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::Elements::Score score;
   std::string expected_error_message =
      "Score::render: error: guard \"al_is_primitives_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(score.render(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}


TEST_F(AllegroFlare_Elements_ScoreTest, render__without_font_addon_initialized__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   AllegroFlare::Elements::Score score;
   std::string expected_error_message =
      "Score::render: error: guard \"al_is_font_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(score.render(), std::runtime_error, expected_error_message);
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_Elements_ScoreTest, render__without_a_font_bin__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   AllegroFlare::Elements::Score score;
   std::string expected_error_message =
      "Score::render: error: guard \"font_bin\" not met";
   EXPECT_THROW_WITH_MESSAGE(score.render(), std::runtime_error, expected_error_message);
   al_shutdown_font_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}   


TEST_F(AllegroFlare_Elements_ScoreTestWithAllegroRenderingFixture, CAPTURE__render__will_not_blow_up)
{
   AllegroFlare::Elements::Score score(&get_font_bin_ref());
   score.render();
   al_flip_display();
   sleep_for(1);
}


