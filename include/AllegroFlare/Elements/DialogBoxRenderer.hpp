#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Base.hpp>
#include <AllegroFlare/FontBin.hpp>


namespace AllegroFlare
{
   namespace Elements
   {
      class DialogBoxRenderer
      {
      private:
         AllegroFlare::FontBin* font_bin;
         AllegroFlare::BitmapBin* bitmap_bin;
         AllegroFlare::Elements::DialogBoxes::Base* dialog_box;

      protected:


      public:
         DialogBoxRenderer(AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::Elements::DialogBoxes::Base* dialog_box=nullptr);
         ~DialogBoxRenderer();

         void render();
      };
   }
}



