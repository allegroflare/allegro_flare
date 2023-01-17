

#include <allegro5/allegro_primitives.h>
#include <framework/color.hpp>
#include <tilemap/sprite.hpp>


Sprite::Sprite(ElementID *parent)
   : ElementID(parent)
   , placement(32*3, 32*3, 16, 16)
   , velocity(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
   , bitmap(nullptr)
{
   placement.align = vec2d(0, 0);
}


Sprite::~Sprite()
{
}


void Sprite::draw()
{
   placement.start_transform();
   al_draw_filled_rectangle(0, 0, placement.size.x, placement.size.y, color::yellow);
   placement.restore_transform();
}


