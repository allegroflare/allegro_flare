



#include <allegro_flare/image.h>
#include <allegro_flare/box.h>
#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/Useful.hpp> // for tostring




namespace allegro_flare
{
   UIImage::UIImage(UIWidget *parent, float x, float y, ALLEGRO_BITMAP *_bitmap)
      : UIWidget(parent, "UIImage", new UISurfaceAreaBox(x, y, _bitmap ? al_get_bitmap_width(_bitmap) : 0, _bitmap ? al_get_bitmap_height(_bitmap) : 0))
      , color(AllegroFlare::color::white)
      , bitmap(_bitmap)
   {}




   void UIImage::on_draw()
   {
      if (bitmap) al_draw_tinted_bitmap(bitmap, color, 0, 0, ALLEGRO_FLAGS_EMPTY);
   }




   void UIImage::set_bitmap(ALLEGRO_BITMAP *bitmap)
   {
      this->bitmap = bitmap;
      place.size.x = bitmap ? al_get_bitmap_width(bitmap) : 0;
      place.size.y = bitmap ? al_get_bitmap_height(bitmap) : 0;
   }




   void UIImage::set_color(ALLEGRO_COLOR color)
   {
      this->color = color;
   }
}



