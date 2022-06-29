#include <AllegroFlare/Random.hpp>

#include <algorithm>
#include <AllegroFlare/Color.hpp>


namespace AllegroFlare
{
   Random::Random(unsigned int seed)
      : seed(seed)
   {
      set_seed(seed);
   }




   void Random::set_seed(unsigned int new_seed)
   {
      seed = new_seed;
      random_number_generator.seed(seed);
   }




   unsigned int Random::get_seed()
   {
      return seed;
   }




   bool Random::get_random_bool()
   {
      return random_number_generator() % 2;
   }




   int Random::get_random_int(int min, int max)
   {
      int fixed_min = std::min(min, max);
      int fixed_max = std::max(min, max);
      int range = fixed_max - fixed_min + 1;
      return random_number_generator() % range + fixed_min;
   }




   float Random::get_random_float(float min, float max)
   {
      float fixed_min = std::min(min, max);
      float fixed_max = std::max(min, max);
      float range = fixed_max - fixed_min;
      
      return (random_number_generator() / (float)random_number_generator.max()) * range + fixed_min;
   }




   double Random::get_random_double(double min, double max)
   {
      double fixed_min = std::min(min, max);
      double fixed_max = std::max(min, max);
      double range = fixed_max - fixed_min;
      
      return (random_number_generator() / (double)random_number_generator.max()) * range + fixed_min;
   }




   unsigned char Random::get_random_letter(bool lowercase)
   {
      int num = get_random_int(0, 26);
      if (lowercase) return (unsigned char)(num%26 + 'a');
      return (unsigned char)(num%26 + 'A');
   }




   unsigned char Random::get_random_letter_or_number()
   {
      int num = get_random_int(0, 10+26+26); // 10 digits, 26 uppercase, 26 lowercase
      if (num <= 10) return (unsigned char)(num%10 + '0');
      else if ((num-10) <= 26) return (unsigned char)(num%26 + 'A');
      else if ((num-10-26) <= 26) return (unsigned char)(num%26 + 'a');
      return '-';
   }




   std::string Random::get_random_string(unsigned int length)
   {
      std::string return_str;
      for (unsigned i=0; i<length; i++)
         return_str += get_random_letter_or_number();
      return return_str;
   }




   bool Random::get_one_in_chance(int chance)
   {
      if (get_random_int(0, chance - 1) == 0)
         return true;
      return false;
   }




   int Random::roll_dice(int sides, int number_of_die)
   {
      int result = 0;
      for (int i = 0; i < number_of_die; i++)
         result += get_random_int(sides, 1);
      return result;
   }




