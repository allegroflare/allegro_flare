




#include <allegro_flare/placement3d.h>
#include <allegro_flare/useful.h> // just for #define TAU




placement3d::placement3d()
	: position(0, 0, 0)
	, size(0, 0, 0)
	, align(0.5, 0.5, 0.5)
	, scale(1.0, 1.0, 1.0)
	, anchor(0, 0, 0)
	, rotation(0, 0, 0)
{}



placement3d::placement3d(float x, float y, float z)
	: position(x, y, z)
	, size(0, 0, 0)
	, align(0.5, 0.5, 0.5)
	, scale(1.0, 1.0, 1.0)
	, anchor(0, 0, 0)
	, rotation(0, 0, 0)
{}



placement3d::placement3d(vec3d position)
	: position(position.x, position.y, position.z)
	, size(0, 0, 0)
	, align(0.5, 0.5, 0.5)
	, scale(1.0, 1.0, 1.0)
	, anchor(0, 0, 0)
	, rotation(0, 0, 0)
{}



void placement3d::start_transform()
{
	ALLEGRO_TRANSFORM transform;
	al_copy_transform(&previous_transform, al_get_current_transform());
	
	this->build_transform(&transform);

	al_compose_transform(&transform, &previous_transform);
	al_use_transform(&transform);
}



void placement3d::restore_transform()
{
	al_use_transform(&previous_transform);
}



void placement3d::build_transform(ALLEGRO_TRANSFORM *transform)
{
	al_identity_transform(transform);

	// offset for alignment and anchors
	al_translate_transform_3d(transform, -align.x*size.x, -align.y*size.y, -align.z*size.z);
	al_scale_transform_3d(transform, scale.x, scale.y, scale.z);
	al_translate_transform_3d(transform, anchor.x, anchor.y, anchor.z);

	// rotate
	al_rotate_transform_3d(transform, 0, 1, 0, rotation.y * TAU); // <-- uuhh... not sure how this should work
	al_rotate_transform_3d(transform, 1, 0, 0, rotation.x * TAU); // <-- uuhh... not sure how this should work
	al_rotate_transform_3d(transform, 0, 0, 1, rotation.z * TAU); // <-- uuhh... not sure how this should work

	// translate
	al_translate_transform_3d(transform, position.x, position.y, position.z);
}



void placement3d::build_reverse_transform(ALLEGRO_TRANSFORM *transform)
{
   al_identity_transform(transform);

   // translate
   al_translate_transform_3d(transform, -position.x, -position.y, -position.z);

   // rotate
   al_rotate_transform_3d(transform, 0, 0, -1, rotation.z * TAU);
   al_rotate_transform_3d(transform, -1, 0, 0, rotation.x * TAU);
   al_rotate_transform_3d(transform, 0, -1, 0, rotation.y * TAU);

   // offset for alignment and anchors
   al_translate_transform_3d(transform, -anchor.x, -anchor.y, -anchor.z);
   al_scale_transform_3d(transform, 1.0/scale.x, 1.0/scale.y, 1.0/scale.z);
   al_translate_transform_3d(transform, align.x*size.x, align.y*size.y, align.z*size.z);
}



placement3d& placement3d::operator+=(const placement3d& other)
{
   position += other.position;
   size += other.size;
   align += other.align;
   scale += other.scale;
   anchor += other.anchor;
   rotation += other.rotation;
   return *this;
}



