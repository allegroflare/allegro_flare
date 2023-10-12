#pragma once


#include <AllegroFlare/DialogTree/Nodes/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace DialogTree
   {
      namespace Nodes
      {
         class Wait : public AllegroFlare::DialogTree::Nodes::Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/DialogTree/Nodes/Wait";

         private:
            float duration_sec;
            std::string next_node_identifier;

         protected:


         public:
            Wait(float duration_sec=0.0f, std::string next_node_identifier="[unset-next_node_identifier]");
            ~Wait();

            void set_next_node_identifier(std::string next_node_identifier);
            float get_duration_sec() const;
            std::string get_next_node_identifier() const;
         };
      }
   }
}



