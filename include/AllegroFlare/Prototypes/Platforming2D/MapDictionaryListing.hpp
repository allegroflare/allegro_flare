#pragma once


#include <string>


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

         protected:


         public:
            MapDictionaryListing(std::string tmj_filename="[unset-tmj_filename]", std::string tile_atlas_bitmap_identifier="[unset-tile_atlas_bitmap_identifier]");
            ~MapDictionaryListing();

            void set_tmj_filename(std::string tmj_filename);
            void set_tile_atlas_bitmap_identifier(std::string tile_atlas_bitmap_identifier);
            std::string get_tmj_filename() const;
            std::string get_tile_atlas_bitmap_identifier() const;
         };
      }
   }
}



