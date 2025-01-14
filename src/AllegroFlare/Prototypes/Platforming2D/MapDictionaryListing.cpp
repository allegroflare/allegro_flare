

#include <AllegroFlare/Prototypes/Platforming2D/MapDictionaryListing.hpp>




namespace AllegroFlare
{
namespace Prototypes
{
namespace Platforming2D
{


MapDictionaryListing::MapDictionaryListing(std::string tmj_filename, std::string tile_atlas_bitmap_identifier, std::vector<AllegroFlare::Prototypes::Platforming2D::ParallaxLayerListing> background_layer_listings)
   : tmj_filename(tmj_filename)
   , tile_atlas_bitmap_identifier(tile_atlas_bitmap_identifier)
   , background_layer_listings(background_layer_listings)
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


void MapDictionaryListing::set_background_layer_listings(std::vector<AllegroFlare::Prototypes::Platforming2D::ParallaxLayerListing> background_layer_listings)
{
   this->background_layer_listings = background_layer_listings;
}


std::string MapDictionaryListing::get_tmj_filename() const
{
   return tmj_filename;
}


std::string MapDictionaryListing::get_tile_atlas_bitmap_identifier() const
{
   return tile_atlas_bitmap_identifier;
}


std::vector<AllegroFlare::Prototypes::Platforming2D::ParallaxLayerListing> MapDictionaryListing::get_background_layer_listings() const
{
   return background_layer_listings;
}




} // namespace Platforming2D
} // namespace Prototypes
} // namespace AllegroFlare


