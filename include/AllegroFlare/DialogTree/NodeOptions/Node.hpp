#pragma once


#include <AllegroFlare/DialogTree/NodeOptions/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace DialogTree
   {
      namespace NodeOptions
      {
         class Node : public AllegroFlare::DialogTree::NodeOptions::Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/DialogTree/NodeOptions/Node";

         private:
            std::string property;

         protected:


         public:
            Node(std::string property="[unset-property]");
            ~Node();

            std::string get_property() const;
            bool property_is(std::string possible_type="");
         };
      }
   }
}



