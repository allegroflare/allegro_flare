

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
      placement2d centered = placement2d();
      centered.position = place.size / 2;
      centered.start_transform();

      float root_diameter = 120;
      float distance_to_height = 30;
      float DEFAULT_NODE_DIAMETER = 30;

      al_draw_circle(0, 0, root_diameter, color::dodgerblue, 8.0);

      std::vector<ElementID *> children = root->get_children();
      for (int i=0; i<children.size(); i++)
      {
         ElementID &child = *children[i];

         float scale = child.exists("scale") ? child.get_as_float("scale") : 1.0;
         float diameter = DEFAULT_NODE_DIAMETER * scale;

         float tau = (float)i/children.size() * ALLEGRO_PI * 2 - (ALLEGRO_PI * 2)/4;
         float circle_x = cos(tau) * (root_diameter + distance_to_height * 1.6);
         float circle_y = sin(tau) * (root_diameter + distance_to_height * 1.6);

         // draw the node itself
         ALLEGRO_COLOR child_color = child.exists("color") ? color::name(child.get("color").c_str()) : color::gray;
         al_draw_circle(circle_x, circle_y, diameter, child_color, 5.0);

         // draw the line connecting to the node
         float d = distance(vec2d(0, 0), vec2d(circle_x, circle_y));
         float hd = d / 2.0;

         vec2d normal = vec2d(circle_x, circle_y).normalized();
         al_draw_line(normal.x * root_diameter, normal.y * root_diameter,
               circle_x - normal.x * diameter, circle_y - normal.y * diameter,
               color::blue, 6.0);

         // draw the name
         if (child.exists("name"))
         {
            ALLEGRO_FONT *f = Framework::font("DroidSans.ttf 20");
            al_draw_text(f, color::white,
               circle_x, circle_y - al_get_font_line_height(f)/2,
               ALLEGRO_ALIGN_CENTRE, child.get("name").c_str());
         }
      }

      centered.restore_transform();
   }
};


ElementID *create_graph();


class Project : public UIScreen
{
public:
   ElementID *root;
   ElementIDGraph graph;

   UIButton add_element_button;
   UIButton remove_element_button;

   Project(Display *display)
      : UIScreen(display)
      , root(create_graph())
      , graph(this, root)
      , add_element_button(this, 100, 80, 80, 60, "Add")
      , remove_element_button(this, 100, 180, 80, 60, "Remove")
   {}
   void on_message(UIWidget *sender, std::string message) override
   {
      if (sender == &add_element_button) new ElementID(root);
      if (sender == &remove_element_button)
      if (root->num_children() != 0) delete root->get_random_child();
   }
};


ElementID *create_graph()
{
   ElementID *root = new ElementID(NULL);

   ElementID *child_1 = new ElementID(root);
   child_1->set("color", "green");
      ElementID *child_1_A = new ElementID(child_1);
      child_1_A->set("color", "orange");
         ElementID *child_1_A_1 = new ElementID(child_1_A);
         child_1_A_1->set("color", "green");
         ElementID *child_1_A_2 = new ElementID(child_1_A);
         child_1_A_2->set("size", "medium");
         ElementID *child_1_A_3 = new ElementID(child_1_A);
         child_1_A_3->set("color", "pink");
      ElementID *child_1_B = new ElementID(child_1);
      child_1_B->set("name", "Samuel");
         ElementID *child_1_B_1 = new ElementID(child_1_B);
         child_1_B_1->set("size", "large");

   ElementID *child_2 = new ElementID(root);
   child_2->set("name", "Emmanuelle");
      ElementID *child_2_A = new ElementID(child_2);
      child_2_A->set("color", "green");
      ElementID *child_2_B = new ElementID(child_2);
      child_2_B->set("power", "42");

   return root;
}


int main(int argc, char **argv)
{
   Framework::initialize();
   Display *d = Framework::create_display(1920, 1080);
   Project project = Project(d);
   Framework::run_loop();
   return 0;
}
