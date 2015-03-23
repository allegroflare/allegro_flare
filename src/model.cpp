





#include <allegro_flare/model.h>

//#include "map.h"








TextureSet::TextureSet()
{
}

#include <iostream>


bool TextureSet::set_texture_by_index(int model_object_index, ALLEGRO_BITMAP *bmp)
{
	for (unsigned i=0; i<textures.size(); i++)
		if (textures[i].first == model_object_index)
		{
			textures[i].second = bmp;
			return true;
		}

	textures.push_back(std::pair<int, ALLEGRO_BITMAP *>(model_object_index, bmp));
	return true;
}



ALLEGRO_BITMAP *TextureSet::get_texture(int model_object_index)
{
	for (unsigned i=0; i<textures.size(); i++)
		if (textures[i].first == model_object_index) return textures[i].second;
	return NULL;
}



bool TextureSet::has_texture(int model_object_index)
{
	for (unsigned i=0; i<textures.size(); i++)
		if (textures[i].first == model_object_index) return true;
	return false;
}









ColorSet::ColorSet()
{
}



bool ColorSet::set_color(int model_object_index, ALLEGRO_COLOR col)
{
	for (unsigned i=0; i<textures.size(); i++)
		if (textures[i].first == model_object_index)
		{
			textures[i].second = col;
			return true;
		}

	textures.push_back(std::pair<int, ALLEGRO_COLOR>(model_object_index, col));
	return true;
}



ALLEGRO_COLOR ColorSet::get_color(int model_object_index)
{
	for (unsigned i=0; i<textures.size(); i++)
		if (textures[i].first == model_object_index) return textures[i].second;
	return color::white;
}



bool ColorSet::has_color(int model_object_index)
{
	for (unsigned i=0; i<textures.size(); i++)
		if (textures[i].first == model_object_index) return true;
	return false;
}











Model::Object::Object(Model *parent)
	: prim_type()
	, parent(parent)
	//, textures()
//	, has_uv_coordinates(false)
{
	prim_type = ALLEGRO_PRIM_TRIANGLE_FAN;
}



#include <iostream>
#include <allegro_flare/useful.h>

void Model::Object::draw(ALLEGRO_BITMAP *texture, ALLEGRO_COLOR col)
{
	//ALLEGRO_BITMAP *texture = NULL;
	if (!parent) return;

	bool override_color = true;
	if (color::basically_equal(col, color::null_color)) override_color = false;

	// this is kinda messy, could be cleaned up a little bit. :)

	if (!face_index_lists.empty() && !parent->vertexes.empty())
	{
		for (unsigned i=0; i<face_index_lists.size(); i++)
		{
			//texture = textures.get_texture(i);

			if (has_uv_coordinates && texture && !uv_index_lists.empty())
			{
				// reset the uv coordinates
				for (unsigned j=0; j<face_index_lists[i].size(); j++)
				{
					ALLEGRO_VERTEX *this_vertex = &parent->vertexes[face_index_lists[i][j]];
					this_vertex->u = parent->uvs[uv_index_lists[i][j]].x * al_get_bitmap_width(texture);
					this_vertex->v = -parent->uvs[uv_index_lists[i][j]].y * al_get_bitmap_height(texture);
					//if (override_color) this_vertex->color = col;
				}
			}

			// draw_textured
			// NEED TO CORRECT THIS, so it doesn't need to use the ? texture:NULL stuff.
			al_draw_indexed_prim(&parent->vertexes[0], NULL, has_uv_coordinates ? texture : NULL, &face_index_lists[i][0], face_index_lists[i].size(), prim_type);

			// draw lines
			//al_draw_indexed_prim(&parent->vertexes[0], NULL, NULL, &face_index_lists[i][0], face_index_lists[i].size(), ::ALLEGRO_PRIM_TRIANGLE_LIST);

			// draw colored prim
			//al_draw_indexed_prim(&parent->vertexes[0], NULL, NULL, &face_index_lists[i][0], face_index_lists[i].size(), ALLEGRO_PRIM_LINE_LOOP);
		}
	}

  //std::cout << "<9>";


	//place.restore_transform();
}





