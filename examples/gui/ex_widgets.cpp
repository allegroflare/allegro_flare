


#include <allegro_flare/allegro_flare.h>



class Project : public UIScreen
{
public:
   Project(Display *display)
      : UIScreen(display)
   {
      new UIText(this, 100, 100, "This is a normal text box.");
      new UIScaledText(this, 100, 150, "This is a scaled text box.  It renders smoothly when in motion.");
      new UICheckbox(this, 100, 200, 20);

      // buttons
      new UIButton(this, 150, 250, 120, 50, "Click Me!");
      UIWidget *widget = new UIButton(this, 150, 320, 120, 50, "Disabled");
      widget->set_as_disabled();
      new UIToggleButton(this, 290, 250, 130, 50, "Toggle Me!");

      // vertical sliders
      new UIVerticalSlider(this, 110, 540, 20, 80);
      new UIVerticalSlider(this, 140, 540, 20, 80);
      new UIVerticalSlider(this, 170, 540, 20, 80);

      new UITextInput(this, 250, 450, 360, 40, "Input some text here");
      new UIDial(this, 400, 300, 80);
      new UIXYController(this, 600, 400, 200, 200);
      new UITextArea(this, 830, 400, 200, 200);

      // spinners
      new UIIntSpinner(this, 400, 200, 140, 40);
      new UIFloatSpinner(this, 400, 300, 140, 40);
      UIListSpinner *list_spinner = new UIListSpinner(this, 600, 200, 200, 40);
      list_spinner->add_items({"Kentucky", "Ohio", "Pennsylvania", "Tennessee", "Colorado", "New York"});
      list_spinner->sort();
   }
};




int main(int argc, char **argv)
{
   Framework::initialize();
   Display *display = Framework::create_display();
   Project *project = new Project(display);
   Framework::run_loop();
   return 0;
}


