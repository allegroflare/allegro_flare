



#include <allegro_flare/generate_textures.h>




namespace allegro_flare
{
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
      al_clear_to_color(AllegroFlare::color::transparent);
      al_draw_filled_circle(w/2, h/2, w/2 - padding*2, col);

      // restore everything back to where it was
      al_restore_state(&previous_state);

      // return the generated image
      return surface; 
   }




   ALLEGRO_BITMAP *generate_triangle_bitmap(float x1, float y1, float x2, float y2, float x3, float y3, ALLEGRO_COLOR col)
   {
      // find the width and height of the bitmap (this could be more comprehensive? What about -negative points?)
      float max_x = std::max(std::max(x1, x2), x2);
      float max_y = std::max(std::max(y1, y2), y3);

      // start drawing
      ALLEGRO_BITMAP *surface = al_create_bitmap(max_x, max_y);
      ALLEGRO_STATE state;
      al_store_state(&state, ALLEGRO_STATE_TARGET_BITMAP);
      al_clear_to_color(AllegroFlare::color::transparent);
      al_set_target_bitmap(surface);

      // build our triangle
      ALLEGRO_VERTEX v[3];
      v[0] = AllegroFlare::build_vertex(x1, y1, 0, col, 0, 0);
      v[1] = AllegroFlare::build_vertex(x2, y2, 0, col, 0, 0);
      v[2] = AllegroFlare::build_vertex(x3, y3, 0, col, 0, 0);

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
      al_clear_to_color(AllegroFlare::color::transparent);

      // build the gradient as a primitive
      ALLEGRO_VERTEX v[4];
      v[0] = AllegroFlare::build_vertex(0+padding, 0+padding, 0, top_color, 0, 0);
      v[1] = AllegroFlare::build_vertex(w-padding, 0+padding, 0, top_color, 0, 0);
      v[2] = AllegroFlare::build_vertex(w-padding, h-padding, 0, bottom_color, 0, 0);
      v[3] = AllegroFlare::build_vertex(0+padding, h-padding, 0, bottom_color, 0, 0);

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
            float val = AllegroFlare::random_float(min_intensity, max_intensity);
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

      al_draw_tinted_scaled_bitmap(noise_texture, AllegroFlare::color::color("white", 1.0), -300, -300, al_get_bitmap_width(noise_texture), al_get_bitmap_height(noise_texture),
            0, 0, al_get_bitmap_width(noise_texture)*h_stretch*1.736, al_get_bitmap_height(noise_texture)*2, ALLEGRO_FLAGS_EMPTY);

      al_draw_tinted_bitmap(noise_texture, AllegroFlare::color::color("white", 0.2), -200, -200, ALLEGRO_FLAGS_EMPTY);

      al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ONE); // normal blender (default blending)

      al_draw_tinted_scaled_bitmap(noise_texture, AllegroFlare::color::color("white", 0.3), 0, 0, al_get_bitmap_width(noise_texture), al_get_bitmap_height(noise_texture),
            0, 0, al_get_bitmap_width(noise_texture)*h_stretch, al_get_bitmap_height(noise_texture), ALLEGRO_FLAGS_EMPTY);

      // erase the other assets
      al_destroy_bitmap(noise_texture);

      // return everything back to the way it was
      al_restore_state(&state);

      // return the generated image
      return surface;
   }




   ALLEGRO_BITMAP *generate_brush_metal_bitmap(float w, float h, ALLEGRO_COLOR base_color)
   {
      // TODO: clean this function up

      // set everything up	
      float h_stretch = 1.0;
      float v_stretch = 26.0;
      ALLEGRO_BITMAP *noise_texture = generate_noise_bitmap(w, h); // TODO: this should be greater(w, h) or something similar
      ALLEGRO_BITMAP *gradient_texture = generate_gradient_bitmap(w); // TODO: this should be greater(w, h) or something similar
      ALLEGRO_BITMAP *tex = al_create_bitmap(w, h);

      // store the state and set the drawing surface
      ALLEGRO_STATE state;
      al_store_state(&state, ALLEGRO_STATE_TARGET_BITMAP | ALLEGRO_STATE_BLENDER);
      al_set_target_bitmap(tex);


      //
      // draw the content
      //
      al_clear_to_color(base_color);

      al_draw_tinted_bitmap(gradient_texture, AllegroFlare::color::name("white", 0.1), 0, 0, ALLEGRO_FLAGS_EMPTY);

      al_set_separate_blender(ALLEGRO_DEST_MINUS_SRC, ALLEGRO_ONE, ALLEGRO_ONE, ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ONE);

      al_draw_tinted_scaled_bitmap(noise_texture, AllegroFlare::color::name("white", 0.3), 0, 0, al_get_bitmap_width(noise_texture), al_get_bitmap_height(noise_texture),
            0, 0, al_get_bitmap_width(noise_texture)*h_stretch, al_get_bitmap_height(noise_texture)*v_stretch, ALLEGRO_FLAGS_EMPTY);

      al_draw_tinted_bitmap(noise_texture, AllegroFlare::color::name("white", 0.1), -200, -200, ALLEGRO_FLAGS_EMPTY);



      // restore the state
      al_restore_state(&state);
      al_destroy_bitmap(gradient_texture);
      al_destroy_bitmap(noise_texture);

      // return the generated image
      return tex;
   }




   ALLEGRO_BITMAP *generate_interpolator_graph_bitmap(float(* interpolator_func)(float), float size, ALLEGRO_COLOR col, float thickness, float padding)
   {
      // setup the drawing surface
      ALLEGRO_BITMAP *surface = al_create_bitmap(size, size);
      ALLEGRO_STATE state;
      al_store_state(&state, ALLEGRO_STATE_TARGET_BITMAP);
      al_set_target_bitmap(surface);
      al_clear_to_color(AllegroFlare::color::transparent);


      //
      //	 start drawing the graph
      //


      float line_width = thickness;

      float w = size;
      float h = size;

      float x = padding;
      float y = padding;
      w += padding*2;
      h += padding*2;

      //y *= -1;
      h *= -1;

      int num_points = 50;

      AllegroFlare::vec2d previous_point(0, 1);
      for (int i=0; i<=(num_points-1); i++)
      {
         float point_x = (float)i/(num_points-1);
         float point_y = interpolator_func(point_x);

         point_x *= (size-padding*2);
         point_y *= -(size-padding*2);

         point_x += x;
         point_y += y+(size-padding*2);

         al_draw_filled_circle(point_x, point_y, line_width*1.3, col);
      }



      // restore things to the way they were
      al_restore_state(&state);

      // return the created image
      return surface;
   }




   ALLEGRO_BITMAP *create_pixel_pattern_1(ALLEGRO_COLOR pixel1_color, ALLEGRO_COLOR pixel2_color, int checker_size)
   {
      int bitmap_size = 64;
      ALLEGRO_BITMAP *surface = al_create_bitmap(bitmap_size, bitmap_size);
      ALLEGRO_STATE state;
      al_store_state(&state, ALLEGRO_STATE_TARGET_BITMAP);
      al_set_target_bitmap(surface);

      // clear to the back color
      al_clear_to_color(pixel2_color);

      // begin drawing the surface
      al_lock_bitmap(surface, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_WRITEONLY); // is ALLEGRO_PIXEL_FORMAT_ANY correct?
      int num_rows_cols = bitmap_size / checker_size;
      for (int row=0; row<num_rows_cols; row++)
         for (int col=0; col<num_rows_cols; col++)
         {
            if ((row+col) % 2 == 1) continue; // skip if the square is even

            // draw a square of n x n size, at (x, y)
            for (int yy=0; yy<checker_size; yy++)
               for (int xx=0; xx<checker_size; xx++)
               {
                  al_put_pixel(col*checker_size + xx, row*checker_size + yy, pixel1_color);
               }
         }
      al_unlock_bitmap(surface);

      al_restore_state(&state);
      return surface;
   }




   ALLEGRO_BITMAP *create_pixel_pattern_2(ALLEGRO_COLOR pixel1_color, ALLEGRO_COLOR pixel2_color, int dot_distance)
   {
      int bitmap_size = 64;
      ALLEGRO_BITMAP *surface = al_create_bitmap(bitmap_size, bitmap_size);
      ALLEGRO_STATE state;
      al_store_state(&state, ALLEGRO_STATE_TARGET_BITMAP);
      al_set_target_bitmap(surface);

      // clear to the back color
      al_clear_to_color(pixel2_color);

      // begin drawing the surface
      al_lock_bitmap(surface, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_WRITEONLY); // is ALLEGRO_PIXEL_FORMAT_ANY correct?
      for (int y=0; y<bitmap_size; y+=dot_distance)
         for (int x=0; x<bitmap_size; x+=dot_distance)
         {
            al_put_pixel(x, y, pixel1_color);
         }
      al_unlock_bitmap(surface);

      al_restore_state(&state);
      return surface;
   }




   ALLEGRO_BITMAP *create_pixel_pattern_3(ALLEGRO_COLOR pixel1_color, ALLEGRO_COLOR pixel2_color, int x_distance, int y_distance)
   {
      int bitmap_size_x = x_distance * 8;
      int bitmap_size_y = y_distance * 8;
      ALLEGRO_BITMAP *surface = al_create_bitmap(bitmap_size_x, bitmap_size_y);
      ALLEGRO_STATE state;
      al_store_state(&state, ALLEGRO_STATE_TARGET_BITMAP);
      al_set_target_bitmap(surface);

      // clear to the back color
      al_clear_to_color(pixel2_color);

      // begin drawing the surface
      int slope = (int)(x_distance * 1.5);
      al_lock_bitmap(surface, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_WRITEONLY); // is ALLEGRO_PIXEL_FORMAT_ANY correct?
      for (int y=0; y<bitmap_size_y; y+=y_distance)
         for (int x=0; x<bitmap_size_x; x+=x_distance)
         {
            al_put_pixel(x + (y*slope)%x_distance, y, pixel1_color);
         }
      al_unlock_bitmap(surface);

      al_restore_state(&state);
      return surface;
   }




   ALLEGRO_BITMAP *create_pixel_pattern_4(ALLEGRO_COLOR pixel1_color, ALLEGRO_COLOR pixel2_color, int x_distance, float slope)
   {
      //TODO this function is not complete, and may not return expected results when other values than the default values are given. 
      // Further development is needed to provide this flexibility to the function, but at the default values, it returns the intended
      // pattern

      int bitmap_size_x = x_distance * 8;
      int bitmap_size_y = x_distance * 8;

      ALLEGRO_BITMAP *surface = al_create_bitmap(bitmap_size_x, bitmap_size_y);
      ALLEGRO_STATE state;
      al_store_state(&state, ALLEGRO_STATE_TARGET_BITMAP);
      al_set_target_bitmap(surface);

      if (x_distance < 0) { al_restore_state(&state); return surface; }
      while (slope < 0) { slope += x_distance; }

      // clear to the back color
      al_clear_to_color(pixel2_color);

      // begin drawing the surface
      al_lock_bitmap(surface, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_WRITEONLY); // is ALLEGRO_PIXEL_FORMAT_ANY correct?
      for (int y=0; y<bitmap_size_y; y+=1)
         for (int x=0; x<bitmap_size_x; x+=x_distance)
         {
            al_put_pixel(x + ((int)(y*slope))%x_distance, y, pixel1_color);
         }
      al_unlock_bitmap(surface);

      al_restore_state(&state);
      return surface;
   }
}



