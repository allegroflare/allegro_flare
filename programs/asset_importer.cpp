#include <allegro5/allegro.h>

#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/AssetStudio/DatabaseCSVLoader.hpp>
#include <AllegroFlare/AssetStudio/AssetImporter.hpp>
#include <stdexcept>
#include <iostream>

std::string ASSETS_FULL_PATH = "/Users/markoates/Assets/";
std::string ASSETS_DB_CSV_FILENAME = "assets_db.csv";


int main(int argc, char** argv)
{
   std::vector<std::string> args;
   for (int i=1; i<argc; i++) args.push_back(argv[i]);

   if (args.size() != 1)
   {
      throw std::runtime_error("Expecting one argument, the identifier for the asset.");
   }

   std::string asset_identifier = args[0];



   al_init();
   al_init_image_addon();

   std::cout << "Loading asset records from CSV" << std::endl;
   // Load the CSV database
   AllegroFlare::AssetStudio::DatabaseCSVLoader loader;
   loader.set_csv_full_path(ASSETS_FULL_PATH + ASSETS_DB_CSV_FILENAME);
   loader.load_records();

   // Load the CSV-loaded records into the database
   AllegroFlare::AssetStudio::Database asset_studio_database;
   asset_studio_database.set_global_records(loader.get_records());

   // Create assets for ALL records
   std::cout << "Creating AssetStudio::Asset objects for every record" << std::endl;
   AllegroFlare::BitmapBin assets_bitmap_bin;
   assets_bitmap_bin.set_full_path(ASSETS_FULL_PATH);
   asset_studio_database.set_assets_bitmap_bin(&assets_bitmap_bin);
   asset_studio_database.load_all_global_assets_from_all_global_records();

   // Create the AssetImporter
   AllegroFlare::AssetStudio::AssetImporter asset_importer;
   asset_importer.set_asset_studio_database(&asset_studio_database);
   asset_importer.set_asset_identifier(asset_identifier);
   // NOTE: Using the default directories as set in the AssetImporter

   // Perform the import
   asset_importer.import();

   assets_bitmap_bin.clear();
   al_uninstall_system();

   return 0;
}
