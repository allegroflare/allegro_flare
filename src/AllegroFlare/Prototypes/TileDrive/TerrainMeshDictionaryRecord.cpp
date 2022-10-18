

#include <AllegroFlare/Prototypes/TileDrive/TerrainMeshDictionaryRecord.hpp>




namespace AllegroFlare
{
namespace Prototypes
{
namespace TileDrive
{


TerrainMeshDictionaryRecord::TerrainMeshDictionaryRecord(std::string tmj_filename, std::string tile_atlas_bitmap_identifier, int tile_atlas_tile_width, int tile_atlas_tile_height, AllegroFlare::Prototypes::TileDrive::TerrainMesh* terrain_mesh)
   : tmj_filename(tmj_filename)
   , tile_atlas_bitmap_identifier(tile_atlas_bitmap_identifier)
   , tile_atlas_tile_width(tile_atlas_tile_width)
   , tile_atlas_tile_height(tile_atlas_tile_height)
   , terrain_mesh(terrain_mesh)
{
}


TerrainMeshDictionaryRecord::~TerrainMeshDictionaryRecord()
{
}


void TerrainMeshDictionaryRecord::set_tmj_filename(std::string tmj_filename)
{
   this->tmj_filename = tmj_filename;
}


void TerrainMeshDictionaryRecord::set_tile_atlas_bitmap_identifier(std::string tile_atlas_bitmap_identifier)
{
   this->tile_atlas_bitmap_identifier = tile_atlas_bitmap_identifier;
}


void TerrainMeshDictionaryRecord::set_tile_atlas_tile_width(int tile_atlas_tile_width)
{
   this->tile_atlas_tile_width = tile_atlas_tile_width;
}


void TerrainMeshDictionaryRecord::set_tile_atlas_tile_height(int tile_atlas_tile_height)
{
   this->tile_atlas_tile_height = tile_atlas_tile_height;
}


void TerrainMeshDictionaryRecord::set_terrain_mesh(AllegroFlare::Prototypes::TileDrive::TerrainMesh* terrain_mesh)
{
   this->terrain_mesh = terrain_mesh;
}


std::string TerrainMeshDictionaryRecord::get_tmj_filename() const
{
   return tmj_filename;
}


std::string TerrainMeshDictionaryRecord::get_tile_atlas_bitmap_identifier() const
{
   return tile_atlas_bitmap_identifier;
}


int TerrainMeshDictionaryRecord::get_tile_atlas_tile_width() const
{
   return tile_atlas_tile_width;
}


int TerrainMeshDictionaryRecord::get_tile_atlas_tile_height() const
{
   return tile_atlas_tile_height;
}


AllegroFlare::Prototypes::TileDrive::TerrainMesh* TerrainMeshDictionaryRecord::get_terrain_mesh() const
{
   return terrain_mesh;
}


AllegroFlare::Prototypes::TileDrive::TerrainMesh* &TerrainMeshDictionaryRecord::get_terrain_mesh_ref()
{
   return terrain_mesh;
}




} // namespace TileDrive
} // namespace Prototypes
} // namespace AllegroFlare


