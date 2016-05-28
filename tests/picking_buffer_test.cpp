

#define BOOST_TEST_MODULE UIIDPicker
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>


#include <allegro_flare/gui/widgets/picking_buffer.h>



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
   int decoded_id = UIPickingBuffer::decode_id(color);

   BOOST_CHECK_EQUAL(0, decoded_id);
}


BOOST_FIXTURE_TEST_CASE(encodes_ID_0_to_transparent, Setup)
{
   ALLEGRO_COLOR color = UIPickingBuffer::encode_id(0);

   unsigned char r, g, b, a;
   al_unmap_rgba(color, &r, &g, &b, &a);

   BOOST_CHECK_EQUAL(0, r);
   BOOST_CHECK_EQUAL(0, g);
   BOOST_CHECK_EQUAL(0, b);
   BOOST_CHECK_EQUAL(0, a);
}


BOOST_FIXTURE_TEST_CASE(encodes_IDs_greater_than_0_with_an_alpha_of_255__test_1, Setup)
{
   ALLEGRO_COLOR color = UIPickingBuffer::encode_id(1);

   unsigned char r, g, b, a;
   al_unmap_rgba(color, &r, &g, &b, &a);

   BOOST_CHECK_EQUAL(255, a);
}


BOOST_FIXTURE_TEST_CASE(encodes_IDs_greater_than_0_with_an_alpha_of_255__test_2, Setup)
{
   for (unsigned i=1; i<1000; i++)
   {
      ALLEGRO_COLOR color = UIPickingBuffer::encode_id(i);
      unsigned char r, g, b, a;
      al_unmap_rgba(color, &r, &g, &b, &a);

      BOOST_CHECK_EQUAL(255, a);
   }
}


BOOST_FIXTURE_TEST_CASE(encodes_all_numbers_less_than_UIPickingBuffer_ID_MAX, Setup)
{
   for (int i=0; i<UIPickingBuffer::ID_MAX; i++)
   {
      int encoded_num = UIPickingBuffer::decode_id(UIPickingBuffer::encode_id(i));
      BOOST_CHECK_EQUAL(i, encoded_num);
   }
}


BOOST_FIXTURE_TEST_CASE(does_not_encode_numbers_greater_than_or_equal_to_UIPickingBuffer_ID_MAX, Setup)
{
   int encoded_num = 0;
   int expected_num = 0;

   encoded_num = UIPickingBuffer::decode_id(UIPickingBuffer::encode_id(UIPickingBuffer::ID_MAX));
   expected_num = UIPickingBuffer::ID_MAX;
   BOOST_CHECK_NE(expected_num, encoded_num);

   encoded_num = UIPickingBuffer::decode_id(UIPickingBuffer::encode_id(UIPickingBuffer::ID_MAX+1));
   expected_num = UIPickingBuffer::ID_MAX+1;
   BOOST_CHECK_NE(expected_num, encoded_num);
}


BOOST_FIXTURE_TEST_CASE(does_not_encode_negative_numbers, Setup)
{
   int encoded_num = UIPickingBuffer::decode_id(UIPickingBuffer::encode_id(-1));
   BOOST_CHECK_NE(-1, encoded_num);
}


BOOST_AUTO_TEST_CASE(builds_an_on_click_id_message)
{
   BOOST_CHECK_EQUAL("on_click_id 42", UIPickingBuffer::compose_on_click_id_message(42));
   BOOST_CHECK_EQUAL("on_click_id 64", UIPickingBuffer::compose_on_click_id_message(64));
   BOOST_CHECK_EQUAL("on_click_id 3", UIPickingBuffer::compose_on_click_id_message(3));
}


BOOST_AUTO_TEST_CASE(extracts_an_id_from_an_on_click_id_message)
{
   BOOST_CHECK_EQUAL(42, UIPickingBuffer::extract_on_click_id("on_click_id 42"));
   BOOST_CHECK_EQUAL(64, UIPickingBuffer::extract_on_click_id("on_click_id 64"));
   BOOST_CHECK_EQUAL(3, UIPickingBuffer::extract_on_click_id("on_click_id 3"));
}


BOOST_AUTO_TEST_CASE(identifies_a_properly_formatted_on_click_id_message)
{
   BOOST_CHECK_EQUAL(true, UIPickingBuffer::is_on_click_id_message("on_click_id 9"));
   BOOST_CHECK_EQUAL(true, UIPickingBuffer::is_on_click_id_message("on_click_id 345678"));
   BOOST_CHECK_EQUAL(true, UIPickingBuffer::is_on_click_id_message("on_click_id 42"));

   BOOST_CHECK_EQUAL(false, UIPickingBuffer::is_on_click_id_message(""));
   BOOST_CHECK_EQUAL(false, UIPickingBuffer::is_on_click_id_message("foo bar"));
   BOOST_CHECK_EQUAL(false, UIPickingBuffer::is_on_click_id_message("on_click_id"));
   BOOST_CHECK_EQUAL(false, UIPickingBuffer::is_on_click_id_message("on_click_id9"));
}


