
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Random.hpp>


class AllegroFlare_MusicMesh_MusicMeshTest : public ::testing::Test
{};

class AllegroFlare_MusicMesh_MusicMeshTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/MusicMesh/MusicMesh.hpp>


TEST_F(AllegroFlare_MusicMesh_MusicMeshTest, can_be_created_without_blowing_up)
{
   AllegroFlare::MusicMesh::MusicMesh music_mesh;
}


TEST_F(AllegroFlare_MusicMesh_MusicMeshTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::MusicMesh::MusicMesh music_mesh;
   std::string expected_error_message =
      "MusicMesh::render: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(music_mesh.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_MusicMesh_MusicMeshTestWithAllegroRenderingFixture,
   CAPTURE__render__will_not_blow_up)
{
   AllegroFlare::MusicMesh::MusicMesh music_mesh(&get_font_bin_ref());
   music_mesh.initialize();
   AllegroFlare::Random random;

   uint32_t start = AllegroFlare::MusicMesh::FontCharacterAtlasBuilder::UNICODE_RANGE_START;

   for (int i=0; i<256*8; i++)
   {
      music_mesh.add_music_symbol(random.get_random_int(0, 1920), random.get_random_int(0, 1080), start + 32 + 2);
      //music_mesh.add_music_symbol(300, 300, start + 32 - 2); // g clef
   }

   music_mesh.render();
   al_flip_display();
   sleep(2);
}

