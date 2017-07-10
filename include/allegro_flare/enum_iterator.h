#pragma once



#include <type_traits>



// This solution comes from:
// https://stackoverflow.com/questions/261963/how-can-i-iterate-over-an-enum
//
// With an enum like:
//
//   enum class foo {
//     one,
//     two,
//     three
//   };
//
// Usage is:
//
//   typedef Iterator<foo, foo::one, foo::three> fooIterator;
//
// And then you can iterate using range-for
//
//   for (foo i : fooIterator() ) { //notice the parenteses!
//      do_stuff(i);
//   }


template <typename T, T begin_val, T end_val>
class EnumIterator
{
private:
   typedef typename std::underlying_type<T>::type val_t;
   int val;

public:
   EnumIterator(const T & f) : val(static_cast<val_t>(f)) {}
   EnumIterator() : val(static_cast<val_t>(begin_val)) {}

   EnumIterator operator++ () { ++val; return *this; }
   T operator* () { return static_cast<T>(val); }
   bool operator!= (const EnumIterator& i) { return val != i.val; }

   EnumIterator begin() { return *this; }
   EnumIterator end() { static const EnumIterator end_iter = ++EnumIterator(end_val); return end_iter; }
};



