
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/NotificationRenderer.hpp>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Elements/Notifications/AchievementUnlocked.hpp>
#include <AllegroFlare/Elements/Notifications/JoystickConnected.hpp>
#include <AllegroFlare/Elements/Notifications/JoystickDisconnected.hpp>


class AllegroFlare_Elements_NotificationRendererTest : public ::testing::Test
{};

class AllegroFlare_Elements_NotificationRendererTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};



TEST_F(AllegroFlare_Elements_NotificationRendererTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::NotificationRenderer notification_renderer;
}


TEST_F(AllegroFlare_Elements_NotificationRendererTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::NotificationRenderer notification_renderer;
   EXPECT_THROW_GUARD_ERROR(
      notification_renderer.render(),
      "AllegroFlare::Elements::NotificationRenderer::render",
      "al_is_system_installed()"
   );
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
   //sleep_for(1);
}


TEST_F(AllegroFlare_Elements_NotificationRendererTestWithAllegroRenderingFixture,
   CAPTURE__render__will_render_a_JoystickConnected_type_notification)
{
   AllegroFlare::Elements::Notifications::JoystickConnected joystick_connected_notification;
   AllegroFlare::Elements::NotificationRenderer notification_renderer(
      &get_bitmap_bin_ref(),
      &get_font_bin_ref(),
      &joystick_connected_notification
   );
   notification_renderer.render();
   al_flip_display();
}


TEST_F(AllegroFlare_Elements_NotificationRendererTestWithAllegroRenderingFixture,
   CAPTURE__render__will_render_a_JoystickDisconnected_type_notification)
{
   AllegroFlare::Elements::Notifications::JoystickDisconnected joystick_disconnected_notification;
   AllegroFlare::Elements::NotificationRenderer notification_renderer(
      &get_bitmap_bin_ref(),
      &get_font_bin_ref(),
      &joystick_disconnected_notification
   );
   notification_renderer.render();
   al_flip_display();
}


