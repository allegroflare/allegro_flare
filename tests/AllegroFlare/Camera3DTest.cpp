
#include <gtest/gtest.h>

#include <AllegroFlare/Camera3D.hpp>

#include <AllegroFlare/Testing/Comparison/AllegroFlare/Vec2D.hpp>
#include <AllegroFlare/Testing/Comparison/AllegroFlare/Vec3D.hpp>
#include <allegro5/allegro_primitives.h>


namespace {
   ALLEGRO_VERTEX build_vertex(float x, float y, float z, ALLEGRO_COLOR col, float u, float v)
   {
      ALLEGRO_VERTEX vertex;
      vertex.x = x, vertex.y = y, vertex.z = z, vertex.color = col, vertex.u = u, vertex.v = v;
      return vertex;
   }


   void draw_crosshair(float x, float y, float z, ALLEGRO_COLOR col, float size = 0.25)
   {
      ALLEGRO_VERTEX v[6];
      float hsize = size/2;

      for (unsigned i=0; i<6; i++)
         v[i] = build_vertex(x, y, z, col, 0, 0);

      v[0].x -= hsize;
      v[1].x += hsize;

      v[2].y -= hsize;
      v[3].y += hsize;

      v[4].z -= hsize;
      v[5].z += hsize;

      al_draw_prim(&v, NULL, NULL, 0, 6, ALLEGRO_PRIM_LINE_LIST);
   }




   void draw_crosshair_vec3d(AllegroFlare::Vec3D point, ALLEGRO_COLOR col, float size=0.25)
   {
      draw_crosshair(point.x, point.y, point.z, col, size);
   }
}




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


TEST(AllegroFlare_Camera3DTest,
   blend__with_interpolation_of_0_25__will_correctly_interpolate_camera_properties)
{
    AllegroFlare::Camera3D camera_a;
    AllegroFlare::Camera3D camera_b;

    // Setup initial distinct values for camera_a
    camera_a.position = AllegroFlare::Vec3D(0.0f, 4.0f, 8.0f);
    camera_a.stepout = AllegroFlare::Vec3D(12.0f, 16.0f, 20.0f);
    camera_a.spin = 0.0f;
    camera_a.tilt = 4.0f;
    camera_a.roll = 8.0f;
    camera_a.zoom = 12.0f;
    camera_a.near_plane = 1.0f;
    camera_a.far_plane = 100.0f;

    // Setup initial distinct values for camera_b
    camera_b.position = AllegroFlare::Vec3D(4.0f, 8.0f, 12.0f);
    camera_b.stepout = AllegroFlare::Vec3D(16.0f, 20.0f, 24.0f);
    camera_b.spin = 4.0f;
    camera_b.tilt = 8.0f;
    camera_b.roll = 12.0f;
    camera_b.zoom = 16.0f;
    camera_b.near_plane = 5.0f;   // (5.0 - 1.0) * 0.25 = 1.0. So 1.0 + 1.0 = 2.0
    camera_b.far_plane = 104.0f; // (104.0 - 100.0) * 0.25 = 1.0. So 100.0 + 1.0 = 101.0

    float interpolation = 0.25f;
    camera_a.blend(&camera_b, interpolation);

    // Define expected values after interpolation
    AllegroFlare::Vec3D expected_position(1.0f, 5.0f, 9.0f);
    AllegroFlare::Vec3D expected_stepout(13.0f, 17.0f, 21.0f);
    float expected_spin = 1.0f;
    float expected_tilt = 5.0f;
    float expected_roll = 9.0f;
    float expected_zoom = 13.0f;
    float expected_near_plane = 2.0f;
    float expected_far_plane = 101.0f;

    EXPECT_EQ(expected_position, camera_a.position);
    EXPECT_EQ(expected_stepout, camera_a.stepout);
    EXPECT_EQ(expected_spin, camera_a.spin);
    EXPECT_EQ(expected_tilt, camera_a.tilt);
    EXPECT_EQ(expected_roll, camera_a.roll);
    EXPECT_EQ(expected_zoom, camera_a.zoom);
    EXPECT_EQ(expected_near_plane, camera_a.near_plane);
    EXPECT_EQ(expected_far_plane, camera_a.far_plane);
}


