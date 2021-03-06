



#include <allegro_flare/text_list.h>

#include <allegro_flare/box.h>
#include <allegro_flare/gui_screen.h>
#include <allegro_flare/style_assets.h>
#include <allegro_flare/allegro_flare.h>




namespace allegro_flare
{
   UIListItem::UIListItem() {};




   UIListItem::~UIListItem() {};




   UITextList::UITextList(UIWidget *parent, float x, float y, float w)
      : UIWidget(parent, "UITextList", new UISurfaceAreaBox(x, y, w, 20))
      , item_padding(5)
      , item_height(20)
      , currently_selected_item(0)
      , items()
   {}




   UITextList::~UITextList()
   {}




   void UITextList::add_item(std::string item)
   {
      // TODO: insert()
      // also, change selection if the new added item is before or after this item, k? :)
      items.push_back(item);
   }




   void UITextList::select_item(int index)
   {
      std::string *item = get_item(index);
      if (!item) { std::cout << "UIList["<< get("id") << "] cannot select item at index " << index; return; }
      else currently_selected_item = index;
   }




   std::string *UITextList::get_item(int index)
   {
      if (index < 0 || index >= (int)items.size()) return NULL;
      return &items[index];
   }




   std::string *UITextList::get_selected_item()
   {
      return get_item(currently_selected_item);
   }




   void UITextList::move_selected_item(int delta)
   {
      currently_selected_item += delta;
      while (currently_selected_item < 0) currently_selected_item += items.size();
      currently_selected_item = currently_selected_item % items.size();
   }




   void UITextList::on_key_char()
   {
      if (!is_focused()) return;
      switch(Framework::current_event->keyboard.keycode)
      {
      case ALLEGRO_KEY_DOWN:
         move_selected_item(1);
         break;
      case ALLEGRO_KEY_UP:
         move_selected_item(-1);
         break;
      }
   }




   float UITextList::get_item_height(int index)
   {
      return item_height + item_padding*2;
   }




   int UITextList::get_item_index_at(float x, float y)
   {
      float padding_y = item_padding;

      // transform the coordin
      float cursor_y = padding_y;
      for (unsigned i=0; i<items.size(); i++)
      {
         //draw_item(cursor, i);
         cursor_y += get_item_height(i);
         if (y < cursor_y) return i;
      }
      return -1;
   }




   void UITextList::on_select() {}




   bool UITextList::select_at(float x, float y)
   {
      int item_at = get_item_index_at(x, y);
      if (item_at == -1 || item_at == currently_selected_item) return false;
      currently_selected_item = item_at;
      on_select();
      return true;
   }




   bool UITextList::select_at_mouse_cursor() // need to eventually account for multiple mouse cursors.
   {
      ALLEGRO_MOUSE_STATE mouse_state;
      al_get_mouse_state(&mouse_state);
      float x = mouse_state.x, y = mouse_state.y;
      place.transform_coordinates(&x, &y);

      return select_at(x, y);
   }




   void UITextList::joy_down_func()
   {
      UIWidget::joy_down_func();
      if (!mouse_over) return;

      if (Framework::current_event->joystick.button == 0) // TODO: this should not be a hard-coded "0"
      {
         select_at_mouse_cursor();
      }
   }




   void UITextList::mouse_down_func()
   {
      UIWidget::mouse_down_func();
      if (!mouse_over) return;

      //std::cout << "(" << mouse_state.x << ", " << mouse_state.y << ") -> (" << x << ", " << y << ")" << std::endl;
      select_at_mouse_cursor();
   }




   void UITextList::draw_item(AllegroFlare::vec2d position, int index)
      // returns the height of this item in the list
   {
      if (index < 0 || index >= (int)items.size()) return;

      position.y += item_padding;
      bool item_is_selected = index == (this->currently_selected_item);

      ALLEGRO_FONT *font = Framework::font("DroidSans.ttf 18");

      if (item_is_selected)
      {
         //font = fonts["DroidSans-Bold_0.ttf 24"];

         float width = al_get_text_width(font, items[index].c_str());
         float height = al_get_font_line_height(font);

         width += 22;
         height += 4;
      }

      al_draw_text(font, AllegroFlare::color::color(AllegroFlare::color::black, item_is_selected ? 1.0 : 0.3), position.x, position.y+2, ALLEGRO_FLAGS_EMPTY, items[index].c_str());
      al_draw_text(font, item_is_selected ? AllegroFlare::color::mix(AllegroFlare::color::white, AllegroFlare::color::yellow, 0.0) : AllegroFlare::color::white, position.x, position.y, ALLEGRO_FLAGS_EMPTY, items[index].c_str());
   }




   void UITextList::on_draw()
   {
      UIStyleAssets::draw_inset(0, 0, place.size.x, place.size.y, AllegroFlare::color::color(AllegroFlare::color::black, 0.1));
      float padding_x = 16*2, padding_y = item_padding;

      AllegroFlare::vec2d cursor = AllegroFlare::vec2d(padding_x, padding_y);
      //al_draw_line(0, cursor.y, place.size.x, cursor.y, color::white, 1.0);
      for (unsigned i=0; i<items.size(); i++)
      {
         bool item_is_selected = i == (this->currently_selected_item);

         if (item_is_selected)
            al_draw_filled_rounded_rectangle(item_padding, cursor.y,
                  place.size.x-item_padding, cursor.y+item_height+item_padding*2, 3, 3, AllegroFlare::color::color(AllegroFlare::color::dodgerblue, 0.2));

         draw_item(cursor, i);
         cursor.y += get_item_height(i);
         //al_draw_line(0, cursor.y, place.size.x, cursor.y, color::color(color::white, 0.4), 1.0);
      }

      cursor += AllegroFlare::vec2d(padding_x, padding_y);
      place.size.y = cursor.y;
   }
}



