#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/SavingAndLoading/SaveSlotRenderer.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();


class AllegroFlare_SavingAndLoading_SaveSlotRendererTest : public ::testing::Test {};
class AllegroFlare_SavingAndLoading_SaveSlotRendererTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};



TEST_F(AllegroFlare_SavingAndLoading_SaveSlotRendererTest, can_be_created_without_blowing_up)
{
   AllegroFlare::SavingAndLoading::SaveSlotRenderer renderer;
}


TEST_F(AllegroFlare_SavingAndLoading_SaveSlotRendererTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::SavingAndLoading::SaveSlotRenderer renderer;
   EXPECT_THROW_GUARD_ERROR(
      renderer.render(),
      "AllegroFlare::SavingAndLoading::SaveSlotRenderer::render",
      "al_is_system_installed()"
   );
}


TEST_F(AllegroFlare_SavingAndLoading_SaveSlotRendererTest,
   render__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::SavingAndLoading::SaveSlotRenderer renderer;
   EXPECT_THROW_GUARD_ERROR(
      renderer.render(),
      "AllegroFlare::SavingAndLoading::SaveSlotRenderer::render",
      "al_is_primitives_addon_initialized()"
   );
   al_uninstall_system();
}


TEST_F(AllegroFlare_SavingAndLoading_SaveSlotRendererTest,
   render__without_font_addon_initialized__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   AllegroFlare::SavingAndLoading::SaveSlotRenderer renderer;
   EXPECT_THROW_GUARD_ERROR(
      renderer.render(),
      "AllegroFlare::SavingAndLoading::SaveSlotRenderer::render",
      "al_is_font_addon_initialized()"
   );
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_SavingAndLoading_SaveSlotRendererTest, render__without_a_bitmap_bin__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   AllegroFlare::SavingAndLoading::SaveSlotRenderer renderer;
   EXPECT_THROW_GUARD_ERROR(
      renderer.render(),
      "AllegroFlare::SavingAndLoading::SaveSlotRenderer::render",
      "bitmap_bin"
   );
   al_shutdown_font_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}   


TEST_F(AllegroFlare_SavingAndLoading_SaveSlotRendererTestWithAllegroRenderingFixture,
   CAPTURE__render__will_not_blow_up)
{
   AllegroFlare::SavingAndLoading::SaveSlotRenderer renderer(
         &get_bitmap_bin_ref(),
         &get_font_bin_ref(),
         "scene3-01.jpg"
      );

   renderer.set_save_slot_type(AllegroFlare::SavingAndLoading::SaveSlot::SAVE_SLOT_TYPE_AUTO_SAVE);

   AllegroFlare::Placement2D place;
   place.position.x = 1920/2;
   place.position.y = 1080/2;
   place.size.x = renderer.get_width();
   place.size.y = renderer.get_height();
   place.start_transform();
   renderer.render();
   place.restore_transform();

   al_flip_display();
   sleep_for(1);
}


TEST_F(AllegroFlare_SavingAndLoading_SaveSlotRendererTestWithAllegroRenderingFixture,
   CAPTURE__render__with_a_time_since_value_less_than_thirty_minutes__will_render_as_expected)
{
   AllegroFlare::SavingAndLoading::SaveSlotRenderer renderer(
         &get_bitmap_bin_ref(),
         &get_font_bin_ref(),
         "scene3-01.jpg"
      );

   renderer.set_save_slot_type(AllegroFlare::SavingAndLoading::SaveSlot::SAVE_SLOT_TYPE_AUTO_SAVE);

   // Render one version under 30 minutes

   renderer.set_time_since_text("29 minutes ago");
   renderer.set_time_since_value(30 * 60 - 1);

   AllegroFlare::Placement2D place;
   place.position.x = 1920/2;
   place.position.y = 1080/2 - 100;
   place.size.x = renderer.get_width();
   place.size.y = renderer.get_height();
   place.start_transform();
   renderer.render();
   place.restore_transform();

   // Render one version at 30 minutes

   renderer.set_time_since_text("30 minutes ago");
   renderer.set_time_since_value(30 * 60);

   place.position.y += 200;
   place.start_transform();
   renderer.render();
   place.restore_transform();

   al_flip_display();
   sleep_for(1);
}


