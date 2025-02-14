

#include <AllegroFlare/FontBin.hpp>


namespace AllegroFlare
{
   int FontBin::_get_valid_font_size(std::string num)
   {
      return atoi(num.c_str());
   }




   FontBin::FontBin()
      : Bin<std::string, ALLEGRO_FONT *>("FontBin")
   {}




   FontBin::~FontBin()
   {
   }



   bool FontBin::validate()
   {
      if (!al_is_font_addon_initialized())
      {
         std::cout << CONSOLE_COLOR_RED
                   << "[FontBin::validate] not properly initialized (requires al_init_font_addon()). "
                   << " Will crash probably crash."
                   << CONSOLE_COLOR_DEFAULT
                   << std::endl;
         return false;
      }
      if (!al_is_ttf_addon_initialized())
      {
         std::cout << CONSOLE_COLOR_RED
                   << "[FontBin::validate] not properly initialized (requires al_init_ttf_addon()). "
                   << " Will crash probably crash."
                   << CONSOLE_COLOR_DEFAULT
                   << std::endl;
         return false;
      }
      return true;
   }



   ALLEGRO_FONT *FontBin::load_data(std::string identifier)
   {
      validate();
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

      static int EMPTY_FLAGS = 0;

      return al_load_font(actual_font_filename.c_str(), font_size, EMPTY_FLAGS);
   }




   void FontBin::destroy_data(ALLEGRO_FONT *f)
   {
      al_destroy_font(f);
   }



   std::string FontBin::build_standard_path(std::string data_folder_path)
   {
      return data_folder_path + "fonts/"; // TODO: Consider moving "fonts/" to a constant
   }
}


