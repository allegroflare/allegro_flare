#ifndef __UI_MUSIC_NOTATION_HEADER
#define __UI_MUSIC_NOTATION_HEADER




#include <allegro_flare/widget.h>
#include <allegro_flare/render_music_notation.h>




namespace allegro_flare
{
   class UIMusicNotation : public UIWidget
   {
   protected:
      MusicNotation notation;
      std::string val;

   public:
      UIMusicNotation(UIWidget *parent, float x, float y);

      std::string get_val();
      void set_val(std::string);
      void on_draw() override;
   };
}



#endif
