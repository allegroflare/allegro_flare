#ifndef __AFGUI_MUSIC_NOTATION_HEADER
#define __AFGUI_MUSIC_NOTATION_HEADER




#include <allegro_flare/music_notation.h>

#include <allegro_flare/gui/widget.h>




class FGUIMusicNotation : public FGUIWidget
{
protected:
   MusicNotation notation;
   std::string val;

public:
   FGUIMusicNotation(FGUIWidget *parent, float x, float y);

   std::string get_val();
   void set_val(std::string);

   void on_draw() override;
};




#endif
