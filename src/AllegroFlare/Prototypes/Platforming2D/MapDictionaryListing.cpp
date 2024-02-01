

#include <AllegroFlare/Prototypes/Platforming2D/MapDictionaryListing.hpp>




namespace AllegroFlare
{
namespace Prototypes
{
namespace Platforming2D
{


MapDictionaryListing::MapDictionaryListing(std::string tmj_filename, std::string tile_atlas_bitmap_identifier)
   : tmj_filename(tmj_filename)
   , tile_atlas_bitmap_identifier(tile_atlas_bitmap_identifier)
{
}


MapDictionaryListing::~MapDictionaryListing()
{
}


void MapDictionaryListing::set_tmj_filename(std::string tmj_filename)
{
   this->tmj_filename = tmj_filename;
}


void MapDictionaryListing::set_tile_atlas_bitmap_identifier(std::string tile_atlas_bitmap_identifier)
{
   this->tile_atlas_bitmap_identifier = tile_atlas_bitmap_identifier;
}


std::string MapDictionaryListing::get_tmj_filename() const
{
   return tmj_filename;
}


std::string MapDictionaryListing::get_tile_atlas_bitmap_identifier() const
{
   return tile_atlas_bitmap_identifier;
}




} // namespace Platforming2D
} // namespace Prototypes
} // namespace AllegroFlare


