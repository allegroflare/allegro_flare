

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


void DialogRoll::append_log(std::string speaker, std::string text, float time)
{
   log.push_back(std::pair<std::string, std::string>{ speaker, text });
   return;
}


} // namespace Elements
} // namespace AllegroFlare