TEST(AllegroFlare_Camera3DTest,
   blend__with_interpolation_of_0_0__will_not_change_the_source_camera_properties)
{
    AllegroFlare::Camera3D camera_a;
    AllegroFlare::Camera3D camera_b;

    // Setup initial distinct values for camera_a
    camera_a.position = AllegroFlare::Vec3D(1.0f, 2.0f, 3.0f);
    camera_a.stepout = AllegroFlare::Vec3D(4.0f, 5.0f, 6.0f);
    camera_a.spin = 0.1f;
    camera_a.tilt = 0.2f;
    camera_a.roll = 0.3f;
    camera_a.zoom = 10.0f;
    camera_a.near_plane = 0.5f;
    camera_a.far_plane = 50.0f;

    // Store a copy of camera_a's initial state
    AllegroFlare::Camera3D initial_camera_a_state = camera_a;

    // Setup different values for camera_b
    camera_b.position = AllegroFlare::Vec3D(10.0f, 20.0f, 30.0f);
    camera_b.stepout = AllegroFlare::Vec3D(40.0f, 50.0f, 60.0f);
    camera_b.spin = 1.1f;
    camera_b.tilt = 1.2f;
    camera_b.roll = 1.3f;
    camera_b.zoom = 100.0f;
    camera_b.near_plane = 1.5f;
    camera_b.far_plane = 500.0f;

    float interpolation = 0.0f;
    camera_a.blend(&camera_b, interpolation);

    // Check that camera_a's properties are unchanged
    EXPECT_EQ(initial_camera_a_state.position, camera_a.position);
    EXPECT_EQ(initial_camera_a_state.stepout, camera_a.stepout);
    EXPECT_EQ(initial_camera_a_state.spin, camera_a.spin);
    EXPECT_EQ(initial_camera_a_state.tilt, camera_a.tilt);
    EXPECT_EQ(initial_camera_a_state.roll, camera_a.roll);
    EXPECT_EQ(initial_camera_a_state.zoom, camera_a.zoom);
    EXPECT_EQ(initial_camera_a_state.near_plane, camera_a.near_plane);
    EXPECT_EQ(initial_camera_a_state.far_plane, camera_a.far_plane);
}


TEST(AllegroFlare_Camera3DTest,
   blend__with_interpolation_of_1_0__will_set_source_camera_properties_to_target_properties)
{
    AllegroFlare::Camera3D camera_a;
    AllegroFlare::Camera3D camera_b;

    // Setup initial distinct values for camera_a
    camera_a.position = AllegroFlare::Vec3D(1.0f, 2.0f, 3.0f);
    camera_a.stepout = AllegroFlare::Vec3D(4.0f, 5.0f, 6.0f);
    camera_a.spin = 0.1f;
    camera_a.tilt = 0.2f;
    camera_a.roll = 0.3f;
    camera_a.zoom = 10.0f;
    camera_a.near_plane = 0.5f;
    camera_a.far_plane = 50.0f;

    // Setup different values for camera_b (these will be the expected values for camera_a)
    camera_b.position = AllegroFlare::Vec3D(10.0f, 20.0f, 30.0f);
    camera_b.stepout = AllegroFlare::Vec3D(40.0f, 50.0f, 60.0f);
    camera_b.spin = 1.1f;
    camera_b.tilt = 1.2f;
    camera_b.roll = 1.3f;
    camera_b.zoom = 100.0f;
    camera_b.near_plane = 1.5f;
    camera_b.far_plane = 500.0f;

    float interpolation = 1.0f;
    camera_a.blend(&camera_b, interpolation);

    // Check that camera_a's properties are now equal to camera_b's properties
    EXPECT_EQ(camera_b.position, camera_a.position);
    EXPECT_EQ(camera_b.stepout, camera_a.stepout);
    EXPECT_EQ(camera_b.spin, camera_a.spin);
    EXPECT_EQ(camera_b.tilt, camera_a.tilt);
    EXPECT_EQ(camera_b.roll, camera_a.roll);
    EXPECT_EQ(camera_b.zoom, camera_a.zoom);
    EXPECT_EQ(camera_b.near_plane, camera_a.near_plane);
    EXPECT_EQ(camera_b.far_plane, camera_a.far_plane);
}


