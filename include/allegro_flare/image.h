#ifndef __UI_IMAGE_HEADER
#define __UI_IMAGE_HEADER




#include <allegro_flare/widget.h>




namespace allegro_flare
{
   class UIImage : public UIWidget
   {
   protected:
      ALLEGRO_COLOR color;
      ALLEGRO_BITMAP *bitmap;

   public:
      UIImage(UIWidget *parent, float x, float y, ALLEGRO_BITMAP *bitmap);

      void set_bitmap(ALLEGRO_BITMAP *bitmap);
      void set_color(ALLEGRO_COLOR color);

      void on_draw() override;
   };
}




#endif
