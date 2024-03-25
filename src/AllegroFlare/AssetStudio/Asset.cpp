

#include <AllegroFlare/AssetStudio/Asset.hpp>




namespace AllegroFlare
{
namespace AssetStudio
{


Asset::Asset(int id, std::string identifier, std::string type, std::string description, AllegroFlare::FrameAnimation::Animation* animation, int cell_width, int cell_height, int align_x, int align_y, int anchor_x, int anchor_y, ALLEGRO_BITMAP* bitmap, std::string asset_pack_identifier, std::string intra_pack_identifier)
   : id(id)
   , identifier(identifier)
   , type(type)
   , description(description)
   , animation(animation)
   , cell_width(cell_width)
   , cell_height(cell_height)
   , align_x(align_x)
   , align_y(align_y)
   , anchor_x(anchor_x)
   , anchor_y(anchor_y)
   , bitmap(bitmap)
   , asset_pack_identifier(asset_pack_identifier)
   , intra_pack_identifier(intra_pack_identifier)
   , categories()
   , tags()
{
}


Asset::~Asset()
{
}




} // namespace AssetStudio
} // namespace AllegroFlare


