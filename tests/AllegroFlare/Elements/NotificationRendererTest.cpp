
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_Elements_NotificationRendererTest : public ::testing::Test
{};

class AllegroFlare_Elements_NotificationRendererTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Elements/NotificationRenderer.hpp>

#include <AllegroFlare/Elements/Notifications/AchievementUnlocked.hpp>

TEST_F(AllegroFlare_Elements_NotificationRendererTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::NotificationRenderer notification_renderer;
}


TEST_F(AllegroFlare_Elements_NotificationRendererTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::NotificationRenderer notification_renderer;
   std::string expected_error_message =
      "NotificationRenderer::render: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(notification_renderer.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Elements_NotificationRendererTest, render__without_font_addon_initialized__raises_an_error)
{
   // TODO
}


TEST_F(AllegroFlare_Elements_NotificationRendererTest, render__without_primitives_addon_initialized__raises_an_error)
{
   // TODO
}


TEST_F(AllegroFlare_Elements_NotificationRendererTestWithAllegroRenderingFixture,
   CAPTURE__render__will_render_an_AchievementUnlocked_type_notification)
{
   AllegroFlare::Elements::Notifications::AchievementUnlocked achievement_unlocked_notification;
   AllegroFlare::Elements::NotificationRenderer notification_renderer(
      &get_bitmap_bin_ref(),
      &get_font_bin_ref(),
      &achievement_unlocked_notification
   );
   notification_renderer.render();
   al_flip_display();
   sleep_for(1);
}


