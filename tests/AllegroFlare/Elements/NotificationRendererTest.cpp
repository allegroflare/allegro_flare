
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_Elements_NotificationRendererTest : public ::testing::Test
{};

class AllegroFlare_Elements_NotificationRendererTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Elements/NotificationRenderer.hpp>


TEST_F(AllegroFlare_Elements_NotificationRendererTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::NotificationRenderer notification_renderer;
}


TEST_F(AllegroFlare_Elements_NotificationRendererTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::NotificationRenderer notification_renderer;
   std::string expected_error_message =
      "NotificationRenderer::render: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(notification_renderer.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Elements_NotificationRendererTest, render__without_font_addon_initialized__raises_an_error)
{
   // TODO
}


TEST_F(AllegroFlare_Elements_NotificationRendererTest, render__without_primitives_addon_initialized__raises_an_error)
{
   // TODO
}


TEST_F(AllegroFlare_Elements_NotificationRendererTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   AllegroFlare::Elements::NotificationRenderer notification_renderer;
   notification_renderer.render();
}


TEST_F(AllegroFlare_Elements_NotificationRendererTestWithAllegroRenderingFixture,
   CAPTURE__render__will_render_as_expected)
{
   AllegroFlare::Elements::NotificationRenderer notification_renderer;
   notification_renderer.render();
   al_flip_display();
   sleep(1);
}


