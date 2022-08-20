

#include <AllegroFlare/MotionComposer/Messages/SetScript.hpp>



namespace AllegroFlare
{
namespace MotionComposer
{
namespace Messages
{


SetScript::SetScript(std::vector<std::string> script_lines)
   : AllegroFlare::MotionComposer::Messages::Base("SetScript")
   , script_lines(script_lines)
{
}


SetScript::~SetScript()
{
}


void SetScript::set_script_lines(std::vector<std::string> script_lines)
{
   this->script_lines = script_lines;
}


std::vector<std::string> SetScript::get_script_lines()
{
   return script_lines;
}


} // namespace Messages
} // namespace MotionComposer
} // namespace AllegroFlare


