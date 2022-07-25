
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/DialogBoxNameTag.hpp>

#ifdef _WIN32
#define TEST_FIXTURE_FONT_FOLDER "/msys64/home/Mark/Repos/allegro_flare/bin/data/fonts/"
#else
#define TEST_FIXTURE_FONT_FOLDER "/Users/markoates/Repos/allegro_flare/bin/data/fonts/"
#endif

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <chrono>
#include <thread>


class AllegroFlare_Elements_DialogBoxNameTagTest : public ::testing::Test {};
class AllegroFlare_Elements_DialogBoxNameTagWithAllegroRenderingFixtureTest
   : public AllegroFlare::Testing::WithAllegroRenderingFixture {};


TEST_F(AllegroFlare_Elements_DialogBoxNameTagTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::DialogBoxNameTag dialog_box_name_tag;
}


TEST_F(AllegroFlare_Elements_DialogBoxNameTagWithAllegroRenderingFixtureTest, render__renders_the_name_tag)
{
   get_font_bin_ref().set_full_path(TEST_FIXTURE_FONT_FOLDER);

   AllegroFlare::Elements::DialogBoxNameTag dialog_box_name_tag(&get_font_bin_ref(), "Mia");
   dialog_box_name_tag.render();
   al_flip_display();
   std::this_thread::sleep_for(std::chrono::seconds(1));
}


