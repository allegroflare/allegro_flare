



#include <allegro_flare/allegro_flare.h>




class MyMediaPlayer : public UIWindow
{
private:
   std::string filename;
   Sound sound;
   UIProgressBar *progress_bar;
   UIButton *play_button;
   UIButton *stop_button;
   UIText *filename_label;
   UIText *media_player_title;
public:
   MyMediaPlayer(UIWidget *parent)
      : UIWindow(parent, 650, 500, 200, 170)
      , filename("water_4.wav")
      , sound(Framework::sample(filename))
      , progress_bar(NULL)
      , play_button(NULL)
      , stop_button(NULL)
      , media_player_title(NULL)
   {
      filename_label = new UIText(this, 100, 34, filename);
      filename_label->place.align.x = 0.5;
      filename_label->set_font_color(color::white);

      new UIDraggableRegion(this, place.size.x/2, place.size.y/2, place.size.x, place.size.y);

      play_button = new UIButton(this, 100-45, 120+4, 80, 50, "play");

      stop_button = new UIButton(this, 190-45, 120+4, 80, 50, "stop");

      progress_bar = new UIProgressBar(this, 100, 70+4, 180, 18);
   }
   void on_message(UIWidget *sender, std::string message) override
   {
      if (sender == play_button) sound.play();
      else if (sender == stop_button) sound.stop();
   }
   void primary_timer_func() override
   {
      progress_bar->set_val(sound.position());
   }
};




#include <cctype>




class MyUIWindow : public UIWindow
{
private:
   class UICircleButton : public UIWidget
   {
   public:
      int32_t icon;
      ALLEGRO_COLOR icon_color;

      UICircleButton(UIWidget *parent, float x, float y, float radius, int32_t icon, std::string message_to_parent)
         : UIWidget(parent, "UICircleButton", new UISurfaceAreaCircle(x-(radius)+10, y+(radius)-10, radius))
         , icon(icon)
         , icon_color(color::gray)
      {}
      void on_draw() override
      {
         ALLEGRO_FONT *font = Framework::font("FontAwesome.otf -" + tostring(place.size.x/3));
         int line_height = al_get_font_line_height(font);
         draw_unicode_char(font, color::white, icon, ALLEGRO_ALIGN_CENTER, place.size.x/2, place.size.y/2 - line_height/2-1);
      }
   };

   ALLEGRO_DISPLAY *display;
   UITextInput *text_input;
   UIMusicNotation *music_render;
   UIProgressBar *progress_bar;
   UIText *text;
   MyMediaPlayer *media_player;

   DataAttr virtual_memory;
   std::string virtual_memory_filename;

