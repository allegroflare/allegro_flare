![](http://zeoxdesign.com/images/allegro_flare_logo-04.png) AllegroFlare
=============

Current version - v0.8.7wip


AllegroFlare is a C++ application toolkit that extends the functionality of the Allegro 5 game programming library.  Every part of the existing Allegro 5 library remains intact when using AllegroFlare.  AllegroFlare also includes an optional Framework class that makes for fast and fun development, or, you can cherry-pick any of the fantastic classes and functions provided by AllegroFlare without using the framework at all.



Simple Example
--------------

```cpp
#include <allegro_flare/allegro_flare.h>

class MyApp : public Screen
{
public:
    MyApp(Display *display) : Screen(display) {}
    void primary_timer_func() override
    {
        al_draw_filled_rectangle(300, 400, 200, 100, color::chartreuse);
    }
}

int main(int argc, char **argv)
{
    af::initialize(); // initialize all things AllegroFlare
    Display *display = af::create_display(800, 600); // creates a new Window
    MyApp *my_app = new MyApp(display); // creates a new instance of your app
    af::run_loop(); // run the AllegroFlare framework
}
```



Dependencies
------------

AllegroFlare requires Allegro 5.1.13 or greater.  You can also include other features with CURL, OpenCV, and Boost.



Some Examples of Features and Tools
-----------------------------------

### Framework
- Initialize (basically) everything with one function (`af::initialize()`)
- Interface with the system through a parent class (`Screen`)
- Use virtual member functions to grab events (`primary_timer_func()`, `mouse_axes_func()`, `joy_button_down_func()`, `key_char_func()`, etc)
- Access assets through global media bins (`af::bitmaps["mypic.jpg"]`, `af::fonts["Times.ttf 16"]`, etc)

### Resource Management
- Bins for media files (`FontBin`, `SampleBin`, `BitmapBin`)
- Use any image, sample, or font by filename

### Graphics
- 2D path shapes (`path2d`)
- 2D and 3D positioning tools (`vec2d`, `vec3d`, `placement2d`, `placement3d`)
- cameras (`Camera2D`, `Camera3D`)
- 3D model loading (`Model`)
- Basic image manipulation (`gaussian_blur()`, `color_overlay()`, `trim()`, `color_curve()`, `invert()`, etc)
- Image generation (`draw_wav_sample()`, `draw_histogram()`, `create_gradient_bitmap()`, etc)
- Create music notation (`MusicNotation`)

### GUI
- see the section further down.

### Motion
- timing and movement control (`Motion`)
- easing functions (`interpolator::fastIn`, `interpolator::trippleSlowInOut`, `interpolator::bounceIn`, etc)

### Scripting and Animation
- Use useful clases to automate playback of your objects (`Motion`, `Timeline`, `Stage`, `Actor`, `Script`)
- Use any member function from your classes in a script (`Scriptable`)
- Add attributes to your classes for scripting, saving, and loading (`Attr`, `ElementID`, `AttrLoader`)

### Color
- Color creation and manipulation (`mix()`, `change_hue()`, `change_lightness()`, etc.)
- Operators for ALLEGRO_COLORs (`+`, `-`, `*`, `==`)
- Many color definitions (`color::yellowgreen`, `color::blue`, `color::plum`, `color::floralwhite`, etc)

### Encryption
- md5 and sha2 functions

### Other cool stuff (requires dependencies)
- Interprocess and Shared Memory (boost)
- Text-to-speech API (windows)
- Download a file in a thread (curl)
- Webcam access (OpenCV)
- Theatre lighting control (dmx-box)
- MIDI control (windows)

### And More
- Bone trees, profiling timers, file path access, php-like functions, chainable media objects, etc..



GUI
---

A new GUI that used to exist as a separate extension called [FlareGUI](https://github.com/MarkOates/flare_gui) has recently been merged into AllegroFlare.  Like AllegroFlare, the GUI is still in beta.  To use it, first create a new screen that derives from `FGUIScreen` (using the GUI requires using the `Framework`).  The easiest way to add widgets (buttons, checkboxes, text, etc.) is to declare them inside the constructor.


```cpp
#include <allegro_flare/allegro_flare.h>


class Project : public FGUIScreen
{
public:
	Project(Display *display) : FGUIScreen(display)
	{
		new FGUIText(this, 100, 100, "This is a normal text box.");
		new FGUIScaledText(this, 100, 150, "This is a scaled text box.  It renders smoothly when in motion.");
		new FGUICheckbox(this, 100, 200, 20);
		new FGUIButton(this, 150, 250, 100, 40, "Click Me!");
		new FGUIVerticalSlider(this, 110, 340, 20, 80);
		new FGUIVerticalSlider(this, 140, 340, 20, 80);
		new FGUIVerticalSlider(this, 170, 340, 20, 80);
		new FGUITextInput(this, 250, 450, 360, 40, "Input some text here");
	}
};


void main()
{
	af::initialize();
	Display *display = af::create_display(800, 600, NULL);
	Project *project = new Project(display);
	af::run_loop();
}
```

### Standard GUI Widgets

* FGUIButton
* FGUICheckbox
* FGUIDial
* FGUIFramedWindow
* FGUIImage
* FGUIIntSpinner
* FGUILabeledCheckbox
* FGUIListSpinner
* FGUIMusicNotation
* FGUIProgressBar
* FGUIScaledText
* FGUIScreen
* FGUIScrollArea
* FGUIScrollBar
* FGUISpinner
* FGUIVerticalSlider
* FGUIText
* FGUITextArea
* FGUITextBox
* FGUITextInput
* FGUITextList
* FGUIToggleButton
* FGUIXYController
* FGUIWidget
* FGUIWindowGUI




