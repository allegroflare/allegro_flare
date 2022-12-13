

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <AllegroFlare/Internationalization.hpp>

#include <allegro5/allegro.h>



struct AllegroFlare_InternationalizationTest : public ::testing::Test
{
// TODO: improve this:
#if defined(_WIN32) || defined(_WIN64)
   const char *TEST_BASE_FOLDER = "/msys64/home/Mark/Repos/allegro_flare/tests/fixtures/";
#else
   const char *TEST_BASE_FOLDER = "/Users/markoates/Repos/allegro_flare/tests/fixtures/";
#endif
   const char *TEST_FOLDER = "languages/";
   static AllegroFlare::Internationalization internationalization;

   virtual void SetUp() override
   {
      ASSERT_EQ(false, al_is_system_installed());
      ASSERT_EQ(true, al_init());

      ALLEGRO_PATH *test_working_directory = al_create_path(TEST_BASE_FOLDER);
      al_change_directory(al_path_cstr(test_working_directory, ALLEGRO_NATIVE_PATH_SEP));
      al_destroy_path(test_working_directory);

      internationalization.set_languages_folder(TEST_FOLDER);
   }

   virtual void TearDown() override
   {
      al_uninstall_system();
   }
};

AllegroFlare::Internationalization AllegroFlare_InternationalizationTest::internationalization;



TEST_F(AllegroFlare_InternationalizationTest, expected_test_files_and_folders_exist)
{
   EXPECT_EQ(true, al_filename_exists("languages/"));
   EXPECT_EQ(true, al_filename_exists("languages/en.txt"));
   EXPECT_EQ(true, al_filename_exists("languages/fr.txt"));
   EXPECT_EQ(true, al_filename_exists("languages/it.txt"));
}



// TODO: this test does not look finished:
TEST_F(AllegroFlare_InternationalizationTest, can_set_a_languages_folder)
{
   EXPECT_EQ(TEST_FOLDER, internationalization.get_languages_folder());
}



TEST_F(AllegroFlare_InternationalizationTest, initialized_its_languages_folder_to_languages_slash__by_default)
{
   AllegroFlare::Internationalization internationalization;
   EXPECT_EQ("languages/", internationalization.get_languages_folder());
}



TEST_F(AllegroFlare_InternationalizationTest, returns_false_when_trying_to_set_a_languages_folder_that_does_not_exist)
{
   std::string fake_folder = "foo/dir/that/doesnt/exist/";
   EXPECT_EQ(false, internationalization.set_languages_folder(fake_folder));
}



TEST_F(AllegroFlare_InternationalizationTest,
   set_languages_folder__when_trying_to_set_a_languages_folder_that_does_not_exist__outputs_an_error_message_to_cout)
{
   std::string fake_folder = "foo/dir/that/doesnt/exist/";

   testing::internal::CaptureStdout();
   EXPECT_EQ(false, internationalization.set_languages_folder(fake_folder));
   std::string output = testing::internal::GetCapturedStdout();

   std::string expected_cerr_output = "\x1B[1;31m[AllegroFlare::Internationalization::set_languages_folder()]: error: "
                                      "Could not find folder \"foo/dir/that/doesnt/exist/\" "
                                      "to find language files.\x1B[0m\n";
   EXPECT_EQ(expected_cerr_output, output);
}



TEST_F(AllegroFlare_InternationalizationTest, returns_a_list_of_language_files_in_the_languages_folder)
{
   std::vector<std::string> expected_files = {"en.txt", "fr.txt", "it.txt"};
   std::vector<std::string> returned_files = internationalization.find_language_filenames();

   EXPECT_THAT(returned_files, ::testing::UnorderedElementsAreArray(expected_files.begin(), expected_files.end()));
}



TEST_F(AllegroFlare_InternationalizationTest, finds_a_language_file_by_language_designator)
{
   std::string expected_filename = "";

   expected_filename = "languages/en.txt";
   EXPECT_EQ(expected_filename, internationalization.find_language_file("en"));

   expected_filename = "languages/fr.txt";
   EXPECT_EQ(expected_filename, internationalization.find_language_file("fr"));

   expected_filename = "languages/it.txt";
   EXPECT_EQ(expected_filename, internationalization.find_language_file("it"));
}



TEST_F(AllegroFlare_InternationalizationTest, DISABLED__returns_an_empty_string_when_a_language_file_cannot_be_found)
   // TODO: This crashes on Windows
{
   EXPECT_EQ("", internationalization.find_language_file("language_designator_that_doesnt_exist"));
}



TEST_F(AllegroFlare_InternationalizationTest, returns_true_when_a_language_file_loads_successfully)
{
   EXPECT_EQ(true, internationalization.load_language_file("en", "English", "languages/en.txt"));
   EXPECT_EQ(true, internationalization.load_language_file("fr", "French", "languages/fr.txt"));
   EXPECT_EQ(true, internationalization.load_language_file("it", "Italian", "languages/it.txt"));
}



