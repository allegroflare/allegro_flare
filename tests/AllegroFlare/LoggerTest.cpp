
#include <gtest/gtest.h>

#include <AllegroFlare/Logger.hpp>


TEST(AllegroFlare_LoggerTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Logger logger;
}


TEST(AllegroFlare_LoggerTest, build_not_included_message__will_return_text_formatted_as_a_not_included_warning)
{
   AllegroFlare::Logger logger;
   std::string expected_message = "The element \"foo\" is not in the list of valid elements [\"bar\", \"baz\", "
                                  "\"buzz\"]";
   EXPECT_EQ(expected_message, logger.build_not_included_message("foo", {"bar", "baz", "buzz"}));
}


TEST(AllegroFlare_LoggerTest, build_not_included_message__will_escape_double_quotes_in_params)
{
   AllegroFlare::Logger logger;
   std::string expected_message = "The element \"element that \\\"contains\\\" quotes\" is not in the list of valid "
                                  "elements [\"foo \\\"faux\\\" farm\", \"\\\"flam\\\" floop \\\"flounder\\\"\"]";
   EXPECT_EQ(expected_message,
      logger.build_not_included_message(
         "element that \"contains\" quotes",
         { "foo \"faux\" farm", "\"flam\" floop \"flounder\"" }
      )
   );
}


TEST(AllegroFlare_LoggerTest, warn_from_once__will_only_emit_an_warning_message_one_time)
{
   // TODO
}


TEST(AllegroFlare_LoggerTest, initialize_log_file__will_open_a_logfile_and_use_it_for_writing)
{
   AllegroFlare::Logger logger;
   logger.set_log_filename("/Users/markoates/Repos/allegro_flare/tmp/test_log_file.txt");
   logger.initialize_log_file(); // TODO: Consider requiring some kind of acknoledgement of log file setup

   AllegroFlare::Logger::set_instance(&logger);
   AllegroFlare::Logger::warn_from(
         "AllegroFlare::LoggerTest::initialize_log_file__will_open_a_logfile_and_use_it_for_writing",
         "All is well!"
      );
   // TODO: Test contents of produced log file
}


