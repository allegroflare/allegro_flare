#pragma once


#include <iostream>
#include <string>
#include <typeinfo>

#if defined(__GNUC__) || defined(__clang__)  // GCC or Clang
   #include <cxxabi.h>
   #include <cstdlib>
   #define DEMANGLE_CLASS_NAME(name) demangle(name)
   inline std::string demangle(const char *mangled_name)
   {
      int status = 0;
      char *demangled = abi::__cxa_demangle(mangled_name, nullptr, nullptr, &status);
      std::string result = (status == 0) ? demangled : mangled_name;
      std::free(demangled);
      return result;
   }
#else  // MSVC (no need to demangle)
   #define DEMANGLE_CLASS_NAME(name) std::string(name)
#endif

// Define non-function-like macros
#define THIS_CLASS_NAME DEMANGLE_CLASS_NAME(typeid(*this).name())
#define THIS_METHOD_NAME __func__
#define THIS_CLASS_AND_METHOD_NAME (THIS_CLASS_NAME + "::" + THIS_METHOD_NAME)


