

#include <AllegroFlare/AllegroContributorsList.hpp>




namespace AllegroFlare
{


AllegroContributorsList::AllegroContributorsList()
{
}


AllegroContributorsList::~AllegroContributorsList()
{
}


std::vector<std::string> AllegroContributorsList::build_allegro_5_contributors_list()
{
   // Label: "People who have contributed code to Allegro 5";
   // This list located at https://github.com/liballeg/allegro5/blob/master/CONTRIBUTORS.txt
   // TODO: Write a test that checks if the list has been updated
   // TODO: Find way to have non-ascii characters rendered
   std::vector<std::string> result = {
      "Aaron Bolyard",
      "Aldo Nunez",
      "Aldrik Ramaekers",
      "Andreas Ronnquist", // Contains non-ascii character
      "Angelo Mottola",
      "Arves100",
      "BQ",
      "Ben Davis",
      "Beoran",
      "Boris Carvajal",
      "Bruce Pascoe",
      "Bruno Felix Rezende Ribeiro", // Contains non-ascii character
      "Chris Robinson",
      "Christian Mauduit (ufoot)",
      "Daniel Johnson",
      "David Capello",
      "Dennis Busch",
      "Dennis Gooden",
      "Doug Thompson",
      "Douglas Mencken",
      "Edgar Reynaldo",
      "ElectricSolstice",
      "Elias Pschernig",
      "Eric Botcazou",
      "Erich Erstu",
      "Evert Glebbeek",
      "Firat Salgur",
      "Gabriel Queiroz",
      "George Foot",
      "Grzegorz Adam Hankiewicz",
      "Henrik Stokseth",
      "Hyena",
      "Isaac Cruz",
      "Javier Gonzalez Garces", // Contains non-ascii character
      "Jeff Bernard",
      "John-Kim Murphy",
      "Jonathan Lilliemarck",
      "Jonathan Seeley",
      "Jordan Woehr",
      "Julian Smythe",
      "Marcus Calhoun-Lopez",
      "Mark Oates",
      "Markus Henschel",
      "Martijn van Iersel",
      "Matt Smith",
      "Matthew Leverton",
      "Max Savenkov",
      "Michael Bukin",
      "Michael Swiger",
      "Michal Cichon", // Contains non-ascii character
      "Miguel A. Gavidia",
      "Milan Mimica",
      "Nick Black",
      "Nick Trout",
      "Peter Hull",
      "Peter Wang",
      "Polybios",
      "Reuben Bell",
      "Robert MacGregor",
      "Robert Ohannessian",
      "Rodolfo Lam",
      "Ryan Dickie",
      "Ryan Gumbs",
      "Ryan Patterson",
      "Ryan Roden-Corrent",
      "Sebastian Krzyszkowiak",
      "SiegeLord",
      "Simon Naarmann",
      "sleepywind",
      "Steven Wallace",
      "Sven Sandberg",
      "Thomas Fjellstrom",
      "Tobias Hansen",
      "Tobias Scheuer",
      "Todd Cope",
      "Tom Bass",
      "Trent Gamblin",
      "Vitaliy V. Tokarev",
      "[bk]door.maus",
      "beoran",
      "gameovera",
      "jmasterx",
      "juvinious",
      "kazzmir",
      "koro",
      "pedro-w",
      "pkrcel",
      "simast",
      "sleepywind",
      "torhu",
      "twobit",
      "verderten",
      "vkensou",
   };
   return result;
}


} // namespace AllegroFlare


