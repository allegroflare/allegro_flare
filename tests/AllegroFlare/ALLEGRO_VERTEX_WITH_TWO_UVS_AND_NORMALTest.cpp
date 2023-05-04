
#include <gtest/gtest.h>

#include <AllegroFlare/ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMAL.hpp>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>


TEST(AllegroFlare_ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMALTest, can_be_created_without_blowing_up)
{
   AllegroFlare::ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMAL allegro_vertex_with_two_uvs_and_normal;
}


TEST(AllegroFlare_ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMALTest,
   create_ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMAL_vertex_declaration__without_allegro_initialized__will_throw_an_error)
{
   EXPECT_THROW_WITH_MESSAGE(
      AllegroFlare::create_ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMAL_vertex_declaration(),
      std::runtime_error,
      "[AllegroFlare::create_ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMAL_vertex_declaration]: error: Allegro must be "
            "initialized. (ai_is_system_installed() returned false)."
   );
}


TEST(AllegroFlare_ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMALTest,
   DISABLED__create_ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMAL_vertex_declaration__without_allegro_primitives_addon_initialized\
__will_throw_an_error)
{
   //al_init();
   //AllegroFlare::create_ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMAL_vertex_declaration();
   //al_uninstall_system();
}


TEST(AllegroFlare_ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMALTest,
   DISABLED__create_ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMAL_vertex_declaration__without_a_current_display__will_throw_an_error)
{
   //al_init();
   //al_init_primitives_addon();
   //AllegroFlare::create_ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMAL_vertex_declaration();
   //al_shutdown_primitives_addon();
   //al_uninstall_system();
}


TEST(AllegroFlare_ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMALTest,
   create_ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMAL_vertex_declaration__will_not_blow_up)
{
   al_init();
   al_init_primitives_addon();
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   ALLEGRO_VERTEX_DECL *vertex_decl = AllegroFlare::create_ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMAL_vertex_declaration();
   al_destroy_display(display);
   al_destroy_vertex_decl(vertex_decl);
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


