
#include <gtest/gtest.h>

#include <AllegroFlare/FrameAnimation/SpriteStripAssembler.hpp>
#include <AllegroFlare/DeploymentEnvironment.hpp>
#include <allegro5/allegro_image.h>


TEST(AllegroFlare_FrameAnimation_SpriteStripAssemblerTest, can_be_created_without_blowing_up)
{
   AllegroFlare::FrameAnimation::SpriteStripAssembler sprite_strip_assembler;
}


TEST(AllegroFlare_FrameAnimation_SpriteStripAssemblerTest, assemble__will_build_the_expected_sprite_strip)
{
   AllegroFlare::DeploymentEnvironment deployment_environment("test");
   std::string images_folder = deployment_environment.get_data_folder_path() + "bitmaps/";

   al_init();
   al_init_image_addon();

   std::vector<ALLEGRO_BITMAP*> bitmaps = {
      al_load_bitmap((images_folder + "sprite_strip_images/robo-soldier1.png").c_str()),
      al_load_bitmap((images_folder + "sprite_strip_images/robo-soldier2.png").c_str()),
      al_load_bitmap((images_folder + "sprite_strip_images/robo-soldier3.png").c_str()),
      al_load_bitmap((images_folder + "sprite_strip_images/robo-soldier4.png").c_str()),
      al_load_bitmap((images_folder + "sprite_strip_images/robo-soldier5.png").c_str()),
      al_load_bitmap((images_folder + "sprite_strip_images/robo-soldier6.png").c_str()),
   };

   AllegroFlare::FrameAnimation::SpriteStripAssembler sprite_strip_assembler;
   sprite_strip_assembler.set_bitmaps(bitmaps);
   sprite_strip_assembler.assemble();
   ALLEGRO_BITMAP* result_sprite_strip = sprite_strip_assembler.get_sprite_strip();

   // Save the bitmap (for now)
   // TODO: Test the pixels on the result bitmap
   // TODO: Programatically generate the save filename
   // TODO: Consider doing a render test
   al_save_bitmap(
      "tmp/test_snapshots/AllegroFlare_FrameAnimation_SpriteStripAssemblerTest__"
         "assemble__will_build_the_expected_sprite_strip.png",
      result_sprite_strip
   );

   // Cleanup
   for (auto &bitmap : bitmaps) al_destroy_bitmap(bitmap);
   al_destroy_bitmap(result_sprite_strip);

   al_shutdown_image_addon();
   al_uninstall_system();
}


