
#include <gtest/gtest.h>

#include <AllegroFlare/LegalClauseGenerator.hpp>


TEST(AllegroFlare_LegalClauseGeneratorTest, can_be_created_without_blowing_up)
{
   AllegroFlare::LegalClauseGenerator legal_clause_generator;
}


TEST(AllegroFlare_LegalClauseGeneratorTest,
   generate_persons_resemblance_disclaimer__will_generate_the_expected_text)
{
   std::string expected_disclaimer = "This is a work of fiction. Any resemblance to actual persons, living or dead, "
      "or events is purely coincidental.";
   std::string actual_disclaimer = AllegroFlare::LegalClauseGenerator::generate_persons_resemblance_disclaimer();
   EXPECT_EQ(expected_disclaimer, actual_disclaimer);
}


TEST(AllegroFlare_LegalClauseGeneratorTest,
   generate_views_and_opinions_disclaimer__will_generate_the_expected_text)
{
   std::string expected_disclaimer = "The views and opinions expressed in this media do not necessarily reflect the "
      "views and opinions of the developers or the production company.";
   std::string actual_disclaimer = AllegroFlare::LegalClauseGenerator::generate_views_and_opinions_disclaimer();
   EXPECT_EQ(expected_disclaimer, actual_disclaimer);
}


TEST(AllegroFlare_LegalClauseGeneratorTest,
   generate_no_mistreatment_of_animals_disclaimer__will_generate_the_expected_text)
{
   std::string expected_disclaimer = "During the production of this game, no animals were subject to injury, "
      "indignity, or mistreatment of any kind.";
   std::string actual_disclaimer = AllegroFlare::LegalClauseGenerator::generate_no_mistreatment_of_animals_disclaimer();
   EXPECT_EQ(expected_disclaimer, actual_disclaimer);
}


TEST(AllegroFlare_LegalClauseGeneratorTest,
   generate_as_is_without_warranty_disclaimer__will_generate_the_expected_text)
{
   std::string expected_disclaimer = "THIS SOFTWARE IS PROVIDED \"AS-IS\", WITHOUT ANY EXPRESS OR IMPLIED WARRANTY. "
      "IN NO EVENT WILL THE AUTHORS BE HELD LIABLE FOR ANY DAMAGES ARISING FROM THE USE OF THIS SOFTWARE.";
   std::string actual_disclaimer = AllegroFlare::LegalClauseGenerator::generate_as_is_without_warranty_disclaimer();
   EXPECT_EQ(expected_disclaimer, actual_disclaimer);
}


TEST(AllegroFlare_LegalClauseGeneratorTest,
   generate_as_is_without_warranty_disclaimer__with_the_in_upcase_option_as_false__will_generate_the_expected_text_\
in_sentence_case)
{
   std::string expected_disclaimer = "This software is provided \"as-is\", without any express or implied warranty. In "
      "no event will the authors be held liable for any damages arising from the use of this software.";
   std::string actual_disclaimer =
      AllegroFlare::LegalClauseGenerator::generate_as_is_without_warranty_disclaimer(false);
   EXPECT_EQ(expected_disclaimer, actual_disclaimer);
}


TEST(AllegroFlare_LegalClauseGeneratorTest,
   generate_as_is_without_warranty_for_use_disclaimer__will_generate_the_expected_text)
{
   std::string expected_disclaimer = "THIS SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR "
     "IMPLIED, INCLUDING BUT NOT LIMITED TO ANY WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND "
     "NONINFRINGEMENT OF COPYRIGHT, PATENT, TRADEMARK, OR OTHER RIGHT. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE "
     "LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, INCLUDING ANY GENERAL, SPECIAL, INDIRECT, INCIDENTAL, OR "
     "CONSEQUENTIAL DAMAGES, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF THE USE OR "
     "INABILITY TO USE THE SOFTWARE OR FROM OTHER DEALINGS IN THE SOFTWARE.";
   std::string actual_disclaimer =
      AllegroFlare::LegalClauseGenerator::generate_as_is_without_warranty_for_use_disclaimer();
   EXPECT_EQ(expected_disclaimer, actual_disclaimer);
}


TEST(AllegroFlare_LegalClauseGeneratorTest,
   generate_as_is_without_warranty_for_use_disclaimer__with_th_in_upcase_option_as_false__will_generate_the_expected_\
text_in_sentence_case)
{
   std::string expected_disclaimer = "This software is provided \"as is\", without warranty of any kind, express or "
      "implied, including but not limited to any warranties of merchantability, fitness for a particular purpose and "
      "noninfringement of copyright, patent, trademark, or other right. In no event shall the copyright holder "
      "be liable for any claim, damages or other liability, including any general, special, indirect, incidental, "
      "or consequential damages, whether in an action of contract, tort or otherwise, arising from, out of the use "
      "or inability to use the software or from other dealings in the software.";
   std::string actual_disclaimer =
      AllegroFlare::LegalClauseGenerator::generate_as_is_without_warranty_for_use_disclaimer(false);
   EXPECT_EQ(expected_disclaimer, actual_disclaimer);
}


TEST(AllegroFlare_LegalClauseGeneratorTest,
   generate_company_non_endorcement_disclaimer__will_generate_the_expected_text)
{
   AllegroFlare::LegalClauseGenerator legal_clause_generator;
   std::string company_name = "SlowPoke Software";
   std::vector<std::string> referenced_software_company_names = { 
      "MeowsterEdit",
      "Gator Graphicshop",
      "FerretFoto",
   };

   std::string expected_disclaimer = "Any company names, brand names, and/or trademarks listed in these credits are "
      "the sole property of their respective owners and are in no way associated with SlowPoke Software. Their "
      "appearance in this list does not constitute an endorsement by either party. The inclusion of software names as "
      "in but no limited to MeowsterEdit, Gator Graphicshop, FerretFoto and their respective versions is solely for "
      "informational purposes and does not imply any partnership, sponsorship, or endorsement of the software "
      "providers by either party. All rights to these software belong to their respective copyright holders.";

   std::string actual_disclaimer = legal_clause_generator.generate_company_non_endorcement_disclaimer(
      company_name,
      referenced_software_company_names
   );

   EXPECT_EQ(expected_disclaimer, actual_disclaimer);
}


TEST(AllegroFlare_LegalClauseGeneratorTest,
   generate_company_non_endorcement_disclaimer__with_an_empty_list_of_referenced_software_company_names__will_output_\
the_expected_text)
{
   // TODO
}


