

#include <AllegroFlare/LoadASavedGame/SaveSlots/Base.hpp>




namespace AllegroFlare
{
namespace LoadASavedGame
{
namespace SaveSlots
{


Base::Base(std::string type)
   : type(type)
   , filename("saves/save.sav")
{
}


Base::~Base()
{
}


void Base::set_filename(std::string filename)
{
   this->filename = filename;
}


std::string Base::get_type() const
{
   return type;
}


std::string Base::get_filename() const
{
   return filename;
}


bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}


} // namespace SaveSlots
} // namespace LoadASavedGame
} // namespace AllegroFlare


