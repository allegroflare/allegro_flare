

#include <AllegroFlare/DialogTree/Nodes/RawScriptLine.hpp>




namespace AllegroFlare
{
namespace DialogTree
{
namespace Nodes
{


RawScriptLine::RawScriptLine(std::string line, int line_number, std::string next_line_identifier)
   : AllegroFlare::DialogTree::Nodes::Base(AllegroFlare::DialogTree::Nodes::RawScriptLine::TYPE)
   , line(line)
   , line_number(line_number)
   , next_line_identifier(next_line_identifier)
{
}


RawScriptLine::~RawScriptLine()
{
}


void RawScriptLine::set_next_line_identifier(std::string next_line_identifier)
{
   this->next_line_identifier = next_line_identifier;
}


std::string RawScriptLine::get_line() const
{
   return line;
}


int RawScriptLine::get_line_number() const
{
   return line_number;
}


std::string RawScriptLine::get_next_line_identifier() const
{
   return next_line_identifier;
}




} // namespace Nodes
} // namespace DialogTree
} // namespace AllegroFlare


