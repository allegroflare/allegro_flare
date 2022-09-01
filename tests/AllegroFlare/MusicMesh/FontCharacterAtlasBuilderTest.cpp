
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


