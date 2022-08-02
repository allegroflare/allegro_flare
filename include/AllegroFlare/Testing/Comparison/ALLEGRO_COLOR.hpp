#pragma once


#include <allegro5/allegro_color.h>
#include <ostream>


bool operator==(const ALLEGRO_COLOR& color, const ALLEGRO_COLOR& other_color);
void PrintTo(const ALLEGRO_COLOR& color, ::std::ostream* os);


