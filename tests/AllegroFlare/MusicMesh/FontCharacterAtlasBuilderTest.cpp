
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_MusicMesh_FontCharacterAtlasBuilderTest : public ::testing::Test
{};

class AllegroFlare_MusicMesh_FontCharacterAtlasBuilderTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/MusicMesh/FontCharacterAtlasBuilder.hpp>


TEST_F(AllegroFlare_MusicMesh_FontCharacterAtlasBuilderTest, can_be_created_without_blowing_up)
{
   AllegroFlare::MusicMesh::FontCharacterAtlasBuilder font_character_atlas_builder;
}


TEST_F(AllegroFlare_MusicMesh_FontCharacterAtlasBuilderTestWithAllegroRenderingFixture,
   CAPTURE__create__will_not_blow_up)
{
   AllegroFlare::MusicMesh::FontCharacterAtlasBuilder font_character_atlas_builder(&get_font_bin_ref());
   ALLEGRO_BITMAP *created_bitmap = font_character_atlas_builder.create();
   ASSERT_NE(nullptr, created_bitmap);
   al_draw_bitmap(created_bitmap, 0, 0, 0);
   al_flip_display();
   sleep_for(2);
}


