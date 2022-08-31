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
         private:
            std::string type;
            bool finished;

         protected:


         public:
            Base(std::string type="Base");
            virtual ~Base();

            void set_finished(bool finished);
            std::string get_type() const;
            bool get_finished() const;
            virtual void start();
            virtual void update();
            virtual void render();
            virtual void advance();
         };
      }
   }
}



