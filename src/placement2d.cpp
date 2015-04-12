

#include <allegro_flare/placement2d.h>

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include <sstream>



placement2d::placement2d()
	: position(0, 0)
	, size(0, 0)
	, align(0.5, 0.5)
	, scale(1, 1)
	, anchor(0, 0)
	, rotation(0)
{}




placement2d::placement2d(float x, float y, float w, float h)
	: position(x, y)
	, size(w, h)
	, align(0.5, 0.5)
	, scale(1, 1)
	, anchor(0, 0)
	, rotation(0)
{}




placement2d::placement2d(float x, float y, float w, float h, float rotation, float scale_x, float scale_y, float align_x, float align_y, float anchor_x, float anchor_y)
	: position(x, y)
	, size(w, h)
	, align(align_x, align_y)
	, scale(scale_x, scale_y)
	, anchor(anchor_x, anchor_y)
	, rotation(rotation)
{}




void placement2d::start_transform()
{
	ALLEGRO_TRANSFORM transform;

	al_copy_transform(&previous_transform, al_get_current_transform()); 
	al_identity_transform(&transform);

	al_translate_transform(&transform, -align.x*size.x, -align.y*size.y);
	al_scale_transform(&transform, scale.x, scale.y);
	al_translate_transform(&transform, anchor.x, anchor.y); // changing this
	al_rotate_transform(&transform, rotation);
	al_translate_transform(&transform, position.x, position.y);

	al_compose_transform(&transform, &previous_transform);

	al_use_transform(&transform);
}




void placement2d::draw_origin()
{
	float half_size = 12;
	ALLEGRO_COLOR color = al_map_rgba_f(1, 0, 0, 1);
	al_draw_line(position.x, position.y-half_size, position.x, position.y+half_size, color, 1.0);
	al_draw_line(position.x-half_size, position.y, position.x+half_size, position.y, color, 1.0);
}



void placement2d::restore_transform()
{
	al_use_transform(&previous_transform);
}



void placement2d::draw_box(ALLEGRO_COLOR color, bool draw_origin)
{
	if (draw_origin) al_draw_circle(position.x, position.y, 5, color, 3.0);
	start_transform();
	al_draw_rectangle(0, 0, size.x, size.y, color, 3.0);
	restore_transform();
}



void placement2d::draw_box_with_padding(ALLEGRO_COLOR color, bool draw_origin, float pt, float pr, float pb, float pl)
{
	if (draw_origin) al_draw_circle(position.x, position.y, 5, color, 3.0);
	start_transform();
	al_draw_rectangle(0, 0, size.x, size.y, color, 3.0);
	al_draw_rectangle(-pl, -pt, size.x+pr, size.y+pb, al_map_rgba_f(color.r*0.5, color.g*0.5, color.b*0.5, color.a*0.5), 3.0);
	restore_transform();
}


void placement2d::transform_coordinates(float *xx, float *yy)
	// unsure
{
	ALLEGRO_TRANSFORM transform;

	al_copy_transform(&transform, al_get_current_transform());
	al_translate_transform(&transform, -align.x*size.x, -align.y*size.y);
	al_scale_transform(&transform, scale.x, scale.y);
	al_translate_transform(&transform, anchor.x, anchor.y); // these were negative, I'm making them positive
	al_rotate_transform(&transform, rotation);
	al_translate_transform(&transform, position.x, position.y);

	al_invert_transform(&transform);
	al_transform_coordinates(&transform, xx, yy);
}



void placement2d::place_coordinates(float *x, float *y)
	// unsure
{
	ALLEGRO_TRANSFORM transform;

	//al_copy_transform(&previous_transform, al_get_current_transform());
	al_identity_transform(&transform);

	al_translate_transform(&transform, -align.x*size.x, -align.y*size.y);
	al_scale_transform(&transform, scale.x, scale.y);
	al_translate_transform(&transform, anchor.x, anchor.y);
	al_rotate_transform(&transform, rotation);
	al_translate_transform(&transform, position.x, position.y);

	al_transform_coordinates(&transform, x, y);
}



bool placement2d::collide(float x, float y)
{
	transform_coordinates(&x, &y);

	// todo account for anchors and widths things (?)
	if (x < 0) return false;
	if (x > size.x) return false;
	if (y < 0) return false;
	if (y > size.y) return false;
	return true;
}



bool placement2d::collide(float x, float y, float padding_top, float padding_right, float padding_bottom, float padding_left)
{
	transform_coordinates(&x, &y);

	if (x < -padding_left) return false;
	if (x > size.x+padding_right) return false;
	if (y < -padding_top) return false;
	if (y > size.y+padding_bottom) return false;
	return true;
}


void placement2d::clear()
{
	position.x = 0;
	position.y = 0;
	align.x = 0.5;
	align.y = 0.5;
	rotation = 0;
	scale.x = 1;
	scale.y = 1;
	size.x = 1;
	size.y = 1;
	anchor.x = 0;
	anchor.y = 0;
}



std::string placement2d::get_string()
{
	std::stringstream ss;
	ss << "x" << position.x << " y" << position.y << " w" << size.x << " h" << size.y;
	return ss.str();
}
