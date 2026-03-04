

#include <AllegroFlare/Layouts/Elements/Polygon.hpp>

#include <iostream>


namespace AllegroFlare
{
namespace Layouts
{
namespace Elements
{


Polygon::Polygon()
   : name("[unset-name]")
   , x(0.0f)
   , y(0.0f)
   , width(0.0f)
   , height(0.0f)
   , polygon({})
   , triangulated_polygon({})
   , path()
   , fill_color(ALLEGRO_COLOR{1, 1, 1, 1})
   , tmj_object_id(0.0f)
   , on_focus({})
   , on_blur({})
   , on_activation({})
{
}


Polygon::~Polygon()
{
}


std::vector<ALLEGRO_VERTEX> Polygon::build_triangulated_polygon()
{
   int polygon_vertex_counts[2] = {
      (int)polygon.size(),
      0,
   };

   struct UserData
   {
      int emissions = 0;
      std::vector<AllegroFlare::Vec2D> *polygon = nullptr;
      std::vector<ALLEGRO_VERTEX> result;
   };

   UserData user_data;
   user_data.polygon = &polygon;

   al_triangulate_polygon(
      &polygon[0].x,
      sizeof(AllegroFlare::Vec2D), 
      polygon_vertex_counts, //polygon.size(),
      //std::function<void(int, int, int, void*), 
      [](int point_i_1, int point_i_2, int point_i_3, void* _user_data){
         auto &user_data = *static_cast<UserData*>(_user_data);
         user_data.emissions++;

         auto &p1 = user_data.polygon->at(point_i_1);
         auto &p2 = user_data.polygon->at(point_i_2);
         auto &p3 = user_data.polygon->at(point_i_3);

         ALLEGRO_COLOR white = ALLEGRO_COLOR{1, 1, 1, 1};

         user_data.result.push_back(ALLEGRO_VERTEX{.x=p1.x, .y=p1.y, .z=0, .u=p1.x, .v=p1.y, .color=white});
         user_data.result.push_back(ALLEGRO_VERTEX{.x=p2.x, .y=p2.y, .z=0, .u=p2.x, .v=p2.y, .color=white});
         user_data.result.push_back(ALLEGRO_VERTEX{.x=p3.x, .y=p3.y, .z=0, .u=p3.x, .v=p3.y, .color=white});
      },
      &user_data
   );

   //std::cout << "Emissions: " << user_data.emissions << std::endl;

   return user_data.result;
}


} // namespace Elements
} // namespace Layouts
} // namespace AllegroFlare