   ALLEGRO_COLOR Random::get_random_color()
   {
      static std::vector<ALLEGRO_COLOR> possible_colors = {
         AllegroFlare::Color::AliceBlue,
         AllegroFlare::Color::AntiqueWhite,
         AllegroFlare::Color::Aqua,
         AllegroFlare::Color::Aquamarine,
         AllegroFlare::Color::Azure,
         AllegroFlare::Color::Beige,
         AllegroFlare::Color::Bisque,
         AllegroFlare::Color::Black,
         AllegroFlare::Color::BlanchedAlmond,
         AllegroFlare::Color::Blue,
         AllegroFlare::Color::BlueViolet,
         AllegroFlare::Color::Brown,
         AllegroFlare::Color::Burlywood,
         AllegroFlare::Color::CadetVlue,
         AllegroFlare::Color::Chartreuse,
         AllegroFlare::Color::Chocolate,
         AllegroFlare::Color::Coral,
         AllegroFlare::Color::CornflowerBlue,
         AllegroFlare::Color::Cornsilk,
         AllegroFlare::Color::Crimson,
         AllegroFlare::Color::Cyan,
         AllegroFlare::Color::DarkBlue,
         AllegroFlare::Color::DarkCyan,
         AllegroFlare::Color::DarkGoldenrod,
         AllegroFlare::Color::DarkGray,
         AllegroFlare::Color::DarkGreen,
         AllegroFlare::Color::DarkKhaki,
         AllegroFlare::Color::DarkMagenta,
         AllegroFlare::Color::DarkOliveGreen,
         AllegroFlare::Color::DarkOrange,
         AllegroFlare::Color::DarkOrchid,
         AllegroFlare::Color::DarkRed,
         AllegroFlare::Color::DarkSalmon,
         AllegroFlare::Color::DarkSeaGreen,
         AllegroFlare::Color::DarkSlateBlue,
         AllegroFlare::Color::DarkSlateGray,
         AllegroFlare::Color::DarkTurquoise,
         AllegroFlare::Color::DarkViolet,
         AllegroFlare::Color::DeepPink,
         AllegroFlare::Color::DeepSkyBlue,
         AllegroFlare::Color::DimGray,
         AllegroFlare::Color::DodgerBlue,
         AllegroFlare::Color::FireBrick,
         AllegroFlare::Color::FloralWhite,
         AllegroFlare::Color::ForestGreen,
         AllegroFlare::Color::Fuchsia,
         AllegroFlare::Color::Gainsboro,
         AllegroFlare::Color::GhostWhite,
         AllegroFlare::Color::Goldenrod,
         AllegroFlare::Color::Gold,
         AllegroFlare::Color::Gray,
         AllegroFlare::Color::Green,
         AllegroFlare::Color::GreenYellow,
         AllegroFlare::Color::Honeydew,
         AllegroFlare::Color::HotPink,
         AllegroFlare::Color::IndianRed,
         AllegroFlare::Color::Indigo,
         AllegroFlare::Color::Ivory,
         AllegroFlare::Color::Khaki,
         AllegroFlare::Color::LavenderBlush,
         AllegroFlare::Color::Lavender,
         AllegroFlare::Color::LawnGreen,
         AllegroFlare::Color::LemonChiffon,
         AllegroFlare::Color::LightBlue,
         AllegroFlare::Color::LightCoral,
         AllegroFlare::Color::LightCyan,
         AllegroFlare::Color::LightGoldenrodYellow,
         AllegroFlare::Color::LightGreen,
         AllegroFlare::Color::LightGrey,
         AllegroFlare::Color::LightPink,
         AllegroFlare::Color::LightSalmon,
         AllegroFlare::Color::LightSeaGreen,
         AllegroFlare::Color::LightSkyBlue,
         AllegroFlare::Color::LightSlateGray,
         AllegroFlare::Color::LightSteelBlue,
         AllegroFlare::Color::LightYellow,
         AllegroFlare::Color::Lime,
         AllegroFlare::Color::LimeGreen,
         AllegroFlare::Color::Linen,
         AllegroFlare::Color::Magenta,
         AllegroFlare::Color::Maroon,
         AllegroFlare::Color::MediumAquamarine,
         AllegroFlare::Color::MediumBlue,
         AllegroFlare::Color::MediumOrchid,
         AllegroFlare::Color::MediumPurple,
         AllegroFlare::Color::MediumSeaGreen,
         AllegroFlare::Color::MediumSlateBlue,
         AllegroFlare::Color::MediumSpringGreen,
         AllegroFlare::Color::MediumTurquoise,
         AllegroFlare::Color::MediumVioletRed,
         AllegroFlare::Color::MidnightBlue,
         AllegroFlare::Color::MintCream,
         AllegroFlare::Color::MistyRose,
         AllegroFlare::Color::Moccasin,
         AllegroFlare::Color::NavajoWhite,
         AllegroFlare::Color::Navy,
         AllegroFlare::Color::Oldlace,
         AllegroFlare::Color::Olive,
         AllegroFlare::Color::OliveDrab,
         AllegroFlare::Color::Orange,
         AllegroFlare::Color::OrangeRed,
         AllegroFlare::Color::Orchid,
         AllegroFlare::Color::PaleGoldenrod,
         AllegroFlare::Color::PaleGreen,
         AllegroFlare::Color::PaleTurquoise,
         AllegroFlare::Color::PaleVioletRed,
         AllegroFlare::Color::PapayaWhip,
         AllegroFlare::Color::PeachPuff,
         AllegroFlare::Color::Peru,
         AllegroFlare::Color::Pink,
         AllegroFlare::Color::Plum,
         AllegroFlare::Color::PowderBlue,
         AllegroFlare::Color::Purple,
         AllegroFlare::Color::WebPurple,
         AllegroFlare::Color::RebeccaPurple,
         AllegroFlare::Color::Red,
         AllegroFlare::Color::RosyBrown,
         AllegroFlare::Color::RoyalBlue,
         AllegroFlare::Color::SaddleBrown,
         AllegroFlare::Color::Salmon,
         AllegroFlare::Color::SandyBrown,
         AllegroFlare::Color::SeaGreen,
         AllegroFlare::Color::Seashell,
         AllegroFlare::Color::Sienna,
         AllegroFlare::Color::Silver,
         AllegroFlare::Color::SkyBlue,
         AllegroFlare::Color::SlateBlue,
         AllegroFlare::Color::SlateGray,
         AllegroFlare::Color::Snow,
         AllegroFlare::Color::SpringGreen,
         AllegroFlare::Color::SteelBlue,
         AllegroFlare::Color::Tan,
         AllegroFlare::Color::Teal,
         AllegroFlare::Color::Thistle,
         AllegroFlare::Color::Tomato,
         AllegroFlare::Color::Turquoise,
         AllegroFlare::Color::Violet,
         AllegroFlare::Color::Wheat,
         AllegroFlare::Color::White,
         AllegroFlare::Color::WhiteSmoke,
         AllegroFlare::Color::Yellow,
         AllegroFlare::Color::YellowGreen,
      };

      return possible_colors[get_random_int(0, possible_colors.size())];
   }
}



