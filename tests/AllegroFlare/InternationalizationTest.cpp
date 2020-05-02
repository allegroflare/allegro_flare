

#include <gtest/gtest.h>

#include <AllegroFlare/Internationalization.hpp>


using namespace AllegroFlare;

#include <allegro5/allegro.h>



struct AllegroFlare_InternationalizationTest : public ::testing::Test
{
   const char *TEST_FOLDER = "./data/languages/tests/";
   static Internationalization internationalization;

   virtual void SetUp() override
   {
      ASSERT_EQ(false, al_is_system_installed());
      ASSERT_EQ(true, al_init());

      ALLEGRO_PATH *resource_path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
      al_change_directory(al_path_cstr(resource_path, ALLEGRO_NATIVE_PATH_SEP));
      al_destroy_path(resource_path);

      internationalization.set_languages_folder(TEST_FOLDER);
   }

   virtual void TearDown() override
   {
      al_uninstall_system();
   }
};

Internationalization AllegroFlare_InternationalizationTest::internationalization;




TEST_F(AllegroFlare_InternationalizationTest, expected_test_files_and_folders_exist)
{
   ASSERT_EQ(true, al_filename_exists("./data/languages/"));
   ASSERT_EQ(true, al_filename_exists("./data/languages/tests/en.txt"));
   ASSERT_EQ(true, al_filename_exists("./data/languages/tests/fr.txt"));
   ASSERT_EQ(true, al_filename_exists("./data/languages/tests/it.txt"));
}




TEST_F(AllegroFlare_InternationalizationTest, can_set_a_languages_folder)
{
   ASSERT_EQ(TEST_FOLDER, internationalization.get_languages_folder());
}




TEST_F(AllegroFlare_InternationalizationTest, initialized_its_languages_folder_to__data_slash_languages__by_default)
{
   Internationalization internationalization;
   ASSERT_EQ("data/languages/", internationalization.get_languages_folder());
}




TEST_F(AllegroFlare_InternationalizationTest, returns_false_when_trying_to_set_a_languages_folder_that_does_not_exist)
{
   std::string fake_folder = "foo/dir/that/doesnt/exist/";
   ASSERT_EQ(false, internationalization.set_languages_folder(fake_folder));
}



#include <gmock/gmock.h>
using ::testing::UnorderedElementsAreArray;


TEST_F(AllegroFlare_InternationalizationTest, returns_a_list_of_language_files_in_the_languages_folder)
{
   std::vector<std::string> expected_files = {"en.txt", "fr.txt", "it.txt"};
   std::vector<std::string> returned_files = internationalization.get_language_filenames();

   ASSERT_THAT(returned_files, UnorderedElementsAreArray(expected_files.begin(), expected_files.end()));
}




TEST_F(AllegroFlare_InternationalizationTest, finds_a_language_file_by_language_designator)
{
   std::string expected_filename = "";

   expected_filename = "./data/languages/tests/en.txt";
   ASSERT_EQ(expected_filename, internationalization.find_language_file("en"));

   expected_filename = "./data/languages/tests/fr.txt";
   ASSERT_EQ(expected_filename, internationalization.find_language_file("fr"));

   expected_filename = "./data/languages/tests/it.txt";
   ASSERT_EQ(expected_filename, internationalization.find_language_file("it"));
}




TEST_F(AllegroFlare_InternationalizationTest, returns_an_empty_string_when_a_language_file_cannot_be_found)
{
   ASSERT_EQ("", internationalization.find_language_file("language_designator_that_doesnt_exist"));
}




TEST_F(AllegroFlare_InternationalizationTest, returns_true_when_a_language_file_loads_successfully)
{
   ASSERT_EQ(true, internationalization.load_language_file("en", "English", "./data/languages/tests/en.txt"));
   ASSERT_EQ(true, internationalization.load_language_file("fr", "French", "./data/languages/tests/fr.txt"));
   ASSERT_EQ(true, internationalization.load_language_file("it", "Italian", "./data/languages/tests/it.txt"));
}




