#pragma once


#include <allegro5/allegro.h>


namespace AllegroFlare
{
   class MouseAxesChangeData
   {
   private:

   protected:


   public:
      int x;
      int y;
      int z;
      int w;
      int dx;
      int dy;
      int dz;
      int dw;
      ALLEGRO_DISPLAY* display;
      MouseAxesChangeData();
      ~MouseAxesChangeData();

      void populate_data_from_ALLEGRO_EVENT(ALLEGRO_EVENT* ev=nullptr);
   };
}



