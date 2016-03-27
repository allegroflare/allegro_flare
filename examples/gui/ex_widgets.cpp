


#include <allegro_flare/allegro_flare.h>



class Project : public FGUIScreen
{
public:
   Project(Display *display)
      : FGUIScreen(display)
   {
      new FGUIText(this, 100, 100, "This is a normal text box.");
      new FGUIScaledText(this, 100, 150, "This is a scaled text box.  It renders smoothly when in motion.");
      new FGUICheckbox(this, 100, 200, 20);

      // buttons
      new FGUIButton(this, 150, 250, 120, 50, "Click Me!");
      FGUIWidget *widget = new FGUIButton(this, 150, 320, 120, 50, "Disabled");
      widget->set_as_disabled();
      new FGUIToggleButton(this, 290, 250, 130, 50, "Toggle Me!");

      // vertical sliders
      new FGUIVerticalSlider(this, 110, 540, 20, 80);
      new FGUIVerticalSlider(this, 140, 540, 20, 80);
      new FGUIVerticalSlider(this, 170, 540, 20, 80);

      new FGUITextInput(this, 250, 450, 360, 40, "Input some text here");
      new FGUIDial(this, 400, 300, 80);
      new FGUIXYController(this, 600, 400, 200, 200);
      new FGUITextArea(this, 830, 400, 200, 200);

      // spinners
      new FGUIIntSpinner(this, 400, 200, 140, 40);
      new FGUIFloatSpinner(this, 400, 300, 140, 40);
      FGUIListSpinner *list_spinner = new FGUIListSpinner(this, 600, 200, 200, 40);
      list_spinner->add_items({"Kentucky", "Ohio", "Pennsylvania", "Tennessee", "Colorado", "New York"});
      list_spinner->sort();
   }
};




int main(int argc, char **argv)
{
   af::initialize();
   Display *display = af::create_display();
   Project *project = new Project(display);
   af::run_loop();
   return 0;
}


