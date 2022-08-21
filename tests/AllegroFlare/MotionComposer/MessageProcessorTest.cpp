
#include <gtest/gtest.h>

#define EXPECT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/MotionComposer/MessageProcessor.hpp>


#include <AllegroFlare/MotionComposer/Messages/SetPlayheadPosition.hpp>


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
                                  "\n";
               expected_message += message_json;


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

   EXPECT_THROW_WITH_MESSAGE(message_processor.build_message_from_json(
         message_json),
         std::runtime_error,
         expected_message
   );
}


TEST(AllegroFlare_MotionComposer_MessageProcessorTest,
   build_message_from_json__when_attempting_to_parse_an_unknown_message_type__will_throw_an_error)
{
   AllegroFlare::MotionComposer::MessageProcessor message_processor;
   std::string message_json =
R"({
  "message": {
    "type": "AnUnknownType"
  }
})";
   std::string expected_message = "AllegroFlare::MotionComposer::MessageProcessor::build_message_from_json: error: "
                                  "Unknown message type \"AnUnknownType\". Cannot parse.";

   EXPECT_THROW_WITH_MESSAGE(message_processor.build_message_from_json(
         message_json),
         std::runtime_error,
         expected_message
   );
}


TEST(AllegroFlare_MotionComposer_MessageProcessorTest,
   build_message_from_json__will_be_able_to_parse_a_SetPlayheadPosition_message)
{
   AllegroFlare::MotionComposer::MessageProcessor message_processor;
   std::string message_json =
R"({
  "message": {
    "type": "SetPlayheadPosition",
    "position": 8.0
  }
})";

   AllegroFlare::MotionComposer::Messages::SetPlayheadPosition* result =
      static_cast<AllegroFlare::MotionComposer::Messages::SetPlayheadPosition*>(
         message_processor.build_message_from_json(message_json)
      );
   ASSERT_NE(nullptr, result);
   ASSERT_EQ("SetPlayheadPosition", result->get_type());
   EXPECT_EQ(8.0, result->get_position());
}


