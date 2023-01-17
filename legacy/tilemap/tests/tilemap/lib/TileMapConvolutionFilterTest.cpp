

#include <gtest/gtest.h>

#include <tilemap/lib/TileMapConvolutionFilter.hpp>


#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }


TEST(TileMapConvolutionFilterTest, can_be_created_without_arguments)
{
   //TileMapConvolutionFilter filter;
}


TEST(TileMapConvolutionFilterTest, process__with_a_tile_set_of_size_not_equal_to_16_raises_an_exception)
{
   std::vector<ALLEGRO_BITMAP *> tile_set;
   for (intptr_t i=0; i<2; i++) tile_set.push_back((ALLEGRO_BITMAP *)(i));

   TileMap source_tilemap(0, 0, 16);
   TileMap destination_tilemap(0, 0, 16);
   TileMapConvolutionFilter filter(tile_set, &source_tilemap, &destination_tilemap);

   std::string expected_message = "Cannot TileMapConvolutionFilter::process(), expecting tile_set.size() to == 16.";
   ASSERT_THROW_WITH_MESSAGE(filter.process(nullptr), std::runtime_error, expected_message);
}


TEST(TileMapConvolutionFilterTest, process__with_an_invalid_destination_tilemap_raises_an_exception)
{
   std::vector<ALLEGRO_BITMAP *> tile_set;
   for (intptr_t i=0; i<16; i++) tile_set.push_back((ALLEGRO_BITMAP *)(i));

   TileMap source_tilemap(0, 0, 16);
   TileMapConvolutionFilter filter(tile_set, &source_tilemap, nullptr);

   std::string expected_message = "Cannot TileMapConvolutionFilter::process() on a nullptr destination_tilemap.";
   ASSERT_THROW_WITH_MESSAGE(filter.process(nullptr), std::runtime_error, expected_message);
}


TEST(TileMapConvolutionFilterTest, process__with_an_invalid_source_tilemap_raises_an_exception)
{
   std::vector<ALLEGRO_BITMAP *> tile_set;
   for (intptr_t i=0; i<16; i++) tile_set.push_back((ALLEGRO_BITMAP *)(i));

   TileMap destination_tilemap(0, 0, 16);
   TileMapConvolutionFilter filter(tile_set, nullptr, &destination_tilemap);

   std::string expected_message = "Cannot TileMapConvolutionFilter::process() on a nullptr source_tilemap.";
   ASSERT_THROW_WITH_MESSAGE(filter.process(nullptr), std::runtime_error, expected_message);
}


TEST(TileMapConvolutionFilterTest, process__when_width_and_height_do_not_match_between_source_and_destination_raises_an_exception)
{
   const int TILEMAP_WIDTH = 20;
   const int TILEMAP_HEIGHT = 13;
   std::vector<ALLEGRO_BITMAP *> tile_set;
   for (intptr_t i=0; i<16; i++) tile_set.push_back((ALLEGRO_BITMAP *)(i));
   TileMap source_tilemap(TILEMAP_WIDTH, TILEMAP_HEIGHT, 16);
   TileMap destination_tilemap(0, 0, 16);
   TileMapConvolutionFilter filter(tile_set, &source_tilemap, &destination_tilemap);

   std::string expected_error_message = "TileMapConvolutionFilter::process(), Width and height must match between source_tilemap and destination_tilemap";

   ASSERT_THROW_WITH_MESSAGE(filter.process(nullptr), std::runtime_error, expected_error_message);

   destination_tilemap.set_width_and_height(TILEMAP_WIDTH+1, TILEMAP_HEIGHT);
   ASSERT_THROW_WITH_MESSAGE(filter.process(nullptr), std::runtime_error, expected_error_message);

   destination_tilemap.set_width_and_height(TILEMAP_WIDTH, TILEMAP_HEIGHT+1);
   ASSERT_THROW_WITH_MESSAGE(filter.process(nullptr), std::runtime_error, expected_error_message);
}


TEST(TileMapConvolutionFilterTest, process__modifies_the_destination_map)
{
   //std::vector<ALLEGRO_BITMAP *> tile_set;
   //for (intptr_t i=0; i<16; i++) tile_set.push_back((ALLEGRO_BITMAP *)(i));

   //const int TILEMAP_WIDTH = 20;
   //const int TILEMAP_HEIGHT = 13;
   //ALLEGRO_BITMAP *grass_tile = (ALLEGRO_BITMAP *)(intptr_t(99));

   //TileMap source_tilemap(TILEMAP_WIDTH, TILEMAP_HEIGHT, 16);
   //TileMap destination_tilemap(1, 1, 16);

   //TileMapConvolutionFilter filter(tile_set, &source_tilemap, &destination_tilemap);

   //filter.process(nullptr);

   //ASSERT_EQ(TILEMAP_WIDTH, destination_tilemap.get_width());
   //ASSERT_EQ(TILEMAP_HEIGHT, destination_tilemap.get_height());
}


int main(int argc, char **argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}


