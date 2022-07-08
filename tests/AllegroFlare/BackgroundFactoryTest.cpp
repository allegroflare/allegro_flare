
#include <gtest/gtest.h>

#include <AllegroFlare/BackgroundFactory.hpp>

TEST(AllegroFlare_BackgroundFactoryTest, can_be_created_without_blowing_up)
{
   AllegroFlare::BackgroundFactory background_factory;
}


TEST(AllegroFlare_BackgroundFactoryTest, create_monoplex__creates_a_monoplex_background_with_the_expected_properties)
{
   AllegroFlare::BitmapBin bitmap_bin;
   AllegroFlare::BackgroundFactory background_factory(&bitmap_bin);

   AllegroFlare::Backgrounds::Monoplex* created_monoplex = background_factory.create_monoplex();

   ASSERT_NE(nullptr, created_monoplex);
   EXPECT_EQ("Monoplex", created_monoplex->get_type());
}


TEST(AllegroFlare_BackgroundFactoryTest, create_image__creates_an_image_type_background_with_the_expected_properties)
{
   AllegroFlare::BitmapBin bitmap_bin;
   AllegroFlare::BackgroundFactory background_factory(&bitmap_bin);

   AllegroFlare::Backgrounds::Image* created_image_background = background_factory.create_image();

   ASSERT_NE(nullptr, created_image_background);
   EXPECT_EQ("Image", created_image_background->get_type());
}


