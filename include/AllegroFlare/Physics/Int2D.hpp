#pragma once




namespace AllegroFlare
{
   namespace Physics
   {
      class Int2D
      {
      private:
         int x;
         int y;

      protected:


      public:
         Int2D(int x=0, int y=0);
         ~Int2D();

         void set_x(int x);
         void set_y(int y);
         int get_x() const;
         int get_y() const;
         void rotate();
      };
   }
}



