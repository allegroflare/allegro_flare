#pragma once


#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace Backgrounds
      {
         class Base
         {
         private:
            std::string type;

         public:
            Base(std::string type="Base");
            virtual ~Base();

            std::string get_type() const;
            virtual void activate();
            virtual void deactivate();
            virtual void update();
            virtual void render();
            virtual void show();
            virtual void hide();
         };
      }
   }
}



