

#include <Wicked/Int2D.hpp>



namespace Wicked
{


Int2D::Int2D(int x, int y)
  : x(x)
  , y(y)
{
}


Int2D::~Int2D()
{
}


void Int2D::rotate()
{
   int s = x;
   x = y;
   y = s;
}

} // namespace Wicked


