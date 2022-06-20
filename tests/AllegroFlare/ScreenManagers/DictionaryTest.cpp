
#include <gtest/gtest.h>

#include <AllegroFlare/ScreenManagers/Dictionary.hpp>
#include <AllegroFlare/Screens/Basic.hpp>


TEST(AllegroFlare_ScreenManagers_DictionaryTest, can_be_created_without_blowing_up)
{
   AllegroFlare::ScreenManagers::Dictionary dictionary;
}


TEST(AllegroFlare_ScreenManagers_DictionaryTest,
   add__will_add_the_screen_with_an_identifier_to_the_dictionary_and_return_true)
{
   AllegroFlare::Screens::Basic screen;
   AllegroFlare::ScreenManagers::Dictionary dictionary;
   typedef AllegroFlare::ScreenManagers::Dictionary::Listing Listing;

   EXPECT_EQ(true, dictionary.add("foobar", &screen));

   std::map<std::string, Listing> expected_dictionary = { { "foobar", { &screen, false } } };
   std::map<std::string, Listing> actual_dictionary = dictionary.get_dictionary_copy();

   EXPECT_EQ(expected_dictionary, actual_dictionary);
}


TEST(AllegroFlare_ScreenManagers_DictionaryTest, add__will_return_false_if_a_record_with_the_identifier_already_exists)
{
   AllegroFlare::Screens::Basic screen;
   AllegroFlare::ScreenManagers::Dictionary dictionary;
   dictionary.add("my_screen", &screen);
   ASSERT_EQ(true, dictionary.exists("my_screen"));

   EXPECT_EQ(false, dictionary.add("my_screen", &screen));
}


TEST(AllegroFlare_ScreenManagers_DictionaryTest,
   exists__will_return_true_if_a_record_with_the_identifier_does_not_exist)
{
   AllegroFlare::Screens::Basic screen;
   AllegroFlare::ScreenManagers::Dictionary dictionary;
   dictionary.add("a-record-identifier-that-does-exist", &screen);

   EXPECT_EQ(true, dictionary.exists("a-record-identifier-that-does-exist"));
}


TEST(AllegroFlare_ScreenManagers_DictionaryTest,
   exists__will_return_false_if_a_record_with_the_identifier_does_not_exist)
{
   AllegroFlare::Screens::Basic screen;
   AllegroFlare::ScreenManagers::Dictionary dictionary;

   EXPECT_EQ(false, dictionary.exists("a-record-identifier-that-does-not-exist"));
}


