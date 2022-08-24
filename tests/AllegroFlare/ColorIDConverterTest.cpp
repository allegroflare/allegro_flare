

#include <gtest/gtest.h>

#include <AllegroFlare/ColorIDConverter.hpp>


struct AllegroFlare_ColorIDConverterTest : public ::testing::Test
{
   virtual void SetUp() override
   {
      ASSERT_EQ(false, al_is_system_installed());
      ASSERT_EQ(true, al_init());
   }

   virtual void TearDown() override
   {
      al_uninstall_system();
   }
};


TEST_F(AllegroFlare_ColorIDConverterTest, decodes_transparent_to_ID_0)
{
   ALLEGRO_COLOR color = al_map_rgba(0, 0, 0, 0);
   int decoded_id = AllegroFlare::ColorIDConverter::decode_id(color);

   EXPECT_EQ(0, decoded_id);
}


TEST_F(AllegroFlare_ColorIDConverterTest, encodes_ID_0_to_transparent)
{
   ALLEGRO_COLOR color = AllegroFlare::ColorIDConverter::encode_id(0);

   unsigned char r, g, b, a;
   al_unmap_rgba(color, &r, &g, &b, &a);

   EXPECT_EQ(0, r);
   EXPECT_EQ(0, g);
   EXPECT_EQ(0, b);
   EXPECT_EQ(0, a);
}


TEST_F(AllegroFlare_ColorIDConverterTest, encodes_IDs_greater_than_0_with_an_alpha_of_255__test_1)
{
   ALLEGRO_COLOR color = AllegroFlare::ColorIDConverter::encode_id(1);

   unsigned char r, g, b, a;
   al_unmap_rgba(color, &r, &g, &b, &a);

   EXPECT_EQ(255, a);
}


TEST_F(AllegroFlare_ColorIDConverterTest, encodes_IDs_greater_than_0_with_an_alpha_of_255__test_2)
{
   for (unsigned i=1; i<1000; i++)
   {
      ALLEGRO_COLOR color = AllegroFlare::ColorIDConverter::encode_id(i);
      unsigned char r, g, b, a;
      al_unmap_rgba(color, &r, &g, &b, &a);

      EXPECT_EQ(255, a);
   }
}


TEST_F(AllegroFlare_ColorIDConverterTest, encodes_all_numbers_less_than_ColorIDConverter_ID_MAX)
{
   for (int i=0; i<AllegroFlare::ColorIDConverter::ID_MAX; i++)
   {
      int encoded_num = AllegroFlare::ColorIDConverter::decode_id(AllegroFlare::ColorIDConverter::encode_id(i));
      EXPECT_EQ(i, encoded_num);
   }
}


TEST_F(AllegroFlare_ColorIDConverterTest, does_not_encode_numbers_greater_than_or_equal_to_ColorIDConverter_ID_MAX)
{
   int encoded_num = 0;
   int expected_num = 0;

   encoded_num = AllegroFlare::ColorIDConverter::decode_id(
      AllegroFlare::ColorIDConverter::encode_id(AllegroFlare::ColorIDConverter::ID_MAX)
   );
   expected_num = AllegroFlare::ColorIDConverter::ID_MAX;
   EXPECT_NE(expected_num, encoded_num);

   encoded_num = AllegroFlare::ColorIDConverter::decode_id(
      AllegroFlare::ColorIDConverter::encode_id(AllegroFlare::ColorIDConverter::ID_MAX+1)
   );
   expected_num = AllegroFlare::ColorIDConverter::ID_MAX+1;
   EXPECT_NE(expected_num, encoded_num);
}


TEST_F(AllegroFlare_ColorIDConverterTest, does_not_encode_negative_numbers)
{
   int encoded_num = AllegroFlare::ColorIDConverter::decode_id(AllegroFlare::ColorIDConverter::encode_id(-1));
   EXPECT_NE(-1, encoded_num);
}


