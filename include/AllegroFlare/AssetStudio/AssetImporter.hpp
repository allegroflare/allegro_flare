#pragma once


#include <AllegroFlare/AssetStudio/Database.hpp>
#include <string>


namespace AllegroFlare
{
   namespace AssetStudio
   {
      class AssetImporter
      {
      public:
         static constexpr char* DEFAULT_SOURCE_DIRECTORY = (char*)"/Users/markoates/Assets/";
         static constexpr char* DEFAULT_DESTINATION_DIRECTORY = (char*)"./bin/data/assets/";

      private:
         AllegroFlare::AssetStudio::Database* asset_studio_database;
         std::string asset_identifier;
         std::string source_directory;
         std::string destination_directory;

      protected:


      public:
         AssetImporter(AllegroFlare::AssetStudio::Database* asset_studio_database=nullptr, std::string asset_identifier="[unset-asset_identifier]");
         ~AssetImporter();

         void set_asset_studio_database(AllegroFlare::AssetStudio::Database* asset_studio_database);
         void set_asset_identifier(std::string asset_identifier);
         void set_source_directory(std::string source_directory);
         void set_destination_directory(std::string destination_directory);
         AllegroFlare::AssetStudio::Database* get_asset_studio_database() const;
         std::string get_asset_identifier() const;
         std::string get_source_directory() const;
         std::string get_destination_directory() const;
         void import();
         static void create_directories_to_filename(std::string filename_with_path="[unset-create_directories]");
      };
   }
}



