

#include <AllegroFlare/Timeline/Actor2D.hpp>
#include <AllegroFlare/Color.hpp>



namespace AllegroFlare
{
namespace Timeline
{


      Actor2D::Actor2D(std::string identifier, ALLEGRO_BITMAP *bitmap)
         : Actor(identifier, 1)
         , bitmap(bitmap)
      {
         register_params();
      }




      Actor2D::~Actor2D()
      {
      }




      void Actor2D::register_params()
      {
         //std::cout << "Here";
         params.clear();
         params.push_back(new Timeline::Track(0, "x"));
         params.push_back(new Timeline::Track(0, "y"));
         params.push_back(new Timeline::Track(0.5, "align_x"));
         params.push_back(new Timeline::Track(0.5, "align_y"));
         params.push_back(new Timeline::Track(1, "scale_x"));
         params.push_back(new Timeline::Track(1, "scale_y"));
         params.push_back(new Timeline::Track(0, "rotation"));
         params.push_back(new Timeline::Track(1, "opacity"));
      }




      void Actor2D::render(double time)
      {
         static int ALLEGRO_FLAGS_EMPTY = 0;

         al_draw_tinted_scaled_rotated_bitmap(
               bitmap,
               AllegroFlare::color::color(AllegroFlare::color::white, get_param_by_id("opacity")->get(time)),
               al_get_bitmap_width(bitmap) * get_param_by_id("align_x")->get(time),
               al_get_bitmap_height(bitmap) * get_param_by_id("align_y")->get(time),
               get_param_by_id("x")->get(time),
               get_param_by_id("y")->get(time),
               get_param_by_id("scale_x")->get(time),
               get_param_by_id("scale_y")->get(time),
               get_param_by_id("rotation")->get(time),
               ALLEGRO_FLAGS_EMPTY);
      }

} // namespace Timeline
} // namespace AllegroFlare


