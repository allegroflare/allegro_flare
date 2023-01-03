
#include <gtest/gtest.h>

#include <AllegroFlare/Logger.hpp>


TEST(AllegroFlare_LoggerTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Logger logger;
}


TEST(AllegroFlare_LoggerTest, build_not_included_message__will_return_text_formatted_as_a_not_included_warning)
{
   AllegroFlare::Logger logger;
   // TODO
}


TEST(AllegroFlare_LoggerTest, build_not_included_message__will_escape_double_quotes_in_params)
{
   AllegroFlare::Logger logger;
   // TODO
}



// Below is a code example showing variadic arguments in C++ using std::format (will be available in C++20
// See: https://codereview.stackexchange.com/questions/269425/implementing-stdformat

/*
template<typename T>
void format_helper(std::ostringstream& oss,
                   std::string_view& str, const T& value)
{
    std::size_t openBracket = str.find('{');
    if (openBracket == std::string::npos) { return; }
    std::size_t closeBracket = str.find('}', openBracket + 1);
    if (closeBracket == std::string::npos) { return; }
    oss << str.substr(0, openBracket) << value;
    str = str.substr(closeBracket + 1);
}

template<typename... Targs>
std::string format(std::string_view str, Targs...args)
{
    std::ostringstream oss;
    (format_helper(oss, str, args),...);
    oss << str;
    return oss.str();
}
*/


