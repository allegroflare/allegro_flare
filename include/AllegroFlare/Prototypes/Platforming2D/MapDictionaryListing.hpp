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

         protected:


         public:
            MapDictionaryListing(std::string tmj_filename="[unset-tmj_filename]");
            ~MapDictionaryListing();

            void set_tmj_filename(std::string tmj_filename);
            std::string get_tmj_filename() const;
         };
      }
   }
}



