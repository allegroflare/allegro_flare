
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Testing/ErrorAssertions.hpp>

class AllegroFlare_TileMaps_MultiMeshTest : public ::testing::Test
{};

class AllegroFlare_TileMaps_MultiMeshTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/TileMaps/MultiMesh.hpp>


TEST_F(AllegroFlare_TileMaps_MultiMeshTest, can_be_created_without_blowing_up)
{
   AllegroFlare::TileMaps::MultiMesh multi_mesh;
}


TEST_F(AllegroFlare_TileMaps_MultiMeshTest, initialize__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::TileMaps::MultiMesh multi_mesh;
   EXPECT_THROW_GUARD_ERROR(
      multi_mesh.initialize(),
      "AllegroFlare::TileMaps::MultiMesh::initialize",
      "al_is_system_installed()"
   );
}


TEST_F(AllegroFlare_TileMaps_MultiMeshTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   AllegroFlare::TileMaps::MultiMesh multi_mesh;
   multi_mesh.initialize();
   multi_mesh.render();
}


TEST_F(AllegroFlare_TileMaps_MultiMeshTestWithAllegroRenderingFixture, CAPTURE__render__will_render_the_mesh)
{
   ALLEGRO_BITMAP *texture = get_bitmap_bin_ref()["uv.png"];
   AllegroFlare::TileMaps::MultiMesh multi_mesh;
   multi_mesh.set_texture(texture);
   multi_mesh.initialize();

   multi_mesh.append_raw(300, 200, 100, 100, 100, 100, 200, 200);
   multi_mesh.append_raw(600, 300, 100, 100, 100, 100, 200, 200);

   multi_mesh.render();
   al_flip_display();
}


TEST_F(AllegroFlare_TileMaps_MultiMeshTestWithAllegroRenderingFixture, append_raw__will_append_an_item_to_the_mesh)
{
   ALLEGRO_BITMAP *texture = get_bitmap_bin_ref()["uv.png"];
   AllegroFlare::TileMaps::MultiMesh multi_mesh;
   multi_mesh.set_texture(texture);
   multi_mesh.initialize();

   multi_mesh.append_raw(300, 200, 100, 100, 100, 100, 200, 200);
   multi_mesh.append_raw(600, 300, 100, 100, 100, 100, 200, 200);

   // TODO: assert
}


TEST_F(AllegroFlare_TileMaps_MultiMeshTestWithAllegroRenderingFixture, CAPTURE__remove__will_remove_the_item_from_the_mesh)
{
   ALLEGRO_BITMAP *texture = get_bitmap_bin_ref()["uv.png"];
   AllegroFlare::TileMaps::MultiMesh multi_mesh;
   multi_mesh.set_texture(texture);
   multi_mesh.initialize();

   multi_mesh.append_raw(300, 200, 100, 100, 100, 100, 200, 200);
   multi_mesh.append_raw(600, 300, 100, 100, 100, 100, 200, 200);
   multi_mesh.append_raw(1000, 500, 100, 100, 100, 100, 200, 200);

   multi_mesh.remove(1);

   multi_mesh.render();
   al_flip_display();
}


TEST_F(AllegroFlare_TileMaps_MultiMeshTestWithAllegroRenderingFixture,
   remove__will_return_the_now_obsolete_index_number_that_has_replaced_the_removed_index_index_number)
{
   ALLEGRO_BITMAP *texture = get_bitmap_bin_ref()["uv.png"];
   AllegroFlare::TileMaps::MultiMesh multi_mesh;
   multi_mesh.set_texture(texture);
   multi_mesh.initialize();

   multi_mesh.append_raw(300, 200, 100, 100, 100, 100, 200, 200);
   multi_mesh.append_raw(600, 300, 100, 100, 100, 100, 200, 200);
   multi_mesh.append_raw(1000, 500, 100, 100, 100, 100, 200, 200);

   int moved_index = multi_mesh.remove(1);
   EXPECT_EQ(2, moved_index);
}


