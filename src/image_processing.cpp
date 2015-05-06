


#include <allegro5/allegro_primitives.h>

#include <allegro_flare/color.h>
#include <allegro_flare/useful.h> // for only ALLEGRO_FLAGS_EMPTY
#include <allegro_flare/image_processing.h>





ALLEGRO_BITMAP *create_scaled_render(ALLEGRO_BITMAP *bmp, int dest_w, int dest_h)
{
	//if (dest_w < 1 || dest_h < 1) logger("[create_scaled_render] dest_w or dest_h too small");
	//if (!bmp) logger("[create_scaled_render] invalid bitmap given");

	ALLEGRO_STATE state;
	ALLEGRO_BITMAP *surface = al_create_bitmap(dest_w, dest_h);
	al_store_state(&state, ALLEGRO_STATE_TARGET_BITMAP);
	al_set_target_bitmap(surface);
	al_clear_to_color(color::transparent);
	al_draw_scaled_bitmap(bmp, 0, 0, al_get_bitmap_width(bmp), al_get_bitmap_height(bmp), 0, 0, dest_w, dest_h, ALLEGRO_FLAGS_EMPTY);

	al_restore_state(&state);
	return surface;
}





ALLEGRO_BITMAP *create_scaled_render(ALLEGRO_BITMAP *bmp, float scale)
{
	//if (!bmp) logger("[create_scaled_render] invalid bitmap given");

	return create_scaled_render(bmp, (int)(al_get_bitmap_width(bmp)*scale), (int)(al_get_bitmap_height(bmp)*scale));
}





void invert(ALLEGRO_BITMAP *img)
{
	//if (!img) return;
	int w = al_get_bitmap_width(img);
	int h = al_get_bitmap_height(img);
	ALLEGRO_STATE state;
	al_store_state(&state, ALLEGRO_STATE_TARGET_BITMAP);
	al_set_target_bitmap(img);
	al_lock_bitmap(img, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READWRITE);
	ALLEGRO_COLOR pix;
	for (int x=0; x<w; x++)
		for (int y=0; y<h; y++)
		{
			pix = al_get_pixel(img, x, y);
			al_put_pixel(x, y, al_map_rgba_f(1.0-pix.r, 1.0-pix.g, 1.0-pix.b, pix.a));
		}
	al_unlock_bitmap(img);
	al_restore_state(&state);
}





void trim(ALLEGRO_BITMAP *bmp)
{
	int top_most = al_get_bitmap_height(bmp);
	int right_most = 0;
	int bottom_most = 0;
	int left_most = al_get_bitmap_width(bmp);

	al_lock_bitmap(bmp, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READWRITE);

	ALLEGRO_COLOR top_left_color = al_get_pixel(bmp, 0, 0);
	for (int y=0; y<al_get_bitmap_height(bmp); y++)
		for (int x=0; x<al_get_bitmap_width(bmp); x++)
		{
			ALLEGRO_COLOR this_color = al_get_pixel(bmp, x, y);
			if (!color::basically_equal(this_color, top_left_color))
			{
				if (x < left_most) left_most = x; 
				if (y < top_most) top_most = y; 
				if (x > right_most) right_most = x; 
				if (y < left_most) top_most = y; 
			}
		}

	al_unlock_bitmap(bmp);


	// draw a rectangle around the trim area

	ALLEGRO_STATE state;
	al_store_state(&state, ALLEGRO_STATE_TARGET_BITMAP);

	al_set_target_bitmap(bmp);
	al_draw_rectangle(left_most, top_most, right_most, bottom_most, color::green, 1.0);

	al_restore_state(&state);
}





