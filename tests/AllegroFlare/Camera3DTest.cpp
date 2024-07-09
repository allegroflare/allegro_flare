
#include <gtest/gtest.h>

#include <AllegroFlare/Camera3D.hpp>

#include <AllegroFlare/Testing/Comparison/AllegroFlare/Vec2D.hpp>
#include <AllegroFlare/Testing/Comparison/AllegroFlare/Vec3D.hpp>


TEST(AllegroFlare_Camera3DTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Camera3D camera3d;
}


TEST(AllegroFlare_Camera3DTest, get_projected_coordinates__will_return_2d_pixel_coordinates)
{
   al_init();
   AllegroFlare::Camera3D camera3d;
   ALLEGRO_DISPLAY *display = al_create_display(800, 600);
   //ALLEGRO_BITMAP *surface = al_create_bitmap(1920, 1080);
   ALLEGRO_BITMAP *surface = al_get_backbuffer(display);

   camera3d.position = AllegroFlare::Vec3D(0, 0, 0);
   camera3d.stepout = AllegroFlare::Vec3D(0, 0, 10);

   int surface_width_num_units = 1920;
   int surface_height_num_units = 1080;

   AllegroFlare::Vec2D expected_projected_coordinates = AllegroFlare::Vec2D(1056, 540);
   AllegroFlare::Vec2D actual_projected_coordinates = camera3d.get_projected_coordinates(
      surface,
      surface_width_num_units,
      surface_height_num_units,
      1,
      0,
      0
   ); // Don't know if "surface_width_num_units" and "surface_height_num_units" is the right terminology here

   EXPECT_EQ(expected_projected_coordinates, actual_projected_coordinates);

   al_flip_display();
   //al_rest(1);

   //al_destroy_bitmap(surface);
   al_destroy_display(display);

   al_uninstall_system();
}


TEST(AllegroFlare_Camera3DTest,
   get_projected_coordinates__when_near_field_is_modified__will_return_2d_pixel_coordinates_that_are_unchanged)
{
   al_init();
   AllegroFlare::Camera3D camera3d;
   ALLEGRO_DISPLAY *display = al_create_display(800, 600);
   //ALLEGRO_BITMAP *surface = al_create_bitmap(1920, 1080);
   ALLEGRO_BITMAP *surface = al_get_backbuffer(display);

   camera3d.position = AllegroFlare::Vec3D(0, 0, 0);
   camera3d.stepout = AllegroFlare::Vec3D(0, 0, 10);

   int surface_width_num_units = 1920;
   int surface_height_num_units = 1080;

   AllegroFlare::Vec2D expected_projected_coordinates = AllegroFlare::Vec2D(1056, 540);
   AllegroFlare::Vec2D actual_projected_coordinates = camera3d.get_projected_coordinates(
      surface,
      surface_width_num_units,
      surface_height_num_units,
      1,
      0,
      0
   ); // Don't know if "surface_width_num_units" and "surface_height_num_units" is the right terminology here

   camera3d.set_near_plane(0.1);

   AllegroFlare::Vec2D projected_coordinates_with_near_plane_changed = camera3d.get_projected_coordinates(
      surface,
      surface_width_num_units,
      surface_height_num_units,
      1,
      0,
      0
   ); // Don't know if "surface_width_num_units" and "surface_height_num_units" is the right terminology here

   EXPECT_EQ(expected_projected_coordinates, actual_projected_coordinates);
   EXPECT_EQ(expected_projected_coordinates, projected_coordinates_with_near_plane_changed);

   al_flip_display();
   //al_rest(1);

   //al_destroy_bitmap(surface);
   al_destroy_display(display);

   al_uninstall_system();
}


TEST(AllegroFlare_Camera3DTest, get_viewing_direction__will_return_the_direction_that_the_camera_is_facing)
{
   // TODO: Add some rigorous tests for this function
   // TODO: Test if these numbers include tilt, stepout, etc.
   AllegroFlare::Camera3D camera3d;

   //camera3d.tilt = 0.0;
   //camera3d.tilt = (3.14159265359 * 1);
   //camera3d.spin = (3.14159265359 * 0);
   //camera3d.roll = 0.25;

   AllegroFlare::Vec3D actual_viewing_direction = camera3d.get_viewing_direction();
   AllegroFlare::Vec3D expected_viewing_direction(0, 0, -1);

   EXPECT_EQ(expected_viewing_direction, actual_viewing_direction);
}


TEST(AllegroFlare_Camera3DTest,
   get_reverse_viewing_direction__will_return_the_view_vector_of_an_object_if_it_were_to_face_the_camera_plane)
{
   // TODO: Add some rigorous tests for this function
   AllegroFlare::Camera3D camera3d;

   //camera3d.tilt = 0.0;
   //camera3d.tilt = (3.14159265359 * 1);
   //camera3d.spin = (3.14159265359 * 0);
   //camera3d.roll = 0.25;

   AllegroFlare::Vec3D actual_reverse_viewing_direction = camera3d.get_reverse_viewing_direction();
   AllegroFlare::Vec3D expected_reverse_viewing_direction(0, 0, 1);

   EXPECT_EQ(expected_reverse_viewing_direction, actual_reverse_viewing_direction);
}


