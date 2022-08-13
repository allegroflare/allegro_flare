
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_Elements_AchievementsListTest : public ::testing::Test
{};

class AllegroFlare_Elements_AchievementsListTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Elements/AchievementsList.hpp>


TEST_F(AllegroFlare_Elements_AchievementsListTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::AchievementsList achievements;
}


TEST_F(AllegroFlare_Elements_AchievementsListTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::AchievementsList achievements;
   std::string expected_error_message =
      "AchievementsList::render: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(achievements.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Elements_AchievementsListTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   AllegroFlare::Elements::AchievementsList achievements(&get_font_bin_ref());
   achievements.render();
   SUCCEED();
}


TEST_F(AllegroFlare_Elements_AchievementsListTestWithAllegroRenderingFixture, CAPTURE__render__will_render_as_expected)
{
   AllegroFlare::Elements::AchievementsList achievements(&get_font_bin_ref());
   achievements.set_achievements(AllegroFlare::Elements::AchievementsList::build_placeholder_achievements());
   achievements.render();
   al_flip_display();
   sleep_for(1);
   SUCCEED();
}

TEST_F(AllegroFlare_Elements_AchievementsListTestWithAllegroRenderingFixture,
   CAPTURE__render__will_offset_the_list_of_items_by__scroll_offset_y)
{
   AllegroFlare::Elements::AchievementsList achievements(&get_font_bin_ref());
   achievements.set_achievements(AllegroFlare::Elements::AchievementsList::build_placeholder_achievements());

   int num_scrolls = 120;
   float amount_per_scroll = 2.6;
   for (int i=0; i<num_scrolls; i++)
   {
      achievements.set_scroll_offset_y(i * amount_per_scroll);

      clear();
      achievements.render();
      al_flip_display();
   }
}


