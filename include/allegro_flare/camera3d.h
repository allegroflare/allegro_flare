#ifndef __AF_CAMERA_3D_HEADER
#define __AF_CAMERA_3D_HEADER




#include <allegro5/allegro.h>
#include <allegro_flare/vec3d.h>



class Camera3D
{
public:
	vec3d position;
	vec3d view_vector;
	vec3d up_vector;
	float pitch;

	// hmm, these I think might crave to be implemented in a better way:
	vec3d stepback;
	float stepback_pitch;
	vec3d stepback_rotation;


	Camera3D(vec3d position, vec3d view_vector=vec3d(0, 0, 1), vec3d up_vector=vec3d(0, 1, 0));
	void set_frustum_as_camera(ALLEGRO_DISPLAY *d);

	void look_at(vec3d target);
};



#endif