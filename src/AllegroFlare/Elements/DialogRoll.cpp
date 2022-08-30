

#include <AllegroFlare/Elements/DialogRoll.hpp>



namespace AllegroFlare
{
namespace Elements
{


DialogRoll::DialogRoll(std::vector<std::pair<std::string, std::string>> log)
   : log(log)
{
}


DialogRoll::~DialogRoll()
{
}


void DialogRoll::set_log(std::vector<std::pair<std::string, std::string>> log)
{
   this->log = log;
}


std::vector<std::pair<std::string, std::string>> DialogRoll::get_log() const
{
   return log;
}


} // namespace Elements
} // namespace AllegroFlare


