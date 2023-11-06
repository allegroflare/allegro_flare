#pragma once


#include <string>
#include <utility>
#include <vector>


namespace AllegroFlare
{
   class TemplatedText
   {
   private:
      std::string template_content;
      std::vector<std::pair<std::string, std::string>> insertion_variables;
      std::string __replace(std::string str="source string", std::string from="source", std::string to="result");

   protected:


   public:
      TemplatedText(std::string template_content="[greeting], [subject]!", std::vector<std::pair<std::string, std::string>> insertion_variables={ { "[greeting]", "Hello" }, { "[subject]", "World" } });
      ~TemplatedText();

      void set_template_content(std::string template_content);
      void set_insertion_variables(std::vector<std::pair<std::string, std::string>> insertion_variables);
      std::string get_template_content() const;
      std::vector<std::pair<std::string, std::string>> get_insertion_variables() const;
      std::string generate_content();
   };
}



