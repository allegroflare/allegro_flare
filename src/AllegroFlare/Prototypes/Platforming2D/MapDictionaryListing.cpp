

#include <AllegroFlare/Prototypes/Platforming2D/MapDictionaryListing.hpp>




namespace AllegroFlare
{
namespace Prototypes
{
namespace Platforming2D
{


MapDictionaryListing::MapDictionaryListing(std::string tmj_filename, std::string tile_atlas_bitmap_identifier, std::vector<AllegroFlare::Elements::Backgrounds::ParallaxLayer> background_layers)
   : tmj_filename(tmj_filename)
   , tile_atlas_bitmap_identifier(tile_atlas_bitmap_identifier)
   , background_layers(background_layers)
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


void MapDictionaryListing::set_background_layers(std::vector<AllegroFlare::Elements::Backgrounds::ParallaxLayer> background_layers)
{
   this->background_layers = background_layers;
}


std::string MapDictionaryListing::get_tmj_filename() const
{
   return tmj_filename;
}


std::string MapDictionaryListing::get_tile_atlas_bitmap_identifier() const
{
   return tile_atlas_bitmap_identifier;
}


std::vector<AllegroFlare::Elements::Backgrounds::ParallaxLayer> MapDictionaryListing::get_background_layers() const
{
   return background_layers;
}




} // namespace Platforming2D
} // namespace Prototypes
} // namespace AllegroFlare