static void draw_3d_line(vec3d start, vec3d end, ALLEGRO_COLOR col=color::red)
{
	ALLEGRO_VERTEX vtx[2];
	vtx[0] = build_vertex(start.x, start.y, start.z, col, 0, 0);
	vtx[1] = build_vertex(end.x, end.y, end.z, col, 0, 0);
	al_draw_prim(&vtx[0], NULL, NULL, 0, 2, ALLEGRO_PRIM_LINE_LIST);
}




static vec3d centroid(vec3d v1, vec3d v2, vec3d v3)
{
	return (v1 + v2 + v3) / 3;
}

static vec3d tovec3d(ALLEGRO_VERTEX v1)
{
	return vec3d(v1.x, v1.y, v1.z); 
}

static vec3d centroid(vec3d v1, vec3d v2, vec3d v3, vec3d v4)
{
	return (v1 + v2 + v3 + v4) / 4;
}



void Model::Object::draw_triangles_and_normals()
{
	// draw outlined shape
	for (unsigned i=0; i<face_index_lists.size(); i++)
		al_draw_indexed_prim(&parent->vertexes[0], NULL, NULL, &face_index_lists[i][0], face_index_lists[i].size(), ALLEGRO_PRIM_LINE_LOOP);

	// draw vertex normals
	//for (unsigned i=0; i<this->vertex_normal_lists.size(); i++)
	for (unsigned f=0; f<face_index_lists.size(); f++)
	{
		if (face_index_lists[f].empty()) continue;

		//ALLEGRO_VERTEX *first_vertex = &parent->vertexes[face_index_lists[f][0]];
		vec3d normal_of_the_first_virtex = parent->normals[vertex_normal_lists[f][0]];
		
		// WARNING!!! THIS WILL ONLY WORK WITH TRIANGULATED OBJECTS
		vec3d centroid_of_the_face = centroid(
			tovec3d(parent->vertexes[face_index_lists[f][0]]),
			tovec3d(parent->vertexes[face_index_lists[f][1]]),
			tovec3d(parent->vertexes[face_index_lists[f][2]])
		);

		draw_crosshair(centroid_of_the_face, color::dodgerblue, 0.5);
		//vec3d this_vertex_normal = parent->normals[vertex_normal_lists[f][vn]];
		draw_3d_line(centroid_of_the_face, centroid_of_the_face + normal_of_the_first_virtex * 2);
		continue;

		for (unsigned vn=0; vn<face_index_lists[f].size(); vn++)
		{
			// draw the vertex
			ALLEGRO_VERTEX *allegro_vtx = &parent->vertexes[face_index_lists[f][vn]];
			vec3d this_vertex_coord = vec3d(allegro_vtx->x, allegro_vtx->y, allegro_vtx->z);
			//draw_crosshair(this_vertex_coord, color::red, 2.0);
			
			// draw the normal
			// WARNING WARNING WARNING!
			// This will probably cause a crash if the # of vertex_normal_lists is not expaned at the same rate
			// I actually think this is ok... *but*... it won't be any good if normals are not included in
			// the model data.  If that's the case, then the normals will be (0,0,0) and this might not work.
			if (vertex_normal_lists[f][vn] < 0) continue;
			vec3d this_vertex_normal = parent->normals[vertex_normal_lists[f][vn]];

			draw_3d_line(this_vertex_coord, this_vertex_coord + this_vertex_normal * 8);

			//vec2d this_vertex_uv = vec2d();
		}
	}

	//al_draw_indexed_prim(&parent->vertexes[0], NULL, NULL, &face_index_lists[i][0], face_index_lists[i].size(), ALLEGRO_PRIM_LINE_LOOP);
}


/*
void Model::set_texture(ALLEGRO_BITMAP *t, int object_num)
{
	if (objects.empty()) return;
	if (object_num >= (int)objects.size()) return;

	if (object_num < 0) // then just texture all of them
	{
		for (unsigned i=0; i<objects.size(); i++)
			objects[0].set_texture(t);
		return;
	}

	objects[object_num].set_texture(t);
}
*/


