



#include <allegro_flare/bins/font_bin.h>

#include <allegro_flare/useful.h>




int FontBin::_get_valid_font_size(std::string num)
{
   return atoi(num.c_str());
}




FontBin::FontBin(std::string directory)
   : Bin<ALLEGRO_FONT *>(directory)
{}




FontBin::~FontBin()
{
   clear();
}




ALLEGRO_FONT *FontBin::load_data(std::string identifier)
{
   std::string actual_font_filename = identifier;
   int font_size = 16; 
   size_t pos = identifier.find_last_of(' ');
   if (pos == std::string::npos)
   {
      std::cout << "[" << __FUNCTION__ << "] font size should be included in the identifier string \"" << identifier << "\"." << std::endl;
   }
   else
   {
      actual_font_filename = identifier.substr(0, pos);
      font_size = _get_valid_font_size(identifier.substr(pos+0));
   }

   return al_load_font(actual_font_filename.c_str(), font_size, ALLEGRO_FLAGS_EMPTY);
}




void FontBin::destroy_data(ALLEGRO_FONT *f)
{
   al_destroy_font(f);
}




