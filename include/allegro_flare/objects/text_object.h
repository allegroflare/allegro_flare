#ifndef __AF_TEXT_OBJECT_HEADER
#define __AF_TEXT_OBJECT_HEADER




#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_color.h>
#include <allegro_flare/bins/font_bin.h>
#include <allegro_flare/object2d.h>
#include <allegro_flare/useful.h>
#include <allegro_flare/vec2d.h>




class TextObject : public object2d
{
private:
   static TextObject *dummy;

public:
   std::string str;
   ALLEGRO_FONT *_font;

   static TextObject *get_dummy()
   {
      if (!dummy) dummy = new TextObject("");
      return dummy;
   }

public:
   TextObject(std::string str="") : object2d(0,0,200,30), str(str), _font(NULL)
   {
      text(str);
   }

   inline TextObject &clean()
   {
      if (_placement) _placement->clear();
      if (_appearance) _appearance->clear();
      str = "";
      _font = NULL;
      *_h = 0;
      *_w = 0;
      return *this;
   }

   inline TextObject &text(std::string str)
   {
      if (str == this->str) return *this;

      this->str = str;
      if (_font)
      {
         *_w = al_get_text_width(_font, str.c_str());
         *_h = al_get_font_line_height(_font);
      }
      return *this;
   }

   inline TextObject &align(float x, float y) override { object2d::align(x, y); return *this; }
   inline TextObject &position(float x, float y) override { object2d::position(x, y); return *this; }
   inline TextObject &anchor(float x, float y) override { object2d::anchor(x, y); return *this; }
   inline TextObject &scale(float x, float y) override { object2d::scale(x, y); return *this; }
   inline TextObject &scale(float s) override { object2d::scale(s); return *this; }
   inline TextObject &opacity(float opacity) override { object2d::opacity(opacity); return *this; }

   inline TextObject &font(ALLEGRO_FONT *font)
   {
      if (_font == font) return *this;
      _font = font;
      *_h = al_get_font_line_height(_font);
      *_w = al_get_text_width(_font, str.c_str());
      return *this;
   }

   inline TextObject &color(ALLEGRO_COLOR _color) override
   {
      object2d::color(_color);
      return *this;
   }

   inline TextObject &color(const char *_color, float opacity=1.0) override
   {
      object2d::color(_color, opacity);
      return *this;
   }

   ALLEGRO_BITMAP *create_render()
   {
      ALLEGRO_BITMAP *img = NULL;
      ALLEGRO_STATE state;
      if (!(*_w>=1.0 && *_h>=1.0)) return NULL;

      img = al_create_bitmap(*_w, *_h);
      al_store_state(&state, ALLEGRO_STATE_TARGET_BITMAP);
      al_set_target_bitmap(img);
      al_clear_to_color(al_map_rgba_f(0,0,0,0));
      al_draw_text(_font, (_appearance)?color::color(_appearance->color, _appearance->opacity):al_map_rgba_f(1,1,1,1), 0, 0, ALLEGRO_FLAGS_EMPTY, str.c_str());
      al_restore_state(&state);
      return img;
   }

   inline TextObject &draw() override
   {
      if (_placement) _placement->start_transform();
      if (_font) al_draw_text(_font, (_appearance)?color::color(_appearance->color, _appearance->opacity):al_map_rgba_f(1,1,1,1), 0, 0, ALLEGRO_FLAGS_EMPTY, str.c_str());
      if (_placement) _placement->restore_transform();
      return *this;
   }
};




inline TextObject &text(std::string str)
{
   TextObject::get_dummy()->clean().text(str);
   return *TextObject::get_dummy();
}




#endif
