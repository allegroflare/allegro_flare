

#include <AllegroFlare/Network2/URLTokenizer.hpp>




namespace AllegroFlare
{
namespace Network2
{


URLTokenizer::URLTokenizer(std::string full_url)
   : full_url(full_url)
{
}


URLTokenizer::~URLTokenizer()
{
}


void URLTokenizer::set_full_url(std::string full_url)
{
   this->full_url = full_url;
}


std::string URLTokenizer::get_full_url() const
{
   return full_url;
}


std::string URLTokenizer::extract_port()
{
   return split_tokens().second;
}

std::string URLTokenizer::extract_host()
{
   return split_tokens().first;
}

std::pair<std::string, std::string> URLTokenizer::split_tokens()
{
   std::pair<std::string, std::string> result;

   std::size_t length_of_prefix = 6;

   if (full_url.substr(0, length_of_prefix) != "tcp://")
   {
      throw std::runtime_error("Network2::URLTokenizer: invalid url format (error 1)");
   }

   std::size_t pos_of_port_start = full_url.find_first_of(":", length_of_prefix);
   if (pos_of_port_start == std::string::npos)
   {
      throw std::runtime_error("Network2::URLTokenizer: invalid url format (error 2)");
   }

   // strip off the port number
   result.second = full_url.substr(pos_of_port_start+1);

   // strip off tcp prefix:
   std::string subresult = full_url.substr(0, pos_of_port_start);
   result.first = subresult.substr(6);

   if (!(has_min_length(result.second, 1)))
   {
      throw std::runtime_error("Network2::URLTokenizer: invalid url format (error 3)");
   }

   if (!(has_min_length(result.second, 4)))
   {
      throw std::runtime_error("Network2::URLTokenizer: invalid url format (error 4)");
   }

   return result;
}

bool URLTokenizer::has_min_length(std::string string, int min)
{
   return (string.length() >= min);
}

std::string URLTokenizer::trim(std::string s)
{
   // ltrim
   s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int c) {return !std::isspace(c);}));
   // rtrim
   s.erase(std::find_if(s.rbegin(), s.rend(), [](int c) {return !std::isspace(c);}).base(), s.end());
   return s;
}


} // namespace Network2
} // namespace AllegroFlare


