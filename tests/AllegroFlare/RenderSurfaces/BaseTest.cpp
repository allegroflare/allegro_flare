
#include <gtest/gtest.h>

#include <AllegroFlare/RenderSurfaces/Base.hpp>


class RenderSurfacesBaseTestClass : public AllegroFlare::RenderSurfaces::Base
{
private:
   ALLEGRO_BITMAP *surface;
   bool initialized;

public:
   RenderSurfacesBaseTestClass()
      : AllegroFlare::RenderSurfaces::Base("RenderSurfacesBaseTestClass")
      , surface(nullptr)
      , initialized(false)
   {}
   ~RenderSurfacesBaseTestClass() {};

   void initialize()
   {
      ALLEGRO_BITMAP *surface = al_create_bitmap(800, 600);
      initialized = true;
   }
   virtual bool set_as_target() override { return true; }
   virtual ALLEGRO_BITMAP* obtain_surface() override { return surface; }
   virtual int get_width() override { return 0; }
   virtual int get_height() override { return 0; }
};


class RenderSurfacesBase_Display_TestClass : public AllegroFlare::RenderSurfaces::Base
{
public:
   RenderSurfacesBase_Display_TestClass()
      : AllegroFlare::RenderSurfaces::Base("RenderSurfacesBase_Display_TestClass")
   {}
   ~RenderSurfacesBase_Display_TestClass() {};

   virtual bool set_as_target() override { return true; }
   virtual ALLEGRO_BITMAP* obtain_surface() override { return al_get_backbuffer(al_get_current_display()); }
   virtual int get_width() override { return 0; }
   virtual int get_height() override { return 0; }
};


class RenderSurfacesBase_DisplaySubBitmap_TestClass : public AllegroFlare::RenderSurfaces::Base
{
private:
   ALLEGRO_BITMAP *surface;
   bool initialized;

public:
   RenderSurfacesBase_DisplaySubBitmap_TestClass()
      : AllegroFlare::RenderSurfaces::Base("RenderSurfacesBase_DisplaySubBitmap_TestClass")
      , surface(nullptr)
      , initialized(false)
   {}
   ~RenderSurfacesBase_DisplaySubBitmap_TestClass() {};

   void initialize()
   {
      ALLEGRO_BITMAP *backbuffer = al_get_backbuffer(al_get_current_display());
      surface = al_create_sub_bitmap(backbuffer, 0, 0, al_get_bitmap_width(backbuffer), al_get_bitmap_height(backbuffer));
   }
   virtual bool set_as_target() override { return true; }
   virtual ALLEGRO_BITMAP* obtain_surface() override { return surface; }
   virtual int get_width() override { return 0; }
   virtual int get_height() override { return 0; }
};


class RenderSurfacesBase_Bitmap_TestClass : public AllegroFlare::RenderSurfaces::Base
{
private:
   ALLEGRO_BITMAP *surface;
   bool initialized;

public:
   RenderSurfacesBase_Bitmap_TestClass()
      : AllegroFlare::RenderSurfaces::Base("RenderSurfacesBase_Bitmap_TestClass")
      , surface(nullptr)
      , initialized(false)
   {}
   ~RenderSurfacesBase_Bitmap_TestClass() {};

   void initialize()
   {
      ALLEGRO_BITMAP *surface = al_create_bitmap(800, 600);
      initialized = true;
   }
   virtual bool set_as_target() override { return true; }
   virtual ALLEGRO_BITMAP* obtain_surface() override { return surface; }
   virtual int get_width() override { return 0; }
   virtual int get_height() override { return 0; }
};



TEST(AllegroFlare_RenderSurfaces_BaseTest, derived_classes_can_be_created_without_blowing_up)
{
   RenderSurfacesBaseTestClass test_class;
}


TEST(AllegroFlare_RenderSurfaces_BaseTest, derived_classes_will_have_the_expected_type)
{
   RenderSurfacesBaseTestClass test_class;
   EXPECT_EQ("RenderSurfacesBaseTestClass", test_class.get_type());
}


TEST(AllegroFlare_RenderSurfaces_BaseTest,
   is_a_display_surface__when_the_surface_is_a_display_backbuffer__will_return_true)
{
   al_init();
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);

   RenderSurfacesBase_Display_TestClass display_test_class;
   EXPECT_EQ(true, display_test_class.is_a_display_surface());

   al_destroy_display(display);
   al_uninstall_system();
}


TEST(AllegroFlare_RenderSurfaces_BaseTest,
   is_a_display_surface__when_the_surface_is_a_sub_bitmap_of_a_display_backbuffer__will_return_true)
{
   al_init();
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);

   RenderSurfacesBase_DisplaySubBitmap_TestClass display_sub_bitmap_test_class;
   EXPECT_EQ(true, display_sub_bitmap_test_class.is_a_display_surface());

   al_destroy_display(display);
   al_uninstall_system();
}


TEST(AllegroFlare_RenderSurfaces_BaseTest,
   is_a_display_surface__when_the_surface_is_not_a_display_backbuffer__will_return_false)
{
   RenderSurfacesBase_Bitmap_TestClass bitmap_surface_test_class;
   EXPECT_EQ(false, bitmap_surface_test_class.is_a_display_surface());
}


TEST(AllegroFlare_RenderSurfaces_BaseTest,
   is_a_display_surface__when_the_surface_is_a_nullptr__will_throw_an_error)
{
   // TODO: Implement this test
   //al_init();
   //ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);

   //RenderSurfacesBase_DisplaySubBitmap_TestClass display_sub_bitmap_test_class;
   //EXPECT_EQ(true, display_sub_bitmap_test_class.is_a_display_surface());

   //al_destroy_display(display);
   //al_uninstall_system();
}


