
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#ifdef _WIN32
#define TEST_FIXTURE_FONT_FOLDER "/msys64/home/Mark/Repos/allegro_flare/bin/data/fonts/"
#define TEST_FIXTURE_BITMAP_FOLDER "/msys64/home/Mark/Repos/allegro_flare/bin/data/bitmaps/"
#else
#define TEST_FIXTURE_FONT_FOLDER "/Users/markoates/Repos/allegro_flare/bin/data/fonts/"
#define TEST_FIXTURE_BITMAP_FOLDER "/Users/markoates/Repos/allegro_flare/bin/data/bitmaps/"
#endif

#include <AllegroFlare/Elements/DialogBoxRenderers/YouGotEvidenceRenderer.hpp>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <chrono>
#include <thread>

class AllegroFlare_Elements_DialogBoxRenderers_YouGotEvidenceRendererTest : public ::testing::Test {};
class AllegroFlare_Elements_DialogBoxRenderers_YouGotEvidenceRendererWithAllegroRenderingFixtureTest
   : public AllegroFlare::Testing::WithAllegroRenderingFixture {};


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_YouGotEvidenceRendererTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::DialogBoxRenderers::YouGotEvidenceRenderer you_got_evidence_renderer;
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_YouGotEvidenceRendererWithAllegroRenderingFixtureTest,
   CAPTURE__render__when_the_dialog_is_fully_revealed__renders_as_expected)
{
   get_font_bin_ref().set_full_path(TEST_FIXTURE_FONT_FOLDER);
   get_bitmap_bin_ref().set_full_path(TEST_FIXTURE_BITMAP_FOLDER);

   AllegroFlare::Placement2D place{ 1920/2, 1080/4*2, 1200, 540 };
   std::string evidence_name = "Standard Issue Blaster";
   std::string evidence_bitmap_identifier = "evidence-placeholder-480x300.png";
   float age = 5.0;

   al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 1});
   place.start_transform();
   AllegroFlare::Elements::DialogBoxRenderers::YouGotEvidenceRenderer you_got_evidence_renderer(
      &get_font_bin_ref(),
      &get_bitmap_bin_ref(),
      evidence_name,
      evidence_bitmap_identifier,
      age,
      place.size.x,
      place.size.y
   );
   you_got_evidence_renderer.render();
   place.restore_transform();
   al_flip_display();
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_YouGotEvidenceRendererWithAllegroRenderingFixtureTest,
   DISABLED__VISUAL__render__renders_the_dialog_box)
   //DISABLED__render__renders_the_dialog_box)
{
   get_font_bin_ref().set_full_path(TEST_FIXTURE_FONT_FOLDER);
   get_bitmap_bin_ref().set_full_path(TEST_FIXTURE_BITMAP_FOLDER);

   AllegroFlare::Placement2D place{ 1920/2, 1080/4*2, 1200, 540 };
   std::string evidence_name = "Standard Issue Blaster";
   std::string evidence_bitmap_identifier = "evidence-placeholder-480x300.png";
   float age = 0.0;

   int passes = 60*2;
   for (unsigned i=0; i<passes; i++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 1});
      place.start_transform();
      AllegroFlare::Elements::DialogBoxRenderers::YouGotEvidenceRenderer you_got_evidence_renderer(
         &get_font_bin_ref(),
         &get_bitmap_bin_ref(),
         evidence_name,
         evidence_bitmap_identifier,
         age,
         place.size.x,
         place.size.y
      );
      you_got_evidence_renderer.render();
      place.restore_transform();
      al_flip_display();
      std::this_thread::sleep_for(std::chrono::milliseconds(1000/60));
      age += 1.0/60.0f;
   }
}


