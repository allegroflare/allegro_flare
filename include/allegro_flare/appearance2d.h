#ifndef __ALLEGRO_FLARE_APPEARANCE_HEADER
#define __ALLEGRO_FLARE_APPEARANCE_HEADER



#include <allegro5/allegro.h>
#include <allegro_flare/blender.h>


class appearance2d
{
public:
	ALLEGRO_COLOR color;
	blender_t blender;
	float opacity;
	// ALLEGRO_SHADER *shader; //< coming soon :o

	appearance2d();
	void clear();
};




#endif
