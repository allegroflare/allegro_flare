



#include <allegro_flare/allegro_flare.h>




class ExSelectors : public UIScreen
{
public:
   ExSelectors(Display *display)
      : UIScreen(display)
   {
      create_widgets();
      use_selectors();
   }

   void create_widgets()
   {
      //
      // create some widgets

      // text
      new UIText(this, 100, 100, "This is a normal text box.");
      new UIScaledText(this, 100, 150, "This is a scaled text box.  It renders smoothly when in motion.");
      new UICheckbox(this, 100, 200, 20);

      // buttons
      new UIButton(this, 150, 250, 120, 50, "Click Me!");
      new UIToggleButton(this, 290, 250, 130, 50, "Toggle Me!");

      // vertical sliders
      new UIVerticalSlider(this, 110, 540, 20, 80);
      new UIVerticalSlider(this, 140, 540, 20, 80);
      new UIVerticalSlider(this, 170, 540, 20, 80);

      // some other cool stuff
      new UITextInput(this, 250, 450, 360, 40, "Input some text here");
      new UIDial(this, 400, 300, 80);
      new UIXYController(this, 600, 400, 200, 200);
      new UITextArea(this, 830, 400, 200, 200);

      // spinners
      new UIIntSpinner(this, 400, 200, 140, 40);
      new UIFloatSpinner(this, 400, 300, 140, 40);
      new UIListSpinner(this, 600, 200, 200, 40, {"Alligator", "Bunny", "Buffalo", "Cat", "Duck", "Dog", "Horse"});
   }

   void use_selectors()
   {
      //
      // select individual items
      //
      // the functions below each return
      // UIWidget *widget;
      //

      // select the whole tree by id
      family.select_descendant_by_id();

      // select children based on the order.
      // (children are direct descendants of family)
      family.select_first_child();
      family.select_last_child();
      family.select_nth_child(4);
      family.select_odd_child();
      family.select_even_child();

      // select a widget by type
      family.select_first_child_by_type(TYPE);
      family.select_descendant_by_type(TYPE);


      //
      // select multiple items
      //
      // all of these functions return
      // std::vector<UIWidget *> widgets;
      //

      // select multiple widgets by type
      family.select_children_by_type("UIScaledText");
      family.select_descendants_by_type(TYPE);

      // or use helper functions
      family.as_button();
      family.buttons();
      family.texts();
      family.text_inputs();
      family.text_areas();
      family.list_spinners();
      family.sliders();
      family.scrollbars();
      family.text_lists();
   }
};




int main(int argc, char **argv)
{
   af::initialize();
   Display *display = af::create_display();

   ExSelectors *example_program = new ExSelectors(display);

   af::run_loop();
   return 0;
}




