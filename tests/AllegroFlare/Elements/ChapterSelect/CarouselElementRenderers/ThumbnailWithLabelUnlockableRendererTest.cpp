
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Elements/ChapterSelect/CarouselElementRenderers/ThumbnailWithLabelUnlockableRenderer.hpp>

class AllegroFlare_Elements_ChapterSelect_CarouselElementRenderers_ThumbnailWithLabelUnlockableRendererTest : public ::testing::Test {};
class AllegroFlare_Elements_ChapterSelect_CarouselElementRenderers_ThumbnailWithLabelUnlockableRendererTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Elements/ChapterSelect/CarouselElementRenderers/ThumbnailWithLabelUnlockableRenderer.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();


TEST_F(AllegroFlare_Elements_ChapterSelect_CarouselElementRenderers_ThumbnailWithLabelUnlockableRendererTest,
   can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::ChapterSelect::CarouselElementRenderers::ThumbnailWithLabelUnlockableRenderer thumbnail_with_label_renderer;
}


TEST_F(AllegroFlare_Elements_ChapterSelect_CarouselElementRenderers_ThumbnailWithLabelUnlockableRendererTest,
   render__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::Elements::ChapterSelect::CarouselElementRenderers::ThumbnailWithLabelUnlockableRenderer thumbnail_with_label_renderer;
   std::string expected_error_message =
      "ThumbnailWithLabelUnlockableRenderer::render: error: guard \"al_is_primitives_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(thumbnail_with_label_renderer.render(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}


TEST_F(AllegroFlare_Elements_ChapterSelect_CarouselElementRenderers_ThumbnailWithLabelUnlockableRendererTest,
   render__without_a_font_bin__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   AllegroFlare::Elements::ChapterSelect::CarouselElementRenderers::ThumbnailWithLabelUnlockableRenderer
         thumbnail_with_label_renderer;
   std::string expected_error_message =
      "ThumbnailWithLabelUnlockableRenderer::render: error: guard \"font_bin\" not met";
   EXPECT_THROW_WITH_MESSAGE(thumbnail_with_label_renderer.render(), std::runtime_error, expected_error_message);
   al_shutdown_font_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_Elements_ChapterSelect_CarouselElementRenderers_ThumbnailWithLabelUnlockableRendererTestWithAllegroRenderingFixture,
   CAPTURE__render__will_render_as_expected)
{
   AllegroFlare::Elements::ChapterSelect::CarouselElementRenderers::ThumbnailWithLabelUnlockableRenderer
         thumbnail_with_label_renderer(&get_bitmap_bin_ref(), &get_font_bin_ref());
   thumbnail_with_label_renderer.set_thumbnail_image_identifier("storyboard-image-1164x500.png");
   thumbnail_with_label_renderer.set_label_text("CHAPTER 12: RISE OF THE CITY");
   thumbnail_with_label_renderer.render();
   al_flip_display();
   sleep_for(1);
}


TEST_F(AllegroFlare_Elements_ChapterSelect_CarouselElementRenderers_ThumbnailWithLabelUnlockableRendererTestWithAllegroRenderingFixture,
   CAPTURE__render__when_locked__will_render_as_expected)
{
   AllegroFlare::Elements::ChapterSelect::CarouselElementRenderers::ThumbnailWithLabelUnlockableRenderer
         thumbnail_with_label_renderer(&get_bitmap_bin_ref(), &get_font_bin_ref());
   thumbnail_with_label_renderer.set_thumbnail_image_identifier("storyboard-image-1164x500.png");
   thumbnail_with_label_renderer.set_label_text("CHAPTER 12: RISE OF THE CITY");
   thumbnail_with_label_renderer.set_locked_label_text("CHAPTER 12");
   thumbnail_with_label_renderer.set_is_unlocked(false);
   thumbnail_with_label_renderer.render();
   al_flip_display();
   sleep_for(1);
}


