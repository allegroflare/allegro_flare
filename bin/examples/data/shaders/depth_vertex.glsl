

attribute vec4 al_pos;
attribute vec3 al_user_attr_0;
attribute vec2 al_texcoord;

uniform mat4 al_tex_matrix;
uniform mat4 al_projview_matrix;
uniform mat4 position_transform; // provided by the user, this is the model's ALLEGRO_TRANSFORM

varying vec3 surface_normal;
varying vec3 world_position;
varying vec2 texture_coords;





//// cube



//DUP attribute vec4 al_pos;
//DUP attribute vec3 al_user_attr_0;

//DUP uniform mat4 al_projview_matrix;
//DUP uniform mat4 position_transform;
uniform vec3 camera_position;

varying vec3 normal;
varying vec3 eye_dir;
//uniform samplerCube cube_map;




varying float dist_from_camera;
varying vec4 glpos;

//// exp

//uniform texture2D 





void main()
{
	surface_normal = (position_transform * vec4(al_user_attr_0, 0.0)).xyz;
	world_position = (position_transform * al_pos).xyz;
	
	//texture_coords = al_texcoord;
	vec4 uv = al_tex_matrix * vec4(al_texcoord, 0, 1);
	texture_coords = vec2(uv.x, uv.y);



   glpos = al_projview_matrix * position_transform * al_pos;
	gl_Position = al_projview_matrix * position_transform * al_pos;



	dist_from_camera = distance(camera_position, (position_transform * al_pos).xyz);




	////




	//DUP gl_Position = al_projview_matrix * position_transform * al_pos;
	//DUP normal = (position_transform * vec4(al_user_attr_0, 0.0)).xyz;
		////// this NORMAL val will probably ned to be multiplied by the position transform
		//////	normal = (al_user_attr_0).xyz;
	//DUP vec3 world_position = (position_transform * al_pos).xyz;
	eye_dir = vec3(camera_position - world_position);



}


