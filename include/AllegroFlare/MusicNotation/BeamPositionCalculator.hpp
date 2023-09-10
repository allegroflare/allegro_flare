#pragma once


#include <utility>
#include <vector>


namespace AllegroFlare
{
   namespace MusicNotation
   {
      class BeamPositionCalculator
      {
      public:

         enum StemDirection
         {
            UNDEFINED = 0,
            UP,
            DOWN,
         };
      private:
         std::vector<std::pair<float, int>> notehead_staff_positions;

      protected:


      public:
         BeamPositionCalculator(std::vector<std::pair<float, int>> notehead_staff_positions={});
         ~BeamPositionCalculator();

         void set_notehead_staff_positions(std::vector<std::pair<float, int>> notehead_staff_positions);
         std::vector<std::pair<float, int>> get_notehead_staff_positions() const;
         BeamPositionCalculator::StemDirection infer_preferred_stem_direction();
      };
   }
}



