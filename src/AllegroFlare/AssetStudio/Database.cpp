

#include <AllegroFlare/AssetStudio/Database.hpp>

#include <AllegroFlare/Errors.hpp>


namespace AllegroFlare
{
namespace AssetStudio
{


Database::Database()
   : assets()
{
}


Database::~Database()
{
}


void Database::set_assets(std::map<std::string, AllegroFlare::AssetStudio::Asset*> assets)
{
   this->assets = assets;
}


std::map<std::string, AllegroFlare::AssetStudio::Asset*> Database::get_assets() const
{
   return assets;
}


bool Database::asset_exists(std::string identifier)
{
   return (assets.count(identifier) > 0);
}

AllegroFlare::AssetStudio::Asset* Database::find_asset_by_identifier(std::string identifier)
{
   if (assets.count(identifier) == 0)
   {
      AllegroFlare::Errors::throw_error(
            "AllegroFlare::AssetStudio::Database::find_asset_by_identifier",
            "No asset exists with the identifier \"" + identifier+ "\""
         );
   }
   return assets[identifier];
}

AllegroFlare::FrameAnimation::Animation* Database::find_animation_by_identifier(std::string identifier)
{
   if (!asset_exists(identifier))
   {
      AllegroFlare::Errors::throw_error(
            "AllegroFlare::AssetStudio::Database::find_animation_by_identifier",
            "No asset exists for identifier \"" + identifier+ "\" to evaluate for an animation."
         );
   }
   AllegroFlare::AssetStudio::Asset* asset = find_asset_by_identifier(identifier);
   if (!asset->animation)
   {
      AllegroFlare::Errors::throw_error(
            "AllegroFlare::AssetStudio::Database::find_animation_by_identifier",
            "The asset \"" + identifier+ "\" exists but does not contain an animation."
         );
   }
   return asset->animation;
}


} // namespace AssetStudio
} // namespace AllegroFlare


