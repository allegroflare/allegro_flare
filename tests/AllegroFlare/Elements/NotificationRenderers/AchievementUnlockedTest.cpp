
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_Elements_NotificationRenderers_AchievementUnlockedTest : public ::testing::Test
{};

class AllegroFlare_Elements_NotificationRenderers_AchievementUnlockedTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Elements/NotificationRenderers/AchievementUnlocked.hpp>


TEST_F(AllegroFlare_Elements_NotificationRenderers_AchievementUnlockedTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::NotificationRenderers::AchievementUnlocked achievement_unlocked;
}


TEST_F(AllegroFlare_Elements_NotificationRenderers_AchievementUnlockedTest,
   render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::NotificationRenderers::AchievementUnlocked achievement_unlocked;
   std::string expected_error_message =
      "AchievementUnlocked::render: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(achievement_unlocked.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Elements_NotificationRenderers_AchievementUnlockedTestWithAllegroRenderingFixture,
   CAPTURE__render__will_not_blow_up)
{
   AllegroFlare::Elements::NotificationRenderers::AchievementUnlocked achievement_unlocked(&get_font_bin_ref());
   achievement_unlocked.set_name("Know Notifications");
   achievement_unlocked.render();
   al_flip_display();
   sleep_for(1);
}


