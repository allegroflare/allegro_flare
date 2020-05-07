#ifdef GL_ES
precision mediump float;
#endif
uniform bool al_use_tex;
 varying vec4 varying_color;
varying vec2 varying_texcoord;

uniform sampler2D diffuse_texture;

// depth pass
uniform sampler2D depth_pass_surface;
varying vec4 glPosition_from_light;
varying vec2 shadow_pass_uv_texcoord;

uniform float texture_offset_x;
uniform float texture_offset_y;

// additions
varying vec3 surface_normal;
varying vec3 world_position;
uniform vec3 light_position;
uniform vec3 camera_position;

#define FRESNEL_SHARPNESS 2.0



void main()
{
	vec3 N = normalize(surface_normal); 
	vec3 L = normalize(light_position - world_position);
	vec3 V = normalize(camera_position - world_position); 

	///
	///
	///
	///

	//float cosTheta = clamp( dot(n, l), 0,1 );
	float light_normal_off_surface = clamp(dot(N, L), 0.0, 1.0);
	float normal_points_away = 1.0;
	if (light_normal_off_surface < 0.001) normal_points_away = 0.0;





	float fresnel = pow(1.0 - dot(N, V), FRESNEL_SHARPNESS);

	// specular
	float reflectance = max(dot(L, N), 0.0);
	float specular_intensity = dot((2.0 * reflectance * N - L), V);
	specular_intensity *= 100.0;
	specular_intensity = max(0.0, specular_intensity);
	//specular_intensity = pow(specular_intensity, 1.0);
	//specular_intensity = pow(specular_intensity, 50.0) * 100.0;

	///
	///
	///
	///



  vec4 final_color = vec4(1.0, 1.0, 1.0, 1.0);
  //vec4 final_color = vec4(0.5, 0.5, 0.5, 1.0);

  if (al_use_tex) final_color = texture2D(diffuse_texture, varying_texcoord);
  else final_color = vec4(0.2, 0.5, 0.48, 1.0);
  
  //gl_FragColor = final_color;  

  //float vertex_dist_from_light = glPosition_from_light.z * 0.04;
  //float vertex_dist_from_light = glPosition_from_light.z;
  //float vertex_dist_from_light = glPosition_from_light.z * 0.75;
  float vertex_dist_from_light = glPosition_from_light.z;

  //gl_FragColor = vec4(
		  //final_color.r * vertex_dist_from_light,
		  //final_color.g * vertex_dist_from_light,
		  //final_color.b * vertex_dist_from_light,
		  //1.0);

  //vec2 corrected_shadow_pass_uv = vec2(shadow_pass_uv_texcoord.x, -shadow_pass_uv_texcoord.y) / 10.0 / 2.0 + vec2(texture_offset_x, texture_offset_y); 
  //vec2 corrected_shadow_pass_uv = vec2(shadow_pass_uv_texcoord.x, -shadow_pass_uv_texcoord.y) * 0.5 + vec2(texture_offset_x, texture_offset_y); 
  vec2 corrected_shadow_pass_uv = vec2(shadow_pass_uv_texcoord.x, -shadow_pass_uv_texcoord.y) * 0.5 + vec2(0.5, 0.0); 


  vec4 sample_from_depth_pass = texture2D(depth_pass_surface, corrected_shadow_pass_uv);
  

  float visibility = 1.0;
  //float bias = 0.005;

  //float cosTheta = dot(N, normalize(vec3(1, 1, 1)));
	//float bias = 0.05*tan(acos(cosTheta)); // cosTheta is dot( n,l ), clamped between 0 and 1
	//bias = clamp(bias, 0.0, 0.01);
  float bias = 0.0;

  bool in_casted_shadow = false;
  if (sample_from_depth_pass.r < vertex_dist_from_light-bias) in_casted_shadow = true;

  float shadow_is_casted_multiplier = 1.0;

  if (in_casted_shadow)
  {
	  visibility = 0.5;
	  specular_intensity = 0.0;
	  normal_points_away = 0.0;
  }
  shadow_is_casted_multiplier = normal_points_away;
/*
  final_color = vec4(
		  final_color.r * specular_intensity * direction_to_light,
		  final_color.g * specular_intensity * direction_to_light,
		  final_color.b * specular_intensity * direction_to_light,
		  1.0);
  */
  ///
  ///
  ///

  shadow_is_casted_multiplier *= light_normal_off_surface;

  vec4 shadow_is_casted_multiplier_color = vec4(
		  shadow_is_casted_multiplier * 1.0,
		  shadow_is_casted_multiplier * 0.8,
		  shadow_is_casted_multiplier * 0.5,
		  1.0);


  /*
  if (shadow_is_casted_multiplier < 0.5)
  {
	  final_color = vec4(
		  final_color.r * 0.55,
		  final_color.g * 0.52,
		  final_color.b,
		  1.0);
  }
  */

  final_color = vec4(
		  final_color.r * shadow_is_casted_multiplier_color.r + final_color.r * 0.0,
		  final_color.g * shadow_is_casted_multiplier_color.g + final_color.g * 0.2,
		  final_color.b * shadow_is_casted_multiplier_color.b + final_color.b * 0.5,
		  1.0);

  //fresnel = 1.0 - fresnel;
  fresnel = fresnel * 0.5;
  final_color = final_color += vec4(fresnel, fresnel, fresnel, 1.0);

  //final_color *= vec4(light_normal_off_surface,light_normal_off_surface,  light_normal_off_surface, 1.0);

  ///
  ///
  ///

  gl_FragColor = final_color;
}
