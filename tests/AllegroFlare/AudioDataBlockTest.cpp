
#include <gtest/gtest.h>

#define EXPECT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/AudioDataBlock.hpp>


TEST(AllegroFlare_AudioDataBlockTest, can_be_created_without_blowing_up)
{
   AllegroFlare::AudioDataBlock audio_data_block;
}


TEST(AllegroFlare_AudioDataBlockTest, sample_count__is_set_to_the_expected_default_value)
{
   AllegroFlare::AudioDataBlock audio_data_block;
   EXPECT_EQ(2048, audio_data_block.get_sample_count());
}


TEST(AllegroFlare_AudioDataBlockTest, initialize__will_work_without_blowing_up)
{
   AllegroFlare::AudioDataBlock audio_data_block;
   audio_data_block.initialize();
}


TEST(AllegroFlare_AudioDataBlockTest, sample_count__when_setting_to_a_value_of_0__raises_an_exception)
{
   AllegroFlare::AudioDataBlock audio_data_block;
   std::string expected_error_message = "AudioDataBlock::set_sample_count: error: guard \"(sample_count > 0)\" not met";
   EXPECT_THROW_WITH_MESSAGE(audio_data_block.set_sample_count(0), std::runtime_error, expected_error_message);
}


TEST(AllegroFlare_AudioDataBlockTest, sample_head_position__has_the_expected_default_value)
{
   AllegroFlare::AudioDataBlock audio_data_block;
   EXPECT_EQ(0, audio_data_block.get_sample_head_position());
}


TEST(AllegroFlare_AudioDataBlockTest, move_sample_head_position_by__will_move_the_sample_head_position)
{
   AllegroFlare::AudioDataBlock audio_data_block;
   audio_data_block.initialize();
   audio_data_block.move_sample_head_position_by(256);
   EXPECT_EQ(256, audio_data_block.get_sample_head_position());
}


TEST(AllegroFlare_AudioDataBlockTest,
   move_sample_head_position_by__when_moving_beyond_the_length_of_the_block__will_modulo_the_sample_head_position)
{
   AllegroFlare::AudioDataBlock audio_data_block;
   audio_data_block.initialize();
   audio_data_block.move_sample_head_position_by(256 + audio_data_block.get_sample_count());
   EXPECT_EQ(256, audio_data_block.get_sample_head_position());
}


TEST(AllegroFlare_AudioDataBlockTest,
   get_sample_at__will_return_the_sample_position_offset_by_the_head_position)
{
   AllegroFlare::AudioDataBlock audio_data_block(8);
   audio_data_block.initialize();
   audio_data_block.set_sample_at(2, 0.2, 0.3);
   std::vector<float> expected_block = {
       0.0f, 0.0f,   0.0f, 0.0f,   0.2f, 0.3f,   0.0f, 0.0f,
       0.0f, 0.0f,   0.0f, 0.0f,   0.0f, 0.0f,   0.0f, 0.0f,
   };
   EXPECT_EQ(expected_block, audio_data_block.get_block());
}


