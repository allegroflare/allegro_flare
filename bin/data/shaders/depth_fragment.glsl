
uniform vec3 camera_position;
uniform sampler2D al_tex;
uniform vec3 light_position;

varying vec3 surface_normal;
varying vec3 world_position;
varying vec2 texture_coords;
#define _sharpness 2.0






//// cube




//DUP varying vec3 normal; // <- replaced as "surface_normal"
varying vec3 eye_dir;
uniform samplerCube cube_map_A;
uniform samplerCube cube_map_B;
//uniform sampler2D al_tex;
uniform bool reflecting;





//// exp

//uniform sampler2D al_tex;
uniform sampler2D diffuse_texture;
uniform sampler2D normal_texture;
uniform sampler2D specular_texture;




varying float dist_from_camera;
varying vec4 glpos;



void main()
{



	//// cube


	vec3 reflected_dir = normalize(reflect(eye_dir, normalize(surface_normal)));

	vec3 incoming_angle = reflected_dir;
	//vec3 incoming_angle = reflecting ? reflected_dir : eye_dir;
	//vec3 incoming_angle = eye_dir;

	incoming_angle.y = -incoming_angle.y;
	incoming_angle.x = -incoming_angle.x;
	//incoming_angle.z = -incoming_angle.z;

	//vec4 texture_cube_color = textureCube(cube_map_A, incoming_angle);

	vec4 diffuse_color = texture2D(diffuse_texture, texture_coords);

	 vec4 texture_cube_color = vec4(0, 0, 0, 1);
//	vec4 texture_cube_color = (textureCube(cube_map_A, incoming_angle) + textureCube(cube_map_B, incoming_angle)) / 2.0;
	//vec4 texture_cube_color = (
										//textureCube(cube_map_A, incoming_angle)
								    //textureCube(cube_map_B, incoming_angle)
	//								 texture2D(diffuse_texture, texture_coords)
	//								 );// / 3.0;



	//gl_FragColor = vec4(1.0, 0, 0, 1.0);


   //float ndist = dist_from_camera * 0.05;
   //float ndist = glpos.b * 0.75;
   float ndist = glpos.b;
   //float ndist = glpos.a * 0.04;
   //float ndist = glpos.a * glpos.a * glpos.a;
   //float ndist = glpos.a;
//	ndist = 1.0 - ndist;
	gl_FragColor = vec4(ndist, ndist, ndist, 1.0);
//	gl_FragColor = vec4(glpos.r, glpos.g, glpos.b, glpos.a);
return;

	texture_cube_color = textureCube(cube_map_B, incoming_angle);
	gl_FragColor = texture_cube_color;


//	vec4 car_texture_fragment = texture2D(my_other_texture, texture_coords);
	vec4 uv_texture_fragment = texture2D(diffuse_texture, texture_coords);
	//gl_FragColor = (uv_texture_fragment + car_texture_fragment + texture_cube_color) / 3.0;
	//gl_FragColor = (car_texture_fragment + texture_cube_color) / 2.0;
	//gl_FragColor = (uv_texture_fragment + texture_cube_color);
	gl_FragColor = (texture_cube_color);

//	gl_FragColor = al_tex




	// stuff




	// grab the color from the texture
	vec4 texture_fragment = texture2D(al_tex, texture_coords);
	
	// make an ambient color
	vec3 color = vec3(0.9, 0.9, 1.0);
	vec3 ambient = vec3(0.6, 0.05, 0.04);
	
	// get our normals and view vectors
	vec3 V = normalize(camera_position - world_position); 
	//vec3 N = normalize(normalize(surface_normal));
	vec3 N = normalize(surface_normal);

	// calculate the fresnel glow
	float fresnel = pow(1.0 - dot(N, V), _sharpness);

	// calculate the light
	vec3 L = normalize(light_position - world_position);
	float reflectance = max(dot(L, N), 0.0);

	// specular
	float specular_intensity = dot((2.0 * reflectance * N - L), V);
	specular_intensity = max(0.0, specular_intensity);
	specular_intensity = pow(specular_intensity, 1.0);
	float spec2 = pow(specular_intensity, 50.0) * 100.0;

	// assign the color to the fragment
	texture_fragment *= 2.0;
	//gl_FragColor = vec4(texture_fragment.r * specular_intensity + fresnel * texture_fragment.r + spec2,
	//						  texture_fragment.g * specular_intensity + fresnel * texture_fragment.g + spec2,
	//						  texture_fragment.b * specular_intensity + fresnel * texture_fragment.b + spec2,
	//						  1.0);

	//fresnel = 1 - fresnel;


	//gl_FragColor = vec4(fresnel * texture_fragment.r + 0.2,
	//						  fresnel * texture_fragment.g ,
	//						  fresnel * texture_fragment.b ,
	//						  1.0);
							  
							  //fresnel = 1 - fresnel;
							  

  float diffuse_luminosity = (diffuse_color.r + diffuse_color.g + diffuse_color.b) / 3.0;
  float inverse_diffuse_luminosity = 1.0 - diffuse_luminosity;

							  
	gl_FragColor = texture_cube_color * diffuse_luminosity
		              + vec4(spec2  * reflectance
									+ reflectance * color.r
									+ ambient.r,
							  spec2 * reflectance
									+ reflectance * color.g
									+ ambient.g,
							  spec2 * reflectance
									+ reflectance * color.b
									+ ambient.b,
							  1.0) * inverse_diffuse_luminosity;


  //gl_FragColor = gl_FragColor / 2.0;

							  
	//gl_FragColor = gl_FragColor * fresnel;
	gl_FragColor.a = 1.0;

//	gl_FragColor = vec4(fresnel * texture_fragment.r*0.5 + reflectance * 0.5 + 0.1 + specular_intensity * reflectance * 0.5 + spec2 * reflectance + ambient.r,
//							  fresnel * texture_fragment.g + reflectance * 0.5 + specular_intensity * reflectance * 0.5 + spec2 * reflectance + ambient.g,
//							  fresnel * texture_fragment.b*0.5 + reflectance * 1.0 + specular_intensity * reflectance * 0.5 + spec2 * reflectance + ambient.b,
//							  1.0);
	
	
//	gl_FragColor = vec4(specular_intensity * reflectance * 0.8,
//							  specular_intensity * reflectance * 0.8,
//							  specular_intensity * reflectance * 0.8,
//							  1.0);
							  


}


