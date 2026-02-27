#pragma once


#include <string>


namespace AllegroFlare
{
   namespace Tiled
   {
      class TMJGroup
      {
      private:

      protected:


      public:
         int id;
         std::string name;
         float offset_x;
         float offset_y;
         TMJGroup(int id=0, std::string name="[unset-name]", float offset_x=0.0f, float offset_y=0.0f);
         ~TMJGroup();

      };
   }
}