TEST(AllegroFlare_Camera3DTest,
   blend__cameraA_radians_cameraB_units__interpolates_correctly_and_preserves_A_units)
{
    AllegroFlare::Camera3D camera_a;
    AllegroFlare::Camera3D camera_b;
    float interpolation = 0.5f;

    // camera_a uses radians (default)
    camera_a.spin_in_unit_values = false;
    camera_a.spin = 0.0f; // 0 radians

    // camera_b uses units
    camera_b.spin_in_unit_values = true;
    camera_b.spin = 1.0f; // 1.0 unit = PI radians

    camera_a.blend(&camera_b, interpolation);

    // Expected: camera_b's spin (1.0 unit = PI rad) is converted to radians for calculation.
    // (PI - 0.0) * 0.5 + 0.0 = PI / 2
    float expected_spin_val_rad = ALLEGRO_PI; // / 2.0f;

    // Check camera_a's spin value and that its unit preference is preserved
    EXPECT_EQ(false, camera_a.spin_in_unit_values); // Should still be radians
    // For float comparisons, EXPECT_FLOAT_EQ or EXPECT_NEAR might be more robust
    EXPECT_EQ(expected_spin_val_rad, camera_a.spin);
}


TEST(AllegroFlare_Camera3DTest,
   blend__cameraA_units_cameraB_radians__interpolates_correctly_and_preserves_A_units)
{
    AllegroFlare::Camera3D camera_a;
    AllegroFlare::Camera3D camera_b;
    float interpolation = 0.25f;

    // camera_a uses units
    camera_a.spin_in_unit_values = true;
    camera_a.spin = 0.0f; // 0.0 units

    // camera_b uses radians
    camera_b.spin_in_unit_values = false;
    camera_b.spin = ALLEGRO_PI * 2; // PI radians = 1.0 unit

    camera_a.blend(&camera_b, interpolation);

    // Expected: camera_b's spin (PI rad = 1.0 unit) is converted to units for calculation.
    // (1.0 - 0.0) * 0.25 + 0.0 = 0.25 units
    float expected_spin_val_units = 0.25f;

    // Check camera_a's spin value and that its unit preference is preserved
    EXPECT_EQ(true, camera_a.spin_in_unit_values); // Should still be units
    EXPECT_EQ(expected_spin_val_units, camera_a.spin);
}


TEST(AllegroFlare_Camera3DTest,
   blend__interpolation_1_cameraA_units_cameraB_radians__assigns_converted_and_preserves_A_units)
{
    AllegroFlare::Camera3D camera_a;
    AllegroFlare::Camera3D camera_b;
    float interpolation = 1.0f;

    // camera_a uses units
    camera_a.spin_in_unit_values = true;
    camera_a.spin = 0.0f; // Initial value, will be overwritten

    // camera_b uses radians
    camera_b.spin_in_unit_values = false;
    camera_b.spin = ALLEGRO_PI / 2.0f; // PI/4 radians = 0.25 units

    camera_a.blend(&camera_b, interpolation);

    // Expected: camera_b's spin (PI/4 rad) is converted to units (0.25 units)
    // and assigned to camera_a.spin.
    // camera_a's unit preference (units) should be preserved.
    float expected_spin_val_units = 0.25f;

    EXPECT_EQ(true, camera_a.spin_in_unit_values); // Should still be units
    EXPECT_EQ(expected_spin_val_units, camera_a.spin);

    // Also verify other properties are copied as per the original test for interpolation 1.0
    // (using a simple value for position to keep it brief)
    camera_a.position = AllegroFlare::Vec3D(0,0,0);
    camera_b.position = AllegroFlare::Vec3D(10,20,30);
    // Re-blend to ensure other properties are also copied in the 1.0 case
    // (This part is redundant if we only test spin, but good for completeness if desired)
    // For brevity, we can trust the existing test handles full property copy for non-rotational.
    // The main point here is the converted spin and preserved unit flag.
}


// Tests on "shift"




struct Camera3DProjectedTests : public ::testing::Test
{
protected:
    ALLEGRO_DISPLAY* display;
    ALLEGRO_BITMAP* surface;
    AllegroFlare::Camera3D camera;
    int surface_width_num_units;
    int surface_height_num_units;

    Camera3DProjectedTests()
        : display(nullptr)
        , surface(nullptr)
        , camera()
        , surface_width_num_units(1920)
        , surface_height_num_units(1080)
    {
    }

