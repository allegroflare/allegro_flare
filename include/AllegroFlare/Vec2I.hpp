#pragma once




namespace AllegroFlare
{
   class Vec2I
   {
   private:
      int x;
      int y;

   public:
      Vec2I(int x=0, int y=0);
      ~Vec2I();

      void set_x(int x);
      void set_y(int y);
      int get_x() const;
      int get_y() const;
   };
}



