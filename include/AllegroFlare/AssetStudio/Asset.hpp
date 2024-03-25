#pragma once


#include <AllegroFlare/FrameAnimation/Animation.hpp>
#include <allegro5/allegro.h>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace AssetStudio
   {
      class Asset
      {
      private:

      protected:


      public:
         int id;
         std::string identifier;
         std::string type;
         std::string description;
         AllegroFlare::FrameAnimation::Animation* animation;
         int cell_width;
         int cell_height;
         int align_x;
         int align_y;
         int anchor_x;
         int anchor_y;
         ALLEGRO_BITMAP* bitmap;
         std::string asset_pack_identifier;
         std::string intra_pack_identifier;
         std::vector<std::string> categories;
         std::vector<std::string> tags;
         Asset(int id=0, std::string identifier="[unset-identifier]", std::string type="[unset-type]", std::string description="[unset-description]", AllegroFlare::FrameAnimation::Animation* animation=nullptr, int cell_width=0, int cell_height=0, int align_x=0.0f, int align_y=0.0f, int anchor_x=0.0f, int anchor_y=0.0f, ALLEGRO_BITMAP* bitmap=nullptr, std::string asset_pack_identifier="[unset-asset_pack_identifier]", std::string intra_pack_identifier="[unset-intra_pack_identifier]");
         ~Asset();

      };
   }
}



