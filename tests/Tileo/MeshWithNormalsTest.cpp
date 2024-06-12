
#include <gtest/gtest.h>

#include <Tileo/MeshWithNormals.hpp>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Vec2D.hpp>
#include <AllegroFlare/Random.hpp>
#include <Tileo/Shaders/AllegroDefault.hpp>
#include <allegro5/allegro_color.h> // for al_color_html


#if defined(_WIN32) || defined(_WIN64)
//#define TEST_FIXTURES_PATH "/msys64/home/Mark/Repos/allegro_flare/tests/fixtures/"
#define TEST_FIXTURE_TEST_RUN_SNAPSHOTS_FOLDER "/msys64/home/Mark/Repos/allegro_flare/tmp/test_snapshots/"
#else
//#define TEST_FIXTURES_PATH "/Users/markoates/Repos/allegro_flare/tests/fixtures/"
#define TEST_FIXTURE_TEST_RUN_SNAPSHOTS_FOLDER "/Users/markoates/Repos/allegro_flare/tmp/test_snapshots/"
#endif


class Tileo_MeshWithNormalsRenderingFixtureTest : public ::testing::Test
{
private:
   //ALLEGRO_DISPLAY *display;

public:
   ALLEGRO_DISPLAY *display;
   Tileo_MeshWithNormalsRenderingFixtureTest()
      : display(nullptr)
   {}

   virtual void SetUp() override
   {
      ASSERT_EQ(false, al_is_system_installed());
      ASSERT_EQ(true, al_init());
      al_init_primitives_addon();
      al_set_new_display_flags(ALLEGRO_PROGRAMMABLE_PIPELINE | ALLEGRO_OPENGL);
      display = al_create_display(1920, 1080);
   }

   virtual void TearDown() override
   {
      if (display) al_destroy_display(display);
      al_shutdown_primitives_addon();
      al_uninstall_system();
   }
};

class Tileo_MeshWithNormalsTestFixture : public ::testing::Test {};


TEST_F(Tileo_MeshWithNormalsTestFixture, can_be_created_without_blowing_up)
{
   Tileo::MeshWithNormals mesh_with_normals;
}


TEST_F(Tileo_MeshWithNormalsRenderingFixtureTest, initialize__works_without_blowing_up)
{
   Tileo::MeshWithNormals mesh_with_normals(6, 4, 16, 16);
   mesh_with_normals.initialize();
   mesh_with_normals.destroy();
}


TEST_F(Tileo_MeshWithNormalsRenderingFixtureTest, initialize__with_num_columns_less_than_zero__throws_an_error)
{
   Tileo::MeshWithNormals mesh_with_normals(-1, 4, 16, 16);
   std::string expected_error_message = AllegroFlare::Logger::build_guard_error_message(
      "Tileo::MeshWithNormals::initialize",
      "(num_columns >= 0)"
   );
   EXPECT_THROW_WITH_MESSAGE(mesh_with_normals.initialize(), std::runtime_error, expected_error_message);
}


TEST_F(Tileo_MeshWithNormalsRenderingFixtureTest, initialize__with_num_rows_less_than_zero__throws_an_error)
{
   Tileo::MeshWithNormals mesh_with_normals(6, -1, 16, 16);
   std::string expected_error_message = AllegroFlare::Logger::build_guard_error_message(
      "Tileo::MeshWithNormals::initialize",
      "(num_rows >= 0)"
   );
   EXPECT_THROW_WITH_MESSAGE(mesh_with_normals.initialize(), std::runtime_error, expected_error_message);
}


TEST_F(Tileo_MeshWithNormalsRenderingFixtureTest, initialize__if_called_more_than_once__throws_an_error)
{
   Tileo::MeshWithNormals mesh_with_normals(6, 4, 16, 16);
   mesh_with_normals.initialize();
   std::string expected_error_message = AllegroFlare::Logger::build_guard_error_message(
      "Tileo::MeshWithNormals::initialize",
      "(!initialized)"
   );
   EXPECT_THROW_WITH_MESSAGE(mesh_with_normals.initialize(), std::runtime_error, expected_error_message);
   mesh_with_normals.destroy();
}


TEST_F(Tileo_MeshWithNormalsRenderingFixtureTest, set_tile__if_called_before_initialization__throws_an_error)
{
   // TODO
}


TEST_F(Tileo_MeshWithNormalsRenderingFixtureTest, set_tile__without_an_atlas__throws_an_error)
{
   // TODO
}


TEST_F(Tileo_MeshWithNormalsRenderingFixtureTest, set_tile__with_a_tile_x_that_is_out_of_bounds__does_nothing)
{
   // TODO
}


