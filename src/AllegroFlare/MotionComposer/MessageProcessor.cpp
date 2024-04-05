

#include <AllegroFlare/MotionComposer/MessageProcessor.hpp>

#include <AllegroFlare/JSONLoaders/AllegroFlare/MotionComposer/Messages/AddActor2D.hpp>
#include <AllegroFlare/JSONLoaders/MotionComposer/Messages/Clear.hpp>
#include <AllegroFlare/JSONLoaders/MotionComposer/Messages/RunBuildProcess.hpp>
#include <AllegroFlare/JSONLoaders/MotionComposer/Messages/SetPlayheadPosition.hpp>
#include <AllegroFlare/JSONLoaders/MotionComposer/Messages/TogglePlayback.hpp>
#include <lib/nlohmann/json.hpp>
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


std::vector<std::string> MessageProcessor::get_messages_json() const
{
   return messages_json;
}


std::vector<AllegroFlare::MotionComposer::Messages::Base*> MessageProcessor::get_messages() const
{
   return messages;
}


void MessageProcessor::push_one(std::string message_json_as_string)
{
   messages_json.push_back(message_json_as_string);
   return;
}

AllegroFlare::MotionComposer::Messages::Base* MessageProcessor::get_one_message_and_pop()
{
   if (messages.empty()) return nullptr;
   AllegroFlare::MotionComposer::Messages::Base* result = messages.front();
   messages.erase(messages.begin()); // (equivelent to .pop_front())
   return result;
}

void MessageProcessor::convert_one()
{
   if (messages_json.empty()) return;
   AllegroFlare::MotionComposer::Messages::Base* message = build_message_from_json(messages_json.front());
   //messages_json.erase(messages_json.begin());
   if (!message)
   {
      std::stringstream error_message;
      error_message << "AllegroFlare::MotionComposer::MessageProcessor: error: "
                    << "could not parse message." << std::endl;
      throw std::runtime_error(error_message.str());
   }
   else
   {
      messages.push_back(message);
      messages_json.erase(messages_json.begin());
   }
   return;
}

void MessageProcessor::process_one()
{
   // TODO
      //message->process();
      //delete message;
   return;
}

AllegroFlare::MotionComposer::Messages::Base* MessageProcessor::build_message_from_json(std::string json_as_string)
{
   AllegroFlare::MotionComposer::Messages::Base* result = nullptr;


   // parse the json

   nlohmann::json parsed_json = nlohmann::json::parse(json_as_string);


   // extract the type

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
         // process the type(s)

         std::string type = parsed_json["message"]["type"];
         if (type == "SetPlayheadPosition")
         //^^ maybe eventually: if (type == "AllegroFlare::MotionComposer::Messages::SetPlayheadPosition")
         {
            AllegroFlare::MotionComposer::Messages::SetPlayheadPosition *typed_result =
               new AllegroFlare::MotionComposer::Messages::SetPlayheadPosition();
            parsed_json["message"].get_to(*typed_result);
            result = typed_result;
         }
         else if (type == "AddActor2D")
         //^^ maybe eventually: if (type == "AllegroFlare::MotionComposer::Messages::SetPlayheadPosition")
         {
            AllegroFlare::MotionComposer::Messages::AddActor2D *typed_result =
               new AllegroFlare::MotionComposer::Messages::AddActor2D();
            parsed_json["message"].get_to(*typed_result);
            result = typed_result;
         }
         else if (type == "Clear")
         //^^ maybe eventually: if (type == "AllegroFlare::MotionComposer::Messages::SetPlayheadPosition")
         {
            AllegroFlare::MotionComposer::Messages::Clear *typed_result =
               new AllegroFlare::MotionComposer::Messages::Clear();
            parsed_json["message"].get_to(*typed_result);
            result = typed_result;
         }
         else if (type == "TogglePlayback")
         //^^ maybe eventually: if (type == "AllegroFlare::MotionComposer::Messages::SetPlayheadPosition")
         {
            AllegroFlare::MotionComposer::Messages::TogglePlayback *typed_result =
               new AllegroFlare::MotionComposer::Messages::TogglePlayback();
            parsed_json["message"].get_to(*typed_result);
            result = typed_result;
         }
         else if (type == AllegroFlare::MotionComposer::Messages::RunBuildProcess::TYPE)
         {
            AllegroFlare::MotionComposer::Messages::RunBuildProcess *typed_result =
               new AllegroFlare::MotionComposer::Messages::RunBuildProcess();
            parsed_json["message"].get_to(*typed_result);
            result = typed_result;
         }
         else
         {
            std::stringstream error_message;
            error_message << "AllegroFlare::MotionComposer::MessageProcessor::build_message_from_json: error: "
                          << "Unknown message type \"" << type << "\". Cannot parse.";
            throw std::runtime_error(error_message.str());
         }
      }
   }

   return result;
}


} // namespace MotionComposer
} // namespace AllegroFlare


