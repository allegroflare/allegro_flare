#ifndef __AF_MODEL_HEADER
#define __AF_MODEL_HEADER





#include <vector>
#include <allegro5/allegro_primitives.h>
#include <allegro_flare/vec2d.h>



class ModelNew
{
private:
	class vt_coord
	{
	public:
		float u;
		float v;
	};

public:
	std::vector<ALLEGRO_VERTEX> vertexes;
	ALLEGRO_BITMAP *texture;
	vec2d texture_scale;

	ModelNew();
	void set_texture(ALLEGRO_BITMAP *tx);
	bool load_obj_file(const char *filename, float scale=1.0);
	void inspect();
	void draw();
};



#endif
