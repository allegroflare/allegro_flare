
#include <gtest/gtest.h>

#include <AllegroFlare/AudioProcessing/AudioDataBlock.hpp>
#include <AllegroFlare/Testing/ErrorAssertions.hpp>


TEST(AllegroFlare_AudioProcessing_AudioDataBlockTest, can_be_created_without_blowing_up)
{
   AllegroFlare::AudioProcessing::AudioDataBlock audio_data_block;
}


TEST(AllegroFlare_AudioProcessing_AudioDataBlockTest, sample_count__is_set_to_the_expected_default_value)
{
   AllegroFlare::AudioProcessing::AudioDataBlock audio_data_block;
   EXPECT_EQ(2048, audio_data_block.get_sample_count());
}


TEST(AllegroFlare_AudioProcessing_AudioDataBlockTest, initialize__will_work_without_blowing_up)
{
   AllegroFlare::AudioProcessing::AudioDataBlock audio_data_block;
   audio_data_block.initialize();
}


TEST(AllegroFlare_AudioProcessing_AudioDataBlockTest, initialize__will_set_the_data_block_to_the_expected_size)
{
   AllegroFlare::AudioProcessing::AudioDataBlock audio_data_block;
   audio_data_block.initialize();
   EXPECT_EQ(2048*2, audio_data_block.get_block_ref().size());
}


TEST(AllegroFlare_AudioProcessing_AudioDataBlockTest, sample_count__when_setting__will_resize_the_data_block_to_fit)
{
   AllegroFlare::AudioProcessing::AudioDataBlock audio_data_block;
   audio_data_block.initialize();
   audio_data_block.set_sample_count(8);
   EXPECT_EQ(16, audio_data_block.get_block_ref().size());
}


TEST(AllegroFlare_AudioProcessing_AudioDataBlockTest, sample_count__before_being_initialized__will_throw_an_error)
   // NOTE: At the time of writing, this guard is only needed because the "channel_count" has not yet been set
{
   AllegroFlare::AudioProcessing::AudioDataBlock audio_data_block;
   EXPECT_THROW_GUARD_ERROR(
      audio_data_block.set_sample_count(256),
      "AllegroFlare::AudioProcessing::AudioDataBlock::set_sample_count",
      "initialized"
   );
}


TEST(AllegroFlare_AudioProcessing_AudioDataBlockTest, sample_count__when_setting_to_a_value_of_0__raises_an_exception)
{
   AllegroFlare::AudioProcessing::AudioDataBlock audio_data_block;
   audio_data_block.initialize();
   EXPECT_THROW_GUARD_ERROR(
      audio_data_block.set_sample_count(0),
      "AllegroFlare::AudioProcessing::AudioDataBlock::set_sample_count",
      "(sample_count > 0)"
   );
}


TEST(AllegroFlare_AudioProcessing_AudioDataBlockTest, sample_head_position__has_the_expected_default_value)
{
   AllegroFlare::AudioProcessing::AudioDataBlock audio_data_block;
   EXPECT_EQ(0, audio_data_block.get_sample_head_position());
}


TEST(AllegroFlare_AudioProcessing_AudioDataBlockTest, move_sample_head_position_by__will_move_the_sample_head_position)
{
   AllegroFlare::AudioProcessing::AudioDataBlock audio_data_block;
   audio_data_block.initialize();
   audio_data_block.move_sample_head_position_by(256);
   EXPECT_EQ(256, audio_data_block.get_sample_head_position());
}


TEST(AllegroFlare_AudioProcessing_AudioDataBlockTest,
   move_sample_head_position_by__when_moving_beyond_the_length_of_the_block__will_modulo_the_sample_head_position)
{
   AllegroFlare::AudioProcessing::AudioDataBlock audio_data_block;
   audio_data_block.initialize();
   audio_data_block.move_sample_head_position_by(256 + audio_data_block.get_sample_count());
   EXPECT_EQ(256, audio_data_block.get_sample_head_position());
}


