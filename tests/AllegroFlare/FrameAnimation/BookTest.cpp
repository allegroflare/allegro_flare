
#include <gtest/gtest.h>

#include <AllegroFlare/FrameAnimation/Book.hpp>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Testing/ErrorAssertions.hpp>


class AllegroFlare_FrameAnimation_BookTest : public ::testing::Test {};
class AllegroFlare_FrameAnimation_BookTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{
protected:
   AllegroFlare::FrameAnimation::Book animation_book;

private:
   virtual void SetUp() override
   {
      AllegroFlare::Testing::WithAllegroRenderingFixture::SetUp();
      animation_book.set_png_source_filename(get_fixtures_path() + "bitmaps/sprites_grid-x.png");
      animation_book.set_json_source_filename(get_fixtures_path() + "bitmaps/sprites_grid-x.json");
      animation_book.initialize();
   }
};



TEST_F(AllegroFlare_FrameAnimation_BookTest, can_be_created_without_blowing_up)
{
   AllegroFlare::FrameAnimation::Book animation_book;
}


TEST_F(AllegroFlare_FrameAnimation_BookTest, find_animation_by_name__before_initialization__will_throw_an_error)
{
   EXPECT_THROW_GUARD_ERROR(
      AllegroFlare::FrameAnimation::Book().find_animation_by_name(),
      "AllegroFlare::FrameAnimation::Book::find_animation_by_name",
      "initialized"
   );
}


TEST_F(AllegroFlare_FrameAnimation_BookTestWithAllegroRenderingFixture,
   find_animation_by_name__when_an_animation_does_not_exist__will_throw_an_error)
{
   std::string expected_error_message = "[AllegroFlare::FrameAnimation::Book::find_animation_by_name]: error: The "
      "element \"animation-name-that-does-not-exist\" is not in the list of valid elements [\"Skeleton\", \"attack\", "
      "\"blob\", \"die\", \"fly\", \"gold_shield\", \"krampus\", \"shield\", \"skull head\", \"sword\"]";
   EXPECT_THROW_WITH_MESSAGE(
      animation_book.find_animation_by_name("animation-name-that-does-not-exist"),
      std::runtime_error,
      expected_error_message
   );
}


TEST_F(AllegroFlare_FrameAnimation_BookTestWithAllegroRenderingFixture, VISUAL__will_load_an_animation)
{
   ALLEGRO_FONT *font = get_any_font();

   AllegroFlare::FrameAnimation::Animation animation = animation_book.find_animation_by_name("blob");
   animation.initialize();
   
   int frames = 120;
   animation.start();
   for (int i=0; i<frames; i++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 1});

      // update and draw
      animation.update();
      animation.draw();
      float playhead_time = animation.get_playhead();

      // draw info text
      uint32_t frame_id = animation.get_sprite_sheet_cell_index_num_at(playhead_time);
      al_draw_textf(font, ALLEGRO_COLOR{1, 1, 1, 1}, 10, 10, 0, "frame %d", frame_id);

      al_flip_display(); // assumes a rest of 1/60.0f
   }
}


