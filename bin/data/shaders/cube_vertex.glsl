
attribute vec4 al_pos;
attribute vec3 al_user_attr_0;

uniform mat4 al_projview_matrix;
uniform mat4 position_transform;
uniform vec3 camera_position;

varying vec3 normal;
varying vec3 eye_dir;
uniform samplerCube cube_map_A;
uniform samplerCube cube_map_B;

void main()
{
	gl_Position = al_projview_matrix * position_transform * al_pos;
	normal = (position_transform * vec4(al_user_attr_0, 0.0)).xyz;
	// this NORMAL val will probably ned to be multiplied by the position transform
//	normal = (al_user_attr_0).xyz;
	vec3 world_position = (position_transform * al_pos).xyz;
	eye_dir = vec3(camera_position - world_position);
}


