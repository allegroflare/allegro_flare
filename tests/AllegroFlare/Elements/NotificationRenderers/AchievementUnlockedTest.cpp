
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
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
   EXPECT_THROW_GUARD_ERROR(
      achievement_unlocked.render(),
      "AllegroFlare::Elements::NotificationRenderers::AchievementUnlocked::render",
      "al_is_system_installed()"
   );
}


TEST_F(AllegroFlare_Elements_NotificationRenderers_AchievementUnlockedTestWithAllegroRenderingFixture,
   CAPTURE__render__will_not_blow_up)
{
   AllegroFlare::Elements::NotificationRenderers::AchievementUnlocked achievement_unlocked(
      &get_bitmap_bin_ref(),
      &get_font_bin_ref()
   );
   achievement_unlocked.set_name("Know Notifications");
   achievement_unlocked.render();
   al_flip_display();
   //sleep_for(1);
}


TEST_F(AllegroFlare_Elements_NotificationRenderers_AchievementUnlockedTestWithAllegroRenderingFixture,
   CAPTURE__render__will_render_an_animation_effect)
{
   AllegroFlare::Elements::NotificationRenderers::AchievementUnlocked achievement_unlocked(
      &get_bitmap_bin_ref(),
      &get_font_bin_ref()
   );
   achievement_unlocked.set_name("Know Notifications");

   for (int frames=60*2; frames>=0; frames--)
   {
      clear();
      achievement_unlocked.render();
      al_flip_display();
      sleep_for_frame();
   }
}


