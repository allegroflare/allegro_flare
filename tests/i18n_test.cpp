

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Internationalization
#include <boost/test/unit_test.hpp>




#include <allegro_flare/i18n.h>

#include <allegro5/allegro.h>




struct Fixture
{
   const char *TEST_FOLDER = "data/languages/tests/";

   Fixture()
   {
      BOOST_REQUIRE_EQUAL(false, al_is_system_installed());
      BOOST_REQUIRE_EQUAL(true, al_init());

      ALLEGRO_PATH *resource_path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
      al_change_directory(al_path_cstr(resource_path, ALLEGRO_NATIVE_PATH_SEP));
      al_destroy_path(resource_path);

      I18n::initialize();
   }

   ~Fixture()
   {
      I18n::destruct();

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




BOOST_FIXTURE_TEST_CASE(can_set_a_languages_folder, Fixture)
{
   BOOST_CHECK_EQUAL(true, I18n::set_languages_folder(TEST_FOLDER));
   BOOST_CHECK_EQUAL(TEST_FOLDER, I18n::get_languages_folder());
}




BOOST_FIXTURE_TEST_CASE(initialized_its_languages_folder_to__data_slash_languages__by_default, Fixture)
{
   BOOST_CHECK_EQUAL("data/languages/", I18n::get_languages_folder());
}




BOOST_FIXTURE_TEST_CASE(returns_false_when_trying_to_set_a_languages_folder_that_does_not_exist, Fixture)
{
   std::string fake_folder = "foo/dir/that/doesnt/exist/";
   BOOST_CHECK_EQUAL(false, I18n::set_languages_folder(fake_folder));
}




BOOST_FIXTURE_TEST_CASE(returns_a_list_of_language_files_in_the_languages_folder, Fixture)
{
   I18n::set_languages_folder(TEST_FOLDER);

   std::vector<std::string> expected_files = {"en.txt", "fr.txt", "it.txt"};
   std::vector<std::string> returned_files = I18n::get_language_filenames();

   BOOST_CHECK_EQUAL_COLLECTIONS(expected_files.begin(), expected_files.end(),
      returned_files.begin(), returned_files.end());
}




BOOST_FIXTURE_TEST_CASE(finds_a_language_file_by_locale, Fixture)
{
   I18n::set_languages_folder(TEST_FOLDER);
   std::string expected_filename = "";

   expected_filename = "data/languages/tests/en.txt";
   BOOST_CHECK_EQUAL(expected_filename, I18n::find_language_file("en"));

   expected_filename = "data/languages/tests/fr.txt";
   BOOST_CHECK_EQUAL(expected_filename, I18n::find_language_file("fr"));

   expected_filename = "data/languages/tests/it.txt";
   BOOST_CHECK_EQUAL(expected_filename, I18n::find_language_file("it"));
}




BOOST_FIXTURE_TEST_CASE(returns_an_empty_string_when_a_language_file_cannot_be_found, Fixture)
{
   I18n::set_languages_folder(TEST_FOLDER);

   BOOST_CHECK_EQUAL("", I18n::find_language_file("locale_that_doesnt_exist"));
}




BOOST_FIXTURE_TEST_CASE(returns_true_when_a_language_file_loads_successfully, Fixture)
{
   BOOST_CHECK_EQUAL(true, I18n::load_language_file("data/languages/tests/en.txt"));
   BOOST_CHECK_EQUAL(true, I18n::load_language_file("data/languages/tests/fr.txt"));
   BOOST_CHECK_EQUAL(true, I18n::load_language_file("data/languages/tests/it.txt"));
}




BOOST_FIXTURE_TEST_CASE(returns_false_when_unable_to_load_a_language_file, Fixture)
{
   BOOST_CHECK_EQUAL(false, I18n::load_language_file("foo/folder/file_that_doesnt_exist.txt"));
}




BOOST_FIXTURE_TEST_CASE(successfully_populates_labels_when_loading_a_language_file, Fixture)
{
   BOOST_REQUIRE_EQUAL(true, I18n::load_language_file("data/languages/tests/en.txt"));

   BOOST_CHECK_EQUAL("Welcome to Allegro!", I18n::t("welcome_message"));
   BOOST_CHECK_EQUAL("start", I18n::t("start_button"));
}




BOOST_AUTO_TEST_CASE(clears_the_locale_and_folder_if_a_file_is_loaded_manually)
{
   // TODO
}




