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
         public:
            static constexpr char* TYPE = "DialogBoxes/Base";

         private:
            std::string type;
            float created_at;

         protected:


         public:
            Base(std::string type=TYPE);
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



