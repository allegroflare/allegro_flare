

//#define BOOST_TEST_DYN_LINK
//#define BOOST_TEST_MODULE Internationalization
//#include <boost/test/unit_test.hpp>




//#include <AllegroFlare/Internationalization.hpp>

//#include <allegro5/allegro.h>




//using namespace AllegroFlare;




//struct Fixture
//{
   //const char *TEST_FOLDER = "../../data/languages/tests/";
   //static Internationalization internationalization;

   //Fixture()
   //{
      //BOOST_REQUIRE_EQUAL(false, al_is_system_installed());
      //BOOST_REQUIRE_EQUAL(true, al_init());

      //ALLEGRO_PATH *resource_path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
      //al_change_directory(al_path_cstr(resource_path, ALLEGRO_NATIVE_PATH_SEP));
      //al_destroy_path(resource_path);

      //internationalization.set_languages_folder(TEST_FOLDER);
   //}

   //~Fixture()
   //{
      //al_uninstall_system();
   //}
//};

//Internationalization Fixture::internationalization;




//BOOST_FIXTURE_TEST_CASE(has_the_proper_files_and_folders_for_testing, Fixture)
//{
   //BOOST_REQUIRE_EQUAL(true, al_filename_exists("../../data/languages/"));
   //BOOST_REQUIRE_EQUAL(true, al_filename_exists("../../data/languages/tests/en.txt"));
   //BOOST_REQUIRE_EQUAL(true, al_filename_exists("../../data/languages/tests/fr.txt"));
   //BOOST_REQUIRE_EQUAL(true, al_filename_exists("../../data/languages/tests/it.txt"));
//}




//BOOST_FIXTURE_TEST_CASE(can_set_a_languages_folder, Fixture)
//{
   //BOOST_CHECK_EQUAL(true, Fixture::internationalization.set_languages_folder(TEST_FOLDER));
   //BOOST_CHECK_EQUAL(TEST_FOLDER, Fixture::internationalization.get_languages_folder());
//}




//BOOST_AUTO_TEST_CASE(initialized_its_languages_folder_to__data_slash_languages__by_default)
//{
   //Internationalization internationalization;
   //BOOST_CHECK_EQUAL("data/languages/", internationalization.get_languages_folder());
//}




//BOOST_FIXTURE_TEST_CASE(returns_false_when_trying_to_set_a_languages_folder_that_does_not_exist, Fixture)
//{
   //std::string fake_folder = "foo/dir/that/doesnt/exist/";
   //BOOST_CHECK_EQUAL(false, Fixture::internationalization.set_languages_folder(fake_folder));
//}




//BOOST_FIXTURE_TEST_CASE(returns_a_list_of_language_files_in_the_languages_folder, Fixture)
//{
   //std::vector<std::string> expected_files = {"en.txt", "fr.txt", "it.txt"};
   //std::vector<std::string> returned_files = internationalization.get_language_filenames();

   //BOOST_CHECK_EQUAL_COLLECTIONS(expected_files.begin(), expected_files.end(),
      //returned_files.begin(), returned_files.end());
//}




//BOOST_FIXTURE_TEST_CASE(finds_a_language_file_by_language_designator, Fixture)
//{
   //std::string expected_filename = "";

   //expected_filename = "../../data/languages/tests/en.txt";
   //BOOST_CHECK_EQUAL(expected_filename, internationalization.find_language_file("en"));

   //expected_filename = "../../data/languages/tests/fr.txt";
   //BOOST_CHECK_EQUAL(expected_filename, internationalization.find_language_file("fr"));

   //expected_filename = "../../data/languages/tests/it.txt";
   //BOOST_CHECK_EQUAL(expected_filename, internationalization.find_language_file("it"));
//}




//BOOST_FIXTURE_TEST_CASE(returns_an_empty_string_when_a_language_file_cannot_be_found, Fixture)
//{
   //BOOST_CHECK_EQUAL("", internationalization.find_language_file("language_designator_that_doesnt_exist"));
//}




//BOOST_FIXTURE_TEST_CASE(returns_true_when_a_language_file_loads_successfully, Fixture)
//{
   //BOOST_CHECK_EQUAL(true, internationalization.load_language_file("en", "English", "../../data/languages/tests/en.txt"));
   //BOOST_CHECK_EQUAL(true, internationalization.load_language_file("fr", "French", "../../data/languages/tests/fr.txt"));
   //BOOST_CHECK_EQUAL(true, internationalization.load_language_file("it", "Italian", "../../data/languages/tests/it.txt"));
//}




