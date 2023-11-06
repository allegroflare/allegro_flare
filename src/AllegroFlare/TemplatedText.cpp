

#include <AllegroFlare/TemplatedText.hpp>




namespace AllegroFlare
{


TemplatedText::TemplatedText(std::string template_content, std::vector<std::pair<std::string, std::string>> insertion_variables)
   : template_content(template_content)
   , insertion_variables(insertion_variables)
{
}


TemplatedText::~TemplatedText()
{
}


void TemplatedText::set_template_content(std::string template_content)
{
   this->template_content = template_content;
}


void TemplatedText::set_insertion_variables(std::vector<std::pair<std::string, std::string>> insertion_variables)
{
   this->insertion_variables = insertion_variables;
}


std::string TemplatedText::get_template_content() const
{
   return template_content;
}


std::vector<std::pair<std::string, std::string>> TemplatedText::get_insertion_variables() const
{
   return insertion_variables;
}


std::string TemplatedText::__replace(std::string str, std::string from, std::string to)
{
   size_t start_pos = 0;
   while((start_pos = str.find(from, start_pos)) != std::string::npos) {
      str.replace(start_pos, from.length(), to);
      start_pos += to.length();
   }
   return str;
}

std::string TemplatedText::generate_content()
{
   std::string result = template_content;

   for (auto &insertion_variable : insertion_variables)
   {
     result = __replace(result, insertion_variable.first, insertion_variable.second);
   }

   return result;
}


} // namespace AllegroFlare


