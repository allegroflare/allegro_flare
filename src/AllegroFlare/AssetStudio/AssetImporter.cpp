

#include <AllegroFlare/AssetStudio/AssetImporter.hpp>

#include <AllegroFlare/Logger.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace AssetStudio
{


AssetImporter::AssetImporter(AllegroFlare::AssetStudio::Database* asset_studio_database)
   : asset_identifier("[unset-asset_identifier]")
   , asset_studio_database(asset_studio_database)
{
}


AssetImporter::~AssetImporter()
{
}


void AssetImporter::set_asset_identifier(std::string asset_identifier)
{
   this->asset_identifier = asset_identifier;
}


void AssetImporter::set_asset_studio_database(AllegroFlare::AssetStudio::Database* asset_studio_database)
{
   this->asset_studio_database = asset_studio_database;
}


std::string AssetImporter::get_asset_identifier() const
{
   return asset_identifier;
}


AllegroFlare::AssetStudio::Database* AssetImporter::get_asset_studio_database() const
{
   return asset_studio_database;
}


void AssetImporter::import()
{
   if (!(asset_studio_database))
   {
      std::stringstream error_message;
      error_message << "[AssetImporter::import]: error: guard \"asset_studio_database\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("AssetImporter::import: error: guard \"asset_studio_database\" not met");
   }
   if (!asset_studio_database->asset_exists(asset_identifier))
   {
      AllegroFlare::Logger::throw_error(
            "AllegroFlare::AssetStudio::AssetImporter::import",
            "The asset \"" + asset_identifier + "\" does not exist."
         );
   }
   // TODO: Get files from asset and copy into the game's directory
   return;
}


} // namespace AssetStudio
} // namespace AllegroFlare


