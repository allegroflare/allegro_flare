



#include <allegro_flare/bins/bitmap_bin.h>








BitmapBin::BitmapBin(std::string directory)
	: Bin<ALLEGRO_BITMAP *>(directory)
{}




BitmapBin::~BitmapBin()
{
	clear();
}




ALLEGRO_BITMAP *BitmapBin::load_data(std::string identifier)
{
	return al_load_bitmap(identifier.c_str());
}




void BitmapBin::destroy_data(ALLEGRO_BITMAP *bmp)
{
	al_destroy_bitmap(bmp);
}


