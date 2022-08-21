#pragma once


#include <AllegroFlare/MotionComposer/Messages/Base.hpp>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace MotionComposer
   {
      class MessageProcessor
      {
      private:
         std::vector<std::string> messages_json;
         std::vector<AllegroFlare::MotionComposer::Messages::Base*> messages;

      public:
         MessageProcessor(std::vector<std::string> messages_json={}, std::vector<AllegroFlare::MotionComposer::Messages::Base*> messages={});
         ~MessageProcessor();

         void set_messages_json(std::vector<std::string> messages_json);
         void set_messages(std::vector<AllegroFlare::MotionComposer::Messages::Base*> messages);
         std::vector<std::string> get_messages_json();
         std::vector<AllegroFlare::MotionComposer::Messages::Base*> get_messages();
         void push_one(std::string message_json_as_string="{}");
         AllegroFlare::MotionComposer::Messages::Base* get_one_message_and_pop();
         void convert_one();
         void process_one();
         AllegroFlare::MotionComposer::Messages::Base* build_message_from_json(std::string json_as_string="{}");
      };
   }
}



