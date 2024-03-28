

#include <AllegroFlare/AssetStudio/AssetImporter.hpp>

#include <AllegroFlare/Logger.hpp>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace AssetStudio
{


AssetImporter::AssetImporter(AllegroFlare::AssetStudio::Database* asset_studio_database, std::string asset_identifier)
   : asset_studio_database(asset_studio_database)
   , asset_identifier(asset_identifier)
   , source_directory(DEFAULT_SOURCE_DIRECTORY)
   , destination_directory(DEFAULT_DESTINATION_DIRECTORY)
{
}


AssetImporter::~AssetImporter()
{
}


void AssetImporter::set_asset_studio_database(AllegroFlare::AssetStudio::Database* asset_studio_database)
{
   this->asset_studio_database = asset_studio_database;
}


void AssetImporter::set_asset_identifier(std::string asset_identifier)
{
   this->asset_identifier = asset_identifier;
}


void AssetImporter::set_source_directory(std::string source_directory)
{
   this->source_directory = source_directory;
}


void AssetImporter::set_destination_directory(std::string destination_directory)
{
   this->destination_directory = destination_directory;
}


AllegroFlare::AssetStudio::Database* AssetImporter::get_asset_studio_database() const
{
   return asset_studio_database;
}


std::string AssetImporter::get_asset_identifier() const
{
   return asset_identifier;
}


std::string AssetImporter::get_source_directory() const
{
   return source_directory;
}


std::string AssetImporter::get_destination_directory() const
{
   return destination_directory;
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
   // Check the presence of the source_directory
   // Postfis '/' for certainty
   //source_directory = source_directory + "/";
   //destination_directory = destination_directory + "/"

   if (!std::filesystem::exists(source_directory))
   {
      AllegroFlare::Logger::throw_error(
            "AllegroFlare::AssetStudio::AssetImporter::import",
            "The source asset directory \"" + source_directory + "\" does not exist."
         );
   }
   if (!std::filesystem::is_directory(source_directory))
   {
      AllegroFlare::Logger::throw_error(
            "AllegroFlare::AssetStudio::AssetImporter::import",
            "The source asset directory \"" + source_directory + "\" exists but is not a folder."
         );
   }

   // Check the presence of the destination_directory
   if (!std::filesystem::exists(destination_directory))
   {
      AllegroFlare::Logger::throw_error(
            "AllegroFlare::AssetStudio::AssetImporter::import",
            "The asset destination directory \"" + destination_directory + "\" does not exist."
         );
   }
   if (!std::filesystem::is_directory(destination_directory))
   {
      AllegroFlare::Logger::throw_error(
            "AllegroFlare::AssetStudio::AssetImporter::import",
            "The asset destination directory \"" + destination_directory + "\" exists but is not a folder."
         );
   }

   // Check that the asset exists in the database
   if (!asset_studio_database->asset_exists(asset_identifier))
   {
      AllegroFlare::Logger::throw_error(
            "AllegroFlare::AssetStudio::AssetImporter::import",
            "The asset \"" + asset_identifier + "\" does not exist."
         );
   }

   // Grab the asset
   AllegroFlare::AssetStudio::Asset *asset = asset_studio_database->find_asset_by_identifier(asset_identifier);

   // Obtain the image filenames that need to be copied
   std::vector<std::string> images_to_copy;
   if (asset->has_single_source_image())
   {
      images_to_copy.push_back(
                            asset->asset_pack_identifier
                            + "/extracted/"
                            //+ asset->intra_pack_identifier
                            //+ "/"
                            + asset->image_filename
         );
   }
   else if (asset->has_single_source_image())
   {
      // TODO: Append multiple images
      images_to_copy =
                                           asset->images_list;
   }
   else
   {
      AllegroFlare::Logger::throw_error(
            "AllegroFlare::AssetStudio::AssetImporter::import",
            "Weird error. Could not infer if asset uses a single source image or multiple source images."
         );
   }

   if (images_to_copy.empty())
   {
      AllegroFlare::Logger::throw_error(
            "AllegroFlare::AssetStudio::AssetImporter::import",
            "Weird error. When retrieving images to import, no images were present witin the asset's listing."
         );
   }

   // HERE
   // TODO: Create the directories if they do not exist (assuming the ./bin/data/assets/ directory exists)
   //     use std::filesystem::create_directories(...)

   for (auto &image_to_copy : images_to_copy)
   {
      std::cout << "Copying \"" << image_to_copy << "\"..." << std::endl;
      //std::cout << "   from: \"" << << "\"" << std::endl;
      //std::cout << "     to: \"" << << "\"" << std::endl;
      std::string full_path_to_source_file = source_directory
                                           + "/"
                                           + image_to_copy;
      std::string full_path_to_destination_file = destination_directory
                                                + "/"
                                                + image_to_copy;
      std::cout << "   from: \"" << full_path_to_source_file << "\"" << std::endl;
      std::cout << "     to: \"" << full_path_to_destination_file << "\"" << std::endl;
      std::filesystem::copy_file(full_path_to_source_file, full_path_to_destination_file);
      std::cout << "...copy successful." << std::endl;
      //std::cout << "Copying
      //std::filesystem::copy_file(images
   }

   return;
}


} // namespace AssetStudio
} // namespace AllegroFlare


