
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>

#include <AllegroFlare/ScreenManagers/Dictionary.hpp>
#include <AllegroFlare/Screens/Base.hpp>


TEST(AllegroFlare_ScreenManagers_DictionaryTest, can_be_created_without_blowing_up)
{
   AllegroFlare::ScreenManagers::Dictionary dictionary;
}


TEST(AllegroFlare_ScreenManagers_DictionaryTest,
   add__will_add_the_screen_with_an_identifier_to_the_dictionary_and_return_true)
{
   AllegroFlare::Screens::Base screen;
   AllegroFlare::ScreenManagers::Dictionary dictionary;
   typedef AllegroFlare::ScreenManagers::Dictionary::Listing Listing;

   EXPECT_EQ(true, dictionary.add("foobar", &screen));

   std::map<std::string, Listing> expected_dictionary = { { "foobar", { &screen, false } } };
   std::map<std::string, Listing> actual_dictionary = dictionary.get_dictionary_copy();

   EXPECT_EQ(expected_dictionary, actual_dictionary);
}


TEST(AllegroFlare_ScreenManagers_DictionaryTest, add__will_return_false_if_a_record_with_the_identifier_already_exists)
{
   AllegroFlare::Screens::Base screen;
   AllegroFlare::ScreenManagers::Dictionary dictionary;
   dictionary.add("my_screen", &screen);
   ASSERT_EQ(true, dictionary.exists("my_screen"));

   EXPECT_EQ(false, dictionary.add("my_screen", &screen));
}


TEST(AllegroFlare_ScreenManagers_DictionaryTest,
   exists__will_return_true_if_a_record_with_the_identifier_does_not_exist)
{
   AllegroFlare::Screens::Base screen;
   AllegroFlare::ScreenManagers::Dictionary dictionary;
   dictionary.add("a-record-identifier-that-does-exist", &screen);

   EXPECT_EQ(true, dictionary.exists("a-record-identifier-that-does-exist"));
}


TEST(AllegroFlare_ScreenManagers_DictionaryTest,
   exists__will_return_false_if_a_record_with_the_identifier_does_not_exist)
{
   AllegroFlare::Screens::Base screen;
   AllegroFlare::ScreenManagers::Dictionary dictionary;

   EXPECT_EQ(false, dictionary.exists("a-record-identifier-that-does-not-exist"));
}


TEST(AllegroFlare_ScreenManagers_DictionaryTest, activate__when_a_screen_does_not_exist_with_the_name__throws_an_error)
{
   al_init(); // Required for event emitter
   AllegroFlare::Screens::Base screen;
   AllegroFlare::EventEmitter event_emitter;
   AllegroFlare::ScreenManagers::Dictionary dictionary;

   event_emitter.initialize();
   dictionary.set_event_emitter(&event_emitter);

   EXPECT_THROW_WITH_MESSAGE(
      dictionary.activate("a-record-identifier-that-does-not-exist"),
      std::runtime_error,
      "[AllegroFlare::ScreenManagers::Dictionary::activate]: error: Cannot activate screen \"a-record-identifier"
         "-that-does-not-exist\". No such screen exists."
   );
   al_uninstall_system();
}


TEST(AllegroFlare_ScreenManagers_DictionaryTest,
   add__with_a_name_that_is_an_empty_string__will_throw_an_error)
{
   AllegroFlare::Screens::Base screen;
   AllegroFlare::ScreenManagers::Dictionary dictionary;

   std::string an_empty_string = "";

   EXPECT_THROW_WITH_MESSAGE(
      dictionary.add(an_empty_string, nullptr),
      std::runtime_error,
      "[AllegroFlare::ScreenManagers::Dictionary::add]: error: A screen name cannot be blank."
   );
}


TEST(AllegroFlare_ScreenManagers_DictionaryTest,
   DISABLED__get_currently_active_screen_name__when_there_is_no_active_screen__will_return_an_empty_string)
{
   // TODO
}

TEST(AllegroFlare_ScreenManagers_DictionaryTest,
   DISABLED__get_currently_active_screen_name__will_return_the_identifier_of_the_currently_active_screen)
{
   // TODO
}


