#pragma once




//#include <cstdint>




template<class T>
class BitFlags
{
private:
   T flags; // 64 possible flags
public:

   BitFlags(T flags=0);

   bool has(T state_flag);
   bool set(T state_flag); // only sets individual flags, not a whole flag set
   bool unset(T state_flag);
   bool toggle(T state_flag);
   void clear();
};




template<class T>
BitFlags<T>::BitFlags(T flags)
   : flags(flags)
{}




template<class T>
bool BitFlags<T>::has(T state_flag)
{
   return (flags & state_flag) == state_flag;
}




template<class T>
bool BitFlags<T>::set(T state_flag)
{
   flags = flags | state_flag;
   return true;
}




template<class T>
bool BitFlags<T>::unset(T state_flag)
{
   flags &= ~state_flag;
   // e.g. this works in this case too, too:
   //		my.emask &= ~(ENABLE_SHOOT|SOME_OTHER|ONE_MORE);
   return false;
}




template<class T>
bool BitFlags<T>::toggle(T state_flag)
{
   if (has(state_flag)) unset(state_flag);
   else set(state_flag);
   return has(state_flag);
}




template<class T>
void BitFlags<T>::clear()
{
   flags = 0;
}




/*

BitFlags bitflags<int> // int is probably 32 bits, so 32 flags. On very old systems, it'll be 16. Newer will be 64.
                       // I opted for templating this instead of "#include <cstdint> because it requires the
                       // gcc user compiler to throw the following error:
                       //						
                       // c:\mingw\lib\gcc\mingw32\4.8.1\include\c++\bits\c++0x_warning.h:32:2: error: #er
                       // ror This file requires compiler and library support for the ISO C++ 2011 standar
                       // d. This support is currently experimental, and must be enabled with the -std=c++
                       // 11 or -std=gnu++11 compiler options.




// you might define your flags something like this:
enum tile_flag_t
{
   // this is 8 flags, and a dullard (0x00) which isn't a flag
   TILE_FLAG_UNDEF = 0x00,
   TILE_FLAG_BOUNDRY_TOP = 0x01,
   TILE_FLAG_BOUNDRY_BOTTOM = 0x02,
   TILE_FLAG_BOUNDRY_LEFT = 0x04,
   TILE_FLAG_BOUNDRY_RIGHT = 0x08,
   TILE_FLAG_LADDER = 0x10,
   TILE_FLAG_INSTADEATH = 0x20,
   TILE_FLAG_DESTRUCTABLE = 0x40,
   TILE_FLAG_GOAL = 0x80
};

*/




#endif
