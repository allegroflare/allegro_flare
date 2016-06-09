#ifndef __AF_BITMAP_BIN_HEADER
#define __AF_BITMAP_BIN_HEADER




#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro_flare/bin.h>




class BitmapBin : public Bin<ALLEGRO_BITMAP *>
{
public:
   BitmapBin(std::string directory="data/bitmaps");
   ~BitmapBin();
   ALLEGRO_BITMAP *load_data(std::string identifier);
   void destroy_data(ALLEGRO_BITMAP *bmp);
};




#endif
