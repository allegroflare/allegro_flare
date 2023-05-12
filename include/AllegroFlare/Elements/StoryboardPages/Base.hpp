#pragma once


#include <allegro5/allegro.h>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace StoryboardPages
      {
         class Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/Elements/StoryboardPages/Base";

         private:
            std::string type;
            float started_at;
            bool finished;

         protected:


         public:
            Base(std::string type=AllegroFlare::Elements::StoryboardPages::Base::TYPE);
            virtual ~Base();

            void set_started_at(float started_at);
            void set_finished(bool finished);
            std::string get_type() const;
            float get_started_at() const;
            bool get_finished() const;
            void managed_start(float time_now=al_get_time());
            virtual void start();
            virtual void update();
            virtual void render();
            virtual void advance();
            float infer_age(float time_now=al_get_time());
         };
      }
   }
}



