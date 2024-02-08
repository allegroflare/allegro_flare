
#include <gtest/gtest.h>

#include <AllegroFlare/Prototypes/Platforming2D/Entities/Basic2D.hpp>


#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Testing/CustomComparison.hpp>


#include <allegro5/allegro_color.h> // for al_color_html
#include <allegro5/allegro_primitives.h> // for al_draw_line


class AllegroFlare_Prototypes_Platforming2D_Entities_Basic2DTest : public ::testing::Test {};
class AllegroFlare_Prototypes_Platforming2D_Entities_Basic2DWithAllegroRenderingFixtureTest
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{
private:
   virtual void SetUp() override
   {
// TODO: improve this:
#if defined(_WIN32) || defined(_WIN64)
      std::string TEST_FIXTURE_BITMAP_FOLDER = "/msys64/home/Mark/Repos/allegro_flare/tests/fixtures/bitmaps";
#else
      std::string TEST_FIXTURE_BITMAP_FOLDER = "/Users/markoates/Repos/allegro_flare/tests/fixtures/bitmaps";
#endif
      AllegroFlare::Testing::WithAllegroRenderingFixture::SetUp();
      get_bitmap_bin_ref().set_full_path(TEST_FIXTURE_BITMAP_FOLDER);
   }

public:
   ALLEGRO_BITMAP *FIXTURE_get_bitmap(std::string filename)
   {
      AllegroFlare::BitmapBin &bitmap_bin = get_bitmap_bin_ref();
      return bitmap_bin[filename];
   }
};




TEST_F(AllegroFlare_Prototypes_Platforming2D_Entities_Basic2DTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D basic2d;
}


TEST_F(AllegroFlare_Prototypes_Platforming2D_Entities_Basic2DTest, TYPE__has_the_expected_value)
{
   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D basic2d;
   EXPECT_EQ("Entities/Basic2D", basic2d.get_type());
}


TEST_F(AllegroFlare_Prototypes_Platforming2D_Entities_Basic2DTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D basic2d;
   EXPECT_EQ(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D::TYPE, basic2d.get_type());
}


TEST_F(AllegroFlare_Prototypes_Platforming2D_Entities_Basic2DTest, update__can_be_called_without_blowing_up)
{
   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D basic2d_entity;
   basic2d_entity.update();
   SUCCEED();
}


TEST_F(AllegroFlare_Prototypes_Platforming2D_Entities_Basic2DTest,
   DISABLED__update__with_a_position_velocity__will_apply_the_position_velocity_to_the_position_place)
   // TODO: ensure this functionality is managed in the collision stepper and this can be removed
{
   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D basic2d_entity;
   basic2d_entity.get_velocity_ref().position = {2, 3};

   basic2d_entity.update();

   AllegroFlare::vec2d expected_position = {2, 3};
   AllegroFlare::vec2d actual_position = basic2d_entity.get_place_ref().position;

   EXPECT_EQ(expected_position, actual_position);
}


TEST_F(AllegroFlare_Prototypes_Platforming2D_Entities_Basic2DTest,
   DISABLED__update__with_a_rotation_velocity__will_apply_the_rotation_velocity_to_the_rotation_place)
   // TODO: ensure this functionality is managed in the collision stepper and this can be removed
{
   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D basic2d_entity;
   basic2d_entity.get_velocity_ref().rotation = 0.01;

   basic2d_entity.update();

   float expected_rotation = 0.01;
   float actual_rotation = basic2d_entity.get_place_ref().rotation;

   EXPECT_EQ(expected_rotation, actual_rotation);
}


