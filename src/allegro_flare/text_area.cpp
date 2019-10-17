



#include <allegro_flare/text_area.h>

#include <allegro5/allegro_primitives.h>
#include <allegro_flare/box.h>
#include <allegro_flare/style_assets.h>
#include <allegro_flare/allegro_flare.h>
#include <allegro_flare/clipboard.h>
#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/Useful.hpp>




//
// UITextArea::Cursor
//




UITextArea::Cursor::Cursor(int head_pos, int anchor_pos)
   : head_pos(head_pos)
   , _anchor_pos(anchor_pos)
   , anchor_down(false)
{}




void UITextArea::Cursor::move(int delta)
{
   head_pos += delta;
   if (!anchor_down) _anchor_pos = head_pos;
}




void UITextArea::Cursor::move(int delta, int min, int max)
{
   head_pos += delta;
   if (head_pos >= max) head_pos = max;
   if (head_pos <= min) head_pos = min;

   if (!anchor_down) _anchor_pos = head_pos;
}




void UITextArea::Cursor::move_to(int pos)
{
   head_pos = pos;
   if (!anchor_down) _anchor_pos = head_pos;
}




void UITextArea::Cursor::move_to(int pos, int min, int max)
{
   head_pos = pos;
   if (head_pos >= max) head_pos = max;
   if (head_pos <= min) head_pos = min;

   //head_pos = pos;
   if (!anchor_down) _anchor_pos = head_pos;
}




void UITextArea::Cursor::move_anchor_to_cursor() { _anchor_pos = head_pos; }
int UITextArea::Cursor::pos() { return head_pos; }
int UITextArea::Cursor::anchor_pos() { return _anchor_pos; }
int UITextArea::Cursor::get_start() { return std::min(head_pos, _anchor_pos); }
int UITextArea::Cursor::get_end() { return std::max(head_pos, _anchor_pos); }
int UITextArea::Cursor::get_selection_length() { return get_end() - get_start(); }
void UITextArea::Cursor::set_anchor_down() { anchor_down = true; }
void UITextArea::Cursor::set_anchor_up() { anchor_down = false; }
bool UITextArea::Cursor::is_anchor_down() { return anchor_down; }
bool UITextArea::Cursor::selection_active() { return head_pos != _anchor_pos; }




//
// UITextArea
//




UITextArea::UITextArea(UIWidget *parent, float x, float y, float w, float h, std::string text)
   : UIWidget(parent, "UITextArea", new UISurfaceAreaBox(x, y, w, h))
   , full_text(text)
   , font(Framework::font("DroidSans.ttf 20"))
   , cursor_blink_counter(1)
   , cursor(0, 0)
{}




void UITextArea::move_cursor(int delta)
{
   cursor.move(delta, 0, (int)full_text.length());
   cursor_blink_counter = 1;
}




void UITextArea::move_cursor_to(int pos)
{
   cursor.move_to(pos, 0, (int)full_text.length());
   cursor_blink_counter = 1;
}




void UITextArea::move_cursor_to_next_of(std::string chars)
{
   int cursor_pos = full_text.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", cursor.pos());
   if (cursor_pos == std::string::npos)
   {
      cursor_pos = full_text.length();
   }
   move_cursor_to(cursor_pos);
   move_cursor(1);
}




void UITextArea::move_cursor_to_previous_not_of(std::string chars)
{
   int cursor_pos = full_text.find_last_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789'\"", std::max(0, cursor.pos()-1));
   if (cursor_pos == std::string::npos) { cursor_pos = 0; }
   cursor.move_to(cursor_pos);
}




void UITextArea::erase_selection()
{
   full_text.erase(cursor.get_start(), cursor.get_selection_length());
   cursor.move_to(cursor.get_start());
   cursor.move_anchor_to_cursor();
}




void UITextArea::set_font(ALLEGRO_FONT *font)
{
   this->font = font;
}




ALLEGRO_FONT *UITextArea::get_font()
{
   return font;
}




void UITextArea::set_text(std::string text)
{
   this->full_text = text;
   cursor.move_to(0);
   cursor.move_anchor_to_cursor();
}




void UITextArea::insert_text(std::string text)
{
   full_text.insert(cursor.pos(), text);
   //cursor.move_to(cursor.pos()+text.length(), 0, full_text.length());
   cursor.move(text.length());
   cursor.move_anchor_to_cursor();
}




std::string UITextArea::get_text()
{
   return this->full_text;
}




