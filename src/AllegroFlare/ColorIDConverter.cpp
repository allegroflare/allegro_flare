

#include <AllegroFlare/ColorIDConverter.hpp>




namespace AllegroFlare
{
   int ColorIDConverter::decode_id(ALLEGRO_COLOR color)
   {
      unsigned char r, g, b, a;
      al_unmap_rgba(color, &r, &g, &b, &a);

      return r + (g * 256) + (b * 65536);
   }



   ALLEGRO_COLOR ColorIDConverter::encode_id(int id)
   {
      unsigned char r = id % 256;
      unsigned char g = id / 256;
      unsigned char b = id / 65536;
      unsigned char a = (id == 0) ? 0 : 255;

      return al_map_rgba(r, g, b, a);
   }
}




