#pragma once




namespace AllegroFlare
{
   namespace Testing
   {
      class Rulers
      {
      private:

      protected:


      public:
         Rulers();
         ~Rulers();

         static void draw_dimensional_grid(float x=0.0f, float y=0.0f, float z=0.0f, float spacing=(16*4.8));
         static void draw_2d_grid(float x=0.0f, float y=0.0f, float size=1.0f, float spacing=(16*4.8));
      };
   }
}



