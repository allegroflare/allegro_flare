#ifndef __AF_RENDER_PATH_2D_HEADER
#define __AF_RENDER_PATH_2D_HEADER




#include <allegro_flare/path2d.h>
#include <allegro_flare/interpolators.h>




// TODO: these functions might need to be placed somewhere else.  Maybe in assets or with the texture generator functions 

path2d create_path_from_interpolator(interpolator::interpolator_func_t func, int num_segments=16);

ALLEGRO_BITMAP *create_interpolator_render(int w, int h, interpolator::interpolator_func_t func, float line_thickness=8, float padding=8, int num_segments=16);





#endif
