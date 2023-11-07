
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/TextMessageBubble.hpp>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_Elements_TextMessageBubbleTest : public ::testing::Test {};
class AllegroFlare_Elements_TextMessageBubbleWithAllegroRenderingFixtureTest
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


TEST_F(AllegroFlare_Elements_TextMessageBubbleTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::TextMessageBubble text_message_bubble;
}


TEST_F(AllegroFlare_Elements_TextMessageBubbleWithAllegroRenderingFixtureTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::TextMessageBubble dialog_bubble(
      &get_font_bin_ref(),
      "Hello, this is bubble text",
      600,
      100,
      true
   );

   al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 1});
   dialog_bubble.render();
   al_flip_display();
   al_rest(1);
}