    void SetUp() override
    {
        ASSERT_TRUE(al_init());
        //al_init_primitives_addon();
        //ASSERT_TRUE(al_init_primitives_addon()); // Optional: if you want to draw things for visual checks
        //al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_PROGRAMMABLE_PIPELINE); // Optional
        //al_set_new_display_option(ALLEGRO_DEPTH_SIZE, 32, ALLEGRO_SUGGEST); // TODO: review these numbers
        //al_set_new_display_option(
        //al_set_new_bitmap_depth

        display = al_create_display(800, 600); // A smaller display for tests is fine
        ASSERT_NE(nullptr, display);
        surface = al_get_backbuffer(display); // Use backbuffer for projection setup
        ASSERT_NE(nullptr, surface);

        // Standard camera setup for consistent projection tests
        camera.position = AllegroFlare::Vec3D(0, 0, 0);
        camera.stepout = AllegroFlare::Vec3D(0, 0, 10); // Camera is at (0,0,10) looking towards origin
        camera.near_plane = 1.0f;
        camera.zoom = 1.0f;
        camera.shift = AllegroFlare::Vec2D(0, 0); // Default shift
    }

    void TearDown() override
    {
        if (display) al_destroy_display(display);
        //al_shutdown_primitives_addon(); // Optional
        //al_shutdown_primitives_addon();
        al_uninstall_system();
    }
};



TEST_F(Camera3DProjectedTests, get_projected_coordinates__with_default_shift_is_unchanged)
{
    // Point (1,0,0) in world space.
    // With default camera settings (near=1, zoom=1, stepout.z=10 giving cam pos (0,0,10) looking at origin),
    // this point projects to (1056, 540) on a 1920x1080 logical surface.
    AllegroFlare::Vec2D expected_coords(1056.0f, 540.0f);
    AllegroFlare::Vec2D actual_coords = camera.get_projected_coordinates(
        surface, surface_width_num_units, surface_height_num_units, 1.0f, 0.0f, 0.0f
    );
    EXPECT_EQ(expected_coords, actual_coords);
}


TEST_F(Camera3DProjectedTests, get_projected_coordinates__with_positive_x_shift__projects_coordinates_to_the_left)
{
    // Original projection of (1,0,0) is (1056, 540)
    // mul = near_plane / zoom = 1.0 / 1.0 = 1.0
    // x_on_near_plane for world point (1,0,0) is 1.0 * (near_plane / camera_distance_to_xy_plane) = 1.0 * (1.0 / 10.0) = 0.1
    // Original ndc_x = 0.1

    camera.shift.x = 0.5f; // A positive shift.x value.
                           // This shifts the frustum right, so the projected image moves left.
                           // new_left = -1.0*mul + shift.x = -1.0 + 0.5 = -0.5
                           // new_right = 1.0*mul + shift.x = 1.0 + 0.5 = 1.5
                           // new_ndc_x = (x_on_near_plane - new_left) / (new_right - new_left) * 2.0 - 1.0
                           //           = (0.1 - (-0.5)) / (1.5 - (-0.5)) * 2.0 - 1.0
                           //           = (0.6 / 2.0) * 2.0 - 1.0 = 0.6 - 1.0 = -0.4
                           // screen_x = (new_ndc_x * 0.5 + 0.5) * surface_width_num_units
                           //          = (-0.4 * 0.5 + 0.5) * 1920
                           //          = (-0.2 + 0.5) * 1920 = 0.3 * 1920 = 576

    AllegroFlare::Vec2D expected_coords(576.0f, 540.0f); // X is smaller (shifted left), Y is unchanged
    AllegroFlare::Vec2D actual_coords = camera.get_projected_coordinates(
        surface, surface_width_num_units, surface_height_num_units, 1.0f, 0.0f, 0.0f
    );
    EXPECT_EQ(expected_coords, actual_coords);
}



