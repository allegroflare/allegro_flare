


#include <allegro_flare/decorated_cout.h>




DecoratedCout::DecoratedCout(const char *prefix, const char *console_color, bool show_to_cout)
   : prefix(prefix)
   , console_color(console_color)
   , show_to_cout(show_to_cout)
{
   if (instances == 0) log_file.open(log_filename);
   instances++;
}



DecoratedCout::~DecoratedCout()
{
   instances--;
   if (instances == 0) log_file.close();
}




DecoratedCout& DecoratedCout::operator<< (std::ostream& (*f)(std::ostream &)) {
   if (show_to_cout) f(std::cout);
   return *this;
}




DecoratedCout& DecoratedCout::operator<< (std::ostream& (*f)(std::ios &)) {
   if (show_to_cout) f(std::cout);
   return *this;
}




DecoratedCout& DecoratedCout::operator<< (std::ostream& (*f)(std::ios_base &)) {
   if (show_to_cout) f(std::cout);
   return *this;
}




const char *DecoratedCout::log_filename = "af_log.txt";
int DecoratedCout::instances = 0;
std::ofstream DecoratedCout::log_file;
const char *DecoratedCout::CONSOLE_RED = "\033[1;31m";
const char *DecoratedCout::CONSOLE_YELLOW = "\033[1;33m";
const char *DecoratedCout::CONSOLE_GREEN = "\033[1;32m";
const char *DecoratedCout::CONSOLE_BLUE = "\033[1;36m";
const char *DecoratedCout::CONSOLE_DEFAULT = "\033[0m";


