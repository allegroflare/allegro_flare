#ifndef __AF_CAMERA_2D_HEADER
#define __AF_CAMERA_2D_HEADER




#include <allegro5/allegro.h>
#include <allegro_flare/placement2d.h>
#include <allegro_flare/vec2d.h>




class projected_point_data
{
public:
	float x;
	float y;
	float scale;
	projected_point_data(float x, float y, float scale);
};




class Camera2D
{
public:
	ALLEGRO_COLOR overlay_color;
	float overlay_opacity;

	ALLEGRO_STATE previous_state; // I believe this will eventually be phased out

	placement2d placement;
	ALLEGRO_TRANSFORM transform;
	/*
	ALLEGRO_TRANSFORM transform;
	float x, y, w, h, align_x, align_y, scale_x, scale_y, rotation;
	*/
	float z, home_z, depth; // these can be used to simulate a cheap 2.5D depth effect.  This may be developed later on...

	Camera2D(float x=0, float y=0, float width=800, float height=600);
	void start_transform();
	void restore_transform();
	//void target(float x, float y); // just set the placement.position

	void translate_screen_to_world(float *x, float *y);
	void translate_screen_to_world(vec2d *vec);
	void translate_world_to_screen(vec2d *vec); // has not been tested

	float get_scale(float world_z);
	projected_point_data get_projected_point(float world_x, float world_y, float world_z);
};




#endif
