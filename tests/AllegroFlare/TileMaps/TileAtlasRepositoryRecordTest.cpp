

#include <gtest/gtest.h>

#include <AllegroFlare/TileMaps/TileAtlasRepositoryRecord.hpp>


TEST(AllegroFlare_TileMaps_TileAtlasRepositoryRecordTest, can_be_created_without_blowing_up)
{
   AllegroFlare::TileMaps::TileAtlasRepositoryRecord tile_atlas_repository_record;
}


TEST(AllegroFlare_TileMaps_TileAtlasRepositoryRecordTest, can_be_created_without_blowing_up)
{
   al_init();
   AllegroFlare::TileMaps::TileAtlasRepositoryRecord tile_atlas_repository_record;
   al_uninstall_system();
}


