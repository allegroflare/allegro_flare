#ifndef __AF_SHADER_HEADER
#define __AF_SHADER_HEADER





#include <allegro5/allegro.h>

#include <allegro_flare/vec3d.h>


class Shader
{
private:
	ALLEGRO_SHADER *shader;

public:
	Shader(const char *vertex_source_filename, const char *fragment_source_filename);
	~Shader();

	// activate and deactivate
	void use();
	static void stop();

	// set uniforms and attributes
	// (these apply only to the /currently active/ shader, and not necessairly
	// this Shader object)
	static bool set_sampler(const char *name, ALLEGRO_BITMAP *bitmap, int unit);
	static bool set_mat4(const char *name, ALLEGRO_TRANSFORM *t);
	static bool set_int(const char *name, int i);
	static bool set_float(const char *name, float f);
	static bool set_bool(const char *name, bool b);
	static bool set_vec3(const char *name, float x, float y, float z);
	static bool set_vec3(const char *name, const vec3d vec);
};






#endif

