

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE UISurfaceAreaBitmapAlpha
#include <boost/test/unit_test.hpp>




#include <allegro_flare/gui/surface_areas/bitmap_alpha.h>

#include <allegro_flare/gui/widget.h>
#include <allegro5/allegro_image.h>
#include <allegro_flare/framework.h>
#include <fstream>




#define TEST_FILENAME "data/bitmaps/elm_circle.png"




struct Fixture
{
   ALLEGRO_BITMAP *bitmap;
   Fixture()
      : bitmap(NULL)
   {
      BOOST_REQUIRE_EQUAL(false, al_is_system_installed());
      BOOST_REQUIRE_EQUAL(true, al_init());
      BOOST_REQUIRE_EQUAL(true, al_init_image_addon());
      bitmap = al_load_bitmap(TEST_FILENAME);
   }
   ~Fixture()
   {
      al_destroy_bitmap(bitmap);
      al_uninstall_system();
   }
};




BOOST_AUTO_TEST_CASE(necessairy_test_file_exists)
{
   std::ifstream ifile(TEST_FILENAME);
   BOOST_CHECK_EQUAL(true, (bool)ifile);
}




BOOST_FIXTURE_TEST_CASE(does_not_collide_at_coordinates_outside_its_bounding_box, Fixture)
{
   UISurfaceAreaBitmapAlpha surface_area = UISurfaceAreaBitmapAlpha(0, 0, Fixture::bitmap);
   surface_area.placement.align = vec2d(0, 0);

   BOOST_CHECK_EQUAL(false, surface_area.collides(-1, -1));
}




BOOST_FIXTURE_TEST_CASE(does_not_collide_on_a_pixel_with_alpha_less_than_threshold, Fixture)
{
   UISurfaceAreaBitmapAlpha surface_area = UISurfaceAreaBitmapAlpha(0, 0, Fixture::bitmap);
   surface_area.placement.align = vec2d(0, 0);

   BOOST_CHECK_EQUAL(false, surface_area.collides(2, 2));
}




BOOST_FIXTURE_TEST_CASE(will_collide_on_a_pixel_with_alpha_greater_than_threshold, Fixture)
{
   UISurfaceAreaBitmapAlpha surface_area = UISurfaceAreaBitmapAlpha(0, 0, Fixture::bitmap);
   surface_area.placement.align = vec2d(0, 0);

   BOOST_CHECK_EQUAL(true, surface_area.collides(150, 150));
}




BOOST_FIXTURE_TEST_CASE(can_set_the_alpha_threshold, Fixture)
{
   ALLEGRO_BITMAP *bmp = al_create_bitmap(1, 1);
   UISurfaceAreaBitmapAlpha surface_area = UISurfaceAreaBitmapAlpha(0, 0, bmp);
   surface_area.placement.align = vec2d(0, 0);
   al_set_target_bitmap(bmp);

   float alpha = 0.5;

   surface_area.set_alpha_threshold(alpha);
   al_put_pixel(0, 0, al_map_rgba_f(1.0, 1.0, 1.0, alpha - 0.01));
   BOOST_CHECK_EQUAL(false, surface_area.collides(0.5, 0.5));
   al_put_pixel(0, 0, al_map_rgba_f(1.0, 1.0, 1.0, alpha + 0.01));
   BOOST_CHECK_EQUAL(true, surface_area.collides(0.5, 0.5));

   alpha = 0.1;

   surface_area.set_alpha_threshold(alpha);
   al_put_pixel(0, 0, al_map_rgba_f(1.0, 1.0, 1.0, alpha - 0.01));
   BOOST_CHECK_EQUAL(false, surface_area.collides(0.5, 0.5));
   al_put_pixel(0, 0, al_map_rgba_f(1.0, 1.0, 1.0, alpha + 0.01));
   BOOST_CHECK_EQUAL(true, surface_area.collides(0.5, 0.5));

   alpha = 0.9;

   surface_area.set_alpha_threshold(alpha);
   al_put_pixel(0, 0, al_map_rgba_f(1.0, 1.0, 1.0, alpha - 0.01));
   BOOST_CHECK_EQUAL(false, surface_area.collides(0.5, 0.5));
   al_put_pixel(0, 0, al_map_rgba_f(1.0, 1.0, 1.0, alpha + 0.01));
   BOOST_CHECK_EQUAL(true, surface_area.collides(0.5, 0.5));
}




