


#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE AllegroColorAttributeDatatypeTestModule
#include <boost/test/unit_test.hpp>



#include <allegro_flare/attributes.h>
#include <allegro_flare/allegro_color_attribute_datatype.h>



BOOST_AUTO_TEST_CASE(allegro_color_custom_attribute_can_set_and_get_an_allegro_color)
{
   Attributes attributes;

   attributes.create_datatype_definition(
      AllegroColorAttributeDatatype::IDENTIFIER,
      AllegroColorAttributeDatatype::to_val_func,
      AllegroColorAttributeDatatype::to_str_func
   );

   ALLEGRO_COLOR color_1 = al_map_rgba_f(0.123, 0.357, 0.876, 0.926);
   ALLEGRO_COLOR color_2 = al_map_rgb(0, 0, 0);

   BOOST_CHECK_EQUAL(true, attributes.set("the_color", AllegroColorAttributeDatatype::IDENTIFIER, &color_1));
   BOOST_CHECK_EQUAL(true, attributes.get_as_custom(&color_2, AllegroColorAttributeDatatype::IDENTIFIER, "the_color"));
   BOOST_CHECK_CLOSE(0.123, color_2.r, 0.0001);
   BOOST_CHECK_CLOSE(0.357, color_2.g, 0.0001);
   BOOST_CHECK_CLOSE(0.876, color_2.b, 0.0001);
   BOOST_CHECK_CLOSE(0.926, color_2.a, 0.0001);
}



BOOST_AUTO_TEST_CASE(allegro_color_custom_attribute_has_the_expected_identifier)
{
   BOOST_CHECK_EQUAL("ALLEGRO_COLOR", AllegroColorAttributeDatatype::IDENTIFIER);
}



