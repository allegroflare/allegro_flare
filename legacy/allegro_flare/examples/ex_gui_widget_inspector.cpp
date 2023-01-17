



#include <allegro_flare/allegro_flare.h>




using namespace allegro_flare;
using namespace AllegroFlare;



template <class T>
class incrementer
{
private:
   T increment;
   T val;
   T initial;
public:
   incrementer(T initial_val, T inc)
      : val(initial_val)
      , initial(initial_val)
      , increment(inc)
   {}
   T operator=(const T &other)
   {
      val = other;
      return val;
   }
   T operator+=(T increment_multiplier)
   {
      val += increment * increment_multiplier;
      return val;
   }
   T operator++(int)
   {
      float return_val = val;
      val += increment;
      return return_val;
   }
   T operator--(int)
   {
      float return_val = val;
      val -= increment;
      return return_val;
   }
   T reset()
   {
      val = initial;
      return val;
   }
};




class UIWidgetInspector : public UIFramedWindow
{
public:
   UIWidget *target_widget;
   incrementer<float> y_cursor;

   UIWidgetInspector(UIWidget *parent)
      : UIFramedWindow(parent, 400, 300, 340, 340)
      , target_widget(NULL)
      , y_cursor(60, 26)
   {
      new UIDraggableRegion(this, place.size.x/2, place.size.y/2, place.size.x, place.size.y);
   }

   void on_draw()
   {
      UIFramedWindow::on_draw();

      ALLEGRO_FONT *font = Framework::font("DroidSans.ttf 15");
      ALLEGRO_FONT *font2 = Framework::font("DroidSans.ttf 15");
      float x_cursor = 160;
      incrementer<float> y_cursor(60, 24);

      al_draw_text(font, color::cornsilk, 10, 10, 0, "Widget Inspector");

      if (!target_widget)
      {
         al_draw_text(font, color::color(color::white, 0.2), place.size.x/2, place.size.y/2, ALLEGRO_ALIGN_CENTER, "(No Widget Selected)");
         return;
      }

      al_draw_text(font, color::white, x_cursor, y_cursor++, ALLEGRO_ALIGN_RIGHT, (tostring("id")).c_str());
      al_draw_text(font, color::white, x_cursor, y_cursor++, ALLEGRO_ALIGN_RIGHT, (tostring(UI_ATTR__UI_WIDGET_TYPE)).c_str());
      y_cursor += 0.5f;
      al_draw_text(font, color::white, x_cursor, y_cursor++, ALLEGRO_ALIGN_RIGHT, (tostring("position.x")).c_str());
      al_draw_text(font, color::white, x_cursor, y_cursor++, ALLEGRO_ALIGN_RIGHT, (tostring("position.y").c_str()));
      al_draw_text(font, color::white, x_cursor, y_cursor++, ALLEGRO_ALIGN_RIGHT, (tostring("size.x")).c_str());
      al_draw_text(font, color::white, x_cursor, y_cursor++, ALLEGRO_ALIGN_RIGHT, (tostring("size.y")).c_str());
      y_cursor += 0.5f;
      al_draw_text(font, color::white, x_cursor, y_cursor++, ALLEGRO_ALIGN_RIGHT, (tostring("rotation")).c_str());
      al_draw_text(font, color::white, x_cursor, y_cursor++, ALLEGRO_ALIGN_RIGHT, (tostring("scale.x")).c_str());
      al_draw_text(font, color::white, x_cursor, y_cursor++, ALLEGRO_ALIGN_RIGHT, (tostring("scale.y")).c_str());

      y_cursor.reset();
      x_cursor += 10;

      al_draw_text(font2, color::white, x_cursor, y_cursor++, 0, (target_widget->get("id")).c_str());
      al_draw_text(font2, color::white, x_cursor, y_cursor++, 0, (target_widget->get(UI_ATTR__UI_WIDGET_TYPE)).c_str());
      y_cursor += 0.5f;
      al_draw_text(font2, color::white, x_cursor, y_cursor++, 0, (tostring(target_widget->place.position.x)).c_str());
      al_draw_text(font2, color::white, x_cursor, y_cursor++, 0, (tostring(target_widget->place.position.y)).c_str());
      al_draw_text(font2, color::white, x_cursor, y_cursor++, 0, (tostring(target_widget->place.size.x)).c_str());
      al_draw_text(font2, color::white, x_cursor, y_cursor++, 0, (tostring(target_widget->place.size.y)).c_str());
      y_cursor += 0.5f;
      al_draw_text(font2, color::white, x_cursor, y_cursor++, 0, (tostring(target_widget->place.rotation)).c_str());
      al_draw_text(font2, color::white, x_cursor, y_cursor++, 0, (tostring(target_widget->place.scale.x)).c_str());
      al_draw_text(font2, color::white, x_cursor, y_cursor++, 0, (tostring(target_widget->place.scale.y)).c_str());

      //al_draw_text(font, color::white, x_cursor, y_cursor++, 0, (tostring("num_children ") + tostring(target_widget->ch)).c_str());
   }

   void set_target_widget(UIWidget *widget)
   {
      target_widget = widget;
   }
};




class Project : public UIScreen
{
public:
   UIWidgetInspector *widget_inspector;
   UIWindow* window[3];
   Project(Display *display)
      : UIScreen(display)
      , widget_inspector(NULL)
      , window()
   {
      window[0] = new UIWindow(this, 200, 200, 300, 200);
      window[1] = new UIWindow(this, 280, 300, 100, 80);
      window[2] = new UIWindow(this, 570, 280, 400, 320);

      widget_inspector = new UIWidgetInspector(this);
   }

   void on_timer()
   {
      if (window[0]->is_focused()) widget_inspector->set_target_widget(window[0]);
      else if (window[1]->is_focused()) widget_inspector->set_target_widget(window[1]);
      else if (window[2]->is_focused()) widget_inspector->set_target_widget(window[2]);
      else if (widget_inspector->is_focused()) widget_inspector->set_target_widget(widget_inspector);

      /*
      // it SHOULD be implemented like this, but there's a bug in get_nth_child_d()
      int num_widgets_d = children.get_num_of_widgets_d();
      for (unsigned i=0; i<num_widgets_d; i++)
      {
         UIWidget *widget = children.get_nth_child_d(i);
         if (widget && widget->is_focused()) widget_inspector->set_target_widget(widget);
      }
      */
   }
};




int main(int argc, char **argv)
{
   Framework::initialize();
   Display *display = Framework::create_display(800, 500);
   Project *proj = new Project(display);
   Framework::run_loop();
   return 0;
}




