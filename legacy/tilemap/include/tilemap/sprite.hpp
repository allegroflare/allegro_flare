#pragma once


#include <allegro5/allegro.h>
#include <framework/element_id.hpp>
#include <framework/placement2d.hpp>


class Sprite : public ElementID
{
public:
   Placement2D placement;
   Placement2D velocity;
   ALLEGRO_BITMAP *bitmap;

   Sprite(ElementID *parent);
   ~Sprite();

   void draw();
};


