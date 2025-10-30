

#include <AllegroFlare/CubemapBuilder.hpp>

#include <iostream>
#include <allegro5/allegro.h>
//#include <allegro_flare/console_color.h>
#include <AllegroFlare/TerminalColors.hpp>
#include <AllegroFlare/Logger.hpp>
#include <allegro5/allegro_opengl.h>



// The define values listed below are missing from the Windows headers
// solution is taken from here:
//    https://stackoverflow.com/questions/5617250/gl-clamp-to-edge-was-not-declared-in-this-scope
// The remaining constants and valuse are derived from this list:
//    https://www.khronos.org/registry/OpenGL/api/GL/glext.h


#ifndef GL_CLAMP_TO_EDGE
  #define GL_CLAMP_TO_EDGE 0x812F
#endif

#ifndef GL_TEXTURE_CUBE_MAP
  #define GL_TEXTURE_CUBE_MAP 0x8513
#endif

#ifndef GL_TEXTURE_WRAP_R
  #define GL_TEXTURE_WRAP_R 0x8072
#endif

#ifndef GL_TEXTURE_CUBE_MAP_POSITIVE_X
  #define GL_TEXTURE_CUBE_MAP_POSITIVE_X 0x8515
#endif



namespace AllegroFlare
{
   // todo
   bool CubemapBuilder::glsl_destroy_cubemap_texture(AllegroFlare::Cubemap *cubemap)
   {
      // cubemap
      AllegroFlare::Logger::warn_from(
         THIS_CLASS_AND_METHOD_NAME,
         "Not implemented. This cubemap texture will remain dangling for the duration of the running application. "
            "Please review this code and ensure the cubemap is properly destroyed."
      );
      return false;
   }




   //https://www.allegro.cc/forums/thread/611449
   //Faces are in a single bitmap. Images in the strip are in the following order:
   //+x -x +y -y +z -z
   AllegroFlare::Cubemap *CubemapBuilder::glsl_create_cubemap_from_vertical_strip(const char *filename)
   {
      auto &RED = AllegroFlare::TerminalColors::RED;
      auto &DEFAULT = AllegroFlare::TerminalColors::DEFAULT;
      auto &YELLOW = AllegroFlare::TerminalColors::YELLOW;

      if (!filename)
      {
         std::cout << RED << "Could not load a NULL filename when creating cubemap" << DEFAULT << std::endl;
         return NULL;
      }

      //AllegroFlare::Cubemap *texture = NULL;
      GLuint texture_id = 0;
      ALLEGRO_BITMAP *strip_of_cube_face_bitmaps = al_load_bitmap(filename);

      //
      // validate the passed image
      //

      if (!strip_of_cube_face_bitmaps)
      {
         std::cout << RED << "Could not load \"" << filename << "\" when creating cubemap" << DEFAULT << std::endl;
         return NULL;
      }

      // we will be using the width of the cube
      int w = al_get_bitmap_width(strip_of_cube_face_bitmaps);

      // if the height of the strip is not w*6, then the image is invalid
      if (al_get_bitmap_height(strip_of_cube_face_bitmaps) != w*6)
      {
         std::cout
            << YELLOW
            << "Cannot create cubemap from strip. The height of the image strip must be width*6."
            << DEFAULT
            << std::endl;
         al_destroy_bitmap(strip_of_cube_face_bitmaps);
         return NULL;
      }

      //
      // construct the AllegroFlare::Cubemap
      //

      // allegro's image coordinates are different from OPEN_GLs, so in order to
      // get the pixel data to send correctly, we'll have to draw each image flipped
      // and then use that bitmap to send the data to the card

      ALLEGRO_BITMAP *flipped = al_create_bitmap(al_get_bitmap_width(strip_of_cube_face_bitmaps), al_get_bitmap_width(strip_of_cube_face_bitmaps));
      //texture = new AllegroFlare::Cubemap;

      glGenTextures(1, &texture_id);
      glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id);

      //std::cout << "Generated OpenGL Cubemap Texture with ID: " << texture->id << std::endl;

      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


      ALLEGRO_STATE state;
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
      al_destroy_bitmap(strip_of_cube_face_bitmaps);

      return new AllegroFlare::Cubemap(texture_id);
   }



} // namespace AllegroFlare