void UITextArea::on_draw()
{
   //if (focused) al_draw_rectangle(0, 0, place.w, place.h, color::red, 2.0);
   //if (focused) al_draw_text(font, color::yellow, -10, -10, NULL, tostring(cursor).c_str());

   //al_draw_filled_rounded_rectangle(-6, -6, place.size.x+6, place.size.y+6, 4, 4, color::color(color::black, 0.2));
   //al_draw_rectangle(0, 0, place.size.x, place.size.y, color::color(color::white, 0.3), 1.0);


   UIStyleAssets::draw_inset(0, 0, place.size.x, place.size.y, color::color(color::black, 0.1));
   if (focused) al_draw_rounded_rectangle(0, 0, place.size.x, place.size.y, 3, 3, color::dodgerblue, 2.0);   


   if ((cursor_blink_counter -= 0.025) < 0) cursor_blink_counter = 1;

   float PADDING = 6;
   float draw_cursor_x = PADDING;
   float draw_cursor_y = PADDING;
   float text_bbox_width = place.size.x - PADDING * 2;
   std::string word;
   int _number_of_lines = 0;

   bool selection_active = cursor.selection_active();
   int selection_line_start = 0;
   int selection_line_end = 0;
   int selection_x_start = 0;
   int selection_x_end = 0;
   int line_height = al_get_font_line_height(font);

   float cursor_draw_pos_x = 0; // the actual x,y location where the input cursor is to be drawn
   float cursor_draw_pos_y = 0;

   unsigned i=0;
   for (i=0; i<full_text.length(); i++)
   {
      if (full_text[i] == '\n')
      {
         if (cursor.pos() == i)
         {
            // if the cursor is at this position
            cursor_draw_pos_x = draw_cursor_x;
            cursor_draw_pos_y = draw_cursor_y;
            selection_x_end = draw_cursor_x;
            selection_line_end = _number_of_lines;
         }

         // move the drawing cursor down on newlines
         draw_cursor_x = PADDING;
         draw_cursor_y += al_get_font_line_height(font);
         _number_of_lines++;
      }
      else
      {
         // proceed with the drawing

         std::string text_packet_to_draw = tostring(full_text[i]).c_str();
         float text_width = al_get_text_width(font, text_packet_to_draw.c_str()); // < this is the process that should be cached

         if (draw_cursor_x + text_width > text_bbox_width)
         {
            // wrap if the text width is beyond the edge
            draw_cursor_x = PADDING;
            draw_cursor_y += al_get_font_line_height(font);
            _number_of_lines++;
         }

         if (selection_active && cursor.anchor_pos() == i)
         {
            // draw the anchor
            if (focused) al_draw_line(draw_cursor_x, draw_cursor_y, draw_cursor_x, draw_cursor_y+line_height, color::color(color::aliceblue, 0.5), 2.0);
            selection_x_start = draw_cursor_x;
            selection_line_start = _number_of_lines;
         }

         if (cursor.pos() == i)
         {
            // draw the cursor
            cursor_draw_pos_x = draw_cursor_x;
            cursor_draw_pos_y = draw_cursor_y;
            selection_x_end = draw_cursor_x;
            selection_line_end = _number_of_lines;
         }

         al_draw_text(font, color::white, draw_cursor_x, draw_cursor_y, ALLEGRO_FLAGS_EMPTY, text_packet_to_draw.c_str());
         draw_cursor_x += text_width;
      }
   }


   // just the one exception where the cursor is in the last place
   if (cursor.pos() == full_text.length())
   {
      cursor_draw_pos_x = draw_cursor_x;
      cursor_draw_pos_y = draw_cursor_y;
      selection_x_end = draw_cursor_x;
      selection_line_end = _number_of_lines;
   }
   if (selection_active && cursor.anchor_pos() == full_text.length())
   {
      // draw the anchor
      cursor_draw_pos_x = draw_cursor_x;
      cursor_draw_pos_y = draw_cursor_y;
      selection_x_start = draw_cursor_x;
      selection_line_start = _number_of_lines;
   }


   //
   // Draw
   //


   // swap the selection_x_start and selection_x_end if the anchor is *after* the cursor

   if (selection_active && cursor.pos() < cursor.anchor_pos())
   {
      selection_x_start ^= selection_x_end;
      selection_x_end ^= selection_x_start;
      selection_x_start ^= selection_x_end;         

      selection_line_start ^= selection_line_end;
      selection_line_end ^= selection_line_start;
      selection_line_start ^= selection_line_end;
   }


   // draw the input cursor
   if (focused)
   {
      al_draw_line(cursor_draw_pos_x, cursor_draw_pos_y,
            cursor_draw_pos_x, cursor_draw_pos_y+line_height,
            color::color(color::aliceblue, 0.5), 2.0);
   }


   // draw the selection box

   if (selection_active)
   {
      float line_height = al_get_font_line_height(font);

      ALLEGRO_COLOR selection_color = color::color(color::aliceblue, 0.2);
      if (selection_line_start == selection_line_end)
      {
         al_draw_filled_rectangle(selection_x_start, selection_line_start*line_height+PADDING, selection_x_end, (selection_line_end+1)*line_height+PADDING, selection_color);
      }
      else
      {
         // draw the first selection line
         al_draw_filled_rectangle(selection_x_start, selection_line_start*line_height+PADDING, text_bbox_width, (selection_line_start+1)*line_height+PADDING, selection_color);

         // draw the last selection line
         al_draw_filled_rectangle(PADDING, selection_line_end*line_height+PADDING, selection_x_end, (selection_line_end+1)*line_height+PADDING, selection_color);

         // if the selection box is larger than 2 lines
         if (abs(selection_line_start - selection_line_end) > 1)
         {
            al_draw_filled_rectangle(PADDING, (selection_line_start+1)*line_height+PADDING, text_bbox_width, (selection_line_end)*line_height+PADDING, selection_color);
         }
      }
   }
}




