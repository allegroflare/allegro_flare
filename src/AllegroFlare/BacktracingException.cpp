

#include <AllegroFlare/BacktracingException.hpp>

#include <AllegroFlare/Stacktracer.hpp>


namespace AllegroFlare
{


BacktracingException::BacktracingException(std::string message)
   : std::runtime_error(message + "\n" + generate_stack_trace())
   , message(message)
{
}


BacktracingException::~BacktracingException()
{
}


std::string BacktracingException::generate_stack_trace()
{
   return AllegroFlare::Stacktracer::generate_stack_trace();
}


} // namespace AllegroFlare


