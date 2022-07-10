#pragma once


#include <AllegroFlare/Elements/StoryboardPages/Base.hpp>
#include <allegro5/allegro.h>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace StoryboardPages
      {
         class Image : public AllegroFlare::Elements::StoryboardPages::Base
         {
         private:
            ALLEGRO_BITMAP* bitmap;

         public:
            Image(ALLEGRO_BITMAP* bitmap=nullptr);
            virtual ~Image();

            void set_bitmap(ALLEGRO_BITMAP* bitmap);
            ALLEGRO_BITMAP* get_bitmap();
            virtual void start() override;
            virtual void update() override;
            virtual void render() override;
            virtual void advance() override;
         };
      }
   }
}