TEST(AllegroFlare_AudioProcessing_AudioDataBlockTest, set_sample_at__will_set_the_sample_at_the_position)
{
   AllegroFlare::AudioProcessing::AudioDataBlock audio_data_block;
   audio_data_block.initialize();
   audio_data_block.set_sample_count(4);
   audio_data_block.set_sample_at(2, 0.2, 0.3);
   std::vector<float> expected_block = { 0.0f, 0.0f,   0.0f, 0.0f,   0.2f, 0.3f,   0.0f, 0.0f, };
   EXPECT_EQ(expected_block, audio_data_block.get_block());
}


TEST(AllegroFlare_AudioProcessing_AudioDataBlockTest,
   set_sample_at__will_set_the_sample_position_offset_by_the_head_position)
{
   AllegroFlare::AudioProcessing::AudioDataBlock audio_data_block;
   audio_data_block.initialize();
   audio_data_block.set_sample_count(4);
   audio_data_block.move_sample_head_position_by(2);
   audio_data_block.set_sample_at(1, 0.4, 0.5);
   std::vector<float> expected_block = { 0.0f, 0.0f,   0.0f, 0.0f,   0.0f, 0.0f,   0.4f, 0.5f, };
   EXPECT_EQ(expected_block, audio_data_block.get_block());
}


TEST(AllegroFlare_AudioProcessing_AudioDataBlockTest,
   set_sample_at__will_set_the_sample_position_if_the_head_position_is_past_the_length)
{
   AllegroFlare::AudioProcessing::AudioDataBlock audio_data_block;
   audio_data_block.initialize();
   audio_data_block.set_sample_count(4);
   audio_data_block.move_sample_head_position_by(6);
   audio_data_block.set_sample_at(3, 0.4, 0.5);
   std::vector<float> expected_block = { 0.0f, 0.0f,   0.4f, 0.5f,   0.0f, 0.0f,   0.0f, 0.0f, };
   EXPECT_EQ(expected_block, audio_data_block.get_block());
}


TEST(AllegroFlare_AudioProcessing_AudioDataBlockTest,
   get_sample_at__will_return_the_sample_at_the_position)
{
   AllegroFlare::AudioProcessing::AudioDataBlock audio_data_block;
   audio_data_block.initialize();
   audio_data_block.set_sample_count(4);
   audio_data_block.get_block_ref() = { 0.0f, 0.0f,   0.4f, 0.5f,   0.0f, 0.0f,   0.0f, 0.0f, };
   std::pair<float, float> expected_sample = { 0.4f, 0.5f };
   std::pair<float, float> actual_sample = audio_data_block.get_sample_at(1);
   EXPECT_EQ(expected_sample, actual_sample);
}


TEST(AllegroFlare_AudioProcessing_AudioDataBlockTest,
   get_sample_at__will_return_the_sample_at_the_position_respecting_the_sample_head_position)
{
   AllegroFlare::AudioProcessing::AudioDataBlock audio_data_block;
   audio_data_block.initialize();
   audio_data_block.set_sample_count(4);
   audio_data_block.get_block_ref() = { 0.0f, 0.0f,   0.0f, 0.0f,   0.0f, 0.0f,   0.4f, 0.5f, };
   audio_data_block.move_sample_head_position_by(2);
   std::pair<float, float> expected_sample = { 0.4f, 0.5f };
   std::pair<float, float> actual_sample = audio_data_block.get_sample_at(1);
   EXPECT_EQ(expected_sample, actual_sample);
}


TEST(AllegroFlare_AudioProcessing_AudioDataBlockTest,
   get_sample_at__will_return_the_sample_at_the_position_respecting_the_sample_head_position_when_it_is_past_the_length)
{
   AllegroFlare::AudioProcessing::AudioDataBlock audio_data_block;
   audio_data_block.initialize();
   audio_data_block.set_sample_count(4);
   audio_data_block.get_block_ref() = { 0.0f, 0.0f,   0.0f, 0.0f,   0.4f, 0.5f,   0.0f, 0.0f };
   audio_data_block.move_sample_head_position_by(5);
   std::pair<float, float> expected_sample = { 0.4f, 0.5f };
   std::pair<float, float> actual_sample = audio_data_block.get_sample_at(1);
   EXPECT_EQ(expected_sample, actual_sample);
}


