#ifndef __AF_DECORATED_COUT
#define __AF_DECORATED_COUT




#include <iostream>
#include <fstream>




struct DecoratedCout
{
private:
   static const char *log_filename;
   static std::ofstream log_file;
   static int instances;

public:
   static const char *CONSOLE_RED;
   static const char *CONSOLE_YELLOW;
   static const char *CONSOLE_GREEN;
   static const char *CONSOLE_BLUE;
   static const char *CONSOLE_DEFAULT;

   const char *prefix;
   const char *console_color;
   bool show_to_cout;
   DecoratedCout(const char *prefix, const char *console_color, bool show_to_cout=false);
   ~DecoratedCout();

   template <typename T>
   DecoratedCout& operator<<(const T &x)
   {
      if (show_to_cout) std::cout << console_color << prefix << x << CONSOLE_DEFAULT;
      log_file << prefix << x << std::endl;
      return *this;
   }

   DecoratedCout& operator<< (std::ostream& (*f)(std::ostream &));
   DecoratedCout& operator<< (std::ostream& (*f)(std::ios &));
   DecoratedCout& operator<< (std::ostream& (*f)(std::ios_base &));
};




#endif
