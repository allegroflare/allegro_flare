

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE PickingBuffer
#include <boost/test/unit_test.hpp>




#define ALLEGRO_UNSTABLE




#include <allegro5/allegro.h>
#include <allegro_flare/picking_buffer.h>




using namespace allegro_flare;




struct SetupWithDisplay
{
   ALLEGRO_DISPLAY *display;
   SetupWithDisplay()
      : display(NULL)
   {
      BOOST_REQUIRE_EQUAL(false, al_is_system_installed());
      BOOST_REQUIRE_EQUAL(true, al_init());

      display = al_create_display(800, 600);
      BOOST_REQUIRE_NE((void *)0, display);
   }
   ~SetupWithDisplay()
   {
      al_uninstall_system();
   }
};




BOOST_FIXTURE_TEST_CASE(creates_a_render_surface_with_or_without_a_depth_buffer, SetupWithDisplay)
{
   PickingBuffer *id_picker_1 = new PickingBuffer(300, 200, 0);
   BOOST_CHECK_EQUAL(0, al_get_bitmap_depth(id_picker_1->get_surface_render()));

   PickingBuffer *id_picker_2 = new PickingBuffer(300, 200, 32);
   BOOST_CHECK_EQUAL(32, al_get_bitmap_depth(id_picker_2->get_surface_render()));
}




BOOST_FIXTURE_TEST_CASE(creates_a_render_surface_without_multisampling, SetupWithDisplay)
{
   al_set_new_bitmap_samples(32);

   PickingBuffer *id_picker = new PickingBuffer(200, 200, 0);
   BOOST_CHECK_EQUAL(0, al_get_bitmap_samples(id_picker->get_surface_render()));

   BOOST_CHECK_EQUAL(32, al_get_new_bitmap_samples());
}




BOOST_FIXTURE_TEST_CASE(when_unable_to_create_a_surface_area_raises_an_exception, SetupWithDisplay)
{
   BOOST_CHECK_THROW(new PickingBuffer(-1, -1, 0), std::runtime_error);
}