TEST_F(AllegroFlare_Prototypes_Platforming2D_Entities_Basic2DTest,
   DISABLED__update__with_a_scale_velocity__will_apply_the_scale_velocity_to_the_scale_place)
   // TODO: this is a bit awkward because the scale velocity initializes to (1.0, 1.0), meaning it increases on each
   // update.  For now, it will be disabled until it's clear what the ideal arrangement should be
{
   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D basic2d_entity;
   basic2d_entity.get_velocity_ref().scale = { 0.01, 0.99 };

   basic2d_entity.update();

   AllegroFlare::vec2d expected_scale = { 1.01, 1.99 };
   AllegroFlare::vec2d actual_scale = basic2d_entity.get_place_ref().scale;

   EXPECT_EQ(expected_scale, actual_scale);
}


TEST_F(AllegroFlare_Prototypes_Platforming2D_Entities_Basic2DWithAllegroRenderingFixtureTest,
   draw__without_primitives_addon_initialized__will_throw_an_error)
{
   // TODO
}


TEST_F(AllegroFlare_Prototypes_Platforming2D_Entities_Basic2DWithAllegroRenderingFixtureTest,
   draw__can_be_called_without_blowing_up)
{
   //al_init_primitives_addon();
   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D basic2d_entity;
   basic2d_entity.draw();
   SUCCEED();
}


TEST_F(AllegroFlare_Prototypes_Platforming2D_Entities_Basic2DWithAllegroRenderingFixtureTest,
   CAPTURE__draw__with_a_bitmap__will_display_the_image)
{
   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D basic2d_entity;
   basic2d_entity.set_bitmap(FIXTURE_get_bitmap("golden_dragon.png"));

   al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
   basic2d_entity.draw();

   ALLEGRO_COLOR expected_sampled_color = al_color_html("f6e272"); // the color of the dragon's right toe nail
   ALLEGRO_COLOR actual_sampled_color = al_get_pixel(al_get_target_bitmap(), 46, 67);

   EXPECT_EQ(expected_sampled_color, actual_sampled_color);

   al_flip_display();
   //sleep(2);
}


TEST_F(AllegroFlare_Prototypes_Platforming2D_Entities_Basic2DWithAllegroRenderingFixtureTest,
   draw__with_a_modified_place__will_display_the_image)
{
   ALLEGRO_BITMAP *bitmap = FIXTURE_get_bitmap("test-sprite-128.png");

   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D basic2d_entity;
   basic2d_entity.get_place_ref().size = {(float)al_get_bitmap_width(bitmap), (float)al_get_bitmap_height(bitmap)};
   basic2d_entity.get_place_ref().position = {800, 400};
   basic2d_entity.get_place_ref().scale = {7, 7};
   basic2d_entity.get_place_ref().rotation = 0.2f;
   basic2d_entity.set_bitmap(bitmap);

   basic2d_entity.draw();

   al_flip_display();
   //sleep(2);

   SUCCEED(); // TODO: pick pixel
}


