#pragma once


#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      class LevelSelectItemBoxRenderParams
      {
      private:

      protected:


      public:
         std::string menu_item_identifier;
         std::string label;
         int row;
         int column;
         float x;
         float y;
         float width;
         float height;
         bool locked;
         bool completed;
         LevelSelectItemBoxRenderParams(std::string menu_item_identifier="[unset-menu_item_identifier]", std::string label="[unset-label]", int row=0, int column=0, float x=0.0f, float y=0.0f, float width=0.0f, float height=0.0f, bool locked=false, bool completed=false);
         ~LevelSelectItemBoxRenderParams();

      };
   }
}