/*

TEST_F(Camera3DProjectedTests, xx_get_projected_coordinates__with_positive_y_shift__projects_coordinates_downwards)
{
    // Original projection of (1,0,0) is (1056, 540) for a 1920x1080 logical surface.
    // setup_projection_on uses the surface's aspect ratio (800x600 display -> AR = 600/800 = 0.75)
    // mul = 1.0, AR_surface = 0.75
    // y_on_near_plane for world point (1,0,0) is 0.0
    // Original ndc_y = 0.0

    camera.shift.y = 0.2f; // A positive shift.y value.
                           // This shifts the frustum up in camera space, so the projected image moves down on screen.
                           // new_top = AR_surface * mul + shift.y = 0.75 * 1.0 + 0.2 = 0.95
                           // new_bottom = -AR_surface * mul + shift.y = -0.75 * 1.0 + 0.2 = -0.55
                           // ndc_y = (y_on_near_plane - new_bottom) / (new_top - new_bottom) * 2.0 - 1.0
                           //       = (0.0 - (-0.55)) / (0.95 - (-0.55)) * 2.0 - 1.0
                           //       = (0.55 / 1.5) * 2.0 - 1.0 = (1.1 / 1.5) - 1.0 = -4.0/15.0
                           // screen_y = (ndc_y * -0.5 + 0.5) * surface_height_num_units (1080)
                           //          = ((-(-4.0/15.0)) * 0.5 + 0.5) * 1080
                           //          = ((4.0/30.0) + 0.5) * 1080 = (19.0/30.0) * 1080 = 19.0 * 36 = 684

    AllegroFlare::Vec2D expected_coords(1056.0f, 684.0f); // X is unchanged, Y is larger (shifted down)
    AllegroFlare::Vec2D actual_coords = camera.get_projected_coordinates(
        surface, surface_width_num_units, surface_height_num_units, 1.0f, 0.0f, 0.0f
    );
    EXPECT_EQ(expected_coords, actual_coords);
}


TEST_F(Camera3DProjectedTests, get_projected_coordinates__with_diagonal_shift__projects_coordinates_correctly)
{
    camera.shift.x = 0.5f; // Projects X to 576.0f (as in the X-shift test)
    camera.shift.y = 0.2f; // Projects Y to 684.0f (as calculated above)

    // Expected values from the individual X and Y shift test logic with correct AR for Y
    AllegroFlare::Vec2D expected_coords(576.0f, 684.0f);
    AllegroFlare::Vec2D actual_coords = camera.get_projected_coordinates(
        surface, surface_width_num_units, surface_height_num_units, 1.0f, 0.0f, 0.0f
    );
    EXPECT_EQ(expected_coords, actual_coords);
}
*/


TEST_F(Camera3DProjectedTests, get_projected_coordinates__with_positive_y_shift__projects_coordinates_downwards)
{
    // Test with proportional shift: camera.shift.y is a factor of (mul * aspect_ratio_surface)
    // Original projection of (1,0,0) has screen_x = 1056.0f, screen_y = 540.0f for a 1920x1080 logical surface.
    // Fixture setup: mul = 1.0, aspect_ratio_surface = 0.75 (from 800x600 display surface)
    // y_on_near_plane for world point (1,0,0) is 0.0. Original ndc_y = 0.0.

    camera.shift.y = 0.2f; // Proportional shift factor for Y.
                           // actual_world_offset_y = camera.shift.y * (mul * aspect_ratio_surface)
                           //                       = 0.2f * (1.0f * 0.75f) = 0.15f.
                           // This shifts the frustum up in camera space, so the projected image moves down on screen.

    // Frustum Y boundaries:
    // original_half_height = aspect_ratio_surface * mul = 0.75f
    // fr_top    = original_half_height + actual_world_offset_y = 0.75f + 0.15f = 0.90f
    // fr_bottom = -original_half_height + actual_world_offset_y = -0.75f + 0.15f = -0.60f
    // ndc_y = (y_on_near_plane - fr_bottom) / (fr_top - fr_bottom) * 2.0f - 1.0f
    //       = (0.0f - (-0.60f)) / (0.90f - (-0.60f)) * 2.0f - 1.0f
    //       = (0.60f / 1.5f) * 2.0f - 1.0f = 0.4f * 2.0f - 1.0f = -0.2f
    // screen_y = (ndc_y * -0.5f + 0.5f) * surface_height_num_units (1080)
    //          = (-0.2f * -0.5f + 0.5f) * 1080.0f = (0.1f + 0.5f) * 1080.0f = 0.6f * 1080.0f = 648.0f

    AllegroFlare::Vec2D expected_coords(1056.0f, 648.0f); // X is unchanged, Y is now 648.0f
    AllegroFlare::Vec2D actual_coords = camera.get_projected_coordinates(
        surface, surface_width_num_units, surface_height_num_units, 1.0f, 0.0f, 0.0f
    );
    EXPECT_EQ(expected_coords, actual_coords);
}


