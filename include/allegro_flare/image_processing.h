#ifndef __AF_IMAGE_PROCESS_HEADER
#define __AF_IMAGE_PROCESS_HEADER




#include <allegro5/allegro.h>
#include <AllegroFlare/Color.hpp>



namespace allegro_flare
{
   ALLEGRO_BITMAP *create_pixel_perfect_scaled_render(ALLEGRO_BITMAP *bmp, int scale);
   ALLEGRO_BITMAP *create_scaled_render(ALLEGRO_BITMAP *bmp, int dest_w, int dest_h);
   ALLEGRO_BITMAP *create_scaled_render(ALLEGRO_BITMAP *bmp, float scale);
   ALLEGRO_BITMAP *create_padded_bitmap(ALLEGRO_BITMAP *original, int padding_top, int padding_right, int padding_bottom, int padding_left);




   void invert(ALLEGRO_BITMAP *img); // does not properly invert the alpha
   void trim(ALLEGRO_BITMAP *img); // doesn't actually trim, yet, just draws rectangle around the trimmed region 
   ALLEGRO_BITMAP *create_color_overlay(ALLEGRO_BITMAP *bmp, ALLEGRO_COLOR color);
   void color_curve(ALLEGRO_BITMAP *img, float(* interpolator_func)(float));




   // blurs

   // TODO: make better api for using these functions, for example:
   //		ALLEGRO_BITMAP *create_blurred_image(ALLEGRO_BITMAP *image, float radius);

   void horizontal_box_blur(ALLEGRO_BITMAP *scl, ALLEGRO_BITMAP *tcl, int w, int h, int r);
   void vertical_box_blur(ALLEGRO_BITMAP *scl, ALLEGRO_BITMAP *tcl, int w, int h, int r);
   void box_blur(ALLEGRO_BITMAP *scl, ALLEGRO_BITMAP *tcl, int w, int h, int r);
   void gaussian_blur(ALLEGRO_BITMAP *scl, ALLEGRO_BITMAP *tcl, int w, int h, int r);




   // draws a histogram of luminance

   void draw_histogram(ALLEGRO_BITMAP *img, float x, float y, float w, float h, ALLEGRO_COLOR hist_col=AllegroFlare::color::white);




   // image masks

   // the names should be changed to create_masked_bitmap() etc...
   // the arguments should probably be changed to "source_bitmap" and "mask_bitmap"
   // I'm not sure about the role of the transform.  Should it only be for the mask?

   ALLEGRO_BITMAP *create_masked_bitmap(ALLEGRO_BITMAP *top_image, ALLEGRO_BITMAP *bottom_image);
   ALLEGRO_BITMAP *create_masked_bitmap(ALLEGRO_BITMAP *top_image, ALLEGRO_BITMAP *bottom_image, int op, int src, int dst, int alpha_op, int alpha_src, int alpha_dst, ALLEGRO_TRANSFORM *top_transform=NULL, ALLEGRO_TRANSFORM *bottom_transform=NULL);
   ALLEGRO_BITMAP *create_masked_bitmap(ALLEGRO_BITMAP *top_image, ALLEGRO_BITMAP *bottom_image, ALLEGRO_TRANSFORM *top_transform, ALLEGRO_TRANSFORM *bottom_transform);

   void draw_masked_bitmap(ALLEGRO_BITMAP *destination, ALLEGRO_BITMAP *top_image, ALLEGRO_BITMAP *bottom_image);
   void draw_masked_bitmap(ALLEGRO_BITMAP *destination, ALLEGRO_BITMAP *top_image, ALLEGRO_BITMAP *bottom_image, ALLEGRO_TRANSFORM *top_transform, ALLEGRO_TRANSFORM *bottom_transform);
   void draw_masked_bitmap(ALLEGRO_BITMAP *destination, ALLEGRO_BITMAP *top_image, ALLEGRO_BITMAP *bottom_image, int op, int src, int dst, int alpha_op, int alpha_src, int alpha_dst, ALLEGRO_TRANSFORM *top_transform=NULL, ALLEGRO_TRANSFORM *bottom_transform=NULL);
}



#endif
