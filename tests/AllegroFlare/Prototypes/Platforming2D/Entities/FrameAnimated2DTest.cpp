
#include <gtest/gtest.h>

#include <AllegroFlare/Prototypes/Platforming2D/Entities/FrameAnimated2D.hpp>


#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Testing/CustomComparison.hpp>


#include <allegro5/allegro_color.h> // for al_color_html
#include <allegro5/allegro_primitives.h> // for al_draw_line


class AllegroFlare_Prototypes_Platforming2D_Entities_FrameAnimated2DTest : public ::testing::Test {};
class AllegroFlare_Prototypes_Platforming2D_Entities_FrameAnimated2DWithAllegroRenderingFixtureTest
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



TEST_F(AllegroFlare_Prototypes_Platforming2D_Entities_FrameAnimated2DTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::Platforming2D::Entities::FrameAnimated2D frame_animated2d;
}


TEST_F(AllegroFlare_Prototypes_Platforming2D_Entities_FrameAnimated2DTest, TYPE__has_the_expected_value)
{
   AllegroFlare::Prototypes::Platforming2D::Entities::FrameAnimated2D frame_animated2d;
   //EXPECT_EQ("Entities/FrameAnimated2D", frame_animated2d.get_type());
   // TODO: resolve this test that
   EXPECT_EQ("Entities/Basic2D", frame_animated2d.get_type());
}


TEST_F(AllegroFlare_Prototypes_Platforming2D_Entities_FrameAnimated2DTest,
   DISABLED__type__has_the_expected_value_matching_TYPE)
   // TODO: resolve this test that
{
   AllegroFlare::Prototypes::Platforming2D::Entities::FrameAnimated2D frame_animated2d;
   EXPECT_EQ(AllegroFlare::Prototypes::Platforming2D::Entities::FrameAnimated2D::TYPE, frame_animated2d.get_type());
}


TEST_F(AllegroFlare_Prototypes_Platforming2D_Entities_FrameAnimated2DTest,
   // TODO: this test requires some more design. There are more requirements in order to have update work
   DISABLED__update__can_be_called_without_blowing_up)
{
   //AllegroFlare::Prototypes::Platforming2D::Entities::FrameAnimated2D frame_animated2d_entity(&animation_book);
   //frame_animated2d_entity.set_animation("golden_dragon");
   //frame_animated2d_entity.update();
   //SUCCEED();
}


TEST_F(AllegroFlare_Prototypes_Platforming2D_Entities_FrameAnimated2DWithAllegroRenderingFixtureTest,
   DISABLED__draw__without_primitives_addon_initialized__will_throw_an_error)
{
   // TODO
}


TEST_F(AllegroFlare_Prototypes_Platforming2D_Entities_FrameAnimated2DWithAllegroRenderingFixtureTest,
   draw__can_be_called_without_blowing_up)
{
   AllegroFlare::Prototypes::Platforming2D::Entities::FrameAnimated2D frame_animated2d_entity;
   frame_animated2d_entity.set_animation_book(&animation_book);
   frame_animated2d_entity.draw();
   SUCCEED();
}


TEST_F(AllegroFlare_Prototypes_Platforming2D_Entities_FrameAnimated2DWithAllegroRenderingFixtureTest,
   CAPTURE__draw__with_a_bitmap__will_display_the_image)
{
   AllegroFlare::Prototypes::Platforming2D::Entities::FrameAnimated2D frame_animated2d_entity; //(&animation_book);
   frame_animated2d_entity.set_animation_book(&animation_book);
   frame_animated2d_entity.set_animation("blob");

   al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
   frame_animated2d_entity.draw();

   ALLEGRO_COLOR expected_sampled_color = al_color_html("687160"); // the blob's top tip
   ALLEGRO_COLOR actual_sampled_color = al_get_pixel(al_get_target_bitmap(), 123, 176);

   // TODO: update this sample pick
   EXPECT_EQ(expected_sampled_color, actual_sampled_color);

   al_flip_display();
   //sleep(2);
}


