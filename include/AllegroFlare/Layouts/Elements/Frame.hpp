#pragma once


#include <functional>
#include <string>


namespace AllegroFlare
{
   namespace Layouts
   {
      namespace Elements
      {
         class Frame
         {
         private:

         protected:


         public:
            std::string name;
            float x;
            float y;
            float width;
            float height;
            float tmj_object_id;
            std::function<void()> on_focus;
            std::function<void()> on_blur;
            std::function<void()> on_activation;
            Frame();
            ~Frame();

         };
      }
   }
}



