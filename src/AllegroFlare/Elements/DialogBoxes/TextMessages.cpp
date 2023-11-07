

#include <AllegroFlare/Elements/DialogBoxes/TextMessages.hpp>




namespace AllegroFlare
{
namespace Elements
{
namespace DialogBoxes
{


TextMessages::TextMessages(std::vector<std::tuple<std::string, std::string, float>> messages)
   : AllegroFlare::Elements::DialogBoxes::Base(AllegroFlare::Elements::DialogBoxes::TextMessages::TYPE)
   , messages(messages)
{
}


TextMessages::~TextMessages()
{
}


void TextMessages::set_messages(std::vector<std::tuple<std::string, std::string, float>> messages)
{
   this->messages = messages;
}


std::vector<std::tuple<std::string, std::string, float>> TextMessages::get_messages() const
{
   return messages;
}




} // namespace DialogBoxes
} // namespace Elements
} // namespace AllegroFlare


