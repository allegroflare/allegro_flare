#ifndef __AF_MODEL_HEADER
#define __AF_MODEL_HEADER





#include <vector>
#include <allegro5/allegro_primitives.h>
#include <allegro_flare/vec2d.h>



class ModelNew
{
private:

	typedef struct
	{
		float x, y, z;
		float u, v;
		ALLEGRO_COLOR color;
		float nx, ny, nz;
	} ALLEGRO_VERTEX_WITH_NORMAL;

	class vt_coord
	{
	public:
		float u;
		float v;
	};

public:
	ALLEGRO_VERTEX_DECL *vertex_declaration;
	std::vector<ALLEGRO_VERTEX_WITH_NORMAL> vertexes;
	ALLEGRO_BITMAP *texture;
	vec2d texture_scale;

	ModelNew();
	void set_texture(ALLEGRO_BITMAP *tx);
	bool load_obj_file(const char *filename, float scale=1.0);
	void inspect();
	void draw();
};



#endif
