#pragma once


#include <string>


namespace AllegroFlare
{
   namespace DialogTree
   {
      namespace NodeOptions
      {
         class Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/DialogTree/NodeOptions/Base";

         private:
            std::string type;

         protected:


         public:
            Base(std::string type=AllegroFlare::DialogTree::NodeOptions::Base::TYPE);
            ~Base();

            std::string get_type() const;
            bool is_type(std::string possible_type="");
         };
      }
   }
}



