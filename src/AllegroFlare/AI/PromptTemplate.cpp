

#include <AllegroFlare/AI/PromptTemplate.hpp>




namespace AllegroFlare
{
namespace AI
{


PromptTemplate::PromptTemplate(std::string template_content, std::vector<std::pair<std::string, std::string>> insertion_variables)
   : template_content(template_content)
   , insertion_variables(insertion_variables)
{
}


PromptTemplate::~PromptTemplate()
{
}


void PromptTemplate::set_insertion_variables(std::vector<std::pair<std::string, std::string>> insertion_variables)
{
   this->insertion_variables = insertion_variables;
}


std::vector<std::pair<std::string, std::string>> PromptTemplate::get_insertion_variables() const
{
   return insertion_variables;
}


std::string PromptTemplate::__replace(std::string str, std::string from, std::string to)
{
   size_t start_pos = 0;
   while((start_pos = str.find(from, start_pos)) != std::string::npos) {
      str.replace(start_pos, from.length(), to);
      start_pos += to.length();
   }
   return str;
}

std::string PromptTemplate::generate_content()
{
   std::string result = template_content;

   for (auto &insertion_variable : insertion_variables)
   {
     result = __replace(result, insertion_variable.first, insertion_variable.second);
   }

   return result;
}


} // namespace AI
} // namespace AllegroFlare


