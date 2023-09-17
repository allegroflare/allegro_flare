#pragma once


#include <AllegroFlare/MusicNotation/Parser/PitchToken.hpp>
#include <vector>


namespace AllegroFlare
{
   namespace MusicNotation
   {
      namespace Parser
      {
         class PitchTokenSorter
         {
         private:
            std::vector<AllegroFlare::MusicNotation::Parser::PitchToken> pitches;
            static bool custom_comparison_for_pitch_tokens(const AllegroFlare::MusicNotation::Parser::PitchToken& token1=AllegroFlare::MusicNotation::Parser::PitchToken(), const AllegroFlare::MusicNotation::Parser::PitchToken& token2=AllegroFlare::MusicNotation::Parser::PitchToken());

         protected:


         public:
            PitchTokenSorter(std::vector<AllegroFlare::MusicNotation::Parser::PitchToken> pitches={});
            ~PitchTokenSorter();

            void set_pitches(std::vector<AllegroFlare::MusicNotation::Parser::PitchToken> pitches);
            std::vector<AllegroFlare::MusicNotation::Parser::PitchToken> get_pitches() const;
            std::vector<AllegroFlare::MusicNotation::Parser::PitchToken> sort_unique_desc();
         };
      }
   }
}



