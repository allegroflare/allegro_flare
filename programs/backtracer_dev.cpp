#include <allegro5/allegro.h>


#include <stdexcept>
#include <iostream>

class CustomException : public std::runtime_error {
public:
    CustomException(const std::string& message);
private:
};


#if defined(_WIN32) || defined(_WIN64)


CustomException::CustomException(const std::string& message)
    : std::runtime_error("This feature is not implemented on this platform (Win64).")
{}


#else


#include <execinfo.h>
#include <cxxabi.h>


std::string generateStackTrace() {
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
}


CustomException::CustomException(const std::string& message)
   : std::runtime_error(message + "\n" + generateStackTrace())
{}


#endif



int main(int argc, char **argv)
{
    try {
        // Some code that may throw an exception
        throw CustomException("An error occurred");
    } catch (const std::exception& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }

    return 0;
}

