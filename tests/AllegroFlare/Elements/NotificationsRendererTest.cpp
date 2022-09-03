
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_Elements_NotificationsRendererTest : public ::testing::Test
{};

class AllegroFlare_Elements_NotificationsRendererTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Elements/NotificationsRenderer.hpp>

#include <AllegroFlare/Elements/Notifications/AchievementUnlocked.hpp>


TEST_F(AllegroFlare_Elements_NotificationsRendererTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::NotificationsRenderer notifications_renderer;
}


TEST_F(AllegroFlare_Elements_NotificationsRendererTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::NotificationsRenderer notifications_renderer;
   std::string expected_error_message =
      "NotificationsRenderer::render: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(notifications_renderer.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Elements_NotificationsRendererTestWithAllegroRenderingFixture,
   CAPTURE__render__will_render_as_expected)
{
   std::vector<AllegroFlare::Elements::Notifications::Base*> notifications({
      new AllegroFlare::Elements::Notifications::AchievementUnlocked("Bite the Bullet"),
      new AllegroFlare::Elements::Notifications::AchievementUnlocked("Work Hard"),
      new AllegroFlare::Elements::Notifications::AchievementUnlocked("Win the Prize"),
   });

   AllegroFlare::Elements::NotificationsRenderer notifications_renderer(&get_font_bin_ref(), notifications);
   notifications_renderer.render();
   al_flip_display();
   sleep_for(1);

   // clean up the notifications
   for (auto &notification : notifications) delete notification;
}


