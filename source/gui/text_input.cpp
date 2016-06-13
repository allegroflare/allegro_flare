



#include <allegro_flare/gui/widgets/text_input.h>

#include <algorithm>
#include <allegro_flare/gui/surface_areas/box.h>
#include <allegro_flare/gui/style_assets.h>
#include <allegro_flare/gui/widget.h>
#include <allegro_flare/allegro_flare.h> // for Framework::current_event and Framework::fonts




UITextInput::UITextInput(UIWidget *parent, float x, float y, float w, float h, std::string text)
   : UIWidget(parent, "UITextInput", new UISurfaceAreaBox(x, y, w, h))
   , text("")
   , cursor_pos(0)
   , cursor_end(0)
   , font(Framework::font("DroidSans.ttf 20"))
   , cursor_blink_counter(0)
   , text_x_offset(0)
   , font_color(color::white)
   , _text_render(NULL)
   , padding(10)
   , mouse_cursor_x(0)
   , mouse_cursor_y(0)
{
   set_text(text);

   _text_render = al_create_bitmap(w, h);
}




UITextInput::~UITextInput()
{
   al_destroy_bitmap(_text_render);
}




void UITextInput::set_text(std::string text)
{
   if (this->text == text) return;
   this->text = text;
   cursor_pos = text.size();
   cursor_end = cursor_pos;
   on_change();
}




std::string UITextInput::get_text()
{
   return text;
}




bool UITextInput::selection_active()
{
   return (cursor_pos != cursor_end);
}




void UITextInput::insert_text(std::string text)
{
   _insert_text(text.c_str());
   cursor_end = cursor_pos; 
}




std::string UITextInput::get_selection()
{
   if (selection_active())
   {
      int min_pos = std::min(cursor_pos, cursor_end);
      int max_pos = std::max(cursor_pos, cursor_end);
      return text.substr(min_pos, max_pos-min_pos);
   }
   return "";
}




void UITextInput::_insert_text(const char *str)
{
   //if (cursor_pos != cursor_end) _handle_erase(); // this causes a crash
   text.insert(cursor_pos, str);
   cursor_pos += strlen(str);
   on_change();
}




void UITextInput::clear_selection()
{
   int cursor_min = std::min(cursor_pos, cursor_end);
   _handle_erase();
   cursor_pos = cursor_min;
   cursor_end = cursor_min;
}




void UITextInput::set_font_color(ALLEGRO_COLOR col)
{
   font_color = col;
}




void UITextInput::_handle_erase()
{
   int del_len = 1;
   int *left = &cursor_pos;
   if (cursor_end != cursor_pos)
   {
      del_len = abs(cursor_pos-cursor_end);
      if (cursor_end < cursor_pos) left = &cursor_end;
   }
   //std::cout << del_len;
   text.replace(*left, del_len, "");
   cursor_pos = *left;
   //_play(keypress_del);
}




void UITextInput::on_click()
{

}




void UITextInput::on_mouse_move(float x, float y, float dx, float dy)
{
   place.transform_coordinates(&x, &y); // hm, could be a really heavy calculation to do repeatedly
   mouse_cursor_x = x;
   mouse_cursor_y = y;
}




