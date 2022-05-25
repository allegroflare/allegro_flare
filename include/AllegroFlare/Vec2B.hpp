#pragma once




namespace AllegroFlare
{
   class Vec2B
   {
   private:
      bool x;
      bool y;

   public:
      Vec2B(bool x=false, bool y=false);
      ~Vec2B();

      void set_x(bool x);
      void set_y(bool y);
      bool get_x();
      bool get_y();
   };
}



