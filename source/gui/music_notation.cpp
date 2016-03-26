



#include <allegro5/allegro_primitives.h>

#include <allegro_flare/color.h>
#include <allegro_flare/drawing_interfaces/drawing_interface_allegro5.h>

#include <allegro_flare/gui/widgets/music_notation.h>
#include <allegro_flare/gui/surface_areas/box.h>

#include <allegro_flare/useful.h>



FGUIMusicNotation::FGUIMusicNotation(FGUIWidget *parent, float x, float y)
   : FGUIWidget(parent, new FGUISurfaceAreaBox(x, y, 300, 80))
   , notation(new DrawingInterfaceAllegro5())
   , val("")
{
   attr.set(FGUI_ATTR__FGUI_WIDGET_TYPE, "FGUIMusicNotation");
   attr.set("id", "MusicNotation" + tostring(FGUIWidget::get_num_created_widgets()));
}



void FGUIMusicNotation::set_val(std::string _val)
{
   val = _val;
}


std::string FGUIMusicNotation::get_val()
{
   return val;
}



void FGUIMusicNotation::on_draw()
{
   placement2d &place = this->surface_area->placement;
   al_draw_filled_rectangle(0, 0, place.size.x, place.size.y, color::color(color::white, mouse_over ? 0.2 : 0.1));
   place.size.x = std::max(10, notation.draw(0, place.size.y/2, val));
}

