
#include <gtest/gtest.h>

#include <AllegroFlare/SavingAndLoading/EmptySaveSlotRenderer.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_SavingAndLoading_EmptySaveSlotRendererTest
   : public ::testing::Test
{};
class AllegroFlare_SavingAndLoading_EmptySaveSlotRendererTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


TEST_F(AllegroFlare_SavingAndLoading_EmptySaveSlotRendererTest, can_be_created_without_blowing_up)
{
   AllegroFlare::SavingAndLoading::EmptySaveSlotRenderer empty_save_slot_renderer;
}


TEST_F(AllegroFlare_SavingAndLoading_EmptySaveSlotRendererTestWithAllegroRenderingFixture,
   CAPTURE__render__will_draw_the_save_slot)
{
   AllegroFlare::SavingAndLoading::EmptySaveSlotRenderer empty_save_slot_renderer;
   empty_save_slot_renderer.set_bitmap_bin(&get_bitmap_bin_ref());
   empty_save_slot_renderer.set_font_bin(&get_font_bin_ref());
   empty_save_slot_renderer.render();
   al_flip_display();
   al_rest(1);
}


