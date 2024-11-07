#pragma once


#include <functional>
#include <string>


namespace AllegroFlare
{
   namespace Layouts
   {
      namespace Elements
      {
         class CursorDestination
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
            int move_up_to_target_tmj_object_id;
            int move_down_to_target_tmj_object_id;
            int move_left_to_target_tmj_object_id;
            int move_right_to_target_tmj_object_id;
            std::function<void()> on_focus;
            std::function<void()> on_blur;
            std::function<void()> on_activation;
            CursorDestination();
            ~CursorDestination();

         };
      }
   }
}