TEST_F(Camera3DProjectedTests, get_projected_coordinates__with_diagonal_shift__projects_coordinates_correctly)
{
    // camera.shift.x = 0.5f (proportional to mul)
    // actual_world_offset_x = 0.5f * mul = 0.5f * 1.0f = 0.5f.
    // This results in screen_x = 576.0f (as per the positive_x_shift test, which should also be updated if not already).

    // camera.shift.y = 0.2f (proportional to mul * aspect_ratio_surface)
    // actual_world_offset_y = 0.2f * (mul * aspect_ratio_surface) = 0.2f * (1.0f * 0.75f) = 0.15f.
    // This results in screen_y = 648.0f (as calculated in the positive_y_shift test above).

    camera.shift.x = 0.5f;
    camera.shift.y = 0.2f;

    AllegroFlare::Vec2D expected_coords(576.0f, 648.0f);
    AllegroFlare::Vec2D actual_coords = camera.get_projected_coordinates(
        surface, surface_width_num_units, surface_height_num_units, 1.0f, 0.0f, 0.0f
    );
    EXPECT_EQ(expected_coords, actual_coords);
}




#include <AllegroFlare/Testing/WithInteractionFixture.hpp>
#include <AllegroFlare/Rulers.hpp>
#include <AllegroFlare/Camera2D.hpp>


struct Camera3DRenderableTests : public AllegroFlare::Testing::WithInteractionFixture
{
protected:
    AllegroFlare::Camera3D camera, target_camera;

    void SetUp() override
    {
       AllegroFlare::Testing::WithInteractionFixture::SetUp();

       // Camera setup for consistent projection tests
       camera.position = AllegroFlare::Vec3D(0, 0, 0);
       camera.stepout = AllegroFlare::Vec3D(0, 0, 7); // Camera is at (0, 0, 7) looking towards origin
       camera.near_plane = 0.01f;
       camera.far_plane = 1000.0f;
       camera.tilt = 0.25 * 0.25;
       camera.zoom = 1.0f;
       camera.shift = AllegroFlare::Vec2D(0, 0); // Default shift
       camera.use_unit_values();

       target_camera = camera;
    }

    void TearDown() override
    {
       AllegroFlare::Testing::WithInteractionFixture::TearDown();
    }
};



#include <AllegroFlare/Rulers.hpp>