void UITextInput::on_key_char()
{
   if (!focused) return;

   // TODO: implement the on_change()


   cursor_blink_counter = 1.0;

   int unichar = Framework::current_event->keyboard.unichar;
   int keycode = Framework::current_event->keyboard.keycode;
   bool printable = false;

   if ((unichar >= ' ') && (unichar <= '~'))
   {
      // these are 'printable' characters
      if (selection_active()) clear_selection();
      _insert_text(tostring((char)unichar).c_str());
      //if (unichar == ' ') _play(keypress_light);
      //else _play(keypress);

      printable = true;
   }
   if ((keycode == ALLEGRO_KEY_C
       || keycode == ALLEGRO_KEY_X
       || keycode == ALLEGRO_KEY_V
       || keycode == ALLEGRO_KEY_A)
       && Framework::current_event->keyboard.modifiers & ALLEGRO_KEYMOD_CTRL)
   {
      //std::cout << "cut-copy-pate" << std::endl;
      if (keycode == ALLEGRO_KEY_A)
      {
         cursor_end = 0;
         cursor_pos = text.length();
      }
      else if (keycode == ALLEGRO_KEY_X)
      {
         Clipboard::set(get_selection());
         clear_selection();
      }
      else if (keycode == ALLEGRO_KEY_C)
      {
         Clipboard::set(get_selection());
      }
      else if (keycode == ALLEGRO_KEY_V)
      {
         clear_selection();
         insert_text(Clipboard::get());
      }

      return;
   }
   if (keycode == ALLEGRO_KEY_RIGHT)
   {
      cursor_pos++;
      if (cursor_pos > (int)text.size())
      {
         cursor_pos = text.size();
         //animate_cursor_error();
      }
      else
      {
         if (Framework::current_event->keyboard.modifiers & ALLEGRO_KEYMOD_CTRL)
         {
            cursor_pos = text.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", cursor_pos);
            if (cursor_pos == std::string::npos)
            {
               cursor_pos = text.length();
            }
         }
         //_play(keypress_light);
      }
   }
   else if (keycode == ALLEGRO_KEY_LEFT)
   {
      cursor_pos--;
      if (cursor_pos < 0)
      {
         cursor_pos = 0;
         //animate_cursor_error();
      }
      else
      {
         if (Framework::current_event->keyboard.modifiers & ALLEGRO_KEYMOD_CTRL)
         {
            cursor_pos = text.find_last_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789'\"", cursor_pos-1);
            if (cursor_pos == std::string::npos)
            {
               cursor_pos = 0;
            }
            else
            {
               cursor_pos++;
            }
         }
         //_play(keypress_light);
      }
   }
   else if (keycode == ALLEGRO_KEY_HOME)
   {
      if (cursor_pos == 0)
      {
         //animate_cursor_error();
      }
      else
      {
         cursor_pos = 0;
         //_play(keypress_swift);
      }
   }
   else if (keycode == ALLEGRO_KEY_END)
   {
      if (cursor_pos == text.size())
      {
         //animate_cursor_error();
      }
      else
      {
         cursor_pos = text.size();
         //_play(keypress_swift);
      }
   }
   else if (keycode == ALLEGRO_KEY_BACKSPACE)
   {
      if ((Framework::current_event->keyboard.modifiers & ALLEGRO_KEYMOD_CTRL)
          && (Framework::current_event->keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT))
      {
         // do nothing in this specific case.
         goto keyout;
      }
      else if (cursor_end == cursor_pos) cursor_pos--;
      if (cursor_pos < 0)
      {
         cursor_pos = 0;
         //animate_cursor_error();
      }
      else
      {
         if (Framework::current_event->keyboard.modifiers & ALLEGRO_KEYMOD_CTRL)
         {
            cursor_pos = text.find_last_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789'\"", cursor_pos-1);
            if (cursor_pos == std::string::npos)
            {
               cursor_pos = 0;
            }
            else
            {
               cursor_pos++;
            }
         }
         _handle_erase();
      }
   }
   else if (keycode == ALLEGRO_KEY_DELETE)
   {
      if (cursor_end != cursor_pos) _handle_erase();
      else
      {
         if (cursor_pos != text.size())
         {
            if (Framework::current_event->keyboard.modifiers & ALLEGRO_KEYMOD_CTRL)
            {
               //cursor = text.find_first_of("", cursor); ?
               cursor_pos = text.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", cursor_pos);
               if (cursor_pos == std::string::npos)
               {
                  cursor_pos = text.length();
               }
               else cursor_pos++;
            }
            _handle_erase();
         }
         else
         {
            //animate_cursor_error();
         }
      }
   }
   else if (keycode == ALLEGRO_KEY_ENTER
         || keycode == ALLEGRO_KEY_PAD_ENTER)
   {
      on_submit();
      //_insert_text(tostring('\n').c_str());
      //_play(keypress);
   }

   keyout:

   if (!(Framework::current_event->keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT) || printable)
      cursor_end = cursor_pos;
}




