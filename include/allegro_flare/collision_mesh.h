#ifndef __AF_COLLISION_MESH_HEADER
#define __AF_COLLISION_MESH_HEADER




#include <vector>

#include <allegro5/allegro_primitives.h>

#include <allegro_flare/vec3d.h>

#include <allegro_flare/model.h>
#include <allegro_flare/useful3d.h>



class CollisionMesh
{
// CollisionMesh
// is essentially a Model, where
// all the faces have been cached
// into one long std::vector of Face objects.
public:
	class Face
		// - is triangulated
		// meaning, when exporting models
		// be sure to check the "triangulate"
		// option.  Faces should only consist of
		// three vertexes otherwise there
		// will be undefined problems.
		// 
		// the Face class is essentially
		// a chashed version of the model's
		// data, that can be quickly
		// used when calculating collisions.
		// for the most part, the member
		// variables should not be modified
		// because they are all interdependent
		// they are left public for accessibility
	{
	public:
		ALLEGRO_VERTEX av0, av1, av2;
		vec3d v0, v1, v2;
		vec3d normal;
		vec3d centroid;
		
		int parent_models_object_num;
		int parent_models_face_num;

		Face(ALLEGRO_VERTEX av0, ALLEGRO_VERTEX av1, ALLEGRO_VERTEX av2,
			int parent_models_object_num, int parent_models_face_num,
			vec3d normal=vec3d(0)
			);

		bool intersect(const Ray &r, IsectData &isectData) const;

		void draw(ALLEGRO_COLOR col=color::azure);
	};


	std::vector<Face> faces;
	Model *model;

	CollisionMesh(Model *m);
};




#endif