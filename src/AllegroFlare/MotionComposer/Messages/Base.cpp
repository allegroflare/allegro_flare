

#include <AllegroFlare/MotionComposer/Messages/Base.hpp>




namespace AllegroFlare
{
namespace MotionComposer
{
namespace Messages
{


Base::Base(std::string type)
   : type(type)
{
}


Base::~Base()
{
}


std::string Base::get_type() const
{
   return type;
}


bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}


} // namespace Messages
} // namespace MotionComposer
} // namespace AllegroFlare


