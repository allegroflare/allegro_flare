#pragma once


#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      class AdvancingText
      {
      public:
         static constexpr float DEFAULT_REVEAL_RATE_CHARACTERS_PER_SECOND = 60.0f;
         static constexpr float MIN_REVEAL_RATE_CHARACTERS_PER_SECOND = 0.0001f;

      private:
         std::string text;
         int revealed_characters_count;
         float reveal_started_at;
         float reveal_ended_at;
         float reveal_rate_characters_per_second;
         bool all_characters_are_revealed;

      protected:


      public:
         AdvancingText(std::string text="[text-not-set]");
         ~AdvancingText();

         void set_text(std::string text);
         std::string get_text() const;
         int get_revealed_characters_count() const;
         float get_reveal_started_at() const;
         float get_reveal_ended_at() const;
         float get_reveal_rate_characters_per_second() const;
         bool get_all_characters_are_revealed() const;
         void start();
         void set_reveal_rate_characters_per_second(float reveal_rate_characters_per_second=DEFAULT_REVEAL_RATE_CHARACTERS_PER_SECOND);
         void update();
         void reveal_all_characters();
         std::string generate_revealed_text();
      };
   }
}



