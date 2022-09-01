
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_MusicMeshTest : public ::testing::Test
{};

class AllegroFlare_MusicMeshTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/MusicMesh.hpp>


TEST_F(AllegroFlare_MusicMeshTest, can_be_created_without_blowing_up)
{
   AllegroFlare::MusicMesh music_mesh;
}


TEST_F(AllegroFlare_MusicMeshTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::MusicMesh music_mesh;
   std::string expected_error_message =
      "MusicMesh::render: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(music_mesh.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_MusicMeshTest, initialize__sets_initialized_to_true)
{
   AllegroFlare::MusicMesh music_mesh;
   ASSERT_EQ(false, music_mesh.get_initialized());
   music_mesh.initialize();
   ASSERT_EQ(true, music_mesh.get_initialized());
}


TEST_F(AllegroFlare_MusicMeshTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   AllegroFlare::MusicMesh music_mesh;
   music_mesh.render();
   SUCCEED();
}

