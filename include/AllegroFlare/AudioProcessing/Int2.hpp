#pragma once




namespace AllegroFlare
{
   namespace AudioProcessing
   {
      class Int2
      {
      private:
         float x;
         float y;

      protected:


      public:
         Int2();
         ~Int2();

         void set_x(float x);
         void set_y(float y);
         float get_x() const;
         float get_y() const;
      };
   }
}



