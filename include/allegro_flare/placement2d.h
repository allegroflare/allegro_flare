#ifndef __AF_PLACEMENT_2D_HEADER
#define __AF_PLACEMENT_2D_HEADER



#include <allegro5/allegro.h>
#include <string>

#include <allegro_flare/vec2d.h>


class placement2d
{
private:
	ALLEGRO_TRANSFORM previous_transform;

public:
	// float x, y, w, h, rotation, scale_x, scale_y, align_x, align_y, anchor_x, anchor_y;
	vec2d position, size, align, scale, anchor;
	float rotation;

	placement2d();
	placement2d(float x, float y, float w, float h);
	placement2d(float x, float y, float w, float h, float rotation, float scale_x=1.0, float scale_y=1.0, float align_x=0.5, float align_y=0.5, float anchor_x=0.0, float anchor_y=0.0);

	void start_transform();
	void restore_transform();
	void draw_box(ALLEGRO_COLOR color, bool draw_origin);
	void draw_box_with_padding(ALLEGRO_COLOR color, bool draw_origin, float pt, float pr, float pb, float pl);
	void draw_origin();
	void clear();
	void transform_coordinates(float *x, float *y);
	void place_coordinates(float *x, float *y);
	bool collide(float x, float y);
	bool collide(float x, float y, float padding_top, float padding_right, float padding_bottom, float padding_left);
	std::string get_string();

	//placement2d operator+=(placement2d &rhs); << this would be cool... for things like placement+=velocity;
};




#endif