TEST_F(AllegroFlare_InternationalizationTest,
   sets_the_language_designator_and_language_name_when_loading_a_language_file)
{
   internationalization.load_language_file("en", "English", "languages/en.txt");
   EXPECT_EQ("en", internationalization.get_language());
   EXPECT_EQ("English", internationalization.get_language_name());

   internationalization.load_language_file("fr", "French", "languages/fr.txt");
   EXPECT_EQ("fr", internationalization.get_language());
   EXPECT_EQ("French", internationalization.get_language_name());

   internationalization.load_language_file("it", "Italian", "languages/it.txt");
   EXPECT_EQ("it", internationalization.get_language());
   EXPECT_EQ("Italian", internationalization.get_language_name());
}



TEST_F(AllegroFlare_InternationalizationTest, returns_false_when_unable_to_load_a_language_file)
{
   EXPECT_EQ(false, internationalization.load_language_file("foo", "Fooanese", "foo/baz/file_that_doesnt_exist.txt"));
}



TEST_F(AllegroFlare_InternationalizationTest, successfully_populates_labels_when_loading_a_language_file)
{
   EXPECT_EQ(true, internationalization.load_language_file("en", "English", "languages/en.txt"));

   EXPECT_EQ("Welcome to Allegro!", internationalization.t("welcome_message"));
   EXPECT_EQ("start", internationalization.t("start_button"));
}



TEST_F(AllegroFlare_InternationalizationTest, can_set_a_language)
{
   EXPECT_EQ(true, internationalization.set_language("en"));
   EXPECT_EQ(true, internationalization.set_language("fr"));
   EXPECT_EQ(true, internationalization.set_language("it"));
}



TEST_F(AllegroFlare_InternationalizationTest, returns_false_when_unable_to_set_a_language)
{
   EXPECT_EQ(false, internationalization.set_language("not_a_language"));
}



TEST_F(AllegroFlare_InternationalizationTest, set_language__outputs_an_error_message_when_a_language_cannot_be_set)
{
   // TODO: this test
   // NOTE: consider throwing in this case rather than just an error message
}



TEST_F(AllegroFlare_InternationalizationTest, can_retrieve_the_current_language_designator)
{
   internationalization.set_language("en");
   EXPECT_EQ("en", internationalization.get_language());

   internationalization.set_language("fr");
   EXPECT_EQ("fr", internationalization.get_language());

   internationalization.set_language("it");
   EXPECT_EQ("it", internationalization.get_language());
}



TEST_F(AllegroFlare_InternationalizationTest, loads_translations_when_a_language_designator_is_set)
{
   internationalization.set_language("en");
   EXPECT_EQ("Welcome to Allegro!", internationalization.t("welcome_message"));
   EXPECT_EQ("start", internationalization.t("start_button"));

   internationalization.set_language("fr");
   EXPECT_EQ("Bienvenue à Allegro!", internationalization.t("welcome_message"));
   EXPECT_EQ("démarrer", internationalization.t("start_button"));

   internationalization.set_language("it");
   EXPECT_EQ("Benvenuti a Allegro!", internationalization.t("welcome_message"));
   EXPECT_EQ("inizio", internationalization.t("start_button"));
}



TEST_F(AllegroFlare_InternationalizationTest, knows_if_a_translation_label_exists_or_not)
{
   internationalization.set_language("en");

   EXPECT_EQ(true, internationalization.t_exists("blank_content"));
   EXPECT_EQ(false, internationalization.t_exists("label_that_does_not_exist"));
}



TEST_F(AllegroFlare_InternationalizationTest,
   returns_an_empty_string_when_a_translation_is_blank_or_does_not_exist_for_that_label)
{
   internationalization.set_language("en");

   EXPECT_EQ("", internationalization.t("blank_content"));
   EXPECT_EQ("", internationalization.t("label_that_does_not_exist"));
}



TEST_F(AllegroFlare_InternationalizationTest, formats_a_translation_with_variable_args)
   // NOTE: This test previously crashed on Windows. It's been modified when on a Mac and has since been unDISABLED.
   // TODO: See if this test works on Win and remove these comments.
{
   internationalization.set_language("en");
   EXPECT_EQ("Travel time is 6 hours and 45 minutes.", internationalization.tf("travel_time", 6, 45));
   EXPECT_EQ("Nice to meet you, Alex.", internationalization.tf("greeting", "Alex"));

   internationalization.set_language("fr");
   EXPECT_EQ("Voyage de temps est de 6 heures et 45 minutes.", internationalization.tf("travel_time", 6, 45));
   EXPECT_EQ("Ravi de vous rencontrer, Alex.", internationalization.tf("greeting", "Alex"));

   internationalization.set_language("it");
   EXPECT_EQ("Il tempo di percorrenza è di 6 ore e 45 minuti.", internationalization.tf("travel_time", 6, 45));
   EXPECT_EQ("Piacere di conoscerti, Alex.", internationalization.tf("greeting", "Alex"));
}