void Model::set_color(ALLEGRO_COLOR col)
{
	if (vertexes.empty()) return;

	for (unsigned i=0; i<vertexes.size(); i++)
		vertexes[i].color = col;
}


void Model::Object::clear()
{
	//face.clear();
	//
	face_index_lists.clear();
	//uvs.clear();
	uv_index_lists.clear();
}


int Model::get_num_objects()
{
	return objects.size();
}








#include <fstream>
#include <iostream>
#include <allegro_flare/useful.h>




Model::Model()
	//: bbox(NULL)
{}



void Model::clear()
{
	objects.clear();
	vertexes.clear();
	uvs.clear();
	normals.clear();
}



void Model::draw(TextureSet *textures_from_instance, ColorSet *colors_from_instance)
{
	for (unsigned o=0; o<objects.size(); o++)
	{
		// get the texture for this object
		ALLEGRO_BITMAP *texture = NULL;
		if (textures_from_instance && textures_from_instance->has_texture(o)) texture = textures_from_instance->get_texture(o);
		else if (textures.has_texture(o)) texture = textures.get_texture(o);
		
		objects[o].draw(
			texture,
			(colors_from_instance && colors_from_instance->has_color(o)) ? colors_from_instance->get_color(o) : color::white
			);
	}
}



void Model::draw_triangles_and_normals()
{
	for (unsigned o=0; o<objects.size(); o++)
		objects[o].draw_triangles_and_normals();
}



bool Model::remove_object(int index)
{
	if (index < 0) return false;
	if (index >= (int)objects.size()) return false;

	objects.erase(objects.begin() + index);
	return true;
}



vec3d Model::get_min_vertex_coordinate()
{
	if (vertexes.empty()) return vec3d(0, 0, 0);

	ALLEGRO_VERTEX *this_vertex = &vertexes[0];

	vec3d min_position(this_vertex->x, this_vertex->y, this_vertex->z);

	for (unsigned v=0; v<vertexes.size(); v++)
	{
		this_vertex = &vertexes[v];

		if (this_vertex->x < min_position.x) min_position.x = this_vertex->x;
		if (this_vertex->y < min_position.y) min_position.y = this_vertex->y;
		if (this_vertex->z < min_position.z) min_position.z = this_vertex->z;
	}

	return min_position;
}



vec3d Model::get_max_vertex_coordinate()
{
	if (vertexes.empty()) return vec3d(0, 0, 0);

	ALLEGRO_VERTEX *this_vertex = &vertexes[0];

	vec3d max_position(this_vertex->x, this_vertex->y, this_vertex->z);
	//vec3d min_position(this_vertex->x, this_vertex->y, this_vertex->z);

	for (unsigned v=0; v<vertexes.size(); v++)
	{
		this_vertex = &vertexes[v];

		if (this_vertex->x > max_position.x) max_position.x = this_vertex->x;
		if (this_vertex->y > max_position.y) max_position.y = this_vertex->y;
		if (this_vertex->z > max_position.z) max_position.z = this_vertex->z;
	}

	return max_position;
}


/*
vec3dAABB3D Model::get_bbox()
{
	//AABB3D bbox("");
	if (vertexes.empty()) return bbox;


	ALLEGRO_VERTEX *this_vertex = &vertexes[0];

	float max_x = this_vertex->x, min_x = this_vertex->x;
	float max_y = this_vertex->y, min_y = this_vertex->y;
	float max_z = this_vertex->z, min_z = this_vertex->z;


	for (unsigned v=0; v<vertexes.size(); v++)
	{
		this_vertex = &vertexes[v];

		if (this_vertex->x < min_x) min_x = this_vertex->x;
		if (this_vertex->x > max_x) max_x = this_vertex->x;

		if (this_vertex->y < min_y) min_y = this_vertex->y;
		if (this_vertex->y > max_y) max_y = this_vertex->y;

		if (this_vertex->z < min_z) min_z = this_vertex->z;
		if (this_vertex->z > max_z) max_z = this_vertex->z;
	}

	bbox.max.x = max_x;
	bbox.max.y = max_y;
	bbox.max.z = max_z;

	bbox.min.x = min_x;
	bbox.min.y = min_y;
	bbox.min.z = min_z;

	// centroid
	//return vec3d(min_x+(max_x-min_x)/2,
	//			min_y+(max_y-min_y)/2,
	//			min_z+(max_z-min_z)/2);

	//bbox.position = vec3d(min_x+(max_x-min_x)/2,
	//				min_y+(max_y-min_y)/2,
	//				min_z+(max_z-min_z)/2);

	//bbox.hsize = vec3d((max_x-min_x)/2, (max_y-min_y)/2, (max_z-min_z)/2);

	return bbox;
}
*/



