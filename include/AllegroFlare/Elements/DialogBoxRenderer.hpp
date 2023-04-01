#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Base.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      class DialogBoxRenderer
      {
      public:
         static constexpr char* DEFAULT_STANDARD_DIALOG_BOX_FONT_NAME = (char*)"Inter-Medium.ttf";
         static constexpr int DEFAULT_STANDARD_DIALOG_BOX_FONT_SIZE = -36;

      private:
         AllegroFlare::FontBin* font_bin;
         AllegroFlare::BitmapBin* bitmap_bin;
         AllegroFlare::Elements::DialogBoxes::Base* dialog_box;
         std::string standard_dialog_box_font_name;
         int standard_dialog_box_font_size;

      protected:


      public:
         DialogBoxRenderer(AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::Elements::DialogBoxes::Base* dialog_box=nullptr, std::string standard_dialog_box_font_name=DEFAULT_STANDARD_DIALOG_BOX_FONT_NAME, int standard_dialog_box_font_size=DEFAULT_STANDARD_DIALOG_BOX_FONT_SIZE);
         ~DialogBoxRenderer();

         void set_standard_dialog_box_font_name(std::string standard_dialog_box_font_name);
         void set_standard_dialog_box_font_size(int standard_dialog_box_font_size);
         std::string get_standard_dialog_box_font_name() const;
         int get_standard_dialog_box_font_size() const;
         void deps();
         void render();
      };
   }
}



