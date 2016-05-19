

#include <allegro_flare/allegro_flare.h>

#include <limits>



class AutomationController : public FGUIWidget
{
private:
   vec2d mouse_pos;
   std::vector<vec2d> points;
   int focused_points_index;

   ALLEGRO_COLOR guide_color;
   float guide_opacity;

   static bool __sort_by_x(const vec2d &p1, const vec2d &p2)
   {
      if (p1.x < p2.x) return true;
      return false;
   }

   void sort_points()
   {
      std::sort(points.begin(), points.end(), AutomationController::__sort_by_x);
   }

public:
   AutomationController(FGUIWidget *parent, float x, float y, float w, float h)
      : FGUIWidget(parent, new FGUISurfaceAreaBox(x, y, w, h))
      , mouse_pos(0)
      , points()
      , guide_color(color::white)
      , guide_opacity(0.3)
      , focused_points_index(-1)
   {
   }
   int find_closest_points_within(vec2d point, float min_distance)
   {
      float shortest_distance = std::numeric_limits<float>::max();
      int shortest_index = -1;
      for (unsigned i=0; i<points.size(); i++)
      {
         float dist = distance(point, points[i]);
         if (dist < shortest_distance && dist < min_distance)
         {
            shortest_distance = dist;
            shortest_index = i;
         }
      }
      return shortest_index;
   }
   int find_closest_points(vec2d point)
   {
      float shortest_distance = std::numeric_limits<float>::max();
      int shortest_index = -1;
      for (unsigned i=0; i<points.size(); i++)
      {
         float dist = distance(point, points[i]);
         if (dist < shortest_distance)
         {
            shortest_distance = dist;
            shortest_index = i;
         }
      }
      return shortest_index;
   }
   void on_mouse_move(float x, float y, float dx, float dy) override
   {
      place.transform_coordinates(&x, &y);
      mouse_pos = vec2d(x, y);

      focused_points_index = find_closest_points_within(mouse_pos, 30);
   }
   void on_draw() override
   {
      FGUIStyleAssets::draw_inset(0, 0, place.size.x, place.size.y, color::color(color::black, 0.1));

      // draw the guides
      if (mouse_over)
      {
         ALLEGRO_COLOR guide_mixed_color = color::color(color::white, guide_opacity);
         al_draw_line(mouse_pos.x, 0, mouse_pos.x, place.size.y, color::color(color::white, guide_opacity), 1.0);
         al_draw_line(0, mouse_pos.y, place.size.x, mouse_pos.y, color::color(color::white, guide_opacity), 1.0);
         draw_crosshair(mouse_pos);
      }

      // draw the lines
      for (unsigned i=1; i<points.size(); i++)
      {
         al_draw_line(points[i-1].x, points[i-1].y, points[i].x, points[i].y, color::color(color::white, 0.2), 2.0);
      }

      // draw the points
      for (unsigned i=0; i<points.size(); i++)
      {
         if (i == focused_points_index)
            al_draw_circle(points[i].x, points[i].y, 10, color::color(color::dodgerblue, 0.2), 6);
         else
            al_draw_circle(points[i].x, points[i].y, 10, color::color(color::orange, 0.2), 6);

         // draw the debug (for testing)
         // al_draw_text(Framework::fonts["DroidSans.ttf 16"], color::white, points[i].x, points[i].y, ALLEGRO_ALIGN_CENTRE, tostring(i).c_str());
      }
   }
   void on_click() override
   {
      if (Framework::current_event->mouse.button == 2) // right-click
      {
         // erase the focused point
         if (focused_points_index != -1)
         {
            points.erase(points.begin() + focused_points_index);
            focused_points_index = -1;
            sort_points();
         }
      }
      else if (Framework::current_event->mouse.button == 1) // left-click
      {
         // create a new point on the graph
         points.push_back(mouse_pos);
         focused_points_index = -1;
         sort_points();
      }
   }
};




class RubberBandDev : public FGUIScreen
{
public:
   RubberBandDev(Display *display)
      : FGUIScreen(display)
   {
      new FGUIText(this, 100, display->height()/5, "Click in the AutomationController to add a point.  Right-click to erase a point.");
      AutomationController *controller = new AutomationController(this, display->width()/2, display->height()/2, display->width()/5*4, 200);
   }
};




int main(int argc, char **argv)
{
   Framework::initialize();
   Display *display = Framework::create_display(1000, 700);
   RubberBandDev *rubber_band_dev = new RubberBandDev(display);
   Framework::run_loop();
   return 0;
}


