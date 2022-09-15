#pragma once


#include <string>


namespace Wicked::Physics
{
   class Int2D
   {
   public:
      int x;
      int y;

      Int2D(int x=0, int y=0);
      ~Int2D();

      void rotate();
   };
}



