

#include <allegro_flare/allegro_flare.h>
#include <cmath>


class ElementIDGraph : UIWidget
{
public:
   ElementID *root;

   ElementIDGraph(UIWidget *parent, ElementID *root)
      : UIWidget(parent, "ElementIDGraph", new UISurfaceAreaNeverCollide(1920/2, 1080/2, 1920, 1080))
      , root(root)
   {}
   void on_draw() override
   {
      float root_diameter = 120;
      float child_diameter = 30;

      al_draw_circle(place.size.x/2, place.size.y/2, child_diameter, color::dodgerblue, 8.0);

      std::vector<ElementID *> children = root->get_children();
      for (int i=0; i<children.size(); i++)
      {
         float tau = (float)i/children.size() * ALLEGRO_PI * 2 - (ALLEGRO_PI * 2)/4;
         float circle_x = cos(tau) * (root_diameter + child_diameter * 1.6) + place.size.x/2;
         float circle_y = sin(tau) * (root_diameter + child_diameter * 1.6) + place.size.y/2;
         al_draw_circle(circle_x, circle_y, child_diameter, color::red, 5.0);
      }
   }
};


class Project : public UIScreen
{
public:
   ElementID root;
   ElementIDGraph graph;

   UIButton add_element_button;
   UIButton remove_element_button;

   Project(Display *display)
      : UIScreen(display)
      , root(NULL)
      , graph(this, &root)
      , add_element_button(this, 100, 80, 80, 60, "Add")
      , remove_element_button(this, 100, 180, 80, 60, "Remove")
   {
      new ElementID(&root);
      new ElementID(&root);
      new ElementID(&root);
      new ElementID(&root);
      new ElementID(&root);
      new ElementID(&root);
   }
   void on_message(UIWidget *sender, std::string message)
   {
      if (sender == &add_element_button) new ElementID(&root);
      if (sender == &remove_element_button)
      if (root.num_children() != 0) delete root.get_random_child();
   }
};


int main(int argc, char **argv)
{
   Framework::initialize();
   Display *d = Framework::create_display(1920, 1080);
   Project project = Project(d);
   Framework::run_loop();
   return 0;
}
