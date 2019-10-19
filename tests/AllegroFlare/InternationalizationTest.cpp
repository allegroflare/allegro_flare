

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Internationalization
#include <boost/test/unit_test.hpp>




#include <allegro_flare/i18n.h>

#include <allegro5/allegro.h>




using namespace allegro_flare;




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

      Internationalization::initialize();
   }

   ~Fixture()
   {
      Internationalization::destruct();

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
   BOOST_CHECK_EQUAL(true, Internationalization::set_languages_folder(TEST_FOLDER));
   BOOST_CHECK_EQUAL(TEST_FOLDER, Internationalization::get_languages_folder());
}




BOOST_FIXTURE_TEST_CASE(initialized_its_languages_folder_to__data_slash_languages__by_default, Fixture)
{
   BOOST_CHECK_EQUAL("data/languages/", Internationalization::get_languages_folder());
}




BOOST_FIXTURE_TEST_CASE(returns_false_when_trying_to_set_a_languages_folder_that_does_not_exist, Fixture)
{
   std::string fake_folder = "foo/dir/that/doesnt/exist/";
   BOOST_CHECK_EQUAL(false, Internationalization::set_languages_folder(fake_folder));
}




BOOST_FIXTURE_TEST_CASE(returns_a_list_of_language_files_in_the_languages_folder, Fixture)
{
   Internationalization::set_languages_folder(TEST_FOLDER);

   std::vector<std::string> expected_files = {"en.txt", "fr.txt", "it.txt"};
   std::vector<std::string> returned_files = Internationalization::get_language_filenames();

   BOOST_CHECK_EQUAL_COLLECTIONS(expected_files.begin(), expected_files.end(),
      returned_files.begin(), returned_files.end());
}




BOOST_FIXTURE_TEST_CASE(finds_a_language_file_by_language_designator, Fixture)
{
   Internationalization::set_languages_folder(TEST_FOLDER);
   std::string expected_filename = "";

   expected_filename = "data/languages/tests/en.txt";
   BOOST_CHECK_EQUAL(expected_filename, Internationalization::find_language_file("en"));

   expected_filename = "data/languages/tests/fr.txt";
   BOOST_CHECK_EQUAL(expected_filename, Internationalization::find_language_file("fr"));

   expected_filename = "data/languages/tests/it.txt";
   BOOST_CHECK_EQUAL(expected_filename, Internationalization::find_language_file("it"));
}




BOOST_FIXTURE_TEST_CASE(returns_an_empty_string_when_a_language_file_cannot_be_found, Fixture)
{
   Internationalization::set_languages_folder(TEST_FOLDER);

   BOOST_CHECK_EQUAL("", Internationalization::find_language_file("language_designator_that_doesnt_exist"));
}




BOOST_FIXTURE_TEST_CASE(returns_true_when_a_language_file_loads_successfully, Fixture)
{
   BOOST_CHECK_EQUAL(true, Internationalization::load_language_file("en", "English", "data/languages/tests/en.txt"));
   BOOST_CHECK_EQUAL(true, Internationalization::load_language_file("fr", "French", "data/languages/tests/fr.txt"));
   BOOST_CHECK_EQUAL(true, Internationalization::load_language_file("it", "Italian", "data/languages/tests/it.txt"));
}




BOOST_FIXTURE_TEST_CASE(sets_the_language_designator_and_language_name_when_loading_a_language_file, Fixture)
{
   Internationalization::load_language_file("en", "English", "data/languages/tests/en.txt");
   BOOST_CHECK_EQUAL("en", Internationalization::get_language());
   BOOST_CHECK_EQUAL("English", Internationalization::get_language_name());

   Internationalization::load_language_file("fr", "French", "data/languages/tests/fr.txt");
   BOOST_CHECK_EQUAL("fr", Internationalization::get_language());
   BOOST_CHECK_EQUAL("French", Internationalization::get_language_name());

   Internationalization::load_language_file("it", "Italian", "data/languages/tests/it.txt");
   BOOST_CHECK_EQUAL("it", Internationalization::get_language());
   BOOST_CHECK_EQUAL("Italian", Internationalization::get_language_name());
}




BOOST_FIXTURE_TEST_CASE(returns_false_when_unable_to_load_a_language_file, Fixture)
{
   BOOST_CHECK_EQUAL(false, Internationalization::load_language_file("foo", "Fooanese", "foo/folder/file_that_doesnt_exist.txt"));
}