TEST_F(AllegroFlare_Prototypes_Platforming2D_Entities_FrameAnimated2DWithAllegroRenderingFixtureTest,
   CAPTURE__draw__with_a_modified_place__will_display_the_image)
{
   AllegroFlare::Prototypes::Platforming2D::Entities::FrameAnimated2D frame_animated2d_entity; //(&animation_book);
   frame_animated2d_entity.set_animation_book(&animation_book);

   frame_animated2d_entity.set_animation("blob");
   frame_animated2d_entity.disable_bitmap_alignment_strategy();
   frame_animated2d_entity.set_draw_debug(true);

   frame_animated2d_entity.get_place_ref().position = { 1920/2, 1080/2 };
   frame_animated2d_entity.get_place_ref().scale = { 2.0, 3.0 };
   frame_animated2d_entity.get_place_ref().align = { 0.5, 0.5 };
   frame_animated2d_entity.get_place_ref().rotation = 0.2f;

   frame_animated2d_entity.draw();

   al_flip_display();

   SUCCEED(); // TODO: pick pixel
}


TEST_F(AllegroFlare_Prototypes_Platforming2D_Entities_FrameAnimated2DWithAllegroRenderingFixtureTest,
   CAPTURE__draw__will_render_the_different_alignment_strategies_as_expected)
{
   AllegroFlare::Prototypes::Platforming2D::Entities::FrameAnimated2D frame_animated2d_entity;//(&animation_book);
   frame_animated2d_entity.set_animation_book(&animation_book);

   frame_animated2d_entity.set_animation("blob");
   frame_animated2d_entity.set_draw_debug(true);
   frame_animated2d_entity.get_place_ref().scale = {1.0, 1.0};
   frame_animated2d_entity.get_place_ref().size = { 80, 60 };

   frame_animated2d_entity.get_place_ref().position = {1920/8*1, 1080/2};
   frame_animated2d_entity.set_bitmap_alignment_strategy("top_left");
   frame_animated2d_entity.update();
   frame_animated2d_entity.draw();

   frame_animated2d_entity.get_place_ref().position = {1920/8*3, 1080/2};
   frame_animated2d_entity.set_bitmap_alignment_strategy("centered");
   frame_animated2d_entity.update();
   frame_animated2d_entity.draw();

   frame_animated2d_entity.get_place_ref().position = {1920/8*5, 1080/2};
   frame_animated2d_entity.set_bitmap_alignment_strategy("bottom_centered");
   frame_animated2d_entity.update();
   frame_animated2d_entity.draw();

   frame_animated2d_entity.get_place_ref().position = {1920/8*7, 1080/2};
   frame_animated2d_entity.set_bitmap_alignment_strategy("bottom_centered_edge");
   frame_animated2d_entity.update();
   frame_animated2d_entity.draw();

   al_draw_line(0, 1080/2, 1920, 1080/2, ALLEGRO_COLOR{1.0f, 1.0f, 0.0f, 1.0f}, 1.0f);
   //al_draw_line(0, 1080/2, 1920, 1080/2, ALLEGRO_COLOR{1, 1, 0, 1});

   al_flip_display();
   //sleep(4);

   SUCCEED(); // TODO: pick pixel
}



TEST_F(AllegroFlare_Prototypes_Platforming2D_Entities_FrameAnimated2DWithAllegroRenderingFixtureTest,
   fit_to_bitmap__without_a_bitmap__will_raise_an_exception)
{
   // TODO
}


TEST_F(AllegroFlare_Prototypes_Platforming2D_Entities_FrameAnimated2DWithAllegroRenderingFixtureTest,
   // TODO: update this test to accomodate the concerns for animation
   fit_to_bitmap__will_set_the_size_of_the_entity_to_match_the_dimensions_of_the_bitmap)
{
   AllegroFlare::Prototypes::Platforming2D::Entities::FrameAnimated2D frame_animated2d_entity;
   frame_animated2d_entity.set_animation_book(&animation_book);
//(&animation_book);
   frame_animated2d_entity.set_animation("blob");
   frame_animated2d_entity.fit_to_bitmap();

   AllegroFlare::vec2d expected_size = {240, 240}; // TODO: use a different bitmap that has different
                                                   // values for width/height
   AllegroFlare::vec2d actual_size = frame_animated2d_entity.get_place_ref().size;

   EXPECT_EQ(expected_size, actual_size);
}


