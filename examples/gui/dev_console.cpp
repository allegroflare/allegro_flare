



#include <allegro_flare/gui/gui_screen.h>
#include <allegro_flare/gui/widgets/text_input.h>
#include <allegro_flare/framework.h>




// come back to this, Mark, this is a cool idea.




class UIConsole : public UIScreen
{
public:
   class Message
   {
   public:
      enum message_type_t
      {
         MESSAGE_TYPE_UNDEF = 0,
         MESSAGE_TYPE_NOTIFICATION
      };
      int type;
      std::string message;
      Message(std::string message, int type)
         : message(message)
         , type(type)
      {}
      void draw(ALLEGRO_FONT *font, float x, float y)
      {
         al_draw_text(font, color::white, x, y, ALLEGRO_ALIGN_LEFT, message.c_str());
      }
      static ALLEGRO_COLOR get_color_from_type(int type)
      {
         switch(type)
         {
            case MESSAGE_TYPE_NOTIFICATION:
               return color::dodgerblue;
               break;
            case MESSAGE_TYPE_UNDEF:
            default:
               return color::gray;
               break;
         }
      }
   };

   bool active;
   float visibility_counter;
   ALLEGRO_FONT *font;
   int toggle_key;
   std::vector<Message> message;
   float console_padding;
   float console_height;
   float text_input_height;
   int current_indexed_past_message;
   UITextInput *text_input_widget;

   UIConsole(Display *display)
      : UIScreen(display)
      , font(Framework::font("DroidSans.ttf 19"))
      , active(false)
      , visibility_counter(0)
      , toggle_key(ALLEGRO_KEY_TILDE)
      , console_height(200)
      , text_input_widget(NULL)
      , text_input_height(al_get_font_line_height(font)*2)
      , console_padding(20)
      , current_indexed_past_message(0)
   {
      text_input_widget = new UITextInput(this, console_padding, -150, display->width()-console_padding*2, text_input_height, "");
      text_input_widget->place.align.x = 0.0;
      text_input_widget->place.align.y = 1.0;
   }

   void key_down_func() override
   {
      if (Framework::current_event->keyboard.keycode == toggle_key)
      {
         toggle_visibility();
      }
      else
      {
         switch(Framework::current_event->keyboard.keycode)
         {
         case ALLEGRO_KEY_UP:
            current_indexed_past_message--;
            break;
         case ALLEGRO_KEY_ENTER:
            std::string message_text = text_input_widget->get_text();
            if (php::trim(message_text) != "")
            {
               append_message(message_text, 0);
               text_input_widget->set_text("");
            }
            break;
         }
      }
   }

   void append_message(std::string text, int type)
   {
      message.push_back(Message(text, type));
   }

   void on_draw() override
   {
      al_draw_filled_rectangle(0, 0, display->width(), console_height * visibility_counter, color::darkblue);

      if (!active) return;

      int message_height = al_get_font_line_height(font);
      //for (int i=(int)message.size()-1; i>=0; i--)
      int message_index = message.size()-1;
      float message_y_start = console_height - console_padding*2 - text_input_height - message_height/2;
      for (int i=0; i<(int)message.size(); i++)
      {
         message[message_index].draw(font, console_padding, message_y_start - message_height*i);
         message_index--;
         //al_draw_text(font, color::white, 20, 20, ALLEGRO_ALIGN_LEFT, "hello world");
      }
   }

   bool toggle_visibility()
   {
      if (active)
      {
         // hide
         Framework::motion().canimate(&visibility_counter, visibility_counter, 0, Framework::time_now, Framework::time_now+0.2, interpolator::fastIn, NULL, NULL);
         Framework::motion().canimate(&text_input_widget->place.position.y, text_input_widget->place.position.y, -150, Framework::time_now, Framework::time_now+0.2, interpolator::fastIn, NULL, NULL);
         text_input_widget->set_as_unfocused();
      }
      else
      {
         // show
         Framework::motion().canimate(&visibility_counter, visibility_counter, 1, Framework::time_now, Framework::time_now+0.2, interpolator::fastIn, NULL, NULL);
         Framework::motion().canimate(&text_input_widget->place.position.y, text_input_widget->place.position.y, console_height-console_padding, Framework::time_now, Framework::time_now+0.2, interpolator::fastIn, NULL, NULL);
         text_input_widget->set_as_focused();
      }

      active = !active;

      return active;
   }

   void receive_signal(std::string const &signal, void *data) override
   {
      if (signal.find("console") == 0)
      {
         std::string *msg = static_cast<std::string *>(data);
      }
   }
};




class ExampleProject : public UIScreen
{
public:
   UIConsole *console;
   ExampleProject(Display *display)
      : UIScreen(display)
      , console(NULL)
   {
      console = new UIConsole(display);
   }
   void mouse_down_func() override
   {
      console->toggle_visibility();
   }
};




int main(int argc, char **argv)
{
   Framework::initialize();
   Display *d = Framework::create_display(800, 600);
   ExampleProject *ex = new ExampleProject(d);
   Framework::run_loop();
   return 0;
}