//TODO
// this one's a doosey, but very useful and should be bullet-proof.

#include <allegro_flare/useful_php.h>

bool Model::load_obj_file(std::string filename, ALLEGRO_COLOR color)
{
	clear();

	bool verbose = false;

  if (verbose) std::cout << "Loading Model..." << std::endl; // filename << "\"" << std::endl;


  std::ifstream in(filename, std::ios::in);
  if (!in)
  {
	  std::cerr << "[" << __FUNCTION__ << "] Cannot open " << filename << std::endl;
	  return false;
	  //exit(1);
  }

  //prim_type = ALLEGRO_PRIM_TYPE::ALLEGRO_PRIM_TRIANGLE_LIST;
  //prim_type = ALLEGRO_PRIM_TYPE::ALLEGRO_PRIM_TRIANGLE_STRIP;
	//ALLEGRO_PRIM_TRIANGLE_FAN;

  //vec3d vec;
  //Face *current_face = face;

  //std::vector<ALLEGRO_VERTEX> *current_face = NULL;
  //std::vector<ALLEGRO_VERTEX> dummy_face;

  //std::cout << "1";

  std::string line;
  float x, y, z;
  std::vector<int> dummy_face_index;
  int line_count = 0;
  //Object dummy_model_object;
  while (getline(in, line))
  {
	  //std::cout << line << std::endl;
	 // line.substr(0,2);

	  line_count++;

	  if (verbose) if (line_count%10000 == 0) std::cout << "..." << line_count;

	 // std::cout << ".";

	if (line.empty())
	{
		/* ignore (and skip) empty lines */
	}
    else if (line.substr(0,2) == "g " || line.substr(0,2) == "o ") // a group statement (TODO: currently, the model loader does not support groups very properly)
	{
		Object *obj = get_object_by_name(line.substr(2));
		// check if named group exists
		// if it doesn't create it and set it to the current active group

		if (!obj)
		{
			objects.push_back(Object(this));
			objects.back().prim_type = ALLEGRO_PRIM_TRIANGLE_FAN;
			objects.back().name = line.substr(2);
		}
	}
    else if (line.substr(0,2) == "v ")
	{
 // std::cout << "3";
      std::istringstream s(line.substr(2));
	  s >> x; s >> y; s >> z;
	  vertexes.push_back(build_vertex(x, y, z, color::white, 0, 0));
 // std::cout << "<3>";
    }
    else if (line.substr(0,3) == "vt ")
	{
		//if (objects.empty())
		//{  
		//	std::cout << "  ![1] Object not explicitly declared (auto-creating)" << std::endl;
		//	objects.push_back(Object(this));
		//}

  // std::cout << "4";
		//objects.back().uses_texture = true;
		//objects.back().has_uv_coordinates = true;
     std::istringstream s(line.substr(3));
	  s >> x; s >> y;
	  uvs.push_back(vec2d(x, y));
//  std::cout << "<4>";
    }
    else if (line.substr(0,3) == "vn ")
	{
  // std::cout << "5";
		//objects.back().uses_texture = true;
      std::istringstream s(line.substr(2));
	  s >> x; s >> y; s >> z;
	  normals.push_back(vec3d(x, y, z));
//  std::cout << "<4>";
    }
	else if (line.substr(0,2) == "f ")
	{
		if (objects.empty()) // this statement and its contents was recenty revised, though it may cause some problems with backward compatib
		{  
			if (verbose) std::cout << "  ! Object not explicitly declared (auto-creating)" << std::endl;
			objects.push_back(Object(this));
			objects.back().prim_type = ALLEGRO_PRIM_TRIANGLE_FAN;
			objects.back().name = "[INTERNALLY_CREATED_UNNAMED_INITIAL_GROUP]";
		}

 //  std::cout << "6";
     std::istringstream s(line.substr(2));

	  objects.back().face_index_lists.push_back(dummy_face_index);
	  objects.back().uv_index_lists.push_back(dummy_face_index);
	  objects.back().vertex_normal_lists.push_back(dummy_face_index);
	  //objects.back().has_uv_coordinates = true; // just putting this here, should be calculated and placed in a more appropriate place

	  std::vector<std::string> tokens = php::explode(" ", line.substr(2));
	  for (unsigned i=0; i<tokens.size(); i++)
	  {
		  std::vector<std::string> face_parts = php::explode("/", tokens[i]);

		  // get the face vertex
		  //if (face_parts.size() >= 1)
		  {
			  int val_to_enter = -1;
			  if ((face_parts.size() >= 1) && !face_parts[0].empty()) val_to_enter = atoi(face_parts[0].c_str()) - 1;
			  objects.back().face_index_lists.back().push_back(val_to_enter);
		  }

		  // get the uv vertex
		  //if (face_parts.size() >= 2)
		  {
			  int val_to_enter = -1;
			  if ((face_parts.size() >= 2) && !face_parts[1].empty())
			  {
				  val_to_enter = atoi(face_parts[1].c_str()) - 1;
				  objects.back().has_uv_coordinates = true;
			  }
			  objects.back().uv_index_lists.back().push_back(val_to_enter);
		  }

		  // get the normal for this face
		  //if (face_parts.size() >= 3)
		  {
			  int val_to_enter = -1;
			  if ((face_parts.size() >= 3) && !face_parts[2].empty()) val_to_enter = atoi(face_parts[2].c_str()) - 1;
			  objects.back().vertex_normal_lists.back().push_back(val_to_enter);
		  }
	  }
    }
    else if (line[0] == '#') { /* ignoring this line */ }
    else { /* ignoring this line */ }
//  std::cout << "<5>";
  }

  if (verbose)
  {
	  std::cout << "  Loaded Successfully" << std::endl;
	  std::cout << "    objects.size(): " << objects.size() << std::endl;
	  std::cout << "    uvs.size(): " << uvs.size() << std::endl;
	  std::cout << "    vertexes.size(): " << vertexes.size() << std::endl;
	  for (unsigned i=0; i<objects.size(); i++)
	  {
		  std::cout << "    + object " << i << " (" << objects[i].name << ")" << std::endl;
		  std::cout << "      face_index_lists.size(): " << objects[i].face_index_lists.size() << std::endl;
		  std::cout << "      uv_index_lists.size(): " << objects[i].uv_index_lists.size() << std::endl;
	  }
  }

  return true;
}



