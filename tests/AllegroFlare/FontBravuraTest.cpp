
#include <gtest/gtest.h>

#include <AllegroFlare/FontBravura.hpp>


TEST(AllegroFlare_FontBravuraTest, can_be_created_without_blowing_up)
{
   AllegroFlare::FontBravura font_bravura;
}


TEST(AllegroFlare_FontBravuraTest, has_stem__returns_true_for_a_character_that_has_a_stem)
{
   EXPECT_EQ(true, AllegroFlare::FontBravura::has_stem(AllegroFlare::FontBravura::sixteenth_note_down));
}


