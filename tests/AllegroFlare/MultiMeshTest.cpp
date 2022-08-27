
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_MultiMeshTest : public ::testing::Test
{};

class AllegroFlare_MultiMeshTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/MultiMesh.hpp>


TEST_F(AllegroFlare_MultiMeshTest, can_be_created_without_blowing_up)
{
   AllegroFlare::MultiMesh multi_mesh;
}


TEST_F(AllegroFlare_MultiMeshTest, initialize__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::MultiMesh multi_mesh;
   std::string expected_error_message =
      "MultiMesh::initialize: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(multi_mesh.initialize(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_MultiMeshTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   AllegroFlare::MultiMesh multi_mesh;
   multi_mesh.initialize();
   multi_mesh.render();
}


TEST_F(AllegroFlare_MultiMeshTestWithAllegroRenderingFixture, CAPTURE__render__will_render_the_mesh)
{
   ALLEGRO_BITMAP *texture = get_bitmap_bin_ref()["uv.png"];
   AllegroFlare::MultiMesh multi_mesh;
   multi_mesh.set_texture(texture);
   multi_mesh.initialize();

   multi_mesh.append(300, 200, 100, 100);
   multi_mesh.append(600, 300, 100, 100);

   multi_mesh.render();
   al_flip_display();
}


TEST_F(AllegroFlare_MultiMeshTestWithAllegroRenderingFixture, CAPTURE__remove__will_remove_the_item_from_the_mesh)
{
   ALLEGRO_BITMAP *texture = get_bitmap_bin_ref()["uv.png"];
   AllegroFlare::MultiMesh multi_mesh;
   multi_mesh.set_texture(texture);
   multi_mesh.initialize();

   multi_mesh.append(300, 200, 100, 100);
   multi_mesh.append(600, 300, 100, 100);
   multi_mesh.append(1000, 500, 100, 100);

   multi_mesh.remove(1);

   multi_mesh.render();
   al_flip_display();
}


TEST_F(AllegroFlare_MultiMeshTestWithAllegroRenderingFixture,
   remove__will_return_the_now_obsolete_index_number_that_has_replaced_the_removed_index_index_number)
{
   ALLEGRO_BITMAP *texture = get_bitmap_bin_ref()["uv.png"];
   AllegroFlare::MultiMesh multi_mesh;
   multi_mesh.set_texture(texture);
   multi_mesh.initialize();

   multi_mesh.append(300, 200, 100, 100);
   multi_mesh.append(600, 300, 100, 100);
   multi_mesh.append(1000, 500, 100, 100);

   int moved_index = multi_mesh.remove(1);
   EXPECT_EQ(2, moved_index);
}


TEST_F(AllegroFlare_MultiMeshTestWithAllegroRenderingFixture,
   append_item_from_atlas_index__will_use_the_atlas_data_to_build_uv)
{
   //TODO: test atlas features
}


