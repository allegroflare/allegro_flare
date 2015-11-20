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

	struct vt_coord
	{
	public:
		float u;
		float v;
	};

	struct named_object
	{
	public:
		std::string identifier;
		std::vector<int> index_list;
	};

public:
	ALLEGRO_VERTEX_DECL *vertex_declaration;
	std::vector<ALLEGRO_VERTEX_WITH_NORMAL> vertexes;
	ALLEGRO_BITMAP *texture;
	std::vector<named_object> named_objects; // < this is not very effecient, vector in a vector. Fix later.

	ModelNew();
	bool load_obj_file(const char *filename, float scale=1.0);
	void inspect();
	int get_num_vertexes();
	int get_num_named_objects();
	void draw();
	bool draw_object(int index);
	bool draw_object(std::string name);

	// modify
	void set_texture(ALLEGRO_BITMAP *tx);
	void scale(float scale);
};




#endif