BOOST_FIXTURE_TEST_CASE(successfully_populates_labels_when_loading_a_language_file, Fixture)
{
   BOOST_REQUIRE_EQUAL(true, Internationalization::load_language_file("en", "English", "data/languages/tests/en.txt"));

   BOOST_CHECK_EQUAL("Welcome to Allegro!", Internationalization::t("welcome_message"));
   BOOST_CHECK_EQUAL("start", Internationalization::t("start_button"));
}




BOOST_FIXTURE_TEST_CASE(can_set_a_language, Fixture)
{
   Internationalization::set_languages_folder(TEST_FOLDER);

   BOOST_CHECK_EQUAL(true, Internationalization::set_language("en"));
   BOOST_CHECK_EQUAL(true, Internationalization::set_language("fr"));
   BOOST_CHECK_EQUAL(true, Internationalization::set_language("it"));
}




BOOST_FIXTURE_TEST_CASE(returns_false_when_unable_to_set_a_language, Fixture)
{
   Internationalization::set_languages_folder(TEST_FOLDER);

   BOOST_CHECK_EQUAL(false, Internationalization::set_language("not_a_language"));
}




BOOST_FIXTURE_TEST_CASE(can_retrieve_the_current_language_designator, Fixture)
{
   Internationalization::set_languages_folder(TEST_FOLDER);

   Internationalization::set_language("en");
   BOOST_CHECK_EQUAL("en", Internationalization::get_language());

   Internationalization::set_language("fr");
   BOOST_CHECK_EQUAL("fr", Internationalization::get_language());

   Internationalization::set_language("it");
   BOOST_CHECK_EQUAL("it", Internationalization::get_language());
}




BOOST_FIXTURE_TEST_CASE(loads_translations_when_a_language_designator_is_set, Fixture)
{
   Internationalization::set_languages_folder(TEST_FOLDER);

   Internationalization::set_language("en");
   BOOST_CHECK_EQUAL("Welcome to Allegro!", Internationalization::t("welcome_message"));
   BOOST_CHECK_EQUAL("start", Internationalization::t("start_button"));

   Internationalization::set_language("fr");
   BOOST_CHECK_EQUAL("Bienvenue à Allegro!", Internationalization::t("welcome_message"));
   BOOST_CHECK_EQUAL("démarrer", Internationalization::t("start_button"));

   Internationalization::set_language("it");
   BOOST_CHECK_EQUAL("Benvenuti a Allegro!", Internationalization::t("welcome_message"));
   BOOST_CHECK_EQUAL("inizio", Internationalization::t("start_button"));
}




BOOST_FIXTURE_TEST_CASE(knows_if_a_translation_label_exists_or_not, Fixture)
{
   Internationalization::set_languages_folder(TEST_FOLDER);
   Internationalization::set_language("en");

   BOOST_CHECK_EQUAL(true, Internationalization::t_exists("blank_content"));
   BOOST_CHECK_EQUAL(false, Internationalization::t_exists("label_that_does_not_exist"));
}




BOOST_FIXTURE_TEST_CASE(returns_an_empty_string_when_a_translation_is_blank_or_does_not_exist_for_that_label, Fixture)
{
   Internationalization::set_languages_folder(TEST_FOLDER);
   Internationalization::set_language("en");

   BOOST_CHECK_EQUAL("", Internationalization::t("blank_content"));
   BOOST_CHECK_EQUAL("", Internationalization::t("label_that_does_not_exist"));
}




BOOST_FIXTURE_TEST_CASE(formats_a_translation_with_variable_args, Fixture)
{
   Internationalization::set_languages_folder(TEST_FOLDER);

   Internationalization::set_language("en");
   BOOST_CHECK_EQUAL("Travel time is 6 hours and 45 minutes.", Internationalization::tf("travel_time", 6, 45));
   BOOST_CHECK_EQUAL("Nice to meet you, Alex.", Internationalization::tf("greeting", "Alex"));

   Internationalization::set_language("fr");
   BOOST_CHECK_EQUAL("Voyage de temps est de 6 heures et 45 minutes.", Internationalization::tf("travel_time", 6, 45));
   BOOST_CHECK_EQUAL("Ravi de vous rencontrer, Alex.", Internationalization::tf("greeting", "Alex"));

   Internationalization::set_language("it");
   BOOST_CHECK_EQUAL("Il tempo di percorrenza è di 6 ore e 45 minuti.", Internationalization::tf("travel_time", 6, 45));
   BOOST_CHECK_EQUAL("Piacere di conoscerti, Alex.", Internationalization::tf("greeting", "Alex"));
}