TEST_F(AllegroFlare_InternationalizationTest, sets_the_language_designator_and_language_name_when_loading_a_language_file)
{
   internationalization.load_language_file("en", "English", "./data/languages/tests/en.txt");
   ASSERT_EQ("en", internationalization.get_language());
   ASSERT_EQ("English", internationalization.get_language_name());

   internationalization.load_language_file("fr", "French", "./data/languages/tests/fr.txt");
   ASSERT_EQ("fr", internationalization.get_language());
   ASSERT_EQ("French", internationalization.get_language_name());

   internationalization.load_language_file("it", "Italian", "./data/languages/tests/it.txt");
   ASSERT_EQ("it", internationalization.get_language());
   ASSERT_EQ("Italian", internationalization.get_language_name());
}




TEST_F(AllegroFlare_InternationalizationTest, returns_false_when_unable_to_load_a_language_file)
{
   ASSERT_EQ(false, internationalization.load_language_file("foo", "Fooanese", "foo/folder/file_that_doesnt_exist.txt"));
}




TEST_F(AllegroFlare_InternationalizationTest, successfully_populates_labels_when_loading_a_language_file)
{
   EXPECT_EQ(true, internationalization.load_language_file("en", "English", "./data/languages/tests/en.txt"));

   ASSERT_EQ("Welcome to Allegro!", internationalization.t("welcome_message"));
   ASSERT_EQ("start", internationalization.t("start_button"));
}




TEST_F(AllegroFlare_InternationalizationTest, can_set_a_language)
{
   ASSERT_EQ(true, internationalization.set_language("en"));
   ASSERT_EQ(true, internationalization.set_language("fr"));
   ASSERT_EQ(true, internationalization.set_language("it"));
}




TEST_F(AllegroFlare_InternationalizationTest, returns_false_when_unable_to_set_a_language)
{
   ASSERT_EQ(false, internationalization.set_language("not_a_language"));
}




TEST_F(AllegroFlare_InternationalizationTest, can_retrieve_the_current_language_designator)
{
   internationalization.set_language("en");
   ASSERT_EQ("en", internationalization.get_language());

   internationalization.set_language("fr");
   ASSERT_EQ("fr", internationalization.get_language());

   internationalization.set_language("it");
   ASSERT_EQ("it", internationalization.get_language());
}




TEST_F(AllegroFlare_InternationalizationTest, loads_translations_when_a_language_designator_is_set)
{
   internationalization.set_language("en");
   ASSERT_EQ("Welcome to Allegro!", internationalization.t("welcome_message"));
   ASSERT_EQ("start", internationalization.t("start_button"));

   internationalization.set_language("fr");
   ASSERT_EQ("Bienvenue à Allegro!", internationalization.t("welcome_message"));
   ASSERT_EQ("démarrer", internationalization.t("start_button"));

   internationalization.set_language("it");
   ASSERT_EQ("Benvenuti a Allegro!", internationalization.t("welcome_message"));
   ASSERT_EQ("inizio", internationalization.t("start_button"));
}




TEST_F(AllegroFlare_InternationalizationTest, knows_if_a_translation_label_exists_or_not)
{
   internationalization.set_language("en");

   ASSERT_EQ(true, internationalization.t_exists("blank_content"));
   ASSERT_EQ(false, internationalization.t_exists("label_that_does_not_exist"));
}




TEST_F(AllegroFlare_InternationalizationTest, returns_an_empty_string_when_a_translation_is_blank_or_does_not_exist_for_that_label)
{
   internationalization.set_language("en");

   ASSERT_EQ("", internationalization.t("blank_content"));
   ASSERT_EQ("", internationalization.t("label_that_does_not_exist"));
}




TEST_F(AllegroFlare_InternationalizationTest, formats_a_translation_with_variable_args)
{
   internationalization.set_language("en");
   ASSERT_EQ("Travel time is 6 hours and 45 minutes.", internationalization.tf("travel_time", 6, 45));
   ASSERT_EQ("Nice to meet you, Alex.", internationalization.tf("greeting", "Alex"));

   internationalization.set_language("fr");
   ASSERT_EQ("Voyage de temps est de 6 heures et 45 minutes.", internationalization.tf("travel_time", 6, 45));
   ASSERT_EQ("Ravi de vous rencontrer, Alex.", internationalization.tf("greeting", "Alex"));

   internationalization.set_language("it");
   ASSERT_EQ("Il tempo di percorrenza è di 6 ore e 45 minuti.", internationalization.tf("travel_time", 6, 45));
   ASSERT_EQ("Piacere di conoscerti, Alex.", internationalization.tf("greeting", "Alex"));
}




