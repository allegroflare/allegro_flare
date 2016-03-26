



#include <allegro_flare/gui/widgets/scaled_text.h>

#include <allegro5/allegro_font.h>

#include <allegro_flare/allegro_flare.h> // for bins
#include <allegro_flare/useful.h> // for tostring

#include <allegro_flare/gui.h>
#include <allegro_flare/gui/gui_screen.h> // < TODO: don't think this is needed
#include <allegro_flare/gui/surface_areas/box.h>




std::string FGUIScaledText::_get_font_index_str()
{
   return font_filename + " " + tostring((int)(font_size * render_scale));
}



void FGUIScaledText::refresh_render()
{
   // for easy life
   ALLEGRO_FONT *scaled_font = af::fonts[_get_font_index_str()];

   // save the previous state
   ALLEGRO_STATE previous_state;
   al_store_state(&previous_state, ALLEGRO_STATE_TARGET_BITMAP);

   // create the bitmap
   if (render) al_destroy_bitmap(render);
   render = al_create_bitmap(al_get_text_width(scaled_font, text.c_str()), al_get_font_line_height(scaled_font));

   // set the target
   al_set_target_bitmap(render);

   // clear and draw the text
   al_clear_to_color(color::transparent);
   al_draw_text(scaled_font, color::white, 0, 0, ALLEGRO_ALIGN_LEFT, text.c_str());

   // restore the state
   al_restore_state(&previous_state);

   // update the placement data
   surface_area->placement.size.x = al_get_bitmap_width(render) / render_scale;
   surface_area->placement.size.y = al_get_bitmap_height(render) / render_scale;
}



FGUIScaledText::FGUIScaledText(FGUIWidget *parent, float x, float y, std::string text)
   : FGUIWidget(parent, new FGUISurfaceAreaBox(x, y, 100, 100))
   , font_filename("DroidSans.ttf")
   , font_size(14)
   , render_scale(3.0)
   , render(NULL)
   , text(text)
   , font_color(color::white)
{
   attr.set(FGUI_ATTR__FGUI_WIDGET_TYPE, "FGUIScaledText");
   attr.set("id", "ScaledText" + tostring(FGUIWidget::get_num_created_widgets()));

   this->surface_area->placement.align.x = 0.0;
   this->no_focus = true;

   refresh_render();
}



void FGUIScaledText::on_draw()
{
   if (!render) return;

   al_draw_tinted_scaled_bitmap(render, font_color, 0, 0, al_get_bitmap_width(render), al_get_bitmap_height(render),
      0, 0, place.size.x, place.size.y, ALLEGRO_FLAGS_EMPTY);
}



void FGUIScaledText::set_font_color(ALLEGRO_COLOR color)
{
   font_color = color;
}



void FGUIScaledText::set_text(std::string text)
{
   if (this->text.compare(text)==0) return;
   this->text = text;
   refresh_render();
}



void FGUIScaledText::set_font(std::string _font_filename, int _font_size)
{
   if (_font_size == font_size && _font_filename == font_filename) return;

   font_size = _font_size;
   font_filename = _font_filename;

   refresh_render();
}


