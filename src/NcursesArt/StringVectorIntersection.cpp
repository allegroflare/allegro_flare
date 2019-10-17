

#include <NcursesArt/StringVectorIntersection.hpp>
#include <algorithm>
#include <algorithm>


namespace NcursesArt
{


StringVectorIntersection::StringVectorIntersection(std::vector<std::string> v1, std::vector<std::string> v2)
   : v1(v1)
   , v2(v2)
{
}


StringVectorIntersection::~StringVectorIntersection()
{
}


std::vector<std::string> StringVectorIntersection::intersection()
{
std::vector<std::string> result;
result.resize(v1.size() + v2.size());
std::vector<std::string>::iterator it;

std::sort(v1.begin(), v1.end());
std::sort(v2.begin(), v2.end());

it = std::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), result.begin());

result.resize(it - result.begin());

return result;

}
} // namespace NcursesArt


