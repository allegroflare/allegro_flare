#ifndef __AF_CUBEMAP_TEXTURE_HEADER
#define __AF_CUBEMAP_TEXTURE_HEADER




#include <allegro5/allegro.h>
#include <allegro5/allegro_opengl.h>




struct ALLEGRO_FLARE_CUBEMAP_TEXTURE
{
   GLuint id;
};




bool glsl_destroy_cubemap_texture(ALLEGRO_FLARE_CUBEMAP_TEXTURE *texture);

ALLEGRO_FLARE_CUBEMAP_TEXTURE *glsl_create_cubemap_from_vertical_strip(const char *filename);




#endif
