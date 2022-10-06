
#include <gtest/gtest.h>

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


