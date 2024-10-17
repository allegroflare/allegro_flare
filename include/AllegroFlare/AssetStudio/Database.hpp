#pragma once


#include <AllegroFlare/AssetStudio/Asset.hpp>
#include <AllegroFlare/AssetStudio/Record.hpp>
#include <AllegroFlare/FrameAnimation/Animation.hpp>
#include <map>
#include <set>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace AssetStudio
   {
      class Database
      {
      public:
         static constexpr char* DEFAULT_GLOBAL_IDENTIFIER_PREFIX = (char*)"asset_studio::";

      private:
         std::vector<AllegroFlare::AssetStudio::Record> records;
         std::map<std::string, AllegroFlare::AssetStudio::Asset*> global_assets;
         std::map<std::string, AllegroFlare::AssetStudio::Asset*> local_assets;
         std::string global_identifier_prefix;
         bool using_global_identifier_prefix;
         void remove_global_identifier_prefixes();
         void prefix_global_identifier_prefix_to_identifiers(std::string prefix="[unset-prefix]");

      protected:


      public:
         Database();
         ~Database();

         void set_records(std::vector<AllegroFlare::AssetStudio::Record> records);
         void set_global_assets(std::map<std::string, AllegroFlare::AssetStudio::Asset*> global_assets);
         void set_local_assets(std::map<std::string, AllegroFlare::AssetStudio::Asset*> local_assets);
         std::vector<AllegroFlare::AssetStudio::Record> get_records() const;
         std::map<std::string, AllegroFlare::AssetStudio::Asset*> get_global_assets() const;
         std::map<std::string, AllegroFlare::AssetStudio::Asset*> get_local_assets() const;
         std::string get_global_identifier_prefix() const;
         bool get_using_global_identifier_prefix() const;
         void set_global_identifier_prefix(std::string global_identifier_prefix=DEFAULT_GLOBAL_IDENTIFIER_PREFIX);
         void remove_global_identifier_prefix();
         std::set<std::string> asset_identifiers();
         std::set<std::string> record_identifiers();
         bool asset_exists(std::string identifier="[unset-identifier]");
         AllegroFlare::AssetStudio::Asset* find_asset_by_identifier(std::string identifier="[unset-identifier]");
         bool asset_exists_as_animation(std::string identifier="[unset-identifier]");
         AllegroFlare::FrameAnimation::Animation* find_animation_by_identifier(std::string identifier="[unset-identifier]");
      };
   }
}



