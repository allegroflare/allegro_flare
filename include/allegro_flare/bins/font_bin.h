#ifndef __AF_FONT_BIN_HEADER
#define __AF_FONT_BIN_HEADER




#include <allegro5/allegro_font.h>
#include <allegro_flare/bin.h>




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
