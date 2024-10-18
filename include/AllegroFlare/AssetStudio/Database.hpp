#pragma once


#include <AllegroFlare/AssetStudio/Asset.hpp>
#include <AllegroFlare/AssetStudio/Record.hpp>
#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/FrameAnimation/Animation.hpp>
#include <AllegroFlare/FrameAnimation/SpriteSheet.hpp>
#include <map>
#include <set>
#include <string>
#include <tuple>
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
         std::vector<AllegroFlare::AssetStudio::Record> global_records;
         std::vector<AllegroFlare::AssetStudio::Record> local_records;
         std::map<std::string, AllegroFlare::AssetStudio::Asset*> global_assets;
         std::map<std::string, AllegroFlare::AssetStudio::Asset*> local_assets;
         AllegroFlare::BitmapBin* assets_bitmap_bin;
         std::map<std::tuple<std::string, int, int, int>, AllegroFlare::FrameAnimation::SpriteSheet*> sprite_sheets;
         int sprite_sheet_scale;
         std::string global_identifier_prefix;
         bool using_global_identifier_prefix;
         void remove_global_identifier_prefixes();
         void prefix_global_identifier_prefix_to_identifiers(std::string prefix="[unset-prefix]");

      protected:


      public:
         Database(AllegroFlare::BitmapBin* assets_bitmap_bin=nullptr);
         ~Database();

         void set_global_records(std::vector<AllegroFlare::AssetStudio::Record> global_records);
         void set_local_records(std::vector<AllegroFlare::AssetStudio::Record> local_records);
         void set_global_assets(std::map<std::string, AllegroFlare::AssetStudio::Asset*> global_assets);
         void set_local_assets(std::map<std::string, AllegroFlare::AssetStudio::Asset*> local_assets);
         void set_assets_bitmap_bin(AllegroFlare::BitmapBin* assets_bitmap_bin);
         void set_sprite_sheets(std::map<std::tuple<std::string, int, int, int>, AllegroFlare::FrameAnimation::SpriteSheet*> sprite_sheets);
         void set_sprite_sheet_scale(int sprite_sheet_scale);
         std::vector<AllegroFlare::AssetStudio::Record> get_global_records() const;
         std::vector<AllegroFlare::AssetStudio::Record> get_local_records() const;
         std::map<std::string, AllegroFlare::AssetStudio::Asset*> get_global_assets() const;
         std::map<std::string, AllegroFlare::AssetStudio::Asset*> get_local_assets() const;
         AllegroFlare::BitmapBin* get_assets_bitmap_bin() const;
         std::map<std::tuple<std::string, int, int, int>, AllegroFlare::FrameAnimation::SpriteSheet*> get_sprite_sheets() const;
         int get_sprite_sheet_scale() const;
         std::string get_global_identifier_prefix() const;
         bool get_using_global_identifier_prefix() const;
         void set_global_identifier_prefix(std::string global_identifier_prefix=DEFAULT_GLOBAL_IDENTIFIER_PREFIX);
         void remove_global_identifier_prefix();
         std::set<std::string> asset_identifiers();
         std::set<std::string> global_record_identifiers();
         std::set<std::string> local_record_identifiers();
         bool asset_exists(std::string identifier="[unset-identifier]");
         AllegroFlare::AssetStudio::Asset* find_asset_by_identifier(std::string identifier="[unset-identifier]");
         bool asset_exists_as_animation(std::string identifier="[unset-identifier]");
         AllegroFlare::FrameAnimation::Animation* find_animation_by_identifier(std::string identifier="[unset-identifier]");
      };
   }
}



