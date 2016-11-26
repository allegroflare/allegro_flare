


#include <allegro_flare/allegro_flare.h>



class UITimerWidget : public UIWidget
{
private:
   float time_;

public:
   UITimerWidget(UIWidget *parent)
      : UIWidget(parent, "UITimerWidget", NULL)
      , time_(0)
   {}

   void on_timer() override
   {
      time_ = Framework::time_now;
   }

   void on_draw() override
   {
      ALLEGRO_FONT *f = Framework::font("DroidSans.ttf 40");
      std::stringstream ss;
      ss << time_;
      al_draw_text(f, color::black, 100, 100, 0, ss.str().c_str());
   }
};



class ExGUIWidgetTimer : public UIScreen
{
private:
   UITimerWidget ui_timer_widget;
public:
   ExGUIWidgetTimer(Display *d)
      : UIScreen(d)
      , ui_timer_widget(this)
   {}
};



int main(int, char**)
{
   Framework::initialize();
   Display *d = Framework::create_display();
   ExGUIWidgetTimer ex_gui_widget_timer(d);
   Framework::run_loop();
   return 0;
}



