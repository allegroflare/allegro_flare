



#include <allegro_flare/camera2d.h>




namespace allegro_flare
{
   projected_point_data::projected_point_data(float x, float y, float scale)
      : x(x)
      , y(y)
      , scale(scale)
   {}




   /*
   ALLEGRO_COLOR overlay_color;
   float overlay_opacity;

   ALLEGRO_STATE previous_state;
   ALLEGRO_TRANSFORM transform;
   float x, y, w, h, align_x, align_y, scale_x, scale_y, rotation;
   float z, home_z, depth;
   */




   Camera2D::Camera2D(float x, float y, float width, float height)
      : overlay_color(al_map_rgb(0,0,0))
      , overlay_opacity(0)
      , previous_state()
      //, transform()
      , placement(x, y, width, height)
      /*	, x(x)
         , y(y)
         , w(width)
         , h(height)
         , align_x(0.5)
         , align_y(0.5)
         , scale_x(1)
         , scale_y(1)
         , rotation(0)
      */
      , z(512)
      , home_z(512)
      , depth(512)
   {
      //depth = 128;  // the bigger this number, the less apparent the depth effect
      //depth = 512;  // 512 is an accurate balance to where moving right 100px feels
      // proportionally the same distance as moving forward 100px
   }




   void Camera2D::start_transform()
   {
      // TODO
      // this functionality should eventually be phased out in favor of placement2d's transforms.
      // at the time of this writing, placement2d will need to have something like a
      // start_transform() and start_inverse_transform(), the second one being the one that
      // would probably be used in this function.
      // "transform_screen_to_camera(x,y)" and it's inverse, "project_into(x, y)"

      al_store_state(&previous_state, ALLEGRO_STATE_TRANSFORM); // this will probably be a 

      /*
      al_build_transform(&transform, -x + w*align_x, -y + h*align_y, scale_x, scale_y, rotation);
      al_use_transform(&transform);
      */

      //al_identity_transform(&transform);
      al_copy_transform(&transform, al_get_current_transform());

      al_translate_transform(&transform, -placement.position.x, -placement.position.y);
      al_scale_transform(&transform, placement.scale.x, placement.scale.y);
      al_rotate_transform(&transform, placement.rotation);
      al_translate_transform(&transform, placement.size.x*placement.align.x, placement.size.y*placement.align.y);

      al_use_transform(&transform);
   }




   void Camera2D::restore_transform()
   {
      al_restore_state(&previous_state);
   }




   /*
   void Camera2D::target(float x, float y)
   {
      this->x = x;
      this->y = y;
   }
   */




   void Camera2D::translate_screen_to_world(AllegroFlare::vec2d *vec)
   {
      translate_screen_to_world(&vec->x, &vec->y);
   }




   void Camera2D::translate_screen_to_world(float *x, float *y)
   {
   /*
      ALLEGRO_TRANSFORM trans;

      al_identity_transform(&trans);
      al_translate_transform(&trans, -this->x, -this->y);
      al_scale_transform(&trans, scale_x, scale_y);
      al_rotate_transform(&trans, rotation);
      al_translate_transform(&trans, w*align_x, h*align_y);

      al_invert_transform(&trans);

      al_transform_coordinates(&trans, x, y);
   */
   }




   // has not been tested
   void Camera2D::translate_world_to_screen(AllegroFlare::vec2d *vec)
   {
      //*
      this->start_transform();
      //al_transform_coordinates(&this->placement.transform, &vec->x, &vec->y);
      al_transform_coordinates(&this->transform, &vec->x, &vec->y);
      this->restore_transform();
      //*/
   }




   float Camera2D::get_scale(float world_z)
   {
      float distance_from_camera = z - world_z;
      if (distance_from_camera <= 0) return 0;
      if (depth <= 0) return 0;

      return depth / distance_from_camera;
   }




   projected_point_data Camera2D::get_projected_point(float world_x, float world_y, float world_z)
   {
      /*
      float scale = get_scale(z);
      return projected_point_data((x-this->x)*scale, (y-this->y)*scale, scale);
      */
      return projected_point_data(0, 0, 1);
   }
}



