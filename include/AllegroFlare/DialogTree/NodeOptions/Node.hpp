#pragma once


#include <AllegroFlare/DialogTree/Node.hpp>
#include <AllegroFlare/DialogTree/NodeOptions/Base.hpp>


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
            AllegroFlare::DialogTree::Node* node;

         protected:


         public:
            Node(AllegroFlare::DialogTree::Node* node=nullptr);
            ~Node();

            void set_node(AllegroFlare::DialogTree::Node* node);
            AllegroFlare::DialogTree::Node* get_node() const;
         };
      }
   }
}



