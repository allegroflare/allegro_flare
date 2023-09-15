
#include <gtest/gtest.h>

#include <AllegroFlare/MusicNotation/ChordNoteheadPositionResolver.hpp>


const bool operator==(
      const AllegroFlare::MusicNotation::ChordNoteheadPositionResolver::PositionType &a1,
      const AllegroFlare::MusicNotation::ChordNoteheadPositionResolver::PositionType &a2
   )
{
   return ((int)a1 == (int)a2);
}


TEST(AllegroFlare_MusicNotation_ChordNoteheadPositionResolverTest, can_be_created_without_blowing_up)
{
   AllegroFlare::MusicNotation::ChordNoteheadPositionResolver chord_notehead_position_resolver;
}


TEST(AllegroFlare_MusicNotation_ChordNoteheadPositionResolverTest, solve__does_not_blow_up)
{
   AllegroFlare::MusicNotation::ChordNoteheadPositionResolver chord_notehead_position_resolver;
   chord_notehead_position_resolver.solve();
}


TEST(AllegroFlare_MusicNotation_ChordNoteheadPositionResolverTest, solve__will_build_the_expected_positions)
{
   using AllegroFlare::MusicNotation::ChordNoteheadPositionResolver;

   AllegroFlare::MusicNotation::ChordNoteheadPositionResolver chord_notehead_position_resolver;
   chord_notehead_position_resolver.solve();
   std::vector<std::pair<int, ChordNoteheadPositionResolver::PositionType>> expected = {};
   std::vector<std::pair<int, ChordNoteheadPositionResolver::PositionType>> actual =
      chord_notehead_position_resolver.get_positions();

   EXPECT_EQ(expected, actual);
}


