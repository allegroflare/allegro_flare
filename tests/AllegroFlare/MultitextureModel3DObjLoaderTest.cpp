
#include <gtest/gtest.h>

#include <AllegroFlare/MultitextureModel3DObjLoader.hpp>
// TODO: improve this:
#if defined(_WIN32) || defined(_WIN64)
      std::string TEST_FIXTURES_FOLDER = "/msys64/home/Mark/Repos/allegro_flare/tests/fixtures/";
#else
      std::string TEST_FIXTURES_FOLDER = "/Users/markoates/Repos/allegro_flare/tests/fixtures/";
#endif


TEST(AllegroFlare_MultitextureModel3DObjLoaderTest, can_be_created_without_blowing_up)
{
   AllegroFlare::MultitextureModel3DObjLoader multitexture_model3dobj_loader;
}


TEST(AllegroFlare_MultitextureModel3DObjLoaderTest, load__will_not_blow_up)
{
   std::string base_obj_filename = TEST_FIXTURES_FOLDER + "models/simple_scene-01.obj";
   std::string uv2_obj_filename = TEST_FIXTURES_FOLDER + "models/simple_scene-01-ao-01.obj";

   al_init();
   al_init_primitives_addon();
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);

   AllegroFlare::MultitextureModel3D model;
   model.initialize();
   AllegroFlare::MultitextureModel3DObjLoader multitexture_model3dobj_loader;
   multitexture_model3dobj_loader.set_base_obj_filename(base_obj_filename);
   multitexture_model3dobj_loader.set_obj_filename_with_uv2_coordinates(uv2_obj_filename);
   multitexture_model3dobj_loader.set_model(&model);

   multitexture_model3dobj_loader.load();

   al_destroy_display(display);
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


