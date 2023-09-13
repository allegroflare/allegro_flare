#pragma once




namespace AllegroFlare
{
   namespace MusicNotation
   {
      namespace Parser
      {
         class PitchToken
         {
         public:
            int staff_position;
            int accidental;
            bool accidental_natural;

            PitchToken(int staff_position=0, int accidental=0, bool accidental_natural=false);
            ~PitchToken();

            void set_staff_position(int staff_position);
            void set_accidental(int accidental);
            void set_accidental_natural(bool accidental_natural);
            int get_staff_position() const;
            int get_accidental() const;
            bool get_accidental_natural() const;
            bool has_accidental();
            int calculate_accidental_weight() const;
         };
      }
   }
}



