

#include <AllegroFlare/AssetStudio/Asset.hpp>




namespace AllegroFlare
{
namespace AssetStudio
{


Asset::Asset(int id, std::string identifier, std::string type, std::string description, AllegroFlare::FrameAnimation::Animation* animation, std::string image_filename, std::vector<std::string> images_list, int cell_width, int cell_height, float align_x, float align_y, float align_in_container_x, float align_in_container_y, float anchor_x, float anchor_y, ALLEGRO_BITMAP* bitmap, std::string asset_pack_identifier, std::string intra_pack_identifier)
   : id(id)
   , identifier(identifier)
   , type(type)
   , description(description)
   , animation(animation)
   , image_filename(image_filename)
   , images_list(images_list)
   , cell_width(cell_width)
   , cell_height(cell_height)
   , align_x(align_x)
   , align_y(align_y)
   , align_in_container_x(align_in_container_x)
   , align_in_container_y(align_in_container_y)
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


bool Asset::has_single_source_image()
{
   return !image_filename.empty() && images_list.empty();
}

bool Asset::has_multiple_source_images()
{
   return image_filename.empty() && (!images_list.empty());
}


} // namespace AssetStudio
} // namespace AllegroFlare


