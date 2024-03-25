#pragma once


#include <AllegroFlare/AssetStudio/Asset.hpp>
#include <AllegroFlare/FrameAnimation/Animation.hpp>
#include <map>
#include <string>


namespace AllegroFlare
{
   namespace AssetStudio
   {
      class Database
      {
      private:
         std::map<std::string, AllegroFlare::AssetStudio::Asset*> assets;

      protected:


      public:
         Database();
         ~Database();

         void set_assets(std::map<std::string, AllegroFlare::AssetStudio::Asset*> assets);
         std::map<std::string, AllegroFlare::AssetStudio::Asset*> get_assets() const;
         bool asset_exists(std::string identifier="[unset-identifier]");
         AllegroFlare::AssetStudio::Asset* find_asset_by_identifier(std::string identifier="[unset-identifier]");
         AllegroFlare::FrameAnimation::Animation* find_animation_by_identifier(std::string identifier="[unset-identifier]");
      };
   }
}



