


#include <allegro_flare/allegro_flare.h>




class ExSelectors : public FGUIScreen
{
public:
   ExSelectors(Display *display)
      : FGUIScreen(display)
   {
      create_widgets();
      use_selectors();
   }

   void create_widgets()
   {
      //
      // create some widgets

      // text
      new FGUIText(this, 100, 100, "This is a normal text box.");
      new FGUIScaledText(this, 100, 150, "This is a scaled text box.  It renders smoothly when in motion.");
      new FGUICheckbox(this, 100, 200, 20);

      // buttons
      new FGUIButton(this, 150, 250, 120, 50, "Click Me!");
      new FGUIToggleButton(this, 290, 250, 130, 50, "Toggle Me!");

      // vertical sliders
      new FGUIVerticalSlider(this, 110, 540, 20, 80);
      new FGUIVerticalSlider(this, 140, 540, 20, 80);
      new FGUIVerticalSlider(this, 170, 540, 20, 80);

      // some other cool stuff
      new FGUITextInput(this, 250, 450, 360, 40, "Input some text here");
      new FGUIDial(this, 400, 300, 80);
      new FGUIXYController(this, 600, 400, 200, 200);
      new FGUITextArea(this, 830, 400, 200, 200);

      // spinners
      new FGUIIntSpinner(this, 400, 200, 140, 40);
      new FGUIFloatSpinner(this, 400, 300, 140, 40);
      new FGUIListSpinner(this, 600, 200, 200, 40, {"Alligator", "Bunny", "Buffalo", "Cat", "Duck", "Dog", "Horse"});
   }

   void use_selectors()
   {
      //
      // select individual items
      //
      // the functions below each return
      // FGUIWidget *widget;
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
      // std::vector<FGUIWidget *> widgets;
      //

      // select multiple widgets by type
      family.select_children_by_type("FGUIScaledText");
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


