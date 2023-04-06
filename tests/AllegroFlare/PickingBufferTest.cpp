
#include <gtest/gtest.h>


#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }



#define ALLEGRO_UNSTABLE


#include <allegro5/allegro.h>
#include <AllegroFlare/PickingBuffer.hpp>


using namespace AllegroFlare;


TEST(AllegroFlare_PickingBufferTest, DISABLED__surface_width__before_initialization__will_throw_an_error)
{
   // TODO
}


TEST(AllegroFlare_PickingBufferTest, DISABLED__surface_height__before_initialization__will_throw_an_error)
{
   // TODO
}


TEST(AllegroFlare_PickingBufferTest, creates_a_render_surface_with_or_without_a_depth_buffer)
{
   //ASSERT_EQ(false, al_is_system_installed());
   if (al_is_system_installed()) al_uninstall_system();
   ASSERT_EQ(true, al_init());

   ALLEGRO_DISPLAY *display = al_create_display(800, 600);
   ASSERT_NE(nullptr, display);


   PickingBuffer *id_picker_1 = new PickingBuffer(300, 200, 0);
   id_picker_1->initialize();
   ASSERT_EQ(0, al_get_bitmap_depth(id_picker_1->get_surface_render()));

   PickingBuffer *id_picker_2 = new PickingBuffer(300, 200, 32);
   id_picker_2->initialize();
   ASSERT_EQ(32, al_get_bitmap_depth(id_picker_2->get_surface_render()));


   al_destroy_display(display);
   al_uninstall_system();
}


TEST(AllegroFlare_PickingBufferTest, creates_a_render_surface_without_multisampling_and_restores_previous_bitmap_samples)
{
   //ASSERT_EQ(false, al_is_system_installed());
   if (al_is_system_installed()) al_uninstall_system();
   ASSERT_EQ(true, al_init());

   ALLEGRO_DISPLAY *display = al_create_display(800, 600);
   ASSERT_NE(nullptr, display);


   al_set_new_bitmap_samples(32);

   PickingBuffer *id_picker = new PickingBuffer(200, 200, 0);
   id_picker->initialize();
   ASSERT_EQ(0, al_get_bitmap_samples(id_picker->get_surface_render()));

   ASSERT_EQ(32, al_get_new_bitmap_samples());


   al_destroy_display(display);
   al_uninstall_system();
}


