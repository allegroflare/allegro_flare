#pragma once


#include <AllegroFlare/DialogTree/NodeOptions/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace DialogTree
   {
      namespace NodeOptions
      {
         class GoToNode : public AllegroFlare::DialogTree::NodeOptions::Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/DialogTree/NodeOptions/GoToNode";

         private:
            std::string target_node_name;

         protected:


         public:
            GoToNode(std::string target_node_name="[unset-target_node_name]");
            ~GoToNode();

            void set_target_node_name(std::string target_node_name);
            std::string get_target_node_name() const;
         };
      }
   }
}



