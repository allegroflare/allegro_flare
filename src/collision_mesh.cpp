


#include <allegro_flare/collision_mesh.h>


#include <iostream>




CollisionMesh::Face::Face(ALLEGRO_VERTEX av0, ALLEGRO_VERTEX av1, ALLEGRO_VERTEX av2,
	int parent_models_object_num, int parent_models_face_num,
	vec3d normal
	)
	: av0(av0)
	, av1(av1)
	, av2(av2)
	, v0(vec3d(av0.x, av0.y, av0.z))
	, v1(vec3d(av1.x, av1.y, av1.z))
	, v2(vec3d(av2.x, av2.y, av2.z))
	, normal(normal)
	, centroid((v0+v1+v2)/3)
	, parent_models_object_num(parent_models_object_num)
	, parent_models_face_num(parent_models_face_num)
{
	// make a normal, if it is not provided << YOU WERE HERE!!
}




bool CollisionMesh::Face::intersect(const Ray &r, IsectData &isectData) const
{
	//http://www.scratchapixel.com/lessons/3d-basic-lessons/lesson-9-ray-triangle-intersection/m-ller-trumbore-algorithm/
	//#ifdef MOLLER_TRUMBORE
	vec3d edge1 = v1 - v0;
	vec3d edge2 = v2 - v0;
	vec3d pvec = cross_product(r.dir, edge2);
	float det = dot_product(edge1, pvec);
	if (det == 0) return false;
	float invDet = 1 / det;
	vec3d tvec = r.orig - v0;
	isectData.u = dot_product(tvec, pvec) * invDet;
	if (isectData.u < 0 || isectData.u > 1) return false;
	vec3d qvec = cross_product(tvec, edge1);
	isectData.v = dot_product(r.dir, qvec) * invDet;
	if (isectData.v < 0 || isectData.u + isectData.v > 1) return false;
	isectData.t = dot_product(edge2, qvec) * invDet;
//#else
//    ...
//#endif
	return true;
}



static ALLEGRO_VERTEX _create_vtx(vec3d vec, ALLEGRO_COLOR col)
{
	return build_vertex(vec.x, vec.y, vec.z, col, 0, 0);
}

void CollisionMesh::Face::draw(ALLEGRO_COLOR col)
{
	ALLEGRO_VERTEX vtx[3];
	vtx[0] = _create_vtx(v0, col);
	vtx[1] = _create_vtx(v1, col);
	vtx[2] = _create_vtx(v2, col);
	al_draw_prim(vtx, NULL, NULL, 0, 3, ALLEGRO_PRIM_TRIANGLE_FAN);
}



CollisionMesh::CollisionMesh(Model *m)
	: faces()
	, model(m)
{
	std::cout << "+CollisionMesh()" << std::endl;
	if (!m) { std::cout << "  !*model is NULL" << std::endl; return; }
	for (unsigned o=0; o<m->objects.size(); o++)
	{
		for (unsigned f=0; f<m->objects[o].face_index_lists.size(); f++)
		{
			if (m->objects[o].face_index_lists[f].size() != 3)
			{
				std::cout << "  !object " << o << " face " << f << " has " << m->objects[o].face_index_lists.size() << " vertexes." << std::endl;
				continue;
			}

			m->objects[o].face_index_lists.size();
			faces.push_back(Face(
				m->vertexes[m->objects[o].face_index_lists[f][0]],
				m->vertexes[m->objects[o].face_index_lists[f][1]],
				m->vertexes[m->objects[o].face_index_lists[f][2]],
				o,
				f,
				m->objects[o].get_face_normal(f)
				));
		}
	}
}
