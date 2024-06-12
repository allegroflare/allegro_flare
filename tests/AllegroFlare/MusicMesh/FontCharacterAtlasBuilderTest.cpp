
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Testing/Comparison/AllegroFlare/Vec2D.hpp>


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
   clear();
   al_draw_bitmap(created_bitmap, 0, 0, 0);
   al_flip_display();
   //sleep_for(2);
}


TEST_F(AllegroFlare_MusicMesh_FontCharacterAtlasBuilderTestWithAllegroRenderingFixture,
   DISABLED__CAPTURE__get_uv_for_index__will_return_the_uv_coordinates_for_a_glyph_at_index)
{
   AllegroFlare::MusicMesh::FontCharacterAtlasBuilder font_character_atlas_builder(&get_font_bin_ref());
   ALLEGRO_BITMAP *created_bitmap = font_character_atlas_builder.create();
   ASSERT_NE(nullptr, created_bitmap);
   uint32_t start = AllegroFlare::MusicMesh::FontCharacterAtlasBuilder::UNICODE_RANGE_START;

   std::pair<AllegroFlare::Vec2D, AllegroFlare::Vec2D> expected_uvs = { { 108, 0 }, { 162, 112 } };
   std::pair<AllegroFlare::Vec2D, AllegroFlare::Vec2D> actual_uvs =
      font_character_atlas_builder.get_uv_for_index(start + 2);

   EXPECT_EQ(expected_uvs, actual_uvs);


   std::pair<AllegroFlare::Vec2D, AllegroFlare::Vec2D> expected_uvs_2 = { { 108, 112 }, { 162, 224 } };
   std::pair<AllegroFlare::Vec2D, AllegroFlare::Vec2D> actual_uvs_2 =
      font_character_atlas_builder.get_uv_for_index(start + 32 + 2);

   EXPECT_EQ(expected_uvs_2, actual_uvs_2);


   std::pair<AllegroFlare::Vec2D, AllegroFlare::Vec2D> expected_uvs_3 = { { 162, 224}, { 216, 336 } };
   std::pair<AllegroFlare::Vec2D, AllegroFlare::Vec2D> actual_uvs_3 =
      font_character_atlas_builder.get_uv_for_index(start + 32*2 + 3);

   EXPECT_EQ(expected_uvs_3, actual_uvs_3);
}


