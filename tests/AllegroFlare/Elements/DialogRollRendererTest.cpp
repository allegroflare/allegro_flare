
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Testing/ErrorAssertions.hpp>


class AllegroFlare_Elements_DialogRollRendererTest : public ::testing::Test
{};

class AllegroFlare_Elements_DialogRollRendererTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Elements/DialogRollRenderer.hpp>


TEST_F(AllegroFlare_Elements_DialogRollRendererTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::DialogRollRenderer dialog_roll_renderer;
}


TEST_F(AllegroFlare_Elements_DialogRollRendererTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::DialogRollRenderer dialog_roll_renderer;
   EXPECT_THROW_GUARD_ERROR(
      dialog_roll_renderer.render(),
      "AllegroFlare::Elements::DialogRollRenderer::render",
      "al_is_system_installed()"
   );
}


TEST_F(AllegroFlare_Elements_DialogRollRendererTestWithAllegroRenderingFixture,
   DISABLED__render__without_a_font_bin__will_throw_an_error)
{
   // TODO
}


TEST_F(AllegroFlare_Elements_DialogRollRendererTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   AllegroFlare::Elements::DialogRollRenderer dialog_roll_renderer(&get_font_bin_ref());
   dialog_roll_renderer.render();
}


TEST_F(AllegroFlare_Elements_DialogRollRendererTestWithAllegroRenderingFixture,
   CAPTURE__render__will_render_as_expected)
{
   AllegroFlare::Elements::DialogRollRenderer dialog_roll_renderer(&get_font_bin_ref(), {
      { "Alice", "This is some dialog." },
      { "Bob",   "This is some dialog, too." },
      { "",      "I feel like I've heard this one before. Not to mention there's probably "
                 "going to be a multiline version." },
   });

   AllegroFlare::Placement2D place = build_centered_placement(dialog_roll_renderer.get_width(), 500);
   clear();
   place.start_transform();
   dialog_roll_renderer.render();
   place.restore_transform();
   al_flip_display();
}