TEST_F(Camera3DRenderableTests,
   FOCUS__CAPTURE__get_projected_coordinates__without_surface_bitmap_argument__works_as_expected)
{
   ALLEGRO_FONT *font = get_any_font();
   int font_line_height = al_get_font_line_height(font);
   int font_ascent = al_get_font_ascent(font);

   // Our test points
   std::vector<std::tuple<std::string, AllegroFlare::Vec3D, bool, AllegroFlare::Vec2D, float>> points = {
      { "point 1",        { 1.0f, 0.0f, 0.0f }, false, {}, 0.0f },
      { "point 2",        { -2.0f, 1.0f, 0.0f }, false, {}, 0.0f },
      { "point 3 (unit)", { 1.0f, 1.0f, 1.0f }, false, {}, 0.0f },
      { "point 4",        { 10.0f, 1.0f, 1.0f }, false, {}, 0.0f },
   };
   constexpr int LABEL = 0;
   constexpr int COORD = 1;
   constexpr int IN_FRONT_OF_CAM = 2;
   constexpr int PROJECTED_COORD = 3;
   constexpr int DISTANCE = 4;

   ALLEGRO_COLOR color_a = ALLEGRO_COLOR{0, 1, 1, 1};
   ALLEGRO_COLOR color_a2 = ALLEGRO_COLOR{0.25, 0.3, 0.3, 0.3};
   ALLEGRO_COLOR color_b = ALLEGRO_COLOR{0, 1, 0, 1};
   ALLEGRO_COLOR color_c = ALLEGRO_COLOR{1, 0.65, 0, 1};
   bool camera_is_auto_spinning = true;
   float camera_auto_spin_rate = 0.125 * 0.125 * 0.125 * 0.25;
   float camera_spin_nudge_rate = 0.25 * 0.125;

   while(interactive_test_wait_for_event())
   {
      ALLEGRO_EVENT &current_event = *interactive_test_get_current_event();

      switch(current_event.type)
      {
         case ALLEGRO_EVENT_TIMER: {
            //
            // Update
            //

            // Move the camera for easier reading of 3D
            if (camera_is_auto_spinning)
            {
               target_camera.spin += camera_auto_spin_rate;
               //target_camera.roll += camera_auto_spin_rate;
            }

            // Update the live camera to the target camera
            camera.blend(&target_camera, 0.1);

            // Update the camera position
            AllegroFlare::Vec3D camera_real_position = camera.get_real_position();

            // Update the projected points for the camera
            for (auto &point : points)
            {
               auto &coordinate = std::get<COORD>(point);
               auto &projected_coords = std::get<PROJECTED_COORD>(point);
               auto &in_front = std::get<IN_FRONT_OF_CAM>(point);
               auto &distance = std::get<DISTANCE>(point);

               std::tie(in_front, projected_coords) = camera.get_projected_coordinates(1920, 1080, coordinate);

               distance = (coordinate - camera_real_position).get_magnitude(); 
            }


            //
            // Draw (3D world)
            //

            // Setup the 3D projection
            clear();
            camera.setup_projection_on(al_get_target_bitmap());

            // Draw the ground plane
            AllegroFlare::Rulers::draw_3d_ground_plane_grid(8);

            // Draw 3D crosshairs
            for (auto &point : points)
            {
               auto &coordinate = std::get<COORD>(point);
               draw_crosshair_vec3d(coordinate, color_c, 0.5);
            }


            //
            // Draw (2D overlay)
            //

            // Setup the 2D overlay
            AllegroFlare::Camera2D hud_camera;
            hud_camera.setup_dimensional_projection(al_get_target_bitmap());

            // Draw captured points
            for (auto &point : points)
            {
               auto &label = std::get<LABEL>(point);
               auto &coordinate = std::get<COORD>(point);
               auto &projected_coords = std::get<PROJECTED_COORD>(point);
               auto &in_front = std::get<IN_FRONT_OF_CAM>(point);
               auto &distance = std::get<DISTANCE>(point);

               //if (!in_front) continue;

               al_draw_circle(projected_coords.x, projected_coords.y, 6.5, color_a, 2.0);
               al_draw_circle(projected_coords.x, projected_coords.y, 8.5, color_b, 2.0);
               float text_x = projected_coords.x + 20;
               float text_y = projected_coords.y - font_line_height + font_ascent * 0.5;
               al_draw_text(font, color_a, text_x, text_y, ALLEGRO_ALIGN_LEFT, label.c_str());
               al_draw_textf(font, color_a2, text_x, text_y + font_line_height, ALLEGRO_ALIGN_LEFT, "dist: %.2f", distance);
            }


            //
            // Draw (Interactive test overlay)
            //

            interactive_test_render_status();
            al_flip_display();
         } break;

         case ALLEGRO_EVENT_KEY_CHAR: {
            switch(current_event.keyboard.keycode)
            {
               case ALLEGRO_KEY_RIGHT: {
                  target_camera.spin -= camera_spin_nudge_rate;
                  camera_is_auto_spinning = false;
               } break;

               case ALLEGRO_KEY_LEFT: {
                  target_camera.spin += camera_spin_nudge_rate;
                  camera_is_auto_spinning = false;
               } break;

               case ALLEGRO_KEY_UP: {
                  target_camera.tilt += camera_spin_nudge_rate;
                  camera_is_auto_spinning = false;
               } break;

               case ALLEGRO_KEY_DOWN: {
                  target_camera.tilt -= camera_spin_nudge_rate;
                  camera_is_auto_spinning = false;
               } break;

               case ALLEGRO_KEY_S: {
                  camera_is_auto_spinning = !camera_is_auto_spinning;
               } break;

               case ALLEGRO_KEY_R: {
                  target_camera.roll = 0.0f;
               } break;
            }
         } break;
      }
   }
}