vec3d Model::Object::get_centroid()
{
	if (!parent) return 0;

	//if (!face_index_lists.empty() && !parent->vertexes.empty())

	if (!face_index_lists.empty() && !parent->vertexes.empty())
	{
		ALLEGRO_VERTEX *this_vertex = &parent->vertexes[face_index_lists[0][0]];

		float max_x = this_vertex->x, min_x = this_vertex->x;
		float max_y = this_vertex->y, min_y = this_vertex->y;
		float max_z = this_vertex->z, min_z = this_vertex->z;

		for (unsigned i=0; i<face_index_lists.size(); i++)
			for (unsigned j=0; j<face_index_lists[i].size(); j++)
			{
				this_vertex = &parent->vertexes[face_index_lists[i][j]];

				if (this_vertex->x < min_x) min_x = this_vertex->x;
				if (this_vertex->x > max_x) max_x = this_vertex->x;

				if (this_vertex->y < min_y) min_y = this_vertex->y;
				if (this_vertex->y > max_y) max_y = this_vertex->y;

				if (this_vertex->z < min_z) min_z = this_vertex->z;
				if (this_vertex->z > max_z) max_z = this_vertex->z;
			}

		return vec3d(min_x+(max_x-min_x)/2,
					min_y+(max_y-min_y)/2,
					min_z+(max_z-min_z)/2);
	}

	return 0;
}


