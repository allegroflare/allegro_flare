#pragma once


#include <AllegroFlare/DialogTree/Nodes/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace DialogTree
   {
      namespace Nodes
      {
         class EnterScene : public AllegroFlare::DialogTree::Nodes::Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/DialogTree/Nodes/EnterScene";

         private:
            std::string property;

         protected:


         public:
            EnterScene(std::string property="[unset-property]");
            ~EnterScene();

            std::string get_property() const;
            bool property_is(std::string possible_type="");
         };
      }
   }
}



