#pragma once


#include <AllegroFlare/AssetStudio/Asset.hpp>
#include <AllegroFlare/FrameAnimation/Animation.hpp>
#include <map>
#include <set>
#include <string>


namespace AllegroFlare
{
   namespace AssetStudio
   {
      class Database
      {
      private:
         std::map<std::string, AllegroFlare::AssetStudio::Asset*> assets;
         std::string global_identifier_prefix;
         bool using_global_identifier_prefix;
         void remove_global_identifier_prefixes(std::string identifier="[unset-identifier]");

      protected:


      public:
         Database();
         ~Database();

         void set_assets(std::map<std::string, AllegroFlare::AssetStudio::Asset*> assets);
         std::map<std::string, AllegroFlare::AssetStudio::Asset*> get_assets() const;
         std::string get_global_identifier_prefix() const;
         bool get_using_global_identifier_prefix() const;
         void set_global_identifier_prefix(std::string global_identifier_prefix="[unset-global_identifier_prefix]");
         std::set<std::string> asset_identifiers();
         void prefix_global_identifier_prefix_to_identifiers(std::string prefix="[unset-prefix]");
         bool asset_exists(std::string identifier="[unset-identifier]");
         AllegroFlare::AssetStudio::Asset* find_asset_by_identifier(std::string identifier="[unset-identifier]");
         bool asset_exists_as_animation(std::string identifier="[unset-identifier]");
         AllegroFlare::FrameAnimation::Animation* find_animation_by_identifier(std::string identifier="[unset-identifier]");
      };
   }
}



