attribute vec4 al_pos;
attribute vec4 al_color;
attribute vec2 al_texcoord;
uniform mat4 al_projview_matrix;
uniform bool al_use_tex_matrix;
uniform mat4 al_tex_matrix;
//varying vec4 varying_color;
varying vec2 varying_texcoord;

uniform mat4 position_transform;
uniform mat4 depth_pass_transform;
varying vec4 glPosition_from_light;
varying vec2 shadow_pass_uv_texcoord;

// additions
attribute vec3 al_user_attr_0;
varying vec3 world_position;
varying vec3 surface_normal;

void main()
{
	surface_normal = (position_transform * vec4(al_user_attr_0, 0.0)).xyz;
	world_position = (position_transform * al_pos).xyz;

  glPosition_from_light = depth_pass_transform * position_transform * al_pos;


   //varying_color = al_color;
  if (al_use_tex_matrix) {
    vec4 uv = al_tex_matrix * vec4(al_texcoord, 0, 1);
    varying_texcoord = vec2(uv.x, uv.y);

    vec4 spuv = al_tex_matrix * vec4(glPosition_from_light.xy, 0, 1);
    shadow_pass_uv_texcoord = vec2(spuv.x, spuv.y);
	 //shadow_pass_uv_texcoord = vec2(glPosition_from_light.x, glPosition_from_light.y);
  }
  else
    varying_texcoord = al_texcoord;

  gl_Position = al_projview_matrix * position_transform * al_pos;
}