TEST_F(AllegroFlare_TileMaps_MultiMeshTestWithAllegroRenderingFixture,
   append_raw__will_return_the_index_number_of_the_newly_added_index)
{
   ALLEGRO_BITMAP *texture = get_bitmap_bin_ref()["uv.png"];
   AllegroFlare::TileMaps::MultiMesh multi_mesh;
   multi_mesh.set_texture(texture);
   multi_mesh.initialize();

   EXPECT_EQ(0, multi_mesh.append_raw(300, 200, 100, 100, 100, 100, 200, 200));
   EXPECT_EQ(1, multi_mesh.append_raw(600, 300, 100, 100, 100, 100, 200, 200));
   EXPECT_EQ(2, multi_mesh.append_raw(1000, 500, 100, 100, 100, 100, 200, 200));
}


TEST_F(AllegroFlare_TileMaps_MultiMeshTestWithAllegroRenderingFixture,
   remove__will_return_the_old_index_of_the_existing_element_whos_value_was_reissued_to_the_removed_index)
{
   ALLEGRO_BITMAP *texture = get_bitmap_bin_ref()["uv.png"];
   AllegroFlare::TileMaps::MultiMesh multi_mesh;
   multi_mesh.set_texture(texture);
   multi_mesh.initialize();

   int index = -1;

   multi_mesh.append_raw(300, 200, 100, 100, 100, 100, 200, 200);
   multi_mesh.append_raw(1000, 500, 100, 100, 100, 100, 200, 200);
   index = multi_mesh.append_raw(600, 300, 100, 100, 100, 100, 200, 200);
   multi_mesh.append_raw(800, 500, 100, 100, 100, 100, 200, 200);

   ASSERT_EQ(2, index);
   EXPECT_EQ(3, multi_mesh.remove(index));
}


TEST_F(AllegroFlare_TileMaps_MultiMeshTestWithAllegroRenderingFixture,
   remove__on_an_item_index_that_is_less_than_zero__will_throw_an_error)
{
   AllegroFlare::TileMaps::MultiMesh multi_mesh;
   multi_mesh.initialize();

   std::string expected_error_message = "AllegroFlare::TileMaps::MultiMesh::remove() error: The item_index that was passed (-1) "
                                        "cannot be less than zero.";
   EXPECT_THROW_WITH_MESSAGE(multi_mesh.remove(-1), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_TileMaps_MultiMeshTestWithAllegroRenderingFixture,
   remove__on_an_item_index_that_is_greater_than_the_last_item_index__will_throw_an_error)
{
   AllegroFlare::TileMaps::MultiMesh multi_mesh;
   multi_mesh.initialize();

   int last_index = -1;
   multi_mesh.append_raw(300, 200, 100, 100, 100, 100, 200, 200);
   multi_mesh.append_raw(1000, 500, 100, 100, 100, 100, 200, 200);
   last_index = multi_mesh.append_raw(800, 500, 100, 100, 100, 100, 200, 200);

   std::string expected_error_message = "AllegroFlare::TileMaps::MultiMesh::remove() error: The item_index that was passed (3) "
                                        "cannot be greater than or equal to the largest existing item index (2).";
   EXPECT_THROW_WITH_MESSAGE(multi_mesh.remove(last_index+1), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_TileMaps_MultiMeshTestWithAllegroRenderingFixture, append__before_initialized__will_throw_an_error)
{
   // TODO
}


TEST_F(AllegroFlare_TileMaps_MultiMeshTestWithAllegroRenderingFixture,
   CAPTURE__append__will_use_the_atlas_data_to_build_uv)
{
   ALLEGRO_BITMAP *texture = get_bitmap_bin_ref()["uv.png"];
   AllegroFlare::TileMaps::MultiMeshUVAtlas atlas({
      { 0, {    0,    0,  100,  100 } },
      { 1, {  100,    0,  200,  100 } },
      { 2, {  200,    0,  300,  100 } },
      { 3, {  300,    0,  400,  100 } },
   });
   AllegroFlare::TileMaps::MultiMesh multi_mesh;
   multi_mesh.set_texture(texture);
   multi_mesh.set_atlas(atlas);
   multi_mesh.initialize();

   multi_mesh.append(1, 300, 600);
   multi_mesh.append(2, 700, 550);
   
   multi_mesh.render();
   al_flip_display();
}