TEST_F(Tileo_MeshWithNormalsRenderingFixtureTest, set_tile__with_a_tile_y_that_is_out_of_bounds__does_nothing)
{
   // TODO
}


TEST_F(Tileo_MeshWithNormalsRenderingFixtureTest, vertexes_will_render_as_expected)
{
   Tileo::MeshWithNormals mesh_with_normals(6, 4, 16, 16);
   mesh_with_normals.initialize();

   std::vector<TILEO_TILE_VERTEX> vertexes = mesh_with_normals.get_vertexes_ref();
   ALLEGRO_VERTEX_DECL* vertex_declaration = mesh_with_normals.obtain_vertex_declaration();
   ALLEGRO_BITMAP* texture = nullptr;

   al_draw_prim(&vertexes[0], vertex_declaration, texture, 0, vertexes.size(), ALLEGRO_PRIM_TRIANGLE_LIST);

   mesh_with_normals.destroy();
}


#include <Tileo/Shaders/MeshWithNormals.hpp>


typedef std::pair<int, int> normaled_tile;

void fill_rect(int x1, int y1, int x2, int y2, normaled_tile t, Tileo::MeshWithNormals &mesh)
{
   for (int y=y1; y<=y2; y++)
      for (int x=x1; x<=x2; x++)
   {
      mesh.set_tile(x, y, t.first); //tile_id);
      mesh.set_normal_tile(x, y, t.second); //normal_til_id);
   }
}

void set_tile(int x, int y, normaled_tile t, Tileo::MeshWithNormals &mesh)
{
   mesh.set_tile(x, y, t.first);
   mesh.set_normal_tile(x, y, t.second);
}

AllegroFlare::vec3d build_light_from(float arc, float z=1.0)
{
   AllegroFlare::vec2d vec = AllegroFlare::vec2d::polar_coords(arc * (3.14159 * 2), 1.0f);
   return AllegroFlare::vec3d({vec.x, vec.y, z}).normalized();
}


AllegroFlare::vec3d build_light_from_top_right(float z=1.0) { return build_light_from(0.875, z); }
AllegroFlare::vec3d build_light_from_top(float z=1.0) { return build_light_from(0.75, z); }


