#ifndef __ALLEGRO_FLARE_FONT_BIN
#define __ALLEGRO_FLARE_FONT_BIN




#include <allegro_flare/bin.h>
#include <allegro5/allegro_font.h>




class FontBin : public Bin<ALLEGRO_FONT *>
{
private:
	int _get_valid_font_size(std::string num);
public:
	FontBin(std::string directory="data/fonts");
	~FontBin();
	ALLEGRO_FONT *load_data(std::string identifier);
	void destroy_data(ALLEGRO_FONT *f);
};





#endif