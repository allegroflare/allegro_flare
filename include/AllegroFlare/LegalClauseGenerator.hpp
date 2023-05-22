#pragma once


#include <string>
#include <vector>


namespace AllegroFlare
{
   class LegalClauseGenerator
   {
   private:

   protected:


   public:
      LegalClauseGenerator();
      ~LegalClauseGenerator();

      std::string generate_company_non_endorcement_disclaimer(std::string company_name="[unset-company_name]", std::vector<std::string> referenced_software_company_names={});
      std::string join(std::vector<std::string> tokens={}, std::string delimiter=", ", bool use_and=false);
   };
}



