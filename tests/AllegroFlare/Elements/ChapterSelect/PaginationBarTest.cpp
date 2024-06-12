
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_Elements_ChapterSelect_PaginationBarTest : public ::testing::Test
{};

class AllegroFlare_Elements_ChapterSelect_PaginationBarTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Elements/ChapterSelect/PaginationBar.hpp>


TEST_F(AllegroFlare_Elements_ChapterSelect_PaginationBarTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::ChapterSelect::PaginationBar health_bar;
}


TEST_F(AllegroFlare_Elements_ChapterSelect_PaginationBarTest, cursor_position__is_negative_one_by_default)
{
   AllegroFlare::Elements::ChapterSelect::PaginationBar health_bar;
   EXPECT_EQ(-1, health_bar.get_cursor_position());
}


TEST_F(AllegroFlare_Elements_ChapterSelect_PaginationBarTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::ChapterSelect::PaginationBar health_bar;
   std::string expected_error_message = "PaginationBar::render: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(health_bar.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Elements_ChapterSelect_PaginationBarTestWithAllegroRenderingFixture,
   CAPTURE__render__will_draw_the_health_bar_to_the_screen)
{
   AllegroFlare::Elements::ChapterSelect::PaginationBar health_bar(
      { true, true, true, true, true, true, true, false, false, false, },
      6
   );
   health_bar.get_placement_ref().position = {200, 300};
   health_bar.render();
   al_flip_display();
   sleep_for(1);
   SUCCEED();
}


TEST_F(AllegroFlare_Elements_ChapterSelect_PaginationBarTestWithAllegroRenderingFixture,
   calculate_width__will_return_the_width_of_the_entire_bar_when_rendered)
{
   AllegroFlare::Elements::ChapterSelect::PaginationBar health_bar(
      { true, true, true, true, true, true, true, false, false, false, },
      6
   );
   int bar_width = health_bar.get_bar_width();
   int bar_spacing = health_bar.get_bar_spacing();
   EXPECT_EQ(bar_spacing*(10-1)+bar_width, health_bar.calculate_width());

   health_bar.set_bar_spacing(36);
   health_bar.set_bar_width(30);
   EXPECT_EQ(36*(10-1)+30, health_bar.calculate_width());

   health_bar.set_elements({ true });
   EXPECT_EQ(30, health_bar.calculate_width());

   health_bar.set_elements({ /* empty */ });
   EXPECT_EQ(0, health_bar.calculate_width());
}


