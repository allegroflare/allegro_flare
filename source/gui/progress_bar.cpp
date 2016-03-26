


#include <allegro_flare/gui/widgets/progress_bar.h>


#include <allegro5/allegro_primitives.h>

#include <allegro_flare/color.h>
#include <allegro_flare/useful.h>
#include <allegro_flare/allegro_flare.h>

#include <allegro_flare/gui.h>
#include <allegro_flare/gui/surface_areas/box.h>
#include <allegro_flare/gui/gui_screen.h>
#include <allegro_flare/gui/style_assets.h>




FGUIProgressBar::FGUIProgressBar(FGUIWidget *parent, float x, float y, float w, float h)
   : FGUIWidget(parent, new FGUISurfaceAreaBox(x, y, w, h))
   , val(0)
   , update_speed(0.4)
   , bar_color(color::dodgerblue)
{
   attr.set(FGUI_ATTR__FGUI_WIDGET_TYPE, "FGUIProgressBar");
   attr.set("id", "ProgressBar" + tostring(FGUIWidget::get_num_created_widgets()));
}



void FGUIProgressBar::set_val(float normalized_val)
{
   normalized_val = limit<float>(0, 1, normalized_val);
   af::motion.cmove_to(&val, normalized_val, update_speed, interpolator::doubleFastIn);
}



void FGUIProgressBar::set_val(float _val, float min, float max)
{
   float normalized_val = (_val - min) / (max - min);
   set_val(normalized_val);
}



void FGUIProgressBar::on_draw()
{
   float roundness = place.size.y/4;
   float inset_padding = 3;

   // draw the background
   al_draw_filled_rounded_rectangle(0, 0, place.size.x, place.size.y, roundness, roundness, color::color(color::black, 0.2));

   // draw the background outline
   al_draw_rounded_rectangle(0, 0, place.size.x, place.size.y, roundness, roundness, color::color(color::black, 0.2), 2.0);
      


   // because of the rounded corners, the min drawing
   // width of the bar
   float min_width = 15/place.size.x; // 15 pixels
   float _val = val;
   if (_val < min_width) _val = min_width;

   // draw the progress bar
   al_draw_filled_rounded_rectangle(inset_padding, inset_padding,
      place.size.x*_val - inset_padding, place.size.y - inset_padding,
      roundness, roundness, bar_color);

   // draw the shaded bitmap
   ALLEGRO_BITMAP *shade_down = FGUIStyleAssets::get_shade_down_gradient();
   draw_stretched_bitmap(3, 3, place.size.x-6, place.size.y-6, shade_down, 0, color::color(color::white, 0.2));
}


