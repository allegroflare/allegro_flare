#ifndef __UI_TEXT_INPUT_HEADER
#define __UI_TEXT_INPUT_HEADER




#include <allegro_flare/gui/widget.h>
#include <allegro5/allegro_font.h>




class UITextInput : public UIWidget
{
protected:
   std::string text;
   std::string default_text_when_empty;
   int cursor_pos;
   int cursor_end;
   float cursor_blink_counter;
   ALLEGRO_FONT *font;
   int text_x_offset;
   ALLEGRO_COLOR font_color;
   float padding;

   ALLEGRO_BITMAP *_text_render;
   void _insert_text(const char *str);
   void _handle_erase();
   void _update_text_and_selection_render(float len_to_cursor, float len_to_cursor_end);

public:
   explicit UITextInput(UIWidget *parent, float x, float y, float w, float h, std::string initial_text="");
   ~UITextInput();

   void set_text(std::string text);
   std::string get_text();
   std::string get_selection();
   void set_font(ALLEGRO_FONT *font);
   ALLEGRO_FONT *get_font();
   void set_font_color(ALLEGRO_COLOR col);
   bool selection_active();
   void insert_text(std::string text);
   void clear_selection();
   void set_default_text_when_empty(std::string default_text="");

   virtual void on_submit(); // usually instigated by the ENTER key

   void on_click() override;
   void on_key_char() override;
   void on_draw() override;
   void on_focus() override;
};




#endif
