
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_Elements_NotificationRenderers_JoystickDisconnectedTest : public ::testing::Test
{};

class AllegroFlare_Elements_NotificationRenderers_JoystickDisconnectedTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Elements/NotificationRenderers/JoystickDisconnected.hpp>


TEST_F(AllegroFlare_Elements_NotificationRenderers_JoystickDisconnectedTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::NotificationRenderers::JoystickDisconnected joystick_disconnected_renderer;
}


TEST_F(AllegroFlare_Elements_NotificationRenderers_JoystickDisconnectedTest,
   render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::NotificationRenderers::JoystickDisconnected joystick_disconnected_renderer;
   EXPECT_THROW_GUARD_ERROR(
      joystick_disconnected_renderer.render(),
      "AllegroFlare::Elements::NotificationRenderers::JoystickDisconnected::render",
      "al_is_system_installed()"
   );
}


TEST_F(AllegroFlare_Elements_NotificationRenderers_JoystickDisconnectedTestWithAllegroRenderingFixture,
   CAPTURE__render__will_not_blow_up)
{
   AllegroFlare::Elements::NotificationRenderers::JoystickDisconnected joystick_disconnected_renderer(
      &get_bitmap_bin_ref(),
      &get_font_bin_ref()
   );
   joystick_disconnected_renderer.set_name("WHITE X-Box 360 Controller");
   joystick_disconnected_renderer.render();
   al_flip_display();
   //sleep_for(1);
}


TEST_F(AllegroFlare_Elements_NotificationRenderers_JoystickDisconnectedTestWithAllegroRenderingFixture,
   CAPTURE__render__will_render_an_animation_effect)
{
   AllegroFlare::Elements::NotificationRenderers::JoystickDisconnected joystick_disconnected_renderer(
      &get_bitmap_bin_ref(),
      &get_font_bin_ref()
   );
   joystick_disconnected_renderer.set_name("WHITE X-Box 360 Controller");

   for (int frames=60*2; frames>=0; frames--)
   {
      clear();
      joystick_disconnected_renderer.render();
      al_flip_display();
      sleep_for_frame();
   }
}


