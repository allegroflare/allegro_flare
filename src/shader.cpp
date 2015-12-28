



#include <allegro_flare/shader.h>

#include <iostream>



Shader::Shader(const char *vertex_source_filename, const char *fragment_source_filename)
	// for now, shaders will be GLSL in AllegroFlare.  This should eventually change in the future
	: shader(al_create_shader(ALLEGRO_SHADER_GLSL))
{
	if (!shader) std::cerr << "There was a problem creating a shader." << std::endl;

	if (!al_attach_shader_source_file(shader, ALLEGRO_VERTEX_SHADER, vertex_source_filename))
		std::cerr << "There was an error attaching the VERTEX shader source from file:"
					<< std::endl << "\"" << vertex_source_filename << "\""
					<< std::endl << al_get_shader_log(shader)
					<< std::endl;

	if (!al_attach_shader_source_file(shader, ALLEGRO_PIXEL_SHADER, fragment_source_filename))
		std::cerr << "There was an error attaching the FRAGMENT shader source from file:"
					<< std::endl << "\"" << fragment_source_filename << "\""
					<< std::endl << al_get_shader_log(shader)
					<< std::endl;

	if (!al_build_shader(shader))
	{
		std::cerr << "There were errors when building the shader:" << std::endl;
		std::cerr << al_get_shader_log(shader) << std::endl;
	}
}



Shader::~Shader()
{
	al_destroy_shader(shader);
}



void Shader::use()
{
	al_use_shader(shader);
}



void Shader::stop()
{
	al_use_shader(NULL);
}



bool Shader::set_sampler(const char *name, ALLEGRO_BITMAP *bitmap, int unit)
{
	return al_set_shader_sampler(name, bitmap, unit);
}



bool Shader::set_mat4(const char *name, ALLEGRO_TRANSFORM *t)
{
	return al_set_shader_matrix(name, t);
}



bool Shader::set_int(const char *name, int i)
{
	return al_set_shader_int(name, i);
}


bool Shader::set_float(const char *name, float f)
{
	return al_set_shader_float(name, f);
}



bool Shader::set_bool(const char *name, bool b)
{
	return al_set_shader_bool(name, b);
}



bool Shader::set_vec3(const char *name, float x, float y, float z)
{
	float vec3[3] = {x, y, z};
	return al_set_shader_float_vector(name, 3, &vec3[0], 1);
}



bool Shader::set_vec3(const char *name, const vec3d vec)
{
	return set_vec3(name, vec.x, vec.y, vec.z);
}




