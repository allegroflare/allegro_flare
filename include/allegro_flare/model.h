#ifndef __AF_MODEL_HEADER
#define __AF_MODEL_HEADER





#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include <allegro_flare/vec2d.h>
#include <allegro_flare/vec3d.h>


#include <allegro_flare/placement3d.h>
//#include <allegro_flare/aabb3d.h>
#include <allegro_flare/color.h>



class TextureSet
{
public:
	std::vector<std::pair<int, ALLEGRO_BITMAP *> > textures;
//	std::vector<std::pair<std::string, ALLEGRO_BITMAP *> > textures;

	TextureSet();
	bool set_texture_by_index(int model_object_index, ALLEGRO_BITMAP *bmp);
	bool has_texture(int model_object_index);

	ALLEGRO_BITMAP *get_texture(int model_object_index);
};


class ColorSet
{
public:
	std::vector<std::pair<int, ALLEGRO_COLOR> > textures;

	ColorSet();
	bool set_color(int model_object_index, ALLEGRO_COLOR col);
	bool has_color(int model_object_index);

	ALLEGRO_COLOR get_color(int model_object_index);
};


class ObjectTextureDef
{
public:
	int object_index;
	std::string object_name;
	ALLEGRO_BITMAP *texture;
	ALLEGRO_COLOR color;
};



class ModelTextures
{
public:
	std::vector<ObjectTextureDef *> object_texture_defs;

	ModelTextures()
		: object_texture_defs()
	{}

	bool add_texture_def(ObjectTextureDef *def)
	{
		if (!def) return false;

		if (get_texture_def_from_index(def->object_index)) return false;
		if (get_texture_def_from_name(def->object_name)) return false;

		object_texture_defs.push_back(def);

		return true;
	}
	ObjectTextureDef *get_texture_def_from_name(std::string name)
	{
		for (unsigned i=0; i<object_texture_defs.size(); i++)
			if (object_texture_defs[i]->object_name == name) return object_texture_defs[i];
		return NULL;
	}
	ObjectTextureDef *get_texture_def_from_index(int index)
	{
		for (unsigned i=0; i<object_texture_defs.size(); i++)
			if (object_texture_defs[i]->object_index == index) return object_texture_defs[i];
		return NULL;
	}
};



class Model
{

public:
	//AABB3D *bbox; // should be thought of as private, read only
	class Object
	{
	public:
		Model *parent;
		std::string name;
		std::vector<std::vector<int> > face_index_lists;
		std::vector<std::vector<int> > vertex_normal_lists;
		std::vector<std::vector<int> > uv_index_lists;
		ALLEGRO_PRIM_TYPE prim_type;
		
		bool has_uv_coordinates;
		//ALLEGRO_BITMAP *texture;

		Object(Model *parent);

		void clear();
		//void set_texture(ALLEGRO_BITMAP *t);
		void draw(ALLEGRO_BITMAP *texture=NULL, ALLEGRO_COLOR col=color::null_color); // recently changed from white to null_color
		void draw_triangles_and_normals();
		int get_num_faces();
		vec3d get_centroid();
		vec3d get_face_centroid(int face_index_num); // coming up next! :D
		vec3d get_face_normal(int face_index_num); // coming up next! :D
		std::vector<vec3d> get_face_points(int face_index_num); // riyaghht naouwww! :E
	};

	std::vector<ALLEGRO_VERTEX> vertexes;
	std::vector<vec3d> normals;
	std::vector<vec2d> uvs;
	std::vector<Object> objects; // <- also known as "groups"
	TextureSet textures;

	Model();

	bool load_obj_file(std::string filename, ALLEGRO_COLOR color=color::white); // only supporting .obj files
	bool remove_object(int index);
	int get_num_objects();

	//void set_texture(ALLEGRO_BITMAP *t, int obj_num=-1);
	void set_color(ALLEGRO_COLOR col);
	void draw(TextureSet *textures=NULL, ColorSet *colors_from_instance=NULL);
	void draw_triangles_and_normals();
	void clear();

	void set_texture_by_name(std::string name, ALLEGRO_BITMAP *texture);
	void set_color_by_name(std::string name, ALLEGRO_COLOR color);
	Model::Object *get_object_by_name(std::string name);

	// transformations

	void move(float x, float y, float z);
	void move_to(float x, float y, float z);
	void scale(float x, float y, float z);

	vec3d get_min_vertex_coordinate();
	vec3d get_max_vertex_coordinate();

	//AABB3D Model::get_bbox();
};







#endif