#pragma once




namespace AllegroFlare
{
   class Vec2B
   {
   private:
      bool x;
      bool y;

   protected:


   public:
      Vec2B(bool x=false, bool y=false);
      ~Vec2B();

      void set_x(bool x);
      void set_y(bool y);
      bool get_x() const;
      bool get_y() const;
      bool &get_x_ref();
      bool &get_y_ref();
   };
}



