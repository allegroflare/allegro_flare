#pragma once


#include <AllegroFlare/AssetStudio/Database.hpp>
#include <string>


namespace AllegroFlare
{
   namespace AssetStudio
   {
      class AssetImporter
      {
      private:
         std::string asset_identifier;
         AllegroFlare::AssetStudio::Database* asset_studio_database;

      protected:


      public:
         AssetImporter(AllegroFlare::AssetStudio::Database* asset_studio_database=nullptr);
         ~AssetImporter();

         void set_asset_identifier(std::string asset_identifier);
         void set_asset_studio_database(AllegroFlare::AssetStudio::Database* asset_studio_database);
         std::string get_asset_identifier() const;
         AllegroFlare::AssetStudio::Database* get_asset_studio_database() const;
         void import();
      };
   }
}



