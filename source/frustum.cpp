



#include <allegro_flare/frustum.h>




//Frustum(int width=800, int height=600, int znear=500, float multiplier=0.01);
Frustum::Frustum(int width, int height, int znear, float multiplier)
   : znear(znear * multiplier)
   , zfar(30000)
   , top(height/2 * multiplier)   //+					//-    <-previously
   , left(-width/2 * multiplier)   //-					//-
   , right(width/2 * multiplier)    //+				//+
   , bottom(-height/2 * multiplier)  //-				//+
{}




