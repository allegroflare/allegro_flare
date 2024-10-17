

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
   : global_assets()
   , local_assets()
   , global_identifier_prefix(DEFAULT_GLOBAL_IDENTIFIER_PREFIX)
   , using_global_identifier_prefix(false)
{
}


Database::~Database()
{
}


void Database::set_global_assets(std::map<std::string, AllegroFlare::AssetStudio::Asset*> global_assets)
{
   this->global_assets = global_assets;
}


void Database::set_local_assets(std::map<std::string, AllegroFlare::AssetStudio::Asset*> local_assets)
{
   this->local_assets = local_assets;
}


std::map<std::string, AllegroFlare::AssetStudio::Asset*> Database::get_global_assets() const
{
   return global_assets;
}


std::map<std::string, AllegroFlare::AssetStudio::Asset*> Database::get_local_assets() const
{
   return local_assets;
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
   if (!((!using_global_identifier_prefix)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AssetStudio::Database::set_global_identifier_prefix]: error: guard \"(!using_global_identifier_prefix)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AssetStudio::Database::set_global_identifier_prefix]: error: guard \"(!using_global_identifier_prefix)\" not met");
   }
   if (using_global_identifier_prefix) remove_global_identifier_prefixes();
   this->global_identifier_prefix = global_identifier_prefix;
   prefix_global_identifier_prefix_to_identifiers(this->global_identifier_prefix);
   return;
}

void Database::remove_global_identifier_prefix()
{
   if (!(using_global_identifier_prefix))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AssetStudio::Database::remove_global_identifier_prefix]: error: guard \"using_global_identifier_prefix\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AssetStudio::Database::remove_global_identifier_prefix]: error: guard \"using_global_identifier_prefix\" not met");
   }
   if (using_global_identifier_prefix) remove_global_identifier_prefixes();
   return;
}

std::set<std::string> Database::asset_identifiers()
{
   // TODO: Test this
   std::set<std::string> result;
   for (auto &asset : global_assets) result.insert(asset.first);
   for (auto &asset : local_assets) result.insert(asset.first);
   return result;
}

void Database::remove_global_identifier_prefixes()
{
   if (!(using_global_identifier_prefix))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AssetStudio::Database::remove_global_identifier_prefixes]: error: guard \"using_global_identifier_prefix\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AssetStudio::Database::remove_global_identifier_prefixes]: error: guard \"using_global_identifier_prefix\" not met");
   }
   int prefix_length = global_identifier_prefix.length();

   // Pull out the keys first
   std::vector<std::string> asset_keys;
   for (auto &asset : global_assets)
   {
      asset_keys.push_back(asset.first);
   }

   // Go through each key, and remove n characters from the front of each key
   for (auto &asset_key : asset_keys)
   {
      auto extracted_asset_element = global_assets.extract(asset_key);
      extracted_asset_element.key() = extracted_asset_element.key().substr(prefix_length);
      // TODO: Validate new key does not already exist
      global_assets.insert(std::move(extracted_asset_element));
   }

   using_global_identifier_prefix = false;
   return;
}

void Database::prefix_global_identifier_prefix_to_identifiers(std::string prefix)
{
   if (!((!using_global_identifier_prefix)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AssetStudio::Database::prefix_global_identifier_prefix_to_identifiers]: error: guard \"(!using_global_identifier_prefix)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AssetStudio::Database::prefix_global_identifier_prefix_to_identifiers]: error: guard \"(!using_global_identifier_prefix)\" not met");
   }
   // Pull out the keys first
   std::vector<std::string> asset_keys;
   for (auto &asset : global_assets)
   {
      asset_keys.push_back(asset.first);
   }

   // Go through each key, and rename
   for (auto &asset_key : asset_keys)
   {
      auto extracted_asset_element = global_assets.extract(asset_key);
      extracted_asset_element.key() = prefix + asset_key;
      // TODO: Validate new key does not already exist
      global_assets.insert(std::move(extracted_asset_element));
   }

   global_identifier_prefix = prefix; // TODO: Test this assignment
   using_global_identifier_prefix = true;
   return;
}

bool Database::asset_exists(std::string identifier)
{
   return (local_assets.count(identifier) > 0) || (global_assets.count(identifier) > 0);
}

AllegroFlare::AssetStudio::Asset* Database::find_asset_by_identifier(std::string identifier)
{
   if (local_assets.count(identifier) != 0) return local_assets[identifier];
   if (global_assets.count(identifier) != 0) return global_assets[identifier];

   AllegroFlare::Errors::throw_error(
         "AllegroFlare::AssetStudio::Database::find_asset_by_identifier",
         "No asset exists with the identifier \"" + identifier+ "\""
      );

   return nullptr;
}

bool Database::asset_exists_as_animation(std::string identifier)
{
   if (!asset_exists(identifier)) return false;
   //if (!(local_assets.count(identifier) > 0)) return false;
   //if (!(global_assets.count(identifier) > 0)) return false;
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


