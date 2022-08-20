#pragma once


#include <string>


namespace AllegroFlare
{
   namespace MotionComposer
   {
      namespace Messages
      {
         class Base
         {
         private:
            std::string type;

         public:
            Base(std::string type="Base");
            ~Base();

            std::string get_type();
            bool is_type(std::string possible_type="");
         };
      }
   }
}



