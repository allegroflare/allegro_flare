


#include <allegro_flare/generate_textures.h>
#include <allegro_flare/image_processing.h>




ALLEGRO_BITMAP *generate_circle_bitmap(float size, ALLEGRO_COLOR col, int padding)
{
	// set everything up for rendering
	int w = size;
	int h = size;
	ALLEGRO_BITMAP *surface = al_create_bitmap(w, h);
	ALLEGRO_STATE previous_state;
	al_store_state(&previous_state, ALLEGRO_STATE_TARGET_BITMAP);

	// start drawing on the bitmap
	al_set_target_bitmap(surface);
	al_clear_to_color(color::transparent);
	al_draw_filled_circle(w/2, h/2, w/2 - padding*2, col);

	// restore everything back to where it was
	al_restore_state(&previous_state);

	// return the generated image
	return surface; 
}



ALLEGRO_BITMAP *generate_triangle_bitmap(float x1, float y1, float x2, float y2, float x3, float y3, ALLEGRO_COLOR col)
{
	// find the width and height of the bitmap (this could be more comprehensive? What about -negative points?)
	float max_x = std::max({x1, x2, x2}); // I now love c++11
	float max_y = std::max({y1, y2, y3});

	// start drawing
	ALLEGRO_BITMAP *surface = al_create_bitmap(max_x, max_y);
	ALLEGRO_STATE state;
	al_store_state(&state, ALLEGRO_STATE_TARGET_BITMAP);
	al_clear_to_color(color::transparent);
	al_set_target_bitmap(surface);

	// build our triangle
	ALLEGRO_VERTEX v[3];
	v[0] = build_vertex(x1, y1, 0, col, 0, 0);
	v[1] = build_vertex(x2, y2, 0, col, 0, 0);
	v[2] = build_vertex(x3, y3, 0, col, 0, 0);

	// draw the triangle
	al_draw_prim(v, NULL, NULL, 0, 3, ALLEGRO_PRIM_TRIANGLE_LIST);

	// restore drawing state
	al_restore_state(&state);
	return surface;
}



ALLEGRO_BITMAP *generate_gradient_bitmap(float size, ALLEGRO_COLOR top_color, ALLEGRO_COLOR bottom_color, int padding)
{
	// set everything up for rendering
	int w = size;
	int h = size;
	ALLEGRO_BITMAP *surface = al_create_bitmap(w, h);
	ALLEGRO_STATE previous_state;
	al_store_state(&previous_state, ALLEGRO_STATE_TARGET_BITMAP);

	// start drawing on the bitmap
	al_set_target_bitmap(surface);
	al_clear_to_color(color::transparent);

	// build the gradient as a primitive
	ALLEGRO_VERTEX v[4];
	v[0] = build_vertex(0+padding, 0+padding, 0, top_color, 0, 0);
	v[1] = build_vertex(w-padding, 0+padding, 0, top_color, 0, 0);
	v[2] = build_vertex(w-padding, h-padding, 0, bottom_color, 0, 0);
	v[3] = build_vertex(0+padding, h-padding, 0, bottom_color, 0, 0);

	// draw it to the surface
	al_draw_prim(v, NULL, NULL, 0, 4, ALLEGRO_PRIM_TRIANGLE_FAN);

	// restore everything back to where it was
	al_restore_state(&previous_state);

	// return the generated image
	return surface; 
}



ALLEGRO_BITMAP *generate_circle_gradient_bitmap(float size, ALLEGRO_COLOR top_color, ALLEGRO_COLOR bottom_color, int padding)
{
	ALLEGRO_BITMAP *circle = generate_circle_bitmap(size);
	ALLEGRO_BITMAP *gradient = generate_gradient_bitmap(size);
	ALLEGRO_BITMAP *circle_gradient = create_masked_bitmap(circle, gradient);
	al_destroy_bitmap(circle);
	al_destroy_bitmap(gradient);
	return circle_gradient;
}



ALLEGRO_BITMAP *generate_noise_bitmap(float w, float h, float min_intensity, float max_intensity)
{
	// set everything up
	ALLEGRO_BITMAP *surface = al_create_bitmap(w, h);
	ALLEGRO_STATE state;
	al_store_state(&state, ALLEGRO_STATE_TARGET_BITMAP);

	// set the drawing surface
	al_set_target_bitmap(surface);

	// write the (randomly colored) pixels
	al_lock_bitmap(surface, ALLEGRO_PIXEL_FORMAT_ARGB_8888, ALLEGRO_LOCK_WRITEONLY);
	for (int x=0; x<w; x++)
	{
		for (int y=0; y<h; y++)
		{
			float val = random_float(min_intensity, max_intensity);
			al_put_pixel(x, y, al_map_rgba_f(val, val, val, 1.0));
		}
	}
	al_unlock_bitmap(surface);

	// return everything back to the way it was
	al_restore_state(&state);

	// return the generated image
	return surface;
}



ALLEGRO_BITMAP *generate_wood_grain_bitmap(float w, float h, ALLEGRO_COLOR base_color)
{
	// set up everything
	float h_stretch = 12;
	float angle = 1.0;
	ALLEGRO_BITMAP *surface = al_create_bitmap(w, h);
	ALLEGRO_BITMAP *noise_texture = generate_noise_bitmap(w, h, 0.5, 0.7);
	ALLEGRO_STATE state;
	al_store_state(&state, ALLEGRO_STATE_TARGET_BITMAP | ALLEGRO_STATE_BLENDER);

	// set the drawing surface
	al_set_target_bitmap(surface);

	// set the base color
	al_clear_to_color(base_color);

	// draw the wood grain (should clean this up a little bit)
	al_set_separate_blender(ALLEGRO_DEST_MINUS_SRC, ALLEGRO_ONE, ALLEGRO_ONE, ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ONE); // subtraction blender

	al_draw_tinted_scaled_bitmap(noise_texture, color::color("white", 1.0), -300, -300, al_get_bitmap_width(noise_texture), al_get_bitmap_height(noise_texture),
		0, 0, al_get_bitmap_width(noise_texture)*h_stretch*1.736, al_get_bitmap_height(noise_texture)*2, ALLEGRO_FLAGS_EMPTY);

	al_draw_tinted_bitmap(noise_texture, color::color("white", 0.2), -200, -200, ALLEGRO_FLAGS_EMPTY);

	al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ONE); // normal blender (default blending)

	al_draw_tinted_scaled_bitmap(noise_texture, color::color("white", 0.3), 0, 0, al_get_bitmap_width(noise_texture), al_get_bitmap_height(noise_texture),
		0, 0, al_get_bitmap_width(noise_texture)*h_stretch, al_get_bitmap_height(noise_texture), ALLEGRO_FLAGS_EMPTY);

	// erase the other assets
	al_destroy_bitmap(noise_texture);

	// return everything back to the way it was
	al_restore_state(&state);

	// return the generated image
	return surface;
}




