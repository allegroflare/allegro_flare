#pragma once



#include <allegro5/allegro_color.h>



class ColorIDConverter
{
public:
   static const int ID_MAX = 16777216;

   static int decode_id(ALLEGRO_COLOR color);
   static ALLEGRO_COLOR encode_id(int id);
};