ALLEGRO_BITMAP *create_color_overlay(ALLEGRO_BITMAP *original, ALLEGRO_COLOR color)
{
	if (!original) return NULL;

	ALLEGRO_BITMAP *bitmap = al_clone_bitmap(original);
	ALLEGRO_STATE previous_drawing_state;
	al_store_state(&previous_drawing_state, ALLEGRO_STATE_TARGET_BITMAP);

	al_set_target_bitmap(bitmap);
	al_clear_to_color(color::black);  // clearing is not necessiary, don't know why this is here.
										    // why don't you take it out then? instead of writing
											// this commment, huh?  You're wierd, mark.

	al_lock_bitmap(original, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READONLY);
	al_lock_bitmap(bitmap, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_WRITEONLY);
	for (int y=0; y<al_get_bitmap_height(original); y++)
	{
		for (int x=0; x<al_get_bitmap_width(original); x++)
		{
			float alpha = al_get_pixel(original, x, y).a;
			al_put_pixel(x, y, al_map_rgba_f(color.r / color.a * alpha, color.g / color.a * alpha, color.b / color.a * alpha, alpha)); 
		}
	}
	al_unlock_bitmap(bitmap);
	al_unlock_bitmap(original);

	al_restore_state(&previous_drawing_state);

	return bitmap;
}




void color_curve(ALLEGRO_BITMAP *img, float(* interpolator_func)(float))
{
	// set everything up
	ALLEGRO_STATE state;
	al_store_state(&state, ALLEGRO_STATE_TARGET_BITMAP);
	ALLEGRO_COLOR col;
	al_set_target_bitmap(img);

	// lock the target for faster processing
	al_lock_bitmap(img, ALLEGRO_PIXEL_FORMAT_ARGB_8888, ALLEGRO_LOCK_WRITEONLY);

	// process each color
	for (int y=0; y<al_get_bitmap_height(img); y++)
	{
		// ? -> float val = 1.0 - (float)y/al_get_bitmap_height(img);
		for (int x=0; x<al_get_bitmap_width(img); x++)
		{
			// grab the pixel at the current x/y location
			col = al_get_pixel(img, x, y);

			// this is the actual color manipulation function
			col.r = interpolator_func(col.r);
			col.g = interpolator_func(col.g);
			col.b = interpolator_func(col.b);
			col.a = interpolator_func(col.a);

			// place the pixel
			al_put_pixel(x, y, col);
		}
	}
	al_unlock_bitmap(img);

	// put everything back to the way it was
	al_restore_state(&state);	
}



#include <allegro_flare/path2d.h>

void draw_histogram(ALLEGRO_BITMAP *img, float x, float y, float w, float h, ALLEGRO_COLOR hist_col)
{
	if (!img) return;

	// lock the target for faster processing
	al_lock_bitmap(img, ALLEGRO_PIXEL_FORMAT_ARGB_8888, ALLEGRO_LOCK_WRITEONLY);

	long histogram[256] = {0};
	float histogram_max = 0;

	// process each color
	for (int pixel_y=0; pixel_y<al_get_bitmap_height(img); pixel_y++)
	{
		// ? -> float val = 1.0 - (float)y/al_get_bitmap_height(img);
		for (int pixel_x=0; pixel_x<al_get_bitmap_width(img); pixel_x++)
		{
			// grab the pixel at the current x/y location
			ALLEGRO_COLOR col = al_get_pixel(img, pixel_x, pixel_y);

			// this is the actual color manipulation function
			float brightness = color::get_lightness(col); // << this is the heart of the function that measures the value of the pixel

			int brightness_index = (int)(brightness*255);
			histogram[brightness_index] += 1;
			if (histogram[brightness_index] > histogram_max) histogram_max = histogram[brightness_index];
		}
	}
	al_unlock_bitmap(img);

	// put the histogram into a path2d
	path2d path;
	path.add_point(0, 0);
	for (unsigned i=0; i<256; i++)
	{
		path.add_point((float)i/255, (float)histogram[i]/histogram_max, false);
	}
	path.add_point(1, 0);

	path.reverse();
	path.flip_v();
	path.scale(w, h);
	path.move(x, y);

	path.refresh_segment_info();
	path.draw_shape(hist_col);
}






