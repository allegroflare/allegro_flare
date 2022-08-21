

#include <AllegroFlare/MotionComposer/MessageProcessor.hpp>
#include <sstream>
#include <lib/nlohmann/json.hpp>


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
   // extract the type
   nlohmann::json parsed_json = nlohmann::json::parse(json_as_string);

   if (!parsed_json.contains("message"))
   {
       std::stringstream error_message;
       error_message << "AllegroFlare::MotionComposer::MessageProcessor::build_message_from_json: error: "
                     << "Expecting JSON to have a \"message\" property but it does not.  JSON:"
                     << std::endl
                     << std::endl
                     << parsed_json.dump(2);
       throw std::runtime_error(error_message.str());
   }
   else
   {
      if (!parsed_json["message"].contains("type"))
      {
         std::stringstream error_message;
         error_message << "AllegroFlare::MotionComposer::MessageProcessor::build_message_from_json: error: "
                       << "Expecting JSON to have a [\"message\"][\"type\"] property but it does not.  JSON:"
                       << std::endl
                       << std::endl
                       << parsed_json.dump(2);
         throw std::runtime_error(error_message.str());
      }
      else
      {
         // TODO, grab the data from the message
      }
   }

   // TODO
   //if (message_type == "AllegroFlare::MotionComposer::Messages::Base");
   AllegroFlare::MotionComposer::Messages::Base *result = nullptr;
   //nlohmann::json parsed_json = nlohmann::json::parse(json);
   //parsed_json.get_to(set_playhead_position);
   return result;
}
} // namespace MotionComposer
} // namespace AllegroFlare