int Model::Object::get_num_faces()
{
	return this->face_index_lists.size();
}


vec3d Model::Object::get_face_centroid(int face_index_num)
{
	if (face_index_num < 0 || face_index_num >= (int)this->face_index_lists.size()) return 0;

	// WARNING!! ASSUMES THERE ARE ONLY 3 VERTEXES IN A FACE
	// there could be more (or less?)

	return centroid(
		tovec3d(parent->vertexes[face_index_lists[face_index_num][0]]),
		tovec3d(parent->vertexes[face_index_lists[face_index_num][1]]),
		tovec3d(parent->vertexes[face_index_lists[face_index_num][2]])
	);
}



vec3d Model::Object::get_face_normal(int face_index_num)
{
	// WAS THIS: if (!parent || face_index_num < 0 || face_index_num >= (int)this->face_index_lists.size()) return 0;
	if (!parent || face_index_num < 0 || face_index_num >= (int)this->vertex_normal_lists.size()) return 0;
	
	// note! this should do some extra bounds checking:
	return parent->normals[vertex_normal_lists[face_index_num][0]];
}



std::vector<vec3d> Model::Object::get_face_points(int face_index_num)
{
	std::vector<vec3d> result;
	if (!parent || face_index_num < 0 || face_index_num >= (int)this->face_index_lists.size()) return result;

	// note! this should do some extra bounds checking:
	result.resize(face_index_lists[face_index_num].size());
	for (unsigned v=0; v<this->face_index_lists[face_index_num].size(); v++)
	{
		int current_vertex_num = face_index_lists[face_index_num][v];
		result[v].x = parent->vertexes[current_vertex_num].x;
		result[v].y = parent->vertexes[current_vertex_num].y;
		result[v].z = parent->vertexes[current_vertex_num].z;
	};
	return result;
}



void Model::scale(float x, float y, float z)
{
	for (unsigned i=0; i<vertexes.size(); i++)
	{
		vertexes[i].x *= x;
		vertexes[i].y *= y;
		vertexes[i].z *= z;
	}
}



void Model::move(float x, float y, float z)
{
	for (unsigned i=0; i<vertexes.size(); i++)
	{
		vertexes[i].x += x;
		vertexes[i].y += y;
		vertexes[i].z += z;
	}
}



void Model::move_to(float x, float y, float z)
{
	if (vertexes.empty()) return;

	float fx = -vertexes[0].x + x;
	float fy = -vertexes[0].y + y;
	float fz = -vertexes[0].z + z;

	for (unsigned i=0; i<vertexes.size(); i++)
	{
		vertexes[i].x += fx;
		vertexes[i].y += fy;
		vertexes[i].z += fz;
	}
}



Model::Object *Model::get_object_by_name(std::string name)
{
	// sigh... it's linear... maybe fix it later
	for (unsigned i=0; i<objects.size(); i++)
		if (objects[i].name == name) return &objects[i];

	return NULL;
}



void Model::set_texture_by_name(std::string name, ALLEGRO_BITMAP *texture)
{
	bool object_found = false;
	for (unsigned i=0; i<objects.size(); i++)
	{
		if (objects[i].name == name)
		{
			textures.set_texture_by_index(i, texture);
		}
	}

	if (!object_found)
	{
		std::cout << __FUNCTION__ << ": could not find object named \"" << name << "\"" << std::endl;
	}
}



void Model::set_color_by_name(std::string name, ALLEGRO_COLOR color)
{
	Model::Object *model_object = get_object_by_name(name);
	if (!model_object) return;
//	model_object->
}





