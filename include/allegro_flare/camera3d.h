#ifndef __AF_CAMERA_3D_HEADER
#define __AF_CAMERA_3D_HEADER




#include <allegro5/allegro.h>
#include <allegro_flare/vec3d.h>
#include <allegro_flare/frustum.h>



class Camera3D
{
public:

	enum camera_tracking_mode_t
	{
		CAMERA_VIEW_DIRECT,
		CAMERA_VIEW_THIRD_PERSON_HIGH,
		CAMERA_VIEW_THIRD_PERSON,
		CAMERA_VIEW_FRIST_PERSON,
		CAMERA_VIEW_TRACK_ALONG_X, // platform game style
		CAMERA_VIEW_TRACK_ALONG_X_HIGH, // sim city style :)
		CAMERA_VIEW_TRACK_ALONG_X_BIRD, // sim city style :)
		CAMERA_VIEW_LAST // for mod
	};

	vec3d position;
	vec3d view_vector;
	vec3d up_vector;
	float pitch;

	//camera_tracking_mode_t camera_tracking_mode;

	// hmm, these I think might crave to be implemented in a better way:
	vec3d stepback;
	float stepback_pitch;
	vec3d stepback_rotation;


	Camera3D(vec3d position, vec3d view_vector=vec3d(0, 0, 1), vec3d up_vector=vec3d(0, 1, 0));
	void set_frustum_as_camera(ALLEGRO_DISPLAY *d);

	void look_at(vec3d target);
	void update_camera_tracking(vec3d targets_position, vec3d targets_view_vector, camera_tracking_mode_t camera_tracking_mode);

	Frustum get_frustum(ALLEGRO_DISPLAY *d);
};



#endif