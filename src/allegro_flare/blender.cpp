



#include <allegro_flare/blender.h>

#include <allegro5/allegro.h>




namespace allegro_flare
{
   void set_blender(blender_t type)
   {
      switch(type)
      {
      case BLENDER_ADDITIVE:
         al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ONE);
         break;
      case BLENDER_MULTIPLY:
         al_set_blender(ALLEGRO_ADD, ALLEGRO_DST_COLOR, ALLEGRO_ZERO); // DUNNO
         break;
      case BLENDER_SCREEN:
         // via Edgar Roboto -> https://www.allegro.cc/forums/revision/984964
         al_set_blender(ALLEGRO_ADD, ALLEGRO_INVERSE_DST_COLOR, ALLEGRO_ONE);
         //al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_SRC_COLOR);  // <-this one should work also
         break;
      case BLENDER_SUBTRACTIVE:
         // not implemented yet
      case BLENDER_NORMAL:
      default:
         al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA);
         break;
      }
   }
}



