

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE UIButtonTest
#include <boost/test/unit_test.hpp>




#include <allegro_flare/framework.h>
#include <allegro_flare/gui/widgets/button.h>




struct Fixture
{
   Fixture()
   {
      Framework::initialize();
   }
   ~Fixture()
   {
      Framework::destruct();
   }
};




BOOST_FIXTURE_TEST_CASE(correctly_sets_its_widget_typename, Fixture)
{
   UIButton button = UIButton(NULL, 0, 0, 10, 10, "Hello");
   BOOST_CHECK_EQUAL("UIButton", button.attr.get(UI_ATTR__UI_WIDGET_TYPE));
}




BOOST_FIXTURE_TEST_CASE(sets_and_gets_the_text, Fixture)
{
   UIButton button = UIButton(NULL, 0, 0, 10, 10, "Hello");
   BOOST_CHECK_EQUAL("Hello", button.get_text());
   button.set_text("foo");
   BOOST_CHECK_EQUAL("foo", button.get_text());
}




