#pragma once


#include <AllegroFlare/Prototypes/Platforming2D/ParallaxLayerListing.hpp>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace Platforming2D
      {
         class MapDictionaryListing
         {
         private:
            std::string tmj_filename;
            std::string tile_atlas_bitmap_identifier;
            std::vector<AllegroFlare::Prototypes::Platforming2D::ParallaxLayerListing> background_layer_listings;

         protected:


         public:
            MapDictionaryListing(std::string tmj_filename="[unset-tmj_filename]", std::string tile_atlas_bitmap_identifier="[unset-tile_atlas_bitmap_identifier]", std::vector<AllegroFlare::Prototypes::Platforming2D::ParallaxLayerListing> background_layer_listings={});
            ~MapDictionaryListing();

            void set_tmj_filename(std::string tmj_filename);
            void set_tile_atlas_bitmap_identifier(std::string tile_atlas_bitmap_identifier);
            void set_background_layer_listings(std::vector<AllegroFlare::Prototypes::Platforming2D::ParallaxLayerListing> background_layer_listings);
            std::string get_tmj_filename() const;
            std::string get_tile_atlas_bitmap_identifier() const;
            std::vector<AllegroFlare::Prototypes::Platforming2D::ParallaxLayerListing> get_background_layer_listings() const;
         };
      }
   }
}



