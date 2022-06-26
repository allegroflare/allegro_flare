
#include <gtest/gtest.h>

#include <AllegroFlare/Generators/LoremIpsumGenerator.hpp>


TEST(AllegroFlare_Generators_LoremIpsumGeneratorTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Generators::LoremIpsumGenerator lorem_ipsum_generator;
}


TEST(AllegroFlare_Generators_LoremIpsumGeneratorTest, generate_paragraphs__will_return_paragraphs_of_lorem_ipsum_text)
{
   AllegroFlare::Generators::LoremIpsumGenerator lorem_ipsum_generator;
   std::string result = lorem_ipsum_generator.generate_paragraphs(2);
   std::string expected_result = {
      "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec fringilla arcu "
      "nec magna mattis cursus. Maecenas non justo urna. Vivamus eu augue tristique, "
      "pharetra enim ut, sollicitudin quam. Aenean ut purus at enim elementum rhoncus. "
      "In a finibus sapien. Donec mattis laoreet luctus. Aliquam eu accumsan sapien, at "
      "congue massa. Phasellus consequat sapien ac scelerisque finibus. Curabitur "
      "hendrerit, diam eget faucibus rhoncus, ante nulla mattis lorem, vitae semper "
      "sapien sem sit amet ex. Donec sit amet dolor libero. Vestibulum ante ipsum "
      "primis in faucibus orci luctus et ultrices posuere cubilia curae; Nunc dignissim "
      "aliquam luctus. Sed varius odio a neque ultrices, ac pretium ligula aliquam. "
      "Proin neque arcu, gravida et nisi non, ullamcorper fringilla ligula. Duis "
      "laoreet sollicitudin nunc, eu ornare diam consequat ac. Duis dapibus tellus ac "
      "mauris bibendum finibus."
      "\n"
      "Proin vitae vulputate orci, a hendrerit tellus. Etiam nec fermentum risus. "
      "Aenean at aliquam est, et hendrerit augue. Vivamus tincidunt convallis "
      "tristique. Nunc nunc ipsum, rutrum consectetur elit at, vulputate sollicitudin "
      "mi. Proin quis nisi lectus. Vestibulum eget condimentum ex. Vivamus facilisis "
      "elit urna, et lacinia velit maximus maximus. Mauris elit mi, pellentesque ut "
      "sagittis sit amet, semper in sapien. Nullam sed lobortis nisl, ac porttitor "
      "metus."
   };
   EXPECT_EQ(expected_result, result);
}