   int mouse_down_x, mouse_down_y;

public:
   MyUIWindow(UIWidget *parent, Display *display)
      : UIWindow(parent, 0, 0, display->width(), display->height())
      , display(display->al_display)
      , text_input(NULL)
      , music_render(NULL)
      , progress_bar(NULL)
      , text(NULL)
      , media_player(NULL)
      , virtual_memory_filename("virtual_memory_file.txt")
      , mouse_down_x(0)
      , mouse_down_y(0)
   {
      int button_width = 130;
      int button_height = 80;

      float x = 1;
      float y = 1;


      text_input = new UITextInput(this, place.size.x/2, 80, place.size.x-30, 50, "");
      text_input->set_as_focused();
      text_input->attr.set("default_text_when_empty", "type a command");

      text = new UIText(this, 27, text_input->place.position.y + text_input->place.size.y + 4, "last:");



      music_render = new UIMusicNotation(this, this->place.size.x/2, 300);


      UIScaledText *title_text = new UIScaledText(this, 20, 12, "UI Example");
      title_text->place.align.x = 0;
      title_text->place.align.y = 0;

      float window_right = this->place.size.x;


      float radius = 30;
      new UICircleButton(this, window_right - 14, 0, radius, font_awesome::remove, "close_window");



      new UIButton(this, 100, 200+60*0, 80, 50, "0.0");
      new UIButton(this, 100, 200+60*1, 80, 50, "0.2");
      new UIButton(this, 100, 200+60*2, 80, 50, "0.5");
      new UIButton(this, 100, 200+60*3, 80, 50, "1.0");

      new UIButton(this, 100, 200+60*4+20, 110, 50, "set music");

      new UIButton(this, 100, 200+60*5+40, 80, 50, "shrink");
      new UIButton(this, 100, 200+60*6+40, 80, 50, "grow");


      new UILabeledCheckbox(this, 600, 160, "Option 1");
      new UILabeledCheckbox(this, 600, 210, "Option 2");
      new UILabeledCheckbox(this, 600, 260, "Option 3");


      progress_bar = new UIProgressBar(this, 225, 400, 160, 20);
      progress_bar->place.rotation = TAU * 0.25;


      media_player = new MyMediaPlayer(this);
   }
   bool parses_as_variable_definition(std::string message)
   {
      message = php::trim(message);
      if (message.empty()) return false;
      size_t pos = message.find_first_of('=');
      if (pos == std::string::npos) return false;
      std::string alleged_variable = message.substr(0, pos);
      return is_valid_variable_name(php::trim(alleged_variable));
   }
   std::pair<std::string, std::string> parse_key_value(std::string message)
   {
      // this function assumes that "message" has already validated
      std::string key="";
      std::string val="";
      size_t pos = message.find_first_of('=');
      key = message.substr(0, pos);
      val = message.substr(pos+1);
      return std::pair<std::string, std::string>(php::trim(key), attempt_to_evaluate(php::trim(val)));
   }
   bool is_valid_variable_name(const std::string &str)
   {
      return (str.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUV_abcdefghijklmnopqrstuvwxyz") == std::string::npos);
   }
   std::string attempt_to_evaluate(std::string str)
   {
      str = php::trim(str);
      if (str.empty()) return str;
      if (str[0]=='$')
      {
         size_t pos_of_first_non_variable_name_char = str.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUV_abcdefghijklmnopqrstuvwxyz", 1);
         std::string possible_variable_name = str.substr(1, pos_of_first_non_variable_name_char);
         if (possible_variable_name.empty())
         {
            std::cout << "[error] $ found without any valid symbol names" << std::endl;
            return "";
         }
         else
         {
            if (!virtual_memory.has(possible_variable_name))
            {
               std::cout << "[error] unrecognized symbol \"" << possible_variable_name << "\"" << std::endl;
               return "";
            }
            else
            {
               //TODO: we might need some recursion here, buddy :)
               return virtual_memory.get(possible_variable_name);
            }
         }
      }
      return str;
   }
   void on_message(UIWidget *sender, std::string message) override
   {
      bool message_caught = false;


      // check if it's one of the possible messages we expect

      if (sender == text_input && message == "on_submit")
      {
         message = text_input->get_text();
         text_input->set_text("");
      }
      else if (parses_as_variable_definition(message))
      {
         message_caught = true;
         std::pair<std::string, std::string> parsed_key_val = parse_key_value(message);
         std::cout << parsed_key_val.first << "=" << parsed_key_val.second;
         virtual_memory.set(parsed_key_val.first, parsed_key_val.second);
         virtual_memory.save(virtual_memory_filename);
      }
      else if (message == "close_window")
      {
         message_caught = true;
         Framework::shutdown_program = true;
      }
      else if (Screen::signal_has_header("set_progress_bar", message))
      {
         message_caught = true;
         std::string val = Screen::strip_signal_header("set_progress_bar", message);
         val = php::trim(val);
         val = attempt_to_evaluate(val);

         if (progress_bar) progress_bar->set_val(atof(val.c_str()));
      }
      else if (message == "shrink")
      {
         message_caught = true;
         Framework::motion().cmove_to(&place.scale.x, 0.86, 0.3);
         Framework::motion().cmove_to(&place.scale.y, 0.86, 0.3);
      }
      else if (message == "grow")
      {
         message_caught = true;
         Framework::motion().cmove_to(&place.scale.x, 1, 0.3);
         Framework::motion().cmove_to(&place.scale.y, 1, 0.3);
      }
      else if (message == "exit")
      {
         message_caught = true;
         Framework::shutdown_program = true;
      }
      else if (Screen::signal_has_header("set_music", message))
      {
         message_caught = true;
         std::string val = Screen::strip_signal_header("set_music", message);
         music_render->set_val(php::trim(val));
      }


      // give feedback on the message that was received

      if (message_caught) text->set_text("last: " + message);
      else std::cout << "Uncaught message: \"" << message << "\"" << std::endl;
   }
   void on_mouse_down() override
   {
      UIWindow::on_mouse_down();
      mouse_down_x = Framework::current_event->mouse.x;
      mouse_down_y = Framework::current_event->mouse.y;
   }
   void on_drag(float x, float y, float mx, float my) override
   {
      UIWindow::on_drag(x, y, mx, my);

      if (mouse_down_y > 40) return;

      int cx, cy;
      if (al_get_mouse_cursor_position(&cx, &cy))
      al_set_window_position(display, cx - mouse_down_x, cy - mouse_down_y);
   }
   void on_draw() override
   {
      UIWindow::on_draw();

      ALLEGRO_COLOR frame_color = color::color(color::hex("8e283e"));
      al_draw_filled_rectangle(0, 0, place.size.x, 40, frame_color);

      float frame_thickness = 6;
      al_draw_filled_rectangle(0, 0, frame_thickness, place.size.y, frame_color);
      al_draw_filled_rectangle(0, place.size.y-frame_thickness, place.size.x, place.size.y, frame_color);
      al_draw_filled_rectangle(place.size.x-frame_thickness, 0, place.size.x, place.size.y, frame_color);

      // white outline
      ALLEGRO_COLOR frame_border_color = color::color(color::black, 0.7);
      al_draw_line(0, 0, place.size.x, 0, frame_border_color, 2.0);
      al_draw_line(place.size.x, 0, place.size.x, place.size.y, frame_border_color, 2.0);
      al_draw_line(0, place.size.y, place.size.x, place.size.y, frame_border_color, 2.0);
      al_draw_line(0, 0, 0, place.size.y, frame_border_color, 2.0);
   }
};




class ExGUI : public UIScreen
{
public:
   MyUIWindow *window;
   ExGUI(Display *display)
      : UIScreen(display)
   {
      draw_focused_outline = false;

      window = new MyUIWindow(this, display);
      window->place.position.x = display->width()/2;
      window->place.position.y = display->height()/2;

      //std::cout << "this widget has " << get_num_ancestors() << " leaves" << std::endl;
   }
};




int main(int argc, char *argv[])
{
   Framework::initialize();
   //Display *display = Framework::create_display(800, 720);

   Display *display = new Display(800, 720, ALLEGRO_NOFRAME);
   al_register_event_source(Framework::event_queue, al_get_display_event_source(display->al_display));

   ExGUI *main = new ExGUI(display);
   Framework::run_loop();

   return 0;
}




