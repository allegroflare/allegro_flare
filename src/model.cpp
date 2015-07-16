


#include <allegro_flare/model.h>

#include <iostream>
#include <cstdio>

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>

#include <allegro_flare/vec3d.h>





ModelNew::ModelNew()
	: vertexes()
	, texture(NULL)
	, texture_scale(vec2d(1.0, 1.0))
{
}



void ModelNew::set_texture(ALLEGRO_BITMAP *tx)
{
	texture = tx;
}



bool ModelNew::load_obj_file(const char *filename, float scale)
{
	vertexes.clear();

	char buff[256];
	ALLEGRO_FILE* file = al_fopen(filename, "r");
	ALLEGRO_COLOR white = al_color_name("white");
	std::vector<ALLEGRO_VERTEX> vtxs;
	std::vector<vt_coord> vt_coords;
	std::vector<vec3d> vt_normals;
	ALLEGRO_VERTEX vtx;
	vt_coord vt_c;
	vec3d vt_normal;
	vec2d vt_s = texture_scale;
	bool vertex_textures_found = false;
	bool vertex_normals_found = false;

	if (!al_filename_exists(filename)) std::cout << "cannot load file " << filename << std::endl;

	while (al_fgets(file, buff, 256))
	{
		vtx.x = vtx.y = vtx.z = 0;
		vtx.color = white;
		vtx.u = vtx.v = 0;

		int face_v1 = 0;
		int face_v2 = 0;
		int face_v3 = 0;
		int face_v4 = 0;

		int face_vt1 = 0;
		int face_vt2 = 0;
		int face_vt3 = 0;
		int face_vt4 = 0;

		int face_vn1 = 0;
		int face_vn2 = 0;
		int face_vn3 = 0;
		int face_vn4 = 0;

		if (strncmp(buff, "v ", 2) == 0)
		{
			sscanf(buff, "v %f %f %f", &vtx.x, &vtx.y, &vtx.z);
			vtxs.push_back(vtx);
		}
		else if (strncmp(buff, "vt ", 3) == 0)
		{
			vertex_textures_found = true;
			sscanf(buff, "vt %f %f", &vt_c.u, &vt_c.v);
			vt_c.u = vt_c.u;
			vt_c.v = 1 - vt_c.v;
			vt_coords.push_back(vt_c);
		}
		else if (strncmp(buff, "vn ", 3) == 0)
		{
			vertex_normals_found = true;
			sscanf(buff, "vn %f %f %f", &vt_normal.x, &vt_normal.y, &vt_normal.z);
			vt_normals.push_back(vt_normal);
		}
		else if (strncmp(buff, "f ", 2) == 0)
		{
			int num_vertexes_captured = 0;

			if (vertex_textures_found && vertex_normals_found)
			{
				num_vertexes_captured = 
					sscanf(buff, "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d", &face_v1, &face_vt1, &face_vn1, &face_v2, &face_vt2, &face_vn2, &face_v3, &face_vt3, &face_vn3, &face_v4, &face_vt4, &face_vn4);
				num_vertexes_captured /= 3;
			}
			else if (vertex_textures_found)
			{
				num_vertexes_captured = 
					sscanf(buff, "f %d/%d %d/%d %d/%d %d/%d", &face_v1, &face_vt1, &face_v2, &face_vt2, &face_v3, &face_vt3, &face_v4, &face_vt4);
				num_vertexes_captured /= 2;
			}
			else if (vertex_normals_found)
			{
				num_vertexes_captured = 
					sscanf(buff, "f %d//%d %d//%d %d//%d %d//%d", &face_v1, &face_vn1, &face_v2, &face_vn2, &face_v3, &face_vn3, &face_v4, &face_vn4);
				num_vertexes_captured /= 2;
			}
			else
			{
				num_vertexes_captured = 
					sscanf(buff, "f %d %d %d %d", &face_v1, &face_v2, &face_v3, &face_v4);
			}

			vtx.x = vtxs[face_v1-1].x * scale;
			vtx.y = vtxs[face_v1-1].y * scale;
			vtx.z = vtxs[face_v1-1].z * scale;
			vtx.u = (vertex_textures_found ? vt_coords[face_vt1-1].u * vt_s.x : 0);
			vtx.v = (vertex_textures_found ? vt_coords[face_vt1-1].v * vt_s.y : 0);
			vertexes.push_back(vtx);

			vtx.x = vtxs[face_v2-1].x * scale;
			vtx.y = vtxs[face_v2-1].y * scale;
			vtx.z = vtxs[face_v2-1].z * scale;
			vtx.u = (vertex_textures_found ? vt_coords[face_vt2-1].u * vt_s.x : 0);
			vtx.v = (vertex_textures_found ? vt_coords[face_vt2-1].v * vt_s.y : 0);
			vertexes.push_back(vtx);

			vtx.x = vtxs[face_v3-1].x * scale;
			vtx.y = vtxs[face_v3-1].y * scale;
			vtx.z = vtxs[face_v3-1].z * scale;
			vtx.u = (vertex_textures_found ? vt_coords[face_vt3-1].u * vt_s.x : 0);
			vtx.v = (vertex_textures_found ? vt_coords[face_vt3-1].v * vt_s.y : 0);
			vertexes.push_back(vtx);

			if (num_vertexes_captured == 4)
			{
				vtx.x = vtxs[face_v3-1].x * scale;
				vtx.y = vtxs[face_v3-1].y * scale;
				vtx.z = vtxs[face_v3-1].z * scale;
				vtx.u = (vertex_textures_found ? vt_coords[face_vt3-1].u * vt_s.x : 0);
				vtx.v = (vertex_textures_found ? vt_coords[face_vt3-1].v * vt_s.y : 0);
				vertexes.push_back(vtx);

				vtx.x = vtxs[face_v4-1].x * scale;
				vtx.y = vtxs[face_v4-1].y * scale;
				vtx.z = vtxs[face_v4-1].z * scale;
				vtx.u = (vertex_textures_found ? vt_coords[face_vt4-1].u * vt_s.x : 0);
				vtx.v = (vertex_textures_found ? vt_coords[face_vt4-1].v * vt_s.y : 0);
				vertexes.push_back(vtx);

				vtx.x = vtxs[face_v1-1].x * scale;
				vtx.y = vtxs[face_v1-1].y * scale;
				vtx.z = vtxs[face_v1-1].z * scale;
				vtx.u = (vertex_textures_found ? vt_coords[face_vt1-1].u * vt_s.x : 0);
				vtx.v = (vertex_textures_found ? vt_coords[face_vt1-1].v * vt_s.y : 0);
				vertexes.push_back(vtx);

			}
		}
	}

	std::cout << "loading complete... " << vertexes.size() << " vertexes assembled." << std::endl;

	al_fclose(file);
}



void ModelNew::inspect()
{
	for (unsigned i=0; i<vertexes.size(); i++)
		printf("%f %f %f : %f %f", vertexes[i].x, vertexes[i].y, vertexes[i].z, vertexes[i].u, vertexes[i].v);
}



void ModelNew::draw()
{
	//ALLEGRO_TRANSFORM t;
	//al_identity_transform(&t);
	//al_translate_transform_3d(&t, 0, 3, 0);
	//al_use_transform(&t);
	//al_draw_prim(&vertexes[0], NULL, NULL, 0, vertexes.size(), ALLEGRO_PRIM_LINE_LOOP);
	al_draw_prim(&vertexes[0], NULL, texture, 0, vertexes.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
}




