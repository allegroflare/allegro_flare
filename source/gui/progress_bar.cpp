



#include <allegro_flare/gui/widgets/progress_bar.h>

#include <allegro5/allegro_primitives.h>
#include <allegro_flare/gui/surface_areas/box.h>
#include <allegro_flare/gui/gui_screen.h>
#include <allegro_flare/gui/style_assets.h>
#include <allegro_flare/allegro_flare.h>
#include <allegro_flare/color.h>
#include <allegro_flare/gui.h>
#include <allegro_flare/useful.h>




UIProgressBar::UIProgressBar(UIWidget *parent, float x, float y, float w, float h)
   : UIWidget(parent, "UIProgressBar", new UISurfaceAreaBox(x, y, w, h))
   , unit_val(0)
   , update_speed(0.4)
   , bar_color(color::dodgerblue)
{}




void UIProgressBar::set_val(float unit_val)
{
   unit_val = limit<float>(0, 1, unit_val);
   Framework::motion().cmove_to(&this->unit_val, unit_val, update_speed, interpolator::doubleFastIn);
}




void UIProgressBar::set_val(float val, float min, float max)
{
   val = (val - min) / (max - min);
   set_val(val);
}




void UIProgressBar::on_draw()
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
   float val = unit_val;
   if (val < min_width) val = min_width;

   // draw the progress bar
   al_draw_filled_rounded_rectangle(inset_padding, inset_padding,
         place.size.x*val - inset_padding, place.size.y - inset_padding,
         roundness, roundness, bar_color);

   // draw the shaded bitmap
   ALLEGRO_BITMAP *shade_down = UIStyleAssets::get_shade_down_gradient();
   draw_stretched_bitmap(3, 3, place.size.x-6, place.size.y-6, shade_down, 0, color::color(color::white, 0.2));
}




