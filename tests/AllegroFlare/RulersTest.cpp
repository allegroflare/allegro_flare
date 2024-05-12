#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Rulers.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();


class AllegroFlare_RulersTest : public ::testing::Test {};
class AllegroFlare_RulersTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};



TEST_F(AllegroFlare_RulersTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Rulers rulers;
}


TEST_F(AllegroFlare_RulersTestWithAllegroRenderingFixture, CAPTURE__render__will_not_blow_up)
{
   AllegroFlare::Rulers rulers(&get_font_bin_ref());
   rulers.draw_vertical_ruler();
   al_flip_display();
   sleep_for(1);
}


