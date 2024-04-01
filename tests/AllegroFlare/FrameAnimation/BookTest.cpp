
#include <gtest/gtest.h>

#include <AllegroFlare/FrameAnimation/Book.hpp>

//#include <allegro5/allegro_image.h>
//#include <allegro5/allegro_ttf.h>
//#include <allegro5/allegro_font.h>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>

using AllegroFlare::FrameAnimation::Book;
using AllegroFlare::FrameAnimation::Animation;


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
   Book animation_book;
}


TEST_F(AllegroFlare_FrameAnimation_BookTestWithAllegroRenderingFixture,
   find_animation_by_name__before_initialization__will_throw_an_error)
{
   // TODO
}


TEST_F(AllegroFlare_FrameAnimation_BookTestWithAllegroRenderingFixture, VISUAL__will_load_an_animation)
{
   ALLEGRO_FONT *font = get_any_font();

   //Book animation_book;
   //animation_book.set_png_source_filename(get_fixtures_path() + "bitmaps/sprites_grid-x.png");
   //animation_book.set_json_source_filename(get_fixtures_path() + "bitmaps/sprites_grid-x.json");
   //animation_book.initialize();

   Animation animation = animation_book.find_animation_by_name("blob");
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


