

#include <AllegroFlare/StackTracer.hpp>


#if defined(_WIN32) || defined(_WIN64)
   // Stacktrace features not implemented in Windows
#else
   #include <cxxabi.h>
   #include <execinfo.h>
#endif


namespace AllegroFlare
{


StackTracer::StackTracer()
{
}


StackTracer::~StackTracer()
{
}


std::string StackTracer::generate_stack_trace()
{
#if defined(_WIN32) || defined(_WIN64)
   return "Stacktrace features are not implemented in Windows.";
#else
   const int max_frames = 16;
   void* frame[max_frames];
   int frames = backtrace(frame, max_frames);
   char** frame_symbols = backtrace_symbols(frame, frames);

   std::string result = "Call stack:\n";
   for (int i = 1; i < frames; ++i) { // start from 1 to skip this function (generateStackTrace)
       std::string demangled;
       int status;
       char* demangled_name = abi::__cxa_demangle(frame_symbols[i], 0, 0, &status);

       if (status == 0) {
           demangled = demangled_name;
           free(demangled_name);
       } else {
           demangled = frame_symbols[i]; // if demangling failed, use the mangled name
       }

       result += "  " + demangled + "\n";
   }

   free(frame_symbols);
   return result;
#endif
}


} // namespace AllegroFlare