void UITextInput::_update_text_and_selection_render(float len_to_cursor, float len_to_cursor_end)
{
   ALLEGRO_STATE state;
   al_store_state(&state, ALLEGRO_STATE_TARGET_BITMAP);

   if (!_text_render
       || place.size.x != al_get_bitmap_width(_text_render)
       || place.size.y != al_get_bitmap_height(_text_render)
      )
   {
      al_destroy_bitmap(_text_render);
      _text_render = al_create_bitmap(place.size.x, place.size.y);
   }
   al_set_target_bitmap(_text_render);
   al_clear_to_color(color::transparent);


   // draw the text hilight
   ALLEGRO_COLOR cursor_select_color = color::hex("c6e2ff");
   al_draw_filled_rectangle(padding+len_to_cursor+text_x_offset, padding, padding+len_to_cursor_end+text_x_offset, padding+al_get_font_line_height(font), focused ? cursor_select_color : color::color(cursor_select_color, 0.4));

   if (text.empty() && attr.has("default_text_when_empty")) al_draw_text(font, color::color(font_color, 0.2), padding+text_x_offset, padding, ALLEGRO_FLAGS_EMPTY, attr.get("default_text_when_empty").c_str());
   else al_draw_text(font, font_color, padding+text_x_offset, padding, ALLEGRO_FLAGS_EMPTY, text.c_str());


   al_restore_state(&state);
}




void UITextInput::on_draw()
{
   placement2d &placement = surface_area->placement;

   //float roundness = 2;


   if ((cursor_blink_counter-= 0.025) < 0) cursor_blink_counter = 1.0;


   int full_len = al_get_text_width(font, text.c_str());
   int len_to_cursor = al_get_text_width(font, text.substr(0, cursor_pos).c_str());
   int len_to_cursor_end = len_to_cursor;
   if (cursor_end != cursor_pos) len_to_cursor_end = al_get_text_width(font, text.substr(0, cursor_end).c_str());
   int font_height = al_get_font_line_height(font);

   //float padding = 10;


   UIStyleAssets::draw_inset(0, 0, placement.size.x, placement.size.y, color::color(color::black, 0.1));
   // draw the border-box
   if (focused) al_draw_rounded_rectangle(0, 0, placement.size.x, placement.size.y, 3, 3, color::dodgerblue, 2.0);   


   text_x_offset = 0;
   float cursor_x = len_to_cursor + padding;
   if (cursor_x > (placement.size.x-padding)) text_x_offset = -(cursor_x - (placement.size.x-padding));
   //if (cursor_x < padding) text_x_offset = (placement.w + padding*2);

   // draw the text
   _update_text_and_selection_render(len_to_cursor, len_to_cursor_end);
   al_draw_bitmap(_text_render, 0, 0, ALLEGRO_FLAGS_EMPTY);

   // draw the cursor
   if (focused) al_draw_line(len_to_cursor+padding+text_x_offset, padding-padding*0.25, len_to_cursor+padding+text_x_offset, padding+padding*0.25+font_height, color::color(color::dodgerblue, cursor_blink_counter), 2.0);

   // draw the inner mouse position
   if (mouse_over) al_draw_line(mouse_cursor_x, 3, mouse_cursor_x, place.size.y-3, color::color(color::white, 0.4), 1.0);
}




void UITextInput::on_focus()
{
   if (attr.has("select_all_on_focus"))
   {
      // select all
      cursor_end = 0;
      cursor_pos = text.length();
   }
}




void UITextInput::on_submit()
{
   if (family.parent) family.parent->on_message(this, "on_submit");
   on_change();
}




