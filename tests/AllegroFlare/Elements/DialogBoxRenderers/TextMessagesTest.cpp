
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/DialogBoxRenderers/TextMessages.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <chrono>
#include <thread>


class AllegroFlare_Elements_DialogBoxRenderers_TextMessagesTest : public ::testing::Test {};
class AllegroFlare_Elements_DialogBoxRenderers_TextMessagesTestWithAllegroRenderingFixtureTest
   : public AllegroFlare::Testing::WithAllegroRenderingFixture {};


TEST(AllegroFlare_Elements_DialogBoxRenderers_TextMessagesTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::DialogBoxRenderers::TextMessages text_messages;
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_TextMessagesTestWithAllegroRenderingFixtureTest,
   render__will_work_as_expected)
{
   AllegroFlare::Placement2D place{ 1920/2, 1080/2, 600, 900 };
   int passes = 60;
   float age = 0;
   for (unsigned i=0; i<passes; i++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 1});
      AllegroFlare::Elements::DialogBoxRenderers::TextMessages smart_phone_dialog_renderer(
         &get_font_bin_ref(),
         place.size.x,
         place.size.y,
         {
            { "Friend", "Hello, this is bubble text", 0.0f },
            { "Friend", "And this is a second line", 0.0f },
            { "Friend", "And finally the last line", 0.0f },
          },
         age
      );

      smart_phone_dialog_renderer.set_draw_background_fill(true);

      place.start_transform();
      smart_phone_dialog_renderer.render();
      place.restore_transform();
      al_flip_display();
      std::this_thread::sleep_for(std::chrono::milliseconds(1000/60));
      age += (1.0/60.0f) * 2;
   }
}