TEST_F(Tileo_MeshWithNormalsRenderingFixtureTest,
   VISUAL__vertexes_will_render_as_expected)
{
   al_init_image_addon();
   AllegroFlare::BitmapBin bitmap_bin;
// TODO: improve this:
#if defined(_WIN32) || defined(_WIN64)
      std::string TEST_FIXTURE_BITMAP_FOLDER = "/msys64/home/Mark/Repos/allegro_flare/bin/data/bitmaps";
#else
      std::string TEST_FIXTURE_BITMAP_FOLDER = "/Users/markoates/Repos/allegro_flare/bin/data/bitmaps";
#endif
   bitmap_bin.set_full_path(TEST_FIXTURE_BITMAP_FOLDER);
   //ALLEGRO_BITMAP* tile_map_texture = bitmap_bin["even-illumination-01.png"];
   ALLEGRO_BITMAP* tile_map_texture = bitmap_bin["tiles_dungeon_v1.1.png"];
   ALLEGRO_BITMAP* irrelevant_texture = bitmap_bin["test_texture.png"];
   ALLEGRO_BITMAP* normal_map_texture = bitmap_bin["normal-tileset-01.png"];
   AllegroFlare::TileMaps::PrimMeshAtlas atlas;
   atlas.duplicate_bitmap_and_load(tile_map_texture, 16, 16);
   AllegroFlare::TileMaps::PrimMeshAtlas normal_atlas;
   normal_atlas.duplicate_bitmap_and_load(normal_map_texture, 16, 16);
   Tileo::MeshWithNormals mesh_with_normals(25, 15, 16*4.8, 16*4.5, &atlas, &normal_atlas);
   mesh_with_normals.initialize();
   Tileo::Shaders::MeshWithNormals shader;
   shader.initialize();

   std::vector<std::pair<int, int>> tile_and_normal_tile_pairs = {
      { 2, 2 }, { 18, 3 }, { 19, 0 }, { 12, 5 }, { 17, 6 }, { 8, 7 }
   };

   int num_tiles_in_atlas = atlas.get_tile_index_size();
   int num_tiles_in_normal_atlas = normal_atlas.get_tile_index_size();
   AllegroFlare::Random random(time(0));
   for (int y=0; y<mesh_with_normals.get_num_rows(); y++)
      for (int x=0; x<mesh_with_normals.get_num_columns(); x++)
      {
         int i = (x + y * mesh_with_normals.get_num_columns());
         //int pair_to_pick = (x + y * mesh_with_normals.get_num_columns()) % tile_and_normal_tile_pairs.size();
         //int pair_to_pick = random.get_random_int(0, (tile_and_normal_tile_pairs.size()-1));
         ////int tile_id = (x + y * mesh_with_normals.get_num_columns());
         //tile_num_to_set = tile_num_to_set % num_tiles_in_atlas;
         //mesh_with_normals.set_tile(x, y, tile_id); //tile_num_to_set);

         // random
         int r1 = random.get_random_int(0, (num_tiles_in_atlas/2)-1);
         int r2 = random.get_random_int(0, num_tiles_in_normal_atlas-1);
         while (r2 == 9) r2 = random.get_random_int(0, num_tiles_in_normal_atlas-1);
         int tile_id = r1 % num_tiles_in_atlas;
         int normal_tile_id = r2 % num_tiles_in_normal_atlas;

         // sequential
         //int tile_id = i % num_tiles_in_atlas;
         //int normal_tile_id = i % num_tiles_in_normal_atlas;

         // picking from preset pairs:
         //int pair_to_pick = random.get_random_int(0, (tile_and_normal_tile_pairs.size()-1));
         //int tile_id = tile_and_normal_tile_pairs[pair_to_pick].first;
         //int normal_tile_id = tile_and_normal_tile_pairs[pair_to_pick].second;

         mesh_with_normals.set_tile(x, y, tile_id); //tile_num_to_set);
         mesh_with_normals.set_normal_tile(x, y, normal_tile_id); //normal_tile_num_to_set);
      }

   //fill_rect(5, 4, 25-6, 15-4, {0, 0}, mesh_with_normals);
   //fill_rect(5, 15-3, 25-6, 15, {4, 3}, mesh_with_normals);

   set_tile(9, 15-4, {22, 12}, mesh_with_normals);
   set_tile(10, 15-4, {22, 13}, mesh_with_normals);
   set_tile(11, 15-4, {22, 14}, mesh_with_normals);

   std::vector<TILEO_TILE_VERTEX> &vertexes = mesh_with_normals.get_vertexes_ref();
   ALLEGRO_VERTEX_DECL* vertex_declaration = mesh_with_normals.obtain_vertex_declaration();
   ALLEGRO_BITMAP* texture = atlas.get_bitmap();
   //ALLEGRO_BITMAP* texture = nullptr;

   //int passes = 60*14;
   int passes = 60;

   //int passes = 30;
   for (int i=0; i<passes; i++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 1});
      //al_clear_to_color(al_color_html("a4dddb"));
      float arc = (float)((int)(((float)(i)/passes * 16))) / 16;

      // spinning
      AllegroFlare::vec2d vec = AllegroFlare::vec2d::polar_coords(arc * (3.14159 * 2), 3.0f); //*(3.14159 / 2), 1.0f);
      AllegroFlare::vec3d vec_n = AllegroFlare::vec3d({vec.x, vec.y, 3.0}).normalized();

      // fixed
      //AllegroFlare::vec3d vec_n = build_light_from_top_right();
      //AllegroFlare::vec3d vec_n = build_light_from_top();

      vec_n.y *= -1;

      shader.activate();
      shader.set_flat_color(ALLEGRO_COLOR{1, 0, 1, 1}, 0.3);
      shader.set_primary_texture(atlas.get_bitmap());
      shader.set_normal_texture(normal_atlas.get_bitmap());
      shader.set_light_direction(vec_n);
      shader.set_light_spread(0);
      shader.set_light_attenuation(1.0);


      al_draw_prim(&vertexes[0], vertex_declaration, irrelevant_texture, 0, vertexes.size(), ALLEGRO_PRIM_TRIANGLE_LIST);


      al_use_shader(nullptr);
      //shader.deactivate();
      float x = 1920/2, y = 1080/2, r=300;
      //al_draw_circle(x, y, r, ALLEGRO_COLOR{0, 1, 1, 1}, 3.0f);
      //al_draw_filled_circle(x+r*vec_n.x, y+-r*vec_n.y, 6, ALLEGRO_COLOR{1, 1, 1, 1});

      //al_draw_bitmap(texture, 1920/2, 1080/2, 0);

      al_flip_display();
   }


   // TODO: improve this test snapshot naming inference
   std::string output_image_full_filename =
      TEST_FIXTURE_TEST_RUN_SNAPSHOTS_FOLDER "Tileo_MeshWithNormalsRenderingFixtureTest_VISUAL__vertexes_will_r"
         "ender_as_expected.png";
      //"the_image_with_the_flat_color.png";
   ASSERT_EQ(true, al_save_bitmap(output_image_full_filename.c_str(), al_get_backbuffer(display)));

   //sleep(2);

   mesh_with_normals.destroy();
   al_shutdown_image_addon();
}