void UITextArea::on_key_down()
{
   int keycode = Framework::current_event->keyboard.keycode;
   if (keycode == ALLEGRO_KEY_RSHIFT || keycode == ALLEGRO_KEY_LSHIFT)
   {
      // note: this should still activate even if the textarea widget is not focused
      cursor.set_anchor_down();
   }

   if (!focused) return;
}




void UITextArea::on_key_up()
{
   int keycode = Framework::current_event->keyboard.keycode;
   if (keycode == ALLEGRO_KEY_RSHIFT || keycode == ALLEGRO_KEY_LSHIFT)
   {
      // note: this should still activate even if the textarea widget is not focused
      cursor.set_anchor_up();
   }

   if (!focused) return;
}




std::string UITextArea::get_selection()
{
   return full_text.substr(cursor.get_start(), cursor.get_selection_length());
}




void UITextArea::on_key_char()
{
   if (!focused) return;

   cursor_blink_counter = 1;

   int unichar = Framework::current_event->keyboard.unichar;
   int keycode = Framework::current_event->keyboard.keycode;

   // test cut-copy-paste
   if ((keycode == ALLEGRO_KEY_C
       || keycode == ALLEGRO_KEY_X
       || keycode == ALLEGRO_KEY_V
       || keycode == ALLEGRO_KEY_A)
       && Framework::current_event->keyboard.modifiers & ALLEGRO_KEYMOD_CTRL)
   {
      //std::cout << "cut-copy-pate" << std::endl;
      if (keycode == ALLEGRO_KEY_A)
      {
         cursor.move_to(0);
         cursor.move_anchor_to_cursor();
         cursor.set_anchor_down();
         cursor.move_to(full_text.length());
         cursor.set_anchor_up();
      }
      else if (keycode == ALLEGRO_KEY_X)
      {
         Clipboard::set(get_selection());
         erase_selection();
      }
      else if (keycode == ALLEGRO_KEY_C)
      {
         Clipboard::set(get_selection());
      }
      else if (keycode == ALLEGRO_KEY_V)
      {
         erase_selection();
         insert_text(Clipboard::get());
      }

      return;
   }
   else if ((unichar >= ' ') && (unichar <= '~'))
   {
      if (cursor.selection_active()) erase_selection();
      full_text.insert(cursor.pos(), tostring((char)unichar));
      move_cursor(1);
      cursor.move_anchor_to_cursor();
   }
   else if (keycode == ALLEGRO_KEY_ENTER)
   {
      full_text.insert(cursor.pos(), "\n");
      move_cursor(1);
   }
   else if (keycode == ALLEGRO_KEY_RIGHT)
   {
      if (Framework::current_event->keyboard.modifiers & ALLEGRO_KEYMOD_CTRL)
      {
         move_cursor_to_next_of("null");
      }
      else
      {
         move_cursor(1);
      }
   }
   else if (keycode == ALLEGRO_KEY_LEFT)
   {
      if (Framework::current_event->keyboard.modifiers & ALLEGRO_KEYMOD_CTRL)
      {
         move_cursor_to_previous_not_of("null");
      }
      else
      {
         move_cursor(-1);
      }
   }
   else if (keycode == ALLEGRO_KEY_BACKSPACE)
   {
      if (cursor.selection_active())
      {
         erase_selection();
      }
      else
      {
         move_cursor(-1);
         full_text.erase(cursor.pos(), 1);
      }
   }
   else if (keycode == ALLEGRO_KEY_DELETE)
   {
      if (cursor.selection_active())
      {
         erase_selection();
      }
      else
      {
         full_text.erase(cursor.pos(), 1);
      }
   }
}




