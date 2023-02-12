#pragma once


#ifdef __APPLE__
// TODO: Fix or improve this depreciation declaration here
#define GL_SILENCE_DEPRECATION
#endif

#include<allegro5/allegro_opengl.h>

#ifdef __APPLE__
#undef GL_SILENCE_DEPRECATION
#endif

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