//BOOST_FIXTURE_TEST_CASE(sets_the_language_designator_and_language_name_when_loading_a_language_file, Fixture)
//{
   //internationalization.load_language_file("en", "English", "../../data/languages/tests/en.txt");
   //BOOST_CHECK_EQUAL("en", internationalization.get_language());
   //BOOST_CHECK_EQUAL("English", internationalization.get_language_name());

   //internationalization.load_language_file("fr", "French", "../../data/languages/tests/fr.txt");
   //BOOST_CHECK_EQUAL("fr", internationalization.get_language());
   //BOOST_CHECK_EQUAL("French", internationalization.get_language_name());

   //internationalization.load_language_file("it", "Italian", "../../data/languages/tests/it.txt");
   //BOOST_CHECK_EQUAL("it", internationalization.get_language());
   //BOOST_CHECK_EQUAL("Italian", internationalization.get_language_name());
//}




//BOOST_FIXTURE_TEST_CASE(returns_false_when_unable_to_load_a_language_file, Fixture)
//{
   //BOOST_CHECK_EQUAL(false, internationalization.load_language_file("foo", "Fooanese", "foo/folder/file_that_doesnt_exist.txt"));
//}




//BOOST_FIXTURE_TEST_CASE(successfully_populates_labels_when_loading_a_language_file, Fixture)
//{
   //BOOST_REQUIRE_EQUAL(true, internationalization.load_language_file("en", "English", "../../data/languages/tests/en.txt"));

   //BOOST_CHECK_EQUAL("Welcome to Allegro!", internationalization.t("welcome_message"));
   //BOOST_CHECK_EQUAL("start", internationalization.t("start_button"));
//}




//BOOST_FIXTURE_TEST_CASE(can_set_a_language, Fixture)
//{
   //BOOST_CHECK_EQUAL(true, internationalization.set_language("en"));
   //BOOST_CHECK_EQUAL(true, internationalization.set_language("fr"));
   //BOOST_CHECK_EQUAL(true, internationalization.set_language("it"));
//}




//BOOST_FIXTURE_TEST_CASE(returns_false_when_unable_to_set_a_language, Fixture)
//{
   //BOOST_CHECK_EQUAL(false, internationalization.set_language("not_a_language"));
//}




//BOOST_FIXTURE_TEST_CASE(can_retrieve_the_current_language_designator, Fixture)
//{
   //internationalization.set_language("en");
   //BOOST_CHECK_EQUAL("en", internationalization.get_language());

   //internationalization.set_language("fr");
   //BOOST_CHECK_EQUAL("fr", internationalization.get_language());

   //internationalization.set_language("it");
   //BOOST_CHECK_EQUAL("it", internationalization.get_language());
//}




//BOOST_FIXTURE_TEST_CASE(loads_translations_when_a_language_designator_is_set, Fixture)
//{
   //internationalization.set_language("en");
   //BOOST_CHECK_EQUAL("Welcome to Allegro!", internationalization.t("welcome_message"));
   //BOOST_CHECK_EQUAL("start", internationalization.t("start_button"));

   //internationalization.set_language("fr");
   //BOOST_CHECK_EQUAL("Bienvenue à Allegro!", internationalization.t("welcome_message"));
   //BOOST_CHECK_EQUAL("démarrer", internationalization.t("start_button"));

   //internationalization.set_language("it");
   //BOOST_CHECK_EQUAL("Benvenuti a Allegro!", internationalization.t("welcome_message"));
   //BOOST_CHECK_EQUAL("inizio", internationalization.t("start_button"));
//}




//BOOST_FIXTURE_TEST_CASE(knows_if_a_translation_label_exists_or_not, Fixture)
//{
   //internationalization.set_language("en");

   //BOOST_CHECK_EQUAL(true, internationalization.t_exists("blank_content"));
   //BOOST_CHECK_EQUAL(false, internationalization.t_exists("label_that_does_not_exist"));
//}




//BOOST_FIXTURE_TEST_CASE(returns_an_empty_string_when_a_translation_is_blank_or_does_not_exist_for_that_label, Fixture)
//{
   //internationalization.set_language("en");

   //BOOST_CHECK_EQUAL("", internationalization.t("blank_content"));
   //BOOST_CHECK_EQUAL("", internationalization.t("label_that_does_not_exist"));
//}




//BOOST_FIXTURE_TEST_CASE(formats_a_translation_with_variable_args, Fixture)
//{
   //internationalization.set_language("en");
   //BOOST_CHECK_EQUAL("Travel time is 6 hours and 45 minutes.", internationalization.tf("travel_time", 6, 45));
   //BOOST_CHECK_EQUAL("Nice to meet you, Alex.", internationalization.tf("greeting", "Alex"));

   //internationalization.set_language("fr");
   //BOOST_CHECK_EQUAL("Voyage de temps est de 6 heures et 45 minutes.", internationalization.tf("travel_time", 6, 45));
   //BOOST_CHECK_EQUAL("Ravi de vous rencontrer, Alex.", internationalization.tf("greeting", "Alex"));

   //internationalization.set_language("it");
   //BOOST_CHECK_EQUAL("Il tempo di percorrenza è di 6 ore e 45 minuti.", internationalization.tf("travel_time", 6, 45));
   //BOOST_CHECK_EQUAL("Piacere di conoscerti, Alex.", internationalization.tf("greeting", "Alex"));
//}




