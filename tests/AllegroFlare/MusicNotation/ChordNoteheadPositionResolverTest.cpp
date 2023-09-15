
#include <gtest/gtest.h>

#include <AllegroFlare/MusicNotation/ChordNoteheadPositionResolver.hpp>


TEST(AllegroFlare_MusicNotation_ChordNoteheadPositionResolverTest, can_be_created_without_blowing_up)
{
   AllegroFlare::MusicNotation::ChordNoteheadPositionResolver chord_notehead_position_resolver;
}


TEST(AllegroFlare_MusicNotation_ChordNoteheadPositionResolverTest, solve__does_not_blow_up)
{
   AllegroFlare::MusicNotation::ChordNoteheadPositionResolver chord_notehead_position_resolver;
   chord_notehead_position_resolver.solve();
}