TEST_F(AllegroFlare_Prototypes_Platforming2D_Entities_Basic2DWithAllegroRenderingFixtureTest,
   CAPTURE__draw__will_render_the_different_alignment_strategies_as_expected)
{
   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D basic2d_entity;
   basic2d_entity.set_bitmap(FIXTURE_get_bitmap("golden_dragon.png"));
   basic2d_entity.set_draw_debug(true);
   basic2d_entity.fit_to_bitmap();
   basic2d_entity.get_place_ref().size.x *= 0.75;
   basic2d_entity.get_place_ref().size.y *= 0.75;
   basic2d_entity.get_place_ref().scale = {2.0, 2.0};

   basic2d_entity.get_bitmap_placement_ref().scale = { 1.25, 1.25 };

   float y = 1080/7*2;
   al_draw_line(0, y, 1920, y, ALLEGRO_COLOR{1.0f, 1.0f, 0.0f, 1.0f}, 1.0f);
   {
      basic2d_entity.get_place_ref().position = {1920/10*1, y};
      basic2d_entity.set_bitmap_alignment_strategy("top_left");
      basic2d_entity.draw();

      basic2d_entity.get_place_ref().position = {1920/10*3, y};
      basic2d_entity.set_bitmap_alignment_strategy("centered");
      basic2d_entity.draw();

      basic2d_entity.get_place_ref().position = {1920/10*5, y};
      basic2d_entity.set_bitmap_alignment_strategy("bottom_centered");
      basic2d_entity.draw();

      basic2d_entity.get_place_ref().position = {1920/10*7, y};
      basic2d_entity.set_bitmap_alignment_strategy("bottom_centered_edge");
      basic2d_entity.draw();

      basic2d_entity.get_place_ref().position = {1920/10*9, y};
      basic2d_entity.set_bitmap_alignment_strategy("top_centered");
      basic2d_entity.draw();
   }
   y = 1080/7*5;
   basic2d_entity.get_place_ref().align = { 0.5f, 1.0f };
   al_draw_line(0, y, 1920, y, ALLEGRO_COLOR{1.0f, 1.0f, 0.0f, 1.0f}, 1.0f);
   {
      basic2d_entity.get_place_ref().position = {1920/10*1, y};
      basic2d_entity.set_bitmap_alignment_strategy("top_left");
      basic2d_entity.draw();

      basic2d_entity.get_place_ref().position = {1920/10*3, y};
      basic2d_entity.set_bitmap_alignment_strategy("centered");
      basic2d_entity.draw();

      basic2d_entity.get_place_ref().position = {1920/10*5, y};
      basic2d_entity.set_bitmap_alignment_strategy("bottom_centered");
      basic2d_entity.draw();

      basic2d_entity.get_place_ref().position = {1920/10*7, y};
      basic2d_entity.set_bitmap_alignment_strategy("bottom_centered_edge");
      basic2d_entity.draw();

      basic2d_entity.get_place_ref().position = {1920/10*9, y};
      basic2d_entity.set_bitmap_alignment_strategy("top_centered");
      basic2d_entity.draw();
   }

   //al_draw_line(0, 1080/2, 1920, 1080/2, ALLEGRO_COLOR{1.0f, 1.0f, 0.0f, 1.0f}, 1.0f);
   //al_draw_line(0, 1080/2, 1920, 1080/2, ALLEGRO_COLOR{1, 1, 0, 1});

   al_flip_display();
   //sleep(4);

   SUCCEED(); // TODO: pick pixel
}


TEST_F(AllegroFlare_Prototypes_Platforming2D_Entities_Basic2DWithAllegroRenderingFixtureTest,
   CAPTURE__draw__with_bitmap_scale_and_rotation_applied__will_render_the_alignment_strategies_as_expected)
{
   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D basic2d_entity;
   basic2d_entity.set_bitmap(FIXTURE_get_bitmap("golden_dragon.png"));
   basic2d_entity.set_draw_debug(true);
   basic2d_entity.fit_to_bitmap();
   basic2d_entity.get_place_ref().position = {1920/8, 1080/2};
   basic2d_entity.get_place_ref().align = {0.5, 0.5};
   basic2d_entity.get_place_ref().size.x *= 0.75;
   basic2d_entity.get_place_ref().size.y *= 0.75;
   basic2d_entity.get_place_ref().scale = {2.0, 2.0};

   basic2d_entity.get_bitmap_placement_ref().scale = { 1.5, 1.5 };
   basic2d_entity.get_bitmap_placement_ref().rotation = 0.2;

   basic2d_entity.get_place_ref().position.x = 1920/10*1;
   basic2d_entity.set_bitmap_alignment_strategy("top_left");
   basic2d_entity.draw();

   basic2d_entity.get_place_ref().position.x = 1920/10*3;
   basic2d_entity.set_bitmap_alignment_strategy("centered");
   basic2d_entity.draw();

   basic2d_entity.get_place_ref().position.x = 1920/10*5;
   basic2d_entity.set_bitmap_alignment_strategy("bottom_centered");
   basic2d_entity.draw();

   basic2d_entity.get_place_ref().position.x = 1920/10*7;
   basic2d_entity.set_bitmap_alignment_strategy("bottom_centered_edge");
   basic2d_entity.draw();

   basic2d_entity.get_place_ref().position.x = 1920/10*9;
   basic2d_entity.set_bitmap_alignment_strategy("top_centered");
   basic2d_entity.draw();

   al_draw_line(0, 1080/2, 1920, 1080/2, ALLEGRO_COLOR{1.0f, 1.0f, 0.0f, 1.0f}, 1.0f);
   //al_draw_line(0, 1080/2, 1920, 1080/2, ALLEGRO_COLOR{1, 1, 0, 1});

   al_flip_display();
   //sleep(4);

   SUCCEED(); // TODO: pick pixel
}


