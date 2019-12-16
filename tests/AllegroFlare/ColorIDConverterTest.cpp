

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE AllegroFlare_ColorIDConverter
#include <boost/test/unit_test.hpp>




#include <AllegroFlare/ColorIDConverter.hpp>




using namespace AllegroFlare;




struct Setup
{
   Setup()
   {
      BOOST_REQUIRE_EQUAL(false, al_is_system_installed());
      BOOST_REQUIRE_EQUAL(true, al_init());
   }
   ~Setup()
   {
      al_uninstall_system();
   }
};




BOOST_FIXTURE_TEST_CASE(decodes_transparent_to_ID_0, Setup)
{
   ALLEGRO_COLOR color = al_map_rgba(0, 0, 0, 0);
   int decoded_id = ColorIDConverter::decode_id(color);

   BOOST_CHECK_EQUAL(0, decoded_id);
}




BOOST_FIXTURE_TEST_CASE(encodes_ID_0_to_transparent, Setup)
{
   ALLEGRO_COLOR color = ColorIDConverter::encode_id(0);

   unsigned char r, g, b, a;
   al_unmap_rgba(color, &r, &g, &b, &a);

   BOOST_CHECK_EQUAL(0, r);
   BOOST_CHECK_EQUAL(0, g);
   BOOST_CHECK_EQUAL(0, b);
   BOOST_CHECK_EQUAL(0, a);
}




BOOST_FIXTURE_TEST_CASE(encodes_IDs_greater_than_0_with_an_alpha_of_255__test_1, Setup)
{
   ALLEGRO_COLOR color = ColorIDConverter::encode_id(1);

   unsigned char r, g, b, a;
   al_unmap_rgba(color, &r, &g, &b, &a);

   BOOST_CHECK_EQUAL(255, a);
}




BOOST_FIXTURE_TEST_CASE(encodes_IDs_greater_than_0_with_an_alpha_of_255__test_2, Setup)
{
   for (unsigned i=1; i<1000; i++)
   {
      ALLEGRO_COLOR color = ColorIDConverter::encode_id(i);
      unsigned char r, g, b, a;
      al_unmap_rgba(color, &r, &g, &b, &a);

      BOOST_CHECK_EQUAL(255, a);
   }
}




BOOST_FIXTURE_TEST_CASE(encodes_all_numbers_less_than_ColorIDConverter_ID_MAX, Setup)
{
   for (int i=0; i<ColorIDConverter::ID_MAX; i++)
   {
      int encoded_num = ColorIDConverter::decode_id(ColorIDConverter::encode_id(i));
      BOOST_CHECK_EQUAL(i, encoded_num);
   }
}




BOOST_FIXTURE_TEST_CASE(does_not_encode_numbers_greater_than_or_equal_to_ColorIDConverter_ID_MAX, Setup)
{
   int encoded_num = 0;
   int expected_num = 0;

   encoded_num = ColorIDConverter::decode_id(ColorIDConverter::encode_id(ColorIDConverter::ID_MAX));
   expected_num = ColorIDConverter::ID_MAX;
   BOOST_CHECK_NE(expected_num, encoded_num);

   encoded_num = ColorIDConverter::decode_id(ColorIDConverter::encode_id(ColorIDConverter::ID_MAX+1));
   expected_num = ColorIDConverter::ID_MAX+1;
   BOOST_CHECK_NE(expected_num, encoded_num);
}




BOOST_FIXTURE_TEST_CASE(does_not_encode_negative_numbers, Setup)
{
   int encoded_num = ColorIDConverter::decode_id(ColorIDConverter::encode_id(-1));
   BOOST_CHECK_NE(-1, encoded_num);
}




