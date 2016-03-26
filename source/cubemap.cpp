


#include <allegro_flare/cubemap.h>

#include <iostream>




bool glsl_destroy_cubemap_texture(ALLEGRO_FLARE_CUBEMAP_TEXTURE *texture)
{
	// todo
	return false;
}



ALLEGRO_FLARE_CUBEMAP_TEXTURE *glsl_create_cubemap_from_vertical_strip(const char *filename)
	//https://www.allegro.cc/forums/thread/611449
	//Faces are in a single bitmap. Images in the strip are in the following order:
	//+x -x +y -y +z -z
{
	ALLEGRO_FLARE_CUBEMAP_TEXTURE *texture = NULL;
	//al_malloc(sizeof(ALLEGRO_CUBEMAP_TEXTURE));
	ALLEGRO_BITMAP *strip_of_cube_face_bitmaps = al_load_bitmap(filename);

	// allegro's image coordinates are different from OPEN_GLs, so in order to
	// get the pixel data to send correctly, we'll have to draw each image flipped
	// and then use that bitmap to send the data to the card
	ALLEGRO_STATE state;
	ALLEGRO_BITMAP *flipped = al_create_bitmap(al_get_bitmap_width(strip_of_cube_face_bitmaps), al_get_bitmap_width(strip_of_cube_face_bitmaps));


	// we will be using the width of the cube
	int w = al_get_bitmap_width(strip_of_cube_face_bitmaps);

	// if the height of the strip is not w*6, then the image is invalid
	if (al_get_bitmap_height(strip_of_cube_face_bitmaps) != w*6)
	{
		std::cout << "The height of the image strip must be width*6" << std::endl;
	   return NULL;
	}

	texture = new ALLEGRO_FLARE_CUBEMAP_TEXTURE;

	glGenTextures(1, &texture->id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture->id);

	std::cout << "Generated OpenGL Cubemap Texture with ID: " << texture->id << std::endl;


	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	GLenum face_target = GL_TEXTURE_CUBE_MAP_POSITIVE_X; // Followed by -x, y, -y, z, -z
	const int FACE_COUNT = 6;
	for (int i = 0; i < FACE_COUNT; ++i)
	{
		al_store_state(&state, ALLEGRO_STATE_TARGET_BITMAP);
		al_set_target_bitmap(flipped);
		al_draw_bitmap(strip_of_cube_face_bitmaps, 0, (-w*((FACE_COUNT-1)-i)), ALLEGRO_FLIP_VERTICAL);
		al_restore_state(&state);

	  ALLEGRO_LOCKED_REGION *face = al_lock_bitmap_region(flipped, 0, 0, w, w, ALLEGRO_PIXEL_FORMAT_ABGR_8888, ALLEGRO_LOCK_READONLY);

	  glPixelStorei(GL_UNPACK_ALIGNMENT, face->pixel_size);
	  glTexImage2D(face_target, 0, GL_RGBA, w, w, 0, GL_RGBA, GL_UNSIGNED_BYTE, ((char *)face->data + (w-1) * (face->pitch)));

	  al_unlock_bitmap(flipped);

	  face_target++;
	}

	al_destroy_bitmap(flipped);
	return texture;
}




