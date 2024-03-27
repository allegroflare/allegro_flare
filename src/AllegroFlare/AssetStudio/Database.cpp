

#include <AllegroFlare/AssetStudio/Database.hpp>

#include <AllegroFlare/Errors.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace AssetStudio
{


Database::Database()
   : assets()
   , global_identifier_prefix("[unset-global_identifier_prefix]")
   , using_global_identifier_prefix(false)
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


std::string Database::get_global_identifier_prefix() const
{
   return global_identifier_prefix;
}


bool Database::get_using_global_identifier_prefix() const
{
   return using_global_identifier_prefix;
}


void Database::set_global_identifier_prefix(std::string global_identifier_prefix)
{
   if (using_global_identifier_prefix) remove_global_identifier_prefixes();
   return;
}

std::set<std::string> Database::asset_identifiers()
{
   std::set<std::string> result;
   //if (using_global_identifier_prefix) remove_global_identifier_prefixes();
   for (auto &asset : assets)
   {
      result.insert(asset.first);
   }
   return result;
}

void Database::remove_global_identifier_prefixes(std::string identifier)
{
   if (!(using_global_identifier_prefix))
   {
      std::stringstream error_message;
      error_message << "[Database::remove_global_identifier_prefixes]: error: guard \"using_global_identifier_prefix\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Database::remove_global_identifier_prefixes: error: guard \"using_global_identifier_prefix\" not met");
   }
   // TODO: This method
   using_global_identifier_prefix = false;
   return;
}

void Database::prefix_global_identifier_prefix_to_identifiers(std::string prefix)
{
   if (!((!using_global_identifier_prefix)))
   {
      std::stringstream error_message;
      error_message << "[Database::prefix_global_identifier_prefix_to_identifiers]: error: guard \"(!using_global_identifier_prefix)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Database::prefix_global_identifier_prefix_to_identifiers: error: guard \"(!using_global_identifier_prefix)\" not met");
   }
   // TODO: This method
   std::vector<std::string> asset_keys;
   for (auto &asset : assets)
   {
      asset_keys.push_back(asset.first);
      //std::map<int, std::string> m{ {10, "potato"}, {1, "banana"} };
      //auto nodeHandler = asset.extract(10);
      //nodeHandler.key() = 2;
      //asset.insert(std::move(nodeHandler)); // { { 1, "banana" }, { 2, "potato" } }
   }

   for (auto &asset_key : asset_keys)
   {
      auto nodeHandler = assets.extract(asset_key);
      nodeHandler.key() = prefix + asset_key;
      // TODO: Validate new key does not already exist
      assets.insert(std::move(nodeHandler)); // { { 1, "banana" }, { 2, "potato" } }
   }

   using_global_identifier_prefix = true;
   return;
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

bool Database::asset_exists_as_animation(std::string identifier)
{
   if (!(assets.count(identifier) > 0)) return false;
   AllegroFlare::AssetStudio::Asset* asset = find_asset_by_identifier(identifier);
   if (asset->animation) return true;
   return false;
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


