

#include <AllegroFlare/Generators/PersonNameGenerator.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Generators
{


PersonNameGenerator::PersonNameGenerator()
   : random()
   , initialized(false)
   , victorian_boy_names({})
   , victorian_girl_names({})
   , next_boy_name_index(0)
   , next_girl_name_index(0)
{
}


PersonNameGenerator::~PersonNameGenerator()
{
}


void PersonNameGenerator::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[PersonNameGenerator::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PersonNameGenerator::initialize: error: guard \"(!initialized)\" not met");
   }
   randomize();
   initialized = true;
   return;
}

void PersonNameGenerator::randomize(uint32_t seed)
{
   random.set_seed(seed);

   victorian_boy_names = build_victorian_boy_name_list();
   victorian_girl_names = build_victorian_girl_name_list();

   random.shuffle_elements(victorian_boy_names);
   random.shuffle_elements(victorian_girl_names);
   return;
}

std::string PersonNameGenerator::generate_boy_name()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[PersonNameGenerator::generate_boy_name]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PersonNameGenerator::generate_boy_name: error: guard \"initialized\" not met");
   }
   if (next_boy_name_index >= victorian_boy_names.size()) return ""; return victorian_boy_names[next_boy_name_index++];
}

std::string PersonNameGenerator::generate_girl_name()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[PersonNameGenerator::generate_girl_name]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PersonNameGenerator::generate_girl_name: error: guard \"initialized\" not met");
   }
   if (next_girl_name_index >= victorian_girl_names.size()) return ""; return victorian_girl_names[next_girl_name_index++];
}

std::vector<std::string> PersonNameGenerator::build_names_with_double_consecutive_ts()
{
   return
      { "Annette"
      , "Atticus"
      , "Barrett"
      , "Beckett"
      , "Bennett"
      , "Bettina"
      , "Brett"
      , "Britta"
      , "Brittany"
      , "Dottie"
      , "Elliott"
      , "Everett"
      , "Garrett"
      , "Gittel"
      , "Gretta"
      , "Hattie"
      , "Henrietta"
      , "Hettie"
      , "Jett"
      , "Lettie"
      , "Loretta"
      , "Lotta"
      , "Lottie"
      , "Matthew"
      , "Mattias"
      , "Mattie"
      , "Nettie"
      , "Ottilia"
      , "Otto"
      , "Patty"
      , "Ritter"
      , "Rosetta"
      , "Scarlett"
      , "Scott"
      , "Scotty"
      , "Sutton"
      , "Wyatt"
      };
}

std::vector<std::string> PersonNameGenerator::build_victorian_boy_name_list()
{
   return { "Adam" , "Billy" , "Bruce" , "Chris" , "Christopher" , "David" , "Donald" , "Donny" , "Frankie" , "George" , "Gorby" , "Greg" , "Hamilton" , "Homer" , "Hugo" , "Jack" , "James" , "Jeremy" , "Johnathan" , "Johnny" , "Jules" , "Kirk" , "Luther" , "Matt" , "Michael" , "Nick" , "Norman" , "Patrick" , "Paul" , "Peter" , "Richard" , "Robert" , "Sam" , "Thomas" , "Tim" , "Timmy" , "Toby" , "Tommy" , "Walter" , "Edward" };
}

std::vector<std::string> PersonNameGenerator::build_victorian_girl_name_list()
{
   return { "Abigail" , "Annabelle" , "Audrey" , "Beth" , "Caren" , "Caroline" , "Christine" , "Claire" , "Doris" , "Elise" , "Elizabeth" , "Ella" , "Emily" , "Erica" , "Florence" , "Gloria" , "Grace" , "Hannah" , "Hellen" , "Ingrid" , "Jill" , "Kelly" , "Lily" , "Lisa" , "Madelyn" , "Mary" , "Natalie" , "Nichole" , "Noel" , "Olga" , "Penelope" , "Penny" , "Sarah" , "Scarlett" , "Sally" , "Stacy" , "Tanya" , "Tara" , "Vivian" , "Wendy" };
}


} // namespace Generators
} // namespace AllegroFlare


