

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
         std::cout << "YIKES! ~Actor2D() without deleting objects." << std::endl;
      }




      void Actor2D::register_params()
      {
         //std::cout << "Here";
         params.clear();
         params.push_back(new Timeline::Track("x", 0.0));
         params.push_back(new Timeline::Track("y", 0.0));
         params.push_back(new Timeline::Track("align_x", 0.5));
         params.push_back(new Timeline::Track("align_y", 0.5));
         params.push_back(new Timeline::Track("scale_x", 0.5));
         params.push_back(new Timeline::Track("scale_y", 1));
         params.push_back(new Timeline::Track("rotation", 0));
         params.push_back(new Timeline::Track("opacity", 1));
         params.push_back(new Timeline::Track("color_r", 1.0));
         params.push_back(new Timeline::Track("color_g", 1.0));
         params.push_back(new Timeline::Track("color_b", 1.0));
         //params.push_back(new Timeline::Track(1, "color_a"));
      }




      void Actor2D::render(double time)
      {
         static int ALLEGRO_FLAGS_EMPTY = 0;
         ALLEGRO_COLOR color{
            get_param_by_id("color_r")->get(time),
            get_param_by_id("color_g")->get(time),
            get_param_by_id("color_b")->get(time),
            1.0
         };

         al_draw_tinted_scaled_rotated_bitmap(
               bitmap,
               AllegroFlare::color::color(color, get_param_by_id("opacity")->get(time)),
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


