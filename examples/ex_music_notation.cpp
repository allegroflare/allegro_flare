



#include <allegro_flare/allegro_flare.h>

#include <allegro_flare/drawing_interfaces/drawing_interface_allegro5.h>




class ExMusicNotation : public UIScreen
{
private:
   DrawingInterfaceAllegro5 drawing_interface_allegro5;
   MusicNotation music_notation;
   std::string music_notation_content_string;
   int notation_width;
   UITextInput *text_input;

public:
   ExMusicNotation(Display *display)
      : UIScreen(display)
      , drawing_interface_allegro5()
      , music_notation(&drawing_interface_allegro5, 16)
      , music_notation_content_string("")
      , notation_width(0)
      , text_input(new UITextInput(this, display->width()/2, display->height()-120, display->width()/2, 60))
   {
      text_input->set_text(" & ^    -6=,e75'q1| -1.,-2 er 4]");
   }

   void on_draw() override
   {
      if (music_notation_content_string != text_input->get_text())
         music_notation_content_string = text_input->get_text();

      notation_width = music_notation.draw(display->width()/2 - notation_width/2, 300, music_notation_content_string);
   }
};




int main(int, char**)
{
   Framework::initialize();
   Display *display = Framework::create_display();
   ExMusicNotation ex_music_notation = ExMusicNotation(display);
   Framework::run_loop();
   return 0;
}




