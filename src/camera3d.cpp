



#include <allegro_flare/camera3d.h>
#include <allegro_flare/vec2d.h>
#include <allegro_flare/useful.h>



Camera3D::Camera3D(vec3d position, vec3d view_vector, vec3d up_vector)
	: position(position)
	, view_vector(view_vector)
	, up_vector(up_vector)
	, pitch(0)
	, stepback(0)
	, stepback_pitch(0)
	, stepback_rotation(0)
	, camera_tracking_mode(Camera3D::CAMERA_VIEW_THIRD_PERSON_HIGH)
{}




void Camera3D::update_camera_tracking(vec3d targets_position, vec3d targets_view_vector)
{
	vec3d view_vec(0, 0, 0);

	switch(camera_tracking_mode)
	{
	case CAMERA_VIEW_THIRD_PERSON_HIGH:
		// a nice, semi angled birds eye view:
		is_fixed_on_axis = false;
		position = targets_position;
		stepback = targets_view_vector * -3;
		stepback += vec3d(0, 5, 0); // ascent
		stepback_pitch = -0.6;
		pitch = 0;
		view_vector = targets_view_vector;
		break;
	case CAMERA_VIEW_THIRD_PERSON:
		// a nice third person view:
		is_fixed_on_axis = false;
		position = targets_position;
		stepback = targets_view_vector * -3;
		stepback += vec3d(0, 2, 0); // ascent
		stepback_pitch = -0.05;
		pitch = 0;
		view_vector = targets_view_vector;
		break;
	case CAMERA_VIEW_FRIST_PERSON:
		// a first person view:
		is_fixed_on_axis = false;
		position = targets_position;
		stepback = 0;
		stepback += vec3d(0, 1.25, 0); // ascent
		stepback_pitch = 0.2;
		//pitch = 0; // in first person, pitch is controlled by the mouse
		view_vector = targets_view_vector;
		break;
	case CAMERA_VIEW_TRACK_ALONG_X:
		// a first person view:
		is_fixed_on_axis = true;
		position = targets_position;
		view_vec = vec3d(0, 0, -1);
		stepback = view_vec * -10;
		stepback += vec3d(0, 5, 0); // ascent
		stepback_pitch = -0.05;
		pitch = 0;
		view_vector = view_vec;
		break;
	case CAMERA_VIEW_TRACK_ALONG_X_HIGH:
		// a first person view:
		is_fixed_on_axis = true;
		position = targets_position;
		view_vec = vec3d(0, 0, -1);
		stepback = view_vec * -12;
		stepback += vec3d(0, 10, 0); // ascent
		pitch = 0;
		stepback_pitch = -0.5;
		view_vector = view_vec;
		break;
	case CAMERA_VIEW_TRACK_ALONG_X_BIRD:
		// a first person view:
		is_fixed_on_axis = true;
		position = targets_position;
		view_vec = vec3d(0, 0, -1);
		stepback = view_vec * -8;
		stepback += vec3d(0, 12, 0); // ascent
		pitch = 0;
		stepback_pitch = -1.0;
		view_vector = view_vec;
		break;
	}
}




void Camera3D::set_frustum_as_camera(ALLEGRO_DISPLAY *d)
	// might want to rename this function to something else
{
	if (!d) return;




	/// hrmkay...
	al_set_render_state(ALLEGRO_DEPTH_TEST, 1);
	al_set_render_state(ALLEGRO_WRITE_MASK, ALLEGRO_MASK_DEPTH | ALLEGRO_MASK_RGBA);
	al_clear_depth_buffer(1); 




	Frustum frustum = get_frustum(d);




	ALLEGRO_TRANSFORM transform;

	al_identity_transform(&transform);

	// ... ok... I don't know why this transform requires a (+0.5, +0.5, 0) but if it's not there,
	// then the camera does not stick on the point 0, 0.  maybe it has something to do with
	// the view vector, maybe something with ALLEGRO doing pixel coordinates,
	// but I'm a little unsure, hopefully this line will be resolved properly somewherre else and
	// not needed in the future: 
	//al_translate_transform_3d(&transform, 0.5, 0.5, 0); // HHHHAAAAAALLLLLEEELULAAHH! o:D

	al_translate_transform_3d(&transform, -position.x-stepback.x, -position.y-stepback.y, -position.z-stepback.z); // hmm, using negatives is new
	//al_translate_transform_3d(&transform, , , ); // hmm, using negatives is new


	vec2d thing(view_vector.x, view_vector.z);
	// HEY, so rotation.y == thing.GetAngle()
	// TODO: figure out these rotations:
	// This one is not correct:
	// al_rotate_transform_3d(&transform, 0, 0, 1, 0.1 * TAU); //  tilt the camera to look downward slightly
	// I believe this one is correct:

	al_rotate_transform_3d(&transform, 0, 1, 0, thing.get_angle() + TAU/4);//(al_get_time()*0.2));

	// This one, *might* be correct:
	//al_rotate_transform_3d(&transform, 1, 0, 0, vec2d(view_vector.y, view_vector.z).get_angle() - TAU/4);


	
	// this is the vector for roll
	//al_rotate_transform_3d(&transform, 0, 0, 1, (TAU/2)); // flip the world ... ? // maybe this messes with the strafe and up vectors



		al_rotate_transform_3d(&transform, 0, 1, 0, stepback_rotation.y); //  tilt the camera to look downward slightly
		//al_rotate_transform_3d(&transform, 1, 0, 0, pitch); //  tilt the camera to look downward slightly			
		//al_translate_transform_3d(&transform, stepback.x, stepback.y, stepback.z); // hmm, using negatives is new
		al_rotate_transform_3d(&transform, -1, 0, 0, stepback_pitch + pitch); //  the up-down tilt of the camera



	al_perspective_transform(&transform,
		frustum.left, frustum.top, frustum.znear,
		frustum.right, frustum.bottom, frustum.zfar);

	al_use_projection_transform(&transform);
}




void Camera3D::look_at(vec3d target)
{
	view_vector = (target - position).Normalized();
}



Frustum Camera3D::get_frustum(ALLEGRO_DISPLAY *d)
{
	return Frustum(al_get_display_width(d), al_get_display_height(d), 500, 0.0001);
}
