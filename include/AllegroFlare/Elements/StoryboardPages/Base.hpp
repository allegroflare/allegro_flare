#pragma once


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
            bool finished;

         protected:


         public:
            Base(std::string type=AllegroFlare::Elements::StoryboardPages::Base::TYPE);
            virtual ~Base();

            void set_finished(bool finished);
            std::string get_type() const;
            bool get_finished() const;
            virtual void start();
            virtual void update();
            virtual void render();
            virtual void advance();
            bool is_type(std::string possible_type="");
         };
      }
   }
}



