#pragma once


#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace DialogBoxes
      {
         class Base
         {
         private:
            std::string type;
            float created_at;

         public:
            Base(std::string type="Base");
            virtual ~Base();

            void set_created_at(float created_at);
            std::string get_type() const;
            float get_created_at() const;
            virtual void update();
            float infer_age();
            bool is_type(std::string possible_type="");
         };
      }
   }
}



