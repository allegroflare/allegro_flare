#pragma once


#include <AllegroFlare/DialogTree/Nodes/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace DialogTree
   {
      namespace Nodes
      {
         class RawScriptLine : public AllegroFlare::DialogTree::Nodes::Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/DialogTree/Nodes/RawScriptLine";

         private:
            std::string line;
            int line_number;
            std::string next_line_identifier;

         protected:


         public:
            RawScriptLine(std::string line="[unset-line]", int line_number=0, std::string next_line_identifier="[unset-next_line_identifier]");
            ~RawScriptLine();

            void set_next_line_identifier(std::string next_line_identifier);
            std::string get_line() const;
            int get_line_number() const;
            std::string get_next_line_identifier() const;
         };
      }
   }
}



