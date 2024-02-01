

#include <AllegroFlare/Prototypes/Platforming2D/MapDictionaryListing.hpp>




namespace AllegroFlare
{
namespace Prototypes
{
namespace Platforming2D
{


MapDictionaryListing::MapDictionaryListing(std::string tmj_filename)
   : tmj_filename(tmj_filename)
{
}


MapDictionaryListing::~MapDictionaryListing()
{
}


void MapDictionaryListing::set_tmj_filename(std::string tmj_filename)
{
   this->tmj_filename = tmj_filename;
}


std::string MapDictionaryListing::get_tmj_filename() const
{
   return tmj_filename;
}




} // namespace Platforming2D
} // namespace Prototypes
} // namespace AllegroFlare


