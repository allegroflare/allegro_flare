#pragma once


#include <AllegroFlare/DialogTree/Nodes/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace DialogTree
   {
      namespace Nodes
      {
         class EmitGameEvent : public AllegroFlare::DialogTree::Nodes::Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/DialogTree/Nodes/EmitGameEvent";

         private:
            std::string game_event_name;
            std::string immediate_next_node_identifier;

         protected:


         public:
            EmitGameEvent(std::string game_event_name="[unset-game_event_name]", std::string immediate_next_node_identifier="[unset-immediate_next_node_identifier]");
            ~EmitGameEvent();

            std::string get_game_event_name() const;
            std::string get_immediate_next_node_identifier() const;
         };
      }
   }
}



