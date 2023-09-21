

#include <AllegroFlare/DialogTree/Nodes/Base.hpp>




namespace AllegroFlare
{
namespace DialogTree
{
namespace Nodes
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


} // namespace Nodes
} // namespace DialogTree
} // namespace AllegroFlare


