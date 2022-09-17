

#include <WickedDemos/TileDemo.hpp>
#include <allegro5/allegro.h>


int main(int argc, char **argv)
{
   std::vector<std::string> args;
   for (int i=1; i<argc; i++) args.push_back(argv[i]);

   WickedDemos::TileDemo::run(args);
   return 0;
}


