
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>

#include <AllegroFlare/ScreenManagers/Dictionary.hpp>
#include <AllegroFlare/Screens/Base.hpp>



class ScreenTestClass : public AllegroFlare::Screens::Base
{
public:
   ScreenTestClass() {};
};


class ScreenTestClassWithActivationDeactivationTracking : public AllegroFlare::Screens::Base
{
private:
   std::string identifier_duplicate;
   std::vector<std::string> *activation_order_tracker;

public:
   ScreenTestClassWithActivationDeactivationTracking(
         std::string identifier_duplicate="",
         std::vector<std::string> *activation_order_tracker=nullptr
      )
      : identifier_duplicate(identifier_duplicate)
      , activation_order_tracker(activation_order_tracker)
   {}

   virtual void on_activate() override { activation_order_tracker->push_back(identifier_duplicate + " - activate"); }
   virtual void on_deactivate() override { activation_order_tracker->push_back(identifier_duplicate + " - deactivate"); }
};


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
   activate__will_set_the_screen_to_be_active)
{
   al_init();
   AllegroFlare::EventEmitter event_emitter;
   AllegroFlare::ScreenManagers::Dictionary dictionary;
   event_emitter.initialize();
   dictionary.set_event_emitter(&event_emitter);

   ScreenTestClass screen_1;
   ScreenTestClass screen_2;
   ScreenTestClass screen_3;

   dictionary.add("screen_1", &screen_1);
   dictionary.add("screen_2", &screen_2);
   dictionary.add("screen_3", &screen_3);

   EXPECT_EQ(false, dictionary.is_active("screen_1"));
   EXPECT_EQ(false, dictionary.is_active("screen_2"));
   EXPECT_EQ(false, dictionary.is_active("screen_3"));

   dictionary.activate("screen_2");

   EXPECT_EQ(false, dictionary.is_active("screen_1"));
   EXPECT_EQ(true, dictionary.is_active("screen_2"));
   EXPECT_EQ(false, dictionary.is_active("screen_3"));

   al_uninstall_system();
}


TEST(AllegroFlare_ScreenManagers_DictionaryTest,
   activate__will_deactivate_any_other_active_screens)
{
   al_init();
   AllegroFlare::EventEmitter event_emitter;
   AllegroFlare::ScreenManagers::Dictionary dictionary;
   event_emitter.initialize();
   dictionary.set_event_emitter(&event_emitter);

   ScreenTestClass screen_1;
   ScreenTestClass screen_2;
   ScreenTestClass screen_3;

   dictionary.add("screen_1", &screen_1);
   dictionary.add("screen_2", &screen_2);
   dictionary.add("screen_3", &screen_3);

   EXPECT_EQ(false, dictionary.is_active("screen_1"));
   EXPECT_EQ(false, dictionary.is_active("screen_2"));
   EXPECT_EQ(false, dictionary.is_active("screen_3"));

   dictionary.activate("screen_2");

   EXPECT_EQ(false, dictionary.is_active("screen_1"));
   EXPECT_EQ(true, dictionary.is_active("screen_2"));
   EXPECT_EQ(false, dictionary.is_active("screen_3"));

   dictionary.activate("screen_3");

   EXPECT_EQ(false, dictionary.is_active("screen_1"));
   EXPECT_EQ(false, dictionary.is_active("screen_2"));
   EXPECT_EQ(true, dictionary.is_active("screen_3"));

   al_uninstall_system();
}


TEST(AllegroFlare_ScreenManagers_DictionaryTest,
   activate__will_always_deactivate_any_other_active_screens_prior_to_activating_the_target_screen)
{
   al_init();
   AllegroFlare::EventEmitter event_emitter;
   AllegroFlare::ScreenManagers::Dictionary dictionary;
   event_emitter.initialize();
   dictionary.set_event_emitter(&event_emitter);

   std::vector<std::string> activation_order_tracker;

   ScreenTestClassWithActivationDeactivationTracking screen_1("screen_1", &activation_order_tracker);
   ScreenTestClassWithActivationDeactivationTracking screen_2("screen_2", &activation_order_tracker);
   ScreenTestClassWithActivationDeactivationTracking screen_3("screen_3", &activation_order_tracker);

   dictionary.add("screen_1", &screen_1);
   dictionary.add("screen_2", &screen_2);
   dictionary.add("screen_3", &screen_3);

   // Using a somewhat random ordering
   dictionary.activate("screen_2");
   dictionary.activate("screen_3");
   dictionary.activate("screen_1");
   dictionary.activate("screen_3");
   dictionary.activate("screen_2");
   dictionary.activate("screen_1");

   std::vector<std::string> expected_activation_order_tracker = {
      "screen_2 - activate",
      "screen_2 - deactivate",
      "screen_3 - activate",
      "screen_3 - deactivate",
      "screen_1 - activate",
      "screen_1 - deactivate",
      "screen_3 - activate",
      "screen_3 - deactivate",
      "screen_2 - activate",
      "screen_2 - deactivate",
      "screen_1 - activate",
   };

   EXPECT_EQ(expected_activation_order_tracker, activation_order_tracker);


   al_uninstall_system();
}


TEST(AllegroFlare_ScreenManagers_DictionaryTest,
   activate__will_emit_a_game_event_indicating_a_screen_has_been_activated)
{
   // TODO
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


