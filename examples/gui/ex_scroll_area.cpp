


#include <allegro_flare/allegro_flare.h>

//S("target", FGUISignalSlot)->game();

class FGUISignalSlot
{
private:
   std::vector<FGUISignalSlot *> outbound_slots;
   std::vector<FGUISignalSlot *> inbound_slots;

public:
   void connect_to_slot(FGUISignalSlot *slot)
   {
      outbound_slots.push_back(slot);
      slot->inbound_slots.push_back(this);
   }
   void disconnect_from_slot(FGUISignalSlot *slot)
   {
      //outbound_slots.push_back(slot);
      //slot->inbound_slots.push_back(this);
   }

   FGUISignalSlot() {}
   ~FGUISignalSlot()
   {
      for (unsigned i=0; i<outbound_slots.size(); i++)
      {
         disconnect_from_slot(outbound_slots[i]);
      }
   }

   void send(std::string message, void *data=NULL)
   {
      for (unsigned i=0; i<outbound_slots.size(); i++)
         outbound_slots[i]->receive(message, data);
   }
   virtual void receive(std::string message, void *data=NULL) {}
};





class ScrollAreaExpampleProgram : public FGUIScreen
{
private:
   FGUIScrollArea *scroll_view;
   FGUITextArea *text_box;
   //FGUISettingsWindow *settings_window;

public:
   ScrollAreaExpampleProgram(Display *display)
      : FGUIScreen(display)
      , text_box(NULL)
      , scroll_view(NULL)
      //, settings_window(NULL)
   {
      new FGUIImage(this, display->width()/2, display->height()/2, Framework::bitmap("maybe_cooler2.png"));

      FGUIWidget *canvas = build_canvas_for_scrollable_area();
      scroll_view = new FGUIScrollArea(this, display->width()/3, display->height()/2, canvas->place.size.x, 600, canvas);

      (new FGUIText(this, 700, 140, "Scroll Area Example"))
         ->place.align.x = 0;

      // settins window
      //settings_window = new FGUISettingsWindow(this, display);



      (new FGUIText(this, 700, 260, "Scroll Area Info"))
         ->place.align.x = 0;

      text_box = new FGUITextArea(this, 700, 300, 300, 200, "InfoPane");
      text_box->place.align = vec2d(0, 0);



      float box_size = 30;
      float cursor_x = 700 + box_size/2;
      float cursor_y = 600;
      float spacing_y = 30;

      (new FGUIText(this, 700, cursor_y, "Options"))
         ->place.align.x = 0;

      cursor_y += 40;

      new FGUICheckbox(this, cursor_x, cursor_y, 24);
         new FGUIText(this, cursor_x+36, cursor_y, "Show hilight on focused widget");

      new FGUICheckbox(this, cursor_x, cursor_y+spacing_y, 24);
         new FGUIText(this, cursor_x+36, cursor_y+spacing_y, "Allow click to focus on no_focus elements");

   }
   FGUIWidget *build_canvas_for_scrollable_area()
   {
      // canvas should always be the first child
      FGUIWidget *canvas = new FGUIWidget(this, new FGUISurfaceAreaBox(0, 0, 400, 600*1.5));
      canvas->place.align = vec2d(0, 0);

      //{
         // some example in-canvas elements
         FGUIImage *img = new FGUIImage(canvas, canvas->place.size.x/2, 120, Framework::bitmap("pic1.jpg"));
            img->place.rotation = 0.2;
         new FGUIImage(canvas, canvas->place.size.x/2, 330, Framework::bitmap("pic2.png"));
         new FGUITextBox(canvas, canvas->place.size.x/2, 510, 300, 120,   "The content in this scroll area is a parent widget.");
         FGUITextList *text_list = new FGUITextList(canvas, canvas->place.size.x/2, 700, 300);
            text_list->add_item("Shoes");
            text_list->add_item("Groceries");
            text_list->add_item("Wrapping Paper");
            text_list->add_item("Toys");
            text_list->add_item("Dishwashing Soap");
         new FGUIButton(canvas, canvas->place.size.x/2, canvas->place.size.y-60, 110, 60, "Button");
      //}
      return canvas;
   }
   void on_timer()
   {
      std::stringstream text_box_text;

      text_box_text << "x: " << scroll_view->get_canvas()->place.position.x << "\n";
      text_box_text << "y: " << scroll_view->get_canvas()->place.position.y << "\n";

      text_box->set_text(text_box_text.str());
   }
};









int main(int argc, char *argv[])
{
   Framework::initialize();
   Display *display = Framework::create_display(Display::RESOLUTION_WXGA);
   ScrollAreaExpampleProgram *proj = new ScrollAreaExpampleProgram(display);
   Framework::run_loop();
   return 0;
}//
