#pragma once


#include <string>
#include <vector>


namespace AllegroFlare
{
   class LegalClauseGenerator
   {
   private:
      static std::string join(std::vector<std::string> tokens={}, std::string delimiter=", ", bool use_and=false);

   protected:


   public:
      LegalClauseGenerator();
      ~LegalClauseGenerator();

      static std::string generate_persons_resemblance_disclaimer();
      static std::string generate_company_non_endorcement_disclaimer(std::string company_name="[unset-company_name]", std::vector<std::string> referenced_software_company_names={});
   };
}



