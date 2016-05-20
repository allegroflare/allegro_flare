



#include <allegro_flare/allegro_flare.h>




#include <allegro_flare/grid2d.h>

class GridHelper : public grid2d
{
public:
   GridHelper()
   {}
   void draw()
   {
      grid2d::draw_guides();
   }
   bool fit_to_grid(int grid_x1, int grid_y1, int grid_x2, int grid_y2, FGUIWidget *widget/*, vec2d align = vec2d(0.5, 0.5)*/)
   {
      vec2d top_left = grid2d::get_guide_pos(grid_x1, grid_y1);
      vec2d bottom_right = grid2d::get_guide_pos(grid_x2, grid_y2);

      vec2d center = (bottom_right - top_left) / 2;

      widget->place.position = center + top_left;
      widget->place.align = vec2d(0.5, 0.5);
      widget->place.size = bottom_right - top_left;

      return true;
   }
   bool fit_in_cell(int cell_x, int cell_y, FGUIWidget *widget/*, vec2d align = vec2d(0.5, 0.5)*/)
   {
      return fit_to_grid(cell_x, cell_y, cell_x+1, cell_y+1, widget);
   }
   bool fit_in_cells(int cell1_x, int cell1_y, int cell2_x, int cell2_y, FGUIWidget *widget/*, vec2d align = vec2d(0.5, 0.5)*/)
   {
      return fit_to_grid(cell1_x, cell1_y, cell2_x+1, cell2_y+1, widget);
   }
};



class Calculator : public FGUIWindow
{
public:
   GridHelper grid;
   FGUITextInput *result_display;
   Calculator(FGUIWidget *parent)
      : FGUIWindow(parent, 400, 400, 100, 100)
      , grid()
      , result_display(NULL)
   {
      build_grid();
      grid.fit_to_grid(0, 0, 11, 11, this);
      place.position += vec2d(500, 100);


      new FGUIDraggableRegion(this, place.size.x/2, place.size.y/2, place.size.x, place.size.y);


      result_display = new FGUITextInput(this, 0, 0, 0, 0, "0");
      result_display->set_font_color(color::aliceblue);
      grid.fit_in_cells(1, 1, 9, 1, result_display);

      // clear button
      m_make_button("CE", 9, 3);


      // number buttons
      m_make_button("7", 1, 3);
      m_make_button("8", 3, 3);
      m_make_button("9", 5, 3);

      m_make_button("4", 1, 5);
      m_make_button("5", 3, 5);
      m_make_button("6", 5, 5);

      m_make_button("1", 1, 7);
      m_make_button("2", 3, 7);
      m_make_button("3", 5, 7);

      m_make_button("0", 1, 9, 5, 9);

      // functions
      m_make_button("/", 7, 3);
      m_make_button("*", 7, 5);
      m_make_button("-", 7, 7);
      m_make_button("+", 7, 9);

      m_make_button("<-", 9, 5);
      m_make_button("=", 9, 7, 9, 9);
   }
   FGUIButton *m_make_button(std::string label, float cell_x, float cell_y)
   {
      FGUIButton *button = new FGUIButton(this, 0, 0, 0, 0, label);
      grid.fit_in_cell(cell_x, cell_y, button);
      return button;
   }
   FGUIButton *m_make_button(std::string label, float cell1_x, float cell1_y, float cell2_x, float cell2_y)
   {
      FGUIButton *button = new FGUIButton(this, 0, 0, 0, 0, label);
      grid.fit_in_cells(cell1_x, cell1_y, cell2_x, cell2_y, button);
      return button;
   }
   void on_message(FGUIWidget *sender, std::string message) override
   {
      if (message == "on_click")
      {
         result_display->set_text("TODO: calculate");
      }
   }
   void build_grid()
   {
      float x_cursor = 0;
      float padding = 3;
      float margin = 7;

      grid.add_horizontal_guide(x_cursor); // left
      x_cursor += padding;
      x_cursor += margin;

      grid.add_horizontal_guide(x_cursor);
      x_cursor += 40;
      grid.add_horizontal_guide(x_cursor);

      x_cursor += padding;

      grid.add_horizontal_guide(x_cursor);
      x_cursor += 40;
      grid.add_horizontal_guide(x_cursor);

      x_cursor += padding;

      grid.add_horizontal_guide(x_cursor);
      x_cursor += 40;
      grid.add_horizontal_guide(x_cursor);

      x_cursor += padding;

      grid.add_horizontal_guide(x_cursor);
      x_cursor += 40;
      grid.add_horizontal_guide(x_cursor);

      x_cursor += padding;

      grid.add_horizontal_guide(x_cursor);
      x_cursor += 40;
      grid.add_horizontal_guide(x_cursor);

      x_cursor += padding;
      x_cursor += margin;

      grid.add_horizontal_guide(x_cursor); // right



      float y_cursor = 0;
      float y_button_height = 50;
      grid.add_vertical_guide(y_cursor); // top
      y_cursor += 30;

      x_cursor += margin;
      y_cursor += padding;

      grid.add_vertical_guide(y_cursor);
      y_cursor += 50;
      grid.add_vertical_guide(y_cursor);

      y_cursor += padding;
      y_cursor += margin;

      grid.add_vertical_guide(y_cursor);
      y_cursor += y_button_height;
      grid.add_vertical_guide(y_cursor);

      y_cursor += padding;

      grid.add_vertical_guide(y_cursor);
      y_cursor += y_button_height;
      grid.add_vertical_guide(y_cursor);

      y_cursor += padding;

      grid.add_vertical_guide(y_cursor);
      y_cursor += y_button_height;
      grid.add_vertical_guide(y_cursor);

      y_cursor += padding;

      grid.add_vertical_guide(y_cursor);
      y_cursor += y_button_height;
      grid.add_vertical_guide(y_cursor);

      y_cursor += padding;
      y_cursor += margin;

      grid.add_vertical_guide(y_cursor); // bottom
   }
};



class Project : public FGUIScreen
{
public:
   Calculator *calculator;

    Project(Display *display)
        : FGUIScreen(display)
    {
      this->draw_focused_outline = false;

      // make a nice background image
      FGUIImage *img = new FGUIImage(this, 0, 0, Framework::bitmap("veddy_nice.png"));
         img->set_color(color::color(color::white, 0.2));
         img->place.position = vec2d(display->center(), display->middle());

      // create the calculator
      calculator = new Calculator(this);

      // set the calc's starting placement
      calculator->place.position = vec2d(display->center()- 100, display->height());
      calculator->place.scale = vec2d(0.4, 0.4);
      calculator->place.rotation = 0.1;

      // create a nice "reveal" animation
      Framework::motion().cmove_to(&calculator->place.position.x, display->center(), 0.7);
      Framework::motion().cmove_to(&calculator->place.position.y, display->middle(), 0.7);
      Framework::motion().cmove_to(&calculator->place.scale.x, 1.0, 0.9);
      Framework::motion().cmove_to(&calculator->place.scale.y, 1.0, 0.9);
      Framework::motion().cmove_to(&calculator->place.rotation, 0, 0.9);
    }
};


int main(int argc, char **argv)
{
   Framework::initialize();
   Display *display = Framework::create_display(1000, 600);
   Project *project = new Project(display);
   Framework::run_loop();
   return 0;
}
