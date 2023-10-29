#pragma once


namespace AllegroFlare
{
   template<class T>
   class BitFlags
   {
   private:
      T flags;
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
      //  my.emask &= ~(ENABLE_SHOOT|SOME_OTHER|ONE_MORE);
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


}



