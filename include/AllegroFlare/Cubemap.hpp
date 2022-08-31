#pragma once


#include <allegro5/allegro_opengl.h>


namespace AllegroFlare
{
   class Cubemap
   {
   private:
      GLuint id;

   protected:


   public:
      Cubemap(GLuint id=0);
      ~Cubemap();

      GLuint get_id() const;
   };
}



