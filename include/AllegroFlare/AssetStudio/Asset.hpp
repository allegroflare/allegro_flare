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
         std::string image_filename;
         std::vector<std::string> images_list;
         int cell_width;
         int cell_height;
         float align_x;
         float align_y;
         float align_in_container_x;
         float align_in_container_y;
         float anchor_x;
         float anchor_y;
         ALLEGRO_BITMAP* bitmap;
         std::string asset_pack_identifier;
         std::string intra_pack_identifier;
         std::vector<std::string> categories;
         std::vector<std::string> tags;
         Asset(int id=0, std::string identifier="[unset-identifier]", std::string type="[unset-type]", std::string description="[unset-description]", AllegroFlare::FrameAnimation::Animation* animation=nullptr, std::string image_filename="[unset-image_filename]", std::vector<std::string> images_list={}, int cell_width=0, int cell_height=0, float align_x=0.0f, float align_y=0.0f, float align_in_container_x=0.5f, float align_in_container_y=0.5f, float anchor_x=0.0f, float anchor_y=0.0f, ALLEGRO_BITMAP* bitmap=nullptr, std::string asset_pack_identifier="[unset-asset_pack_identifier]", std::string intra_pack_identifier="[unset-intra_pack_identifier]");
         ~Asset();

         bool has_single_source_image();
         bool has_multiple_source_images();
      };
   }
}



