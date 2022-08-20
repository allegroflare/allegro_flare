

#include <AllegroFlare/MotionComposer/MessageProcessor.hpp>
#include <sstream>


namespace AllegroFlare
{
namespace MotionComposer
{


MessageProcessor::MessageProcessor(std::vector<std::string> messages_json, std::vector<AllegroFlare::MotionComposer::Messages::Base*> messages)
   : messages_json(messages_json)
   , messages(messages)
{
}


MessageProcessor::~MessageProcessor()
{
}


void MessageProcessor::set_messages_json(std::vector<std::string> messages_json)
{
   this->messages_json = messages_json;
}


void MessageProcessor::set_messages(std::vector<AllegroFlare::MotionComposer::Messages::Base*> messages)
{
   this->messages = messages;
}


std::vector<std::string> MessageProcessor::get_messages_json()
{
   return messages_json;
}


std::vector<AllegroFlare::MotionComposer::Messages::Base*> MessageProcessor::get_messages()
{
   return messages;
}


void MessageProcessor::convert_one()
{
   if (messages_json.empty()) return;
   AllegroFlare::MotionComposer::Messages::Base* message = build_message_from_json(messages_json.front());
   if (!message)
   {
      std::stringstream error_message;
      error_message << "AllegroFlare::MotionComposer::MessageProcessor: error: "
                    << "could not parse message." << std::endl;
      throw std::runtime_error(error_message.str());
   }
   else
   {
      // TODO: message->process();
      delete message;
   }
   return;
}

AllegroFlare::MotionComposer::Messages::Base* MessageProcessor::build_message_from_json(std::string json_as_string)
{
   AllegroFlare::MotionComposer::Messages::Base* result = nullptr;
   return result;
}
} // namespace MotionComposer
} // namespace AllegroFlare


