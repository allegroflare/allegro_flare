#pragma once


#include <AllegroFlare/Elements/Backgrounds/ParallaxLayer.hpp>
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
            std::vector<AllegroFlare::Elements::Backgrounds::ParallaxLayer> background_layers;

         protected:


         public:
            MapDictionaryListing(std::string tmj_filename="[unset-tmj_filename]", std::string tile_atlas_bitmap_identifier="[unset-tile_atlas_bitmap_identifier]", std::vector<AllegroFlare::Elements::Backgrounds::ParallaxLayer> background_layers={});
            ~MapDictionaryListing();

            void set_tmj_filename(std::string tmj_filename);
            void set_tile_atlas_bitmap_identifier(std::string tile_atlas_bitmap_identifier);
            void set_background_layers(std::vector<AllegroFlare::Elements::Backgrounds::ParallaxLayer> background_layers);
            std::string get_tmj_filename() const;
            std::string get_tile_atlas_bitmap_identifier() const;
            std::vector<AllegroFlare::Elements::Backgrounds::ParallaxLayer> get_background_layers() const;
         };
      }
   }
}



