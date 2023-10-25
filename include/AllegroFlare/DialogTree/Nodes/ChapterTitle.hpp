#pragma once


#include <AllegroFlare/DialogTree/Nodes/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace DialogTree
   {
      namespace Nodes
      {
         class ChapterTitle : public AllegroFlare::DialogTree::Nodes::Base
         {
         public:
            static constexpr float DEFAULT_DURATION = 6.0f;
            static constexpr char* TYPE = (char*)"AllegroFlare/DialogTree/Nodes/ChapterTitle";

         private:
            std::string title_text;
            float duration;
            std::string next_node_identifier;

         protected:


         public:
            ChapterTitle(std::string title_text="[unset-title_text]", float duration=DEFAULT_DURATION, std::string next_node_identifier="[unset-next_node_identifier]");
            ~ChapterTitle();

            void set_next_node_identifier(std::string next_node_identifier);
            std::string get_title_text() const;
            float get_duration() const;
            std::string get_next_node_identifier() const;
         };
      }
   }
}



