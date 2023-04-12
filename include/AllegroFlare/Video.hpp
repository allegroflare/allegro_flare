#pragma once


#include <allegro5/allegro_video.h>


namespace AllegroFlare
{
   class Video
   {
   private:
      ALLEGRO_VIDEO* al_video;

   protected:


   public:
      Video(ALLEGRO_VIDEO* al_video=nullptr);
      ~Video();

      void set_al_video(ALLEGRO_VIDEO* al_video);
      ALLEGRO_VIDEO* get_al_video() const;
   };
}



