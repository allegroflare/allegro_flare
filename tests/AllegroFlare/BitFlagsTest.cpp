
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/BitFlags.hpp>


enum test_flag_t
{
   FLAG_0 = 0x00, // or, you could use (1 << 0), (1 << 1), (1 << 2), etc..
   FLAG_1 = 0x01,
   FLAG_2 = 0x02,
   FLAG_3 = 0x04,
   FLAG_4 = 0x08,
   FLAG_5 = 0x10,
   FLAG_6 = 0x20,
};



TEST(AllegroFlare_BitFlagsTest, can_be_crated_without_blowing_up)
{
   AllegroFlare::BitFlags<int16_t> bit_flags;
}


TEST(AllegroFlare_BitFlagsTest, can_be_copied)
{
   AllegroFlare::BitFlags<int16_t> bit_flags_a;
   AllegroFlare::BitFlags<int16_t> bit_flags_b;
   bit_flags_a = bit_flags_b;
}


TEST(AllegroFlare_BitFlagsTest, can_be_initialized_with_flags)
{
   AllegroFlare::BitFlags<int16_t> bit_flags(FLAG_3 | FLAG_5 | FLAG_6);

   EXPECT_EQ(true, bit_flags.has(FLAG_3));
   EXPECT_EQ(true, bit_flags.has(FLAG_5));
   EXPECT_EQ(true, bit_flags.has(FLAG_6));
}


TEST(AllegroFlare_BitFlagsTest, will_not_set_unintialized_flags)
{
   AllegroFlare::BitFlags<int16_t> bit_flags(FLAG_3 | FLAG_5 | FLAG_6);

   EXPECT_EQ(false, bit_flags.has(FLAG_1));
   EXPECT_EQ(false, bit_flags.has(FLAG_2));
   EXPECT_EQ(false, bit_flags.has(FLAG_4));
}


TEST(AllegroFlare_BitFlagsTest, set__sets_the_value_to_true)
{
   AllegroFlare::BitFlags<int16_t> bit_flags;
     
   ASSERT_EQ(false, bit_flags.has(FLAG_2));
   bit_flags.set(FLAG_2);
   EXPECT_EQ(true, bit_flags.has(FLAG_2));
}


TEST(AllegroFlare_BitFlagsTest, unset__sets_the_value_to_false)
{
   AllegroFlare::BitFlags<int16_t> bit_flags(FLAG_3);
     
   //bit_flags.set(FLAG_3);
   //ASSERT_EQ(true, bit_flags.has(FLAG_3));

   bit_flags.unset(FLAG_3);
   EXPECT_EQ(false, bit_flags.has(FLAG_3));
}