TEST_F(AllegroFlare_Prototypes_Platforming2D_Entities_Basic2DWithAllegroRenderingFixtureTest,
   CAPTURE__draw__with_different_bitmap_blend_modes__will_render_as_expected)
{
   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D basic2d_entity;
   basic2d_entity.set_bitmap(FIXTURE_get_bitmap("golden_dragon.png"));
   basic2d_entity.set_draw_debug(true);
   basic2d_entity.fit_to_bitmap();
   basic2d_entity.get_place_ref().position = {1920/8, 1080/2};
   basic2d_entity.get_place_ref().align = {0.5, 0.5};
   basic2d_entity.get_place_ref().size.x *= 0.75;
   basic2d_entity.get_place_ref().size.y *= 0.75;
   basic2d_entity.get_place_ref().scale = {2.0, 2.0};
   basic2d_entity.set_bitmap_alignment_strategy("centered");

   basic2d_entity.get_bitmap_placement_ref().scale = { 1.5, 1.5 };
   basic2d_entity.get_bitmap_placement_ref().rotation = 0.2;

   al_clear_to_color(ALLEGRO_COLOR{0.4, 0.42, 0.46, 1.0});

   basic2d_entity.get_place_ref().position.x = 1920/8*2;
   basic2d_entity.set_bitmap_blend_mode(
         AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D::BlendMode::NORMAL
      );
   basic2d_entity.draw();

   basic2d_entity.get_place_ref().position.x = 1920/8*4;
   basic2d_entity.set_bitmap_blend_mode(
         AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D::BlendMode::ADDITIVE
      );
   basic2d_entity.draw();

   basic2d_entity.get_place_ref().position.x = 1920/8*6;
   basic2d_entity.set_bitmap_blend_mode(
         AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D::BlendMode::MULTIPLY
      );
   basic2d_entity.draw();

   //al_draw_line(0, 1080/2, 1920, 1080/2, ALLEGRO_COLOR{1.0f, 1.0f, 0.0f, 1.0f}, 1.0f);
   //al_draw_line(0, 1080/2, 1920, 1080/2, ALLEGRO_COLOR{1, 1, 0, 1});

   al_flip_display();
   //sleep(4);

   SUCCEED(); // TODO: pick pixel
}


TEST_F(AllegroFlare_Prototypes_Platforming2D_Entities_Basic2DWithAllegroRenderingFixtureTest,
   fit_to_bitmap__without_a_bitmap__will_raise_an_exception)
{
   // TODO
}

TEST_F(AllegroFlare_Prototypes_Platforming2D_Entities_Basic2DWithAllegroRenderingFixtureTest,
   fit_to_bitmap__will_set_the_size_of_the_entity_to_match_the_dimensions_of_the_bitmap)
{
   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D basic2d_entity;
   basic2d_entity.set_bitmap(FIXTURE_get_bitmap("test-sprite-128.png"));
   basic2d_entity.fit_to_bitmap();

   AllegroFlare::vec2d expected_size = {128, 128}; // TODO: use a different bitmap that has different
                                                   // values for width/height
   AllegroFlare::vec2d actual_size = basic2d_entity.get_place_ref().size;

   EXPECT_EQ(expected_size, actual_size);
}