ALLEGRO_BITMAP *create_masked_bitmap(ALLEGRO_BITMAP *top_image, ALLEGRO_BITMAP *bottom_image, int op, int src, int dst, int alpha_op, int alpha_src, int alpha_dst, ALLEGRO_TRANSFORM *top_transform, ALLEGRO_TRANSFORM *bottom_transform)
{
	ALLEGRO_TRANSFORM identity_transform;
	al_identity_transform(&identity_transform);
	if (!top_image || !bottom_image) return NULL;

	ALLEGRO_STATE state;
	al_store_state(&state, ALLEGRO_STATE_TARGET_BITMAP | ALLEGRO_STATE_BLENDER | ALLEGRO_STATE_TRANSFORM);

	ALLEGRO_BITMAP *dest = al_create_bitmap(al_get_bitmap_width(top_image), al_get_bitmap_height(top_image));
	al_set_target_bitmap(dest);
	al_clear_to_color(al_map_rgba_f(0,0,0,0));


	// draw the contents
	if (bottom_transform) al_use_transform(bottom_transform);
	else al_use_transform(&identity_transform);
	al_draw_bitmap(bottom_image, 0, 0, ALLEGRO_FLAGS_EMPTY);
	al_set_separate_blender(op, src, dst, alpha_op, alpha_src, alpha_dst);
	if (top_transform) al_use_transform(top_transform);
	else al_use_transform(&identity_transform);
	al_draw_bitmap(top_image, 0, 0, ALLEGRO_FLAGS_EMPTY);
	al_restore_state(&state);

	return dest;
}







ALLEGRO_BITMAP *create_masked_bitmap(ALLEGRO_BITMAP *top_image, ALLEGRO_BITMAP *bottom_image)
{
	return create_masked_bitmap(top_image, bottom_image, 0, 0, 2, 2, 0, 2, NULL, NULL);
}


ALLEGRO_BITMAP *create_masked_bitmap(ALLEGRO_BITMAP *top_image, ALLEGRO_BITMAP *bottom_image, ALLEGRO_TRANSFORM *top_transform, ALLEGRO_TRANSFORM *bottom_transform)
{
	return create_masked_bitmap(top_image, bottom_image, 0, 0, 2, 2, 0, 2, top_transform, bottom_transform);
}


void draw_masked_bitmap(ALLEGRO_BITMAP *destination, ALLEGRO_BITMAP *top_image, ALLEGRO_BITMAP *bottom_image, int op, int src, int dst, int alpha_op, int alpha_src, int alpha_dst, ALLEGRO_TRANSFORM *top_transform, ALLEGRO_TRANSFORM *bottom_transform)
{
	ALLEGRO_TRANSFORM identity_transform;
	al_identity_transform(&identity_transform);
	if (!destination || !top_image || !bottom_image) return;

	ALLEGRO_STATE state;
	al_store_state(&state, ALLEGRO_STATE_TARGET_BITMAP | ALLEGRO_STATE_BLENDER | ALLEGRO_STATE_TRANSFORM);

	//ALLEGRO_BITMAP *dest = al_create_bitmap(al_get_bitmap_width(top_image), al_get_bitmap_height(top_image));
	al_set_target_bitmap(destination);
	al_clear_to_color(al_map_rgba_f(0,0,0,0));


	// draw the contents
	if (bottom_transform) al_use_transform(bottom_transform);
	else al_use_transform(&identity_transform);
	al_draw_bitmap(bottom_image, 0, 0, ALLEGRO_FLAGS_EMPTY);
	al_set_separate_blender(op, src, dst, alpha_op, alpha_src, alpha_dst);
	if (top_transform) al_use_transform(top_transform);
	else al_use_transform(&identity_transform);
	al_draw_bitmap(top_image, 0, 0, ALLEGRO_FLAGS_EMPTY);
	al_restore_state(&state);

	return;
}


void draw_masked_bitmap(ALLEGRO_BITMAP *destination, ALLEGRO_BITMAP *top_image, ALLEGRO_BITMAP *bottom_image)
{
	draw_masked_bitmap(destination, top_image, bottom_image, 0, 0, 2, 2, 0, 2, NULL, NULL);
}


void draw_masked_bitmap(ALLEGRO_BITMAP *destination, ALLEGRO_BITMAP *top_image, ALLEGRO_BITMAP *bottom_image, ALLEGRO_TRANSFORM *top_transform, ALLEGRO_TRANSFORM *bottom_transform)
{
	draw_masked_bitmap(destination, top_image, bottom_image, 0, 0, 2, 2, 0, 2, top_transform, bottom_transform);
}

