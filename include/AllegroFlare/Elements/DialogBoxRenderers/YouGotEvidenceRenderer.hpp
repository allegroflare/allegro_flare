#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro.h>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace DialogBoxRenderers
      {
         class YouGotEvidenceRenderer
         {
         private:
            AllegroFlare::FontBin* font_bin;
            AllegroFlare::BitmapBin* bitmap_bin;
            std::string evidence_name;
            std::string evidence_bitmap_identifier;
            float age;
            float width;
            float height;
            ALLEGRO_FONT* obtain_notification_text_font();
            ALLEGRO_FONT* obtain_evidence_name_text_font();

         protected:


         public:
            YouGotEvidenceRenderer(AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::BitmapBin* bitmap_bin=nullptr, std::string evidence_name="[a-name-that-has-not-been-set]", std::string evidence_bitmap_identifier="[an-bitmap-identifier-that-nas-not-been-set]", float age=0, float width=1200, float height=540);
            ~YouGotEvidenceRenderer();

            std::string get_evidence_name() const;
            std::string get_evidence_bitmap_identifier() const;
            float get_age() const;
            void render();
            float get_live_reveal_counter();
            ALLEGRO_COLOR opaquify(ALLEGRO_COLOR color={0,0,0,0});
         };
      }
   }
}



