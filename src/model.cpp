


#include <allegro_flare/model.h>

#include <iostream>
#include <cstdio>

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>

#include <allegro_flare/vec3d.h>



ModelNew::ModelNew()
	: vertex_declaration(NULL)
	, vertexes()
	, texture(NULL)
{
	ALLEGRO_VERTEX_ELEMENT elems[] = {
		{ALLEGRO_PRIM_POSITION, ALLEGRO_PRIM_FLOAT_3, offsetof(ALLEGRO_VERTEX_WITH_NORMAL, x)},
		{ALLEGRO_PRIM_TEX_COORD, ALLEGRO_PRIM_FLOAT_2, offsetof(ALLEGRO_VERTEX_WITH_NORMAL, u)},
		{ALLEGRO_PRIM_COLOR_ATTR, 0, offsetof(ALLEGRO_VERTEX_WITH_NORMAL, color)},
		{ALLEGRO_PRIM_USER_ATTR, ALLEGRO_PRIM_FLOAT_3, offsetof(ALLEGRO_VERTEX_WITH_NORMAL, nx)},
		{0, 0, 0}
	};

	vertex_declaration = al_create_vertex_decl(elems, sizeof(ALLEGRO_VERTEX_WITH_NORMAL));
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
	std::vector<ALLEGRO_VERTEX_WITH_NORMAL> vtxs;
	std::vector<vt_coord> vt_coords;
	std::vector<vec3d> vt_normals;
	ALLEGRO_VERTEX_WITH_NORMAL vtx;
	vt_coord vt_c;
	vec3d vt_normal;
	bool vertex_textures_found = false;
	bool vertex_normals_found = false;

	if (!al_filename_exists(filename)) std::cout << "cannot load file " << filename << std::endl;

	while (al_fgets(file, buff, 256))
	{
		vtx.x = vtx.y = vtx.z = 0;
		vtx.color = white;
		vtx.u = vtx.v = 0;
		vtx.nx = vtx.nz = 0;
		vtx.ny = 1;

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
			vtx.u = (vertex_textures_found ? vt_coords[face_vt1-1].u : 0);
			vtx.v = (vertex_textures_found ? vt_coords[face_vt1-1].v : 0);
			vtx.nx = vt_normals[face_vn1-1].x;
			vtx.ny = vt_normals[face_vn1-1].y;
			vtx.nz = vt_normals[face_vn1-1].z;
			vertexes.push_back(vtx);

			vtx.x = vtxs[face_v2-1].x * scale;
			vtx.y = vtxs[face_v2-1].y * scale;
			vtx.z = vtxs[face_v2-1].z * scale;
			vtx.u = (vertex_textures_found ? vt_coords[face_vt2-1].u : 0);
			vtx.v = (vertex_textures_found ? vt_coords[face_vt2-1].v : 0);
			vtx.nx = vt_normals[face_vn2-1].x;
			vtx.ny = vt_normals[face_vn2-1].y;
			vtx.nz = vt_normals[face_vn2-1].z;
			vertexes.push_back(vtx);

			vtx.x = vtxs[face_v3-1].x * scale;
			vtx.y = vtxs[face_v3-1].y * scale;
			vtx.z = vtxs[face_v3-1].z * scale;
			vtx.u = (vertex_textures_found ? vt_coords[face_vt3-1].u : 0);
			vtx.v = (vertex_textures_found ? vt_coords[face_vt3-1].v : 0);
			vtx.nx = vt_normals[face_vn3-1].x;
			vtx.ny = vt_normals[face_vn3-1].y;
			vtx.nz = vt_normals[face_vn3-1].z;
			vertexes.push_back(vtx);

			if (num_vertexes_captured == 4)
			{
				vtx.x = vtxs[face_v3-1].x * scale;
				vtx.y = vtxs[face_v3-1].y * scale;
				vtx.z = vtxs[face_v3-1].z * scale;
				vtx.u = (vertex_textures_found ? vt_coords[face_vt3-1].u : 0);
				vtx.v = (vertex_textures_found ? vt_coords[face_vt3-1].v : 0);
				vtx.nx = vt_normals[face_vn3-1].x;
				vtx.ny = vt_normals[face_vn3-1].y;
				vtx.nz = vt_normals[face_vn3-1].z;
				vertexes.push_back(vtx);

				vtx.x = vtxs[face_v4-1].x * scale;
				vtx.y = vtxs[face_v4-1].y * scale;
				vtx.z = vtxs[face_v4-1].z * scale;
				vtx.u = (vertex_textures_found ? vt_coords[face_vt4-1].u : 0);
				vtx.v = (vertex_textures_found ? vt_coords[face_vt4-1].v : 0);
				vtx.nx = vt_normals[face_vn4-1].x;
				vtx.ny = vt_normals[face_vn4-1].y;
				vtx.nz = vt_normals[face_vn4-1].z;
				vertexes.push_back(vtx);

				vtx.x = vtxs[face_v1-1].x * scale;
				vtx.y = vtxs[face_v1-1].y * scale;
				vtx.z = vtxs[face_v1-1].z * scale;
				vtx.u = (vertex_textures_found ? vt_coords[face_vt1-1].u : 0);
				vtx.v = (vertex_textures_found ? vt_coords[face_vt1-1].v : 0);
				vtx.nx = vt_normals[face_vn1-1].x;
				vtx.ny = vt_normals[face_vn1-1].y;
				vtx.nz = vt_normals[face_vn1-1].z;
				vertexes.push_back(vtx);

			}
		}
	}

	al_fclose(file);
	return true;
}



void ModelNew::inspect()
{
	for (unsigned i=0; i<vertexes.size(); i++)
		printf("[%d] %f %f %f : %f %f : %f %f %f\n", i, vertexes[i].x, vertexes[i].y, vertexes[i].z, vertexes[i].u, vertexes[i].v, vertexes[i].nx, vertexes[i].ny, vertexes[i].nz);
}



int ModelNew::get_num_vertexes()
{
	return vertexes.size();
}



void ModelNew::draw()
{
	if (vertexes.empty()) return;

	al_draw_prim(&vertexes[0], vertex_declaration, texture, 0, vertexes.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
}




