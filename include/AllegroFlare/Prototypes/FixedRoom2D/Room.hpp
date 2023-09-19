#pragma once




namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace FixedRoom2D
      {
         class Room
         {
         private:
            float min_x;
            float min_y;
            float max_x;
            float max_y;
            bool suspended;
            float suspended_at;

         protected:


         public:
            Room();
            ~Room();

            void set_min_x(float min_x);
            void set_min_y(float min_y);
            void set_max_x(float max_x);
            void set_max_y(float max_y);
            float get_min_x() const;
            float get_min_y() const;
            float get_max_x() const;
            float get_max_y() const;
            bool get_suspended() const;
            void suspend();
            void resume();
            void show();
            void hide();
         };
      }
   }
}



