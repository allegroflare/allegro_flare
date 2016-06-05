

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Internationalization
#include <boost/test/unit_test.hpp>




#include <allegro_flare/i18n.h>

#include <allegro5/allegro.h>




struct Fixture
{
   Fixture()
   {
      BOOST_REQUIRE_EQUAL(false, al_is_system_installed());
      BOOST_REQUIRE_EQUAL(true, al_init());

      ALLEGRO_PATH *resource_path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
      al_change_directory(al_path_cstr(resource_path, ALLEGRO_NATIVE_PATH_SEP));
      al_destroy_path(resource_path);
   }
   ~Fixture()
   {
      al_uninstall_system();
   }
};




BOOST_FIXTURE_TEST_CASE(has_the_proper_files_and_folders_for_testing, Fixture)
{
   BOOST_REQUIRE_EQUAL(true, al_filename_exists("data/languages/"));
   BOOST_REQUIRE_EQUAL(true, al_filename_exists("data/languages/tests/en.txt"));
   BOOST_REQUIRE_EQUAL(true, al_filename_exists("data/languages/tests/fr.txt"));
   BOOST_REQUIRE_EQUAL(true, al_filename_exists("data/languages/tests/it.txt"));
}




BOOST_AUTO_TEST_CASE(can_set_a_languages_folder)
{
   // TODO
}




BOOST_AUTO_TEST_CASE(returns_false_when_trying_to_set_a_languages_folder_that_does_not_exist)
{
   // TODO
}




BOOST_AUTO_TEST_CASE(can_set_a_locale)
{
   // TODO
}




BOOST_AUTO_TEST_CASE(returns_false_when_a_trying_to_set_a_locale_does_not_exist)
{
   // TODO
}




BOOST_AUTO_TEST_CASE(initialized_its_languages_folder_to__data_slash_languages__by_default)
{
   // TODO
}




BOOST_AUTO_TEST_CASE(clears_the_locale_and_folder_if_a_file_is_loaded_manually)
{
   // TODO
}




