#pragma once


#include <allegro5/allegro.h>
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
            static constexpr char* TYPE = (char*)"DialogBoxes/Base";

         private:
            std::string type;
            float created_at;
            bool finished;

         protected:


         public:
            Base(std::string type=AllegroFlare::Elements::DialogBoxes::Base::TYPE);
            virtual ~Base();

            void set_created_at(float created_at);
            void set_finished(bool finished);
            std::string get_type() const;
            float get_created_at() const;
            bool get_finished() const;
            virtual void update();
            virtual void advance() = 0;
            virtual void cursor_up();
            virtual void cursor_down();
            float infer_age(float time_now=al_get_time());
            bool is_type(std::string possible_type="");
         };
      }
   }
}



