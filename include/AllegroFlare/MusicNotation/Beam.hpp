#pragma once




namespace AllegroFlare
{
   namespace MusicNotation
   {
      class Beam
      {
      private:
         enum Alignment
         {
            UNDEFINED = 0,
            TOP,
            MIDDLE,
            BOTTOM,
         };
         float staff_line_distance;
         float start_x;
         float start_staff_pos;
         Beam::Alignment start_alignment;
         float end_x;
         float end_staff_pos;
         Beam::Alignment end_alignment;

      protected:


      public:
         Beam(float staff_line_distance=0, float start_x=0, float start_staff_pos=0, Beam::Alignment start_alignment=Beam::Alignment::UNDEFINED, float end_x=0.0f, float end_staff_pos=0.0f, Beam::Alignment end_alignment=Beam::Alignment::UNDEFINED);
         ~Beam();

         void set_staff_line_distance(float staff_line_distance);
         void set_start_x(float start_x);
         void set_start_staff_pos(float start_staff_pos);
         void set_start_alignment(Beam::Alignment start_alignment);
         void set_end_x(float end_x);
         void set_end_staff_pos(float end_staff_pos);
         void set_end_alignment(Beam::Alignment end_alignment);
         float get_staff_line_distance() const;
         float get_start_x() const;
         float get_start_staff_pos() const;
         Beam::Alignment get_start_alignment() const;
         float get_end_x() const;
         float get_end_staff_pos() const;
         Beam::Alignment get_end_alignment() const;
         void render();
      };
   }
}



