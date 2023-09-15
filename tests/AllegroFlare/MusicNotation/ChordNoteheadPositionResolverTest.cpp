
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
   std::vector<AllegroFlare::MusicNotation::Parser::PitchToken> pitches = {
      { 7, 0, 0 },
      { 5, 0, 0 },
      { 4, 0, 0 },
      { 3, 0, 0 },
      { 1, 0, 0 },
      { -2, 0, 0 },
      { -3, 0, 0 },
      { -5, 0, 0 },
   };

   AllegroFlare::MusicNotation::ChordNoteheadPositionResolver chord_notehead_position_resolver(pitches);
   chord_notehead_position_resolver.solve();
   std::vector<std::pair<int, ChordNoteheadPositionResolver::PositionType>> expected = {
      { 7, ChordNoteheadPositionResolver::PositionType::STEMSIDE },
      { 5, ChordNoteheadPositionResolver::PositionType::RIGHT },
      { 4, ChordNoteheadPositionResolver::PositionType::LEFT },
      { 3, ChordNoteheadPositionResolver::PositionType::RIGHT },
      { 1, ChordNoteheadPositionResolver::PositionType::STEMSIDE },
      { -2, ChordNoteheadPositionResolver::PositionType::RIGHT},
      { -3, ChordNoteheadPositionResolver::PositionType::LEFT },
      { -5, ChordNoteheadPositionResolver::PositionType::STEMSIDE },
   };
   std::vector<std::pair<int, ChordNoteheadPositionResolver::PositionType>> actual =
      chord_notehead_position_resolver.get_positions();

   EXPECT_EQ(expected, actual);
}


TEST(AllegroFlare_MusicNotation_ChordNoteheadPositionResolverTest,
   seconds_exist__will_return_true_if_there_are_two_or_more_staff_positions_that_are_adjacent)
{
   using AllegroFlare::MusicNotation::ChordNoteheadPositionResolver;
   std::vector<AllegroFlare::MusicNotation::Parser::PitchToken> pitches = {
      { 5, 0, 0 },
      { 4, 0, 0 },
   };

   AllegroFlare::MusicNotation::ChordNoteheadPositionResolver chord_notehead_position_resolver(pitches);
   chord_notehead_position_resolver.solve();
   EXPECT_EQ(true, chord_notehead_position_resolver.get_seconds_exist());
}


TEST(AllegroFlare_MusicNotation_ChordNoteheadPositionResolverTest,
   seconds_exist__will_return_false_if_there_not_two_or_more_staff_positions_that_are_adjacent)
{
   using AllegroFlare::MusicNotation::ChordNoteheadPositionResolver;
   std::vector<AllegroFlare::MusicNotation::Parser::PitchToken> pitches = {
      { 5, 0, 0 },
      { 3, 0, 0 },
      { 1, 0, 0 },
   };

   AllegroFlare::MusicNotation::ChordNoteheadPositionResolver chord_notehead_position_resolver(pitches);
   chord_notehead_position_resolver.solve();
   EXPECT_EQ(false, chord_notehead_position_resolver.get_seconds_exist());
}


