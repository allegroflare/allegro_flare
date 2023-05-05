
#include <gtest/gtest.h>

#include <AllegroFlare/Shaders/Multitexture.hpp>


class AllegroFlare_Shaders_MultitextureTest : public ::testing::Test {};

class AllegroFlare_Shaders_MultitextureTestWithSetup : public ::testing::Test
{
protected:
   ALLEGRO_DISPLAY *display;

   AllegroFlare_Shaders_MultitextureTestWithSetup()
      : display(nullptr)
   {
   }

   virtual void SetUp() override
   {
      ASSERT_EQ(false, al_is_system_installed());
      ASSERT_EQ(true, al_init());

      al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_PROGRAMMABLE_PIPELINE);
      ASSERT_EQ(ALLEGRO_OPENGL, al_get_new_display_flags() & ALLEGRO_OPENGL);
      ASSERT_EQ(ALLEGRO_PROGRAMMABLE_PIPELINE, al_get_new_display_flags() & ALLEGRO_PROGRAMMABLE_PIPELINE);
      ALLEGRO_DISPLAY *display = al_create_display(800, 600);
      ASSERT_NE(nullptr, display);
   }

   virtual void TearDown() override
   {
      if (al_get_current_display()) al_destroy_display(al_get_current_display());
      al_uninstall_system();
   }

   ALLEGRO_DISPLAY *get_display()
   {
      return display;
   }
};


TEST_F(AllegroFlare_Shaders_MultitextureTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Shaders::Multitexture multitexture;
}


TEST_F(AllegroFlare_Shaders_MultitextureTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/Shaders/Multitexture",
     AllegroFlare::Shaders::Multitexture::TYPE
   );
}


TEST_F(AllegroFlare_Shaders_MultitextureTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Shaders::Multitexture multitexture;
   EXPECT_EQ(AllegroFlare::Shaders::Multitexture::TYPE, multitexture.get_type());
}


TEST_F(AllegroFlare_Shaders_MultitextureTestWithSetup, when_active__will_render_model_as_expected)
{
   // TODO
}


