
#include <gtest/gtest.h>

#define EXPECT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/MotionComposer/MessageProcessor.hpp>


TEST(AllegroFlare_MotionComposer_MessageProcessorTest, can_be_created_without_blowing_up)
{
   AllegroFlare::MotionComposer::MessageProcessor message_processor;
}


TEST(AllegroFlare_MotionComposer_MessageProcessorTest,
   build_message_from_json__when_the_message_key_is_not_present__will_throw_an_error)
{
   AllegroFlare::MotionComposer::MessageProcessor message_processor;
   std::string message_json =
R"({
  "a_key_but_not_the_message_key": 1.5
})";
   std::string expected_message = "AllegroFlare::MotionComposer::MessageProcessor::build_message_from_json: error: "
                                  "Expecting JSON to have a \"message\" property but it does not.  JSON:\n"
                                  "\n"
                                  "{\n"
                                  "  \"a_key_but_not_the_message_key\": 1.5\n"
                                  "}";


   EXPECT_THROW_WITH_MESSAGE(message_processor.build_message_from_json(
         message_json),
         std::runtime_error,
         expected_message
   );
}


TEST(AllegroFlare_MotionComposer_MessageProcessorTest,
   build_message_from_json__when_the_message_is_present__but_a_type_is_not__will_throw_an_error)
{
   AllegroFlare::MotionComposer::MessageProcessor message_processor;
   std::string message_json =
R"({
  "message": {
    "a_key_but_not_the_type_key": "irrelevant"
  }
})";
   std::string expected_message = "AllegroFlare::MotionComposer::MessageProcessor::build_message_from_json: error: "
                                  "Expecting JSON to have a [\"message\"][\"type\"] property but it does not.  JSON:\n"
                                  "\n";
               expected_message += message_json;
                                  //"{\n"
                                  //"  \"a_key_but_not_the_message_key\": 1.5\n"
                                  //"}";

   EXPECT_THROW_WITH_MESSAGE(message_processor.build_message_from_json(
         message_json),
         std::runtime_error,
         expected_message
   );
}


