

varying vec3 normal;
varying vec3 eye_dir;
uniform samplerCube cube_map_A;
uniform samplerCube cube_map_B;
//uniform sampler2D al_tex;
uniform bool reflecting;

void main()
{
	vec3 reflected_dir = normalize(reflect(eye_dir, normalize(normal)));

	vec3 incoming_angle = reflecting ? reflected_dir : eye_dir;
	//vec3 incoming_angle = eye_dir;

	incoming_angle.y = -incoming_angle.y;
	incoming_angle.x = -incoming_angle.x;
	//incoming_angle.z = -incoming_angle.z;

	vec4 color = textureCube(cube_map_A, incoming_angle);
	//color = textureCube(cube_map_B, incoming_angle);
	
	

	 vec4 golden_color = vec4(1.0, 0.74, 0.0, 1.0);

	 color = golden_color * 0.6 + color * 0.7;
	
	
	gl_FragColor = color;
}
