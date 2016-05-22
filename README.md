![](http://zeoxdesign.com/images/allegro_flare_logo-04.png) AllegroFlare
=============

Current version - v0.8.8wip


AllegroFlare is a C++ application toolkit that extends the functionality of the Allegro 5 game programming library.  Every part of the existing Allegro 5 library remains intact when using AllegroFlare.  AllegroFlare also includes an optional Framework class that makes for fast and fun development, or, you can cherry-pick any of the fantastic classes and functions provided by AllegroFlare without using the framework at all.



Build Instructions
-----------------------------------

AllegroFlare works on Windows, Linux, and OSX.  Before compiling, you'll need to have [Allegro 5.2.0](http://liballeg.org/) or greater on your system.  If you're using `gcc` or `clang`, the process for building is the same on all systems.

#### Step 1: Clone the repo
```
$> git clone https://github.com/MarkOates/allegro_flare.git
```

#### Step 2: Set your directories in `Makefile`
At the top of the `Makefile` are 4 variables.  Edit them to point to the locations where you have Allegro and AllegroFlare on your computer.  If you're on Windows, your `LIBS_ROOT` might be something like `C:/Users/Repos/`.
```
LIBS_ROOT=/Users/markoates/Repos
ALLEGRO_DIR=$(LIBS_ROOT)/allegro5
ALLEGRO_LIB_DIR=$(LIBS_ROOT)/allegro5/build/lib
ALLEGROFLARE_DIR=$(LIBS_ROOT)/allegro_flare
```

#### Step 3: Run Make
```
$> make
```
Success!  The only thing left to do is `#include <allegro_flare/allegro_flare.h>` in your program and link with the AllegroFlare lib and the Allegro libs when compiling your program.  Optionally, you can build the example programs with `make examples`.



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
    Framework::initialize(); // initialize all things AllegroFlare
    Display *display = Framework::create_display(800, 600); // creates a new Window
    MyApp *my_app = new MyApp(display); // creates a new instance of your app
    Framework::run_loop(); // run the AllegroFlare framework
}
```



Some Examples of Features and Tools
-----------------------------------

### Framework
- Initialize (basically) everything with one function (`Framework::initialize()`)
- Interface with the system through a parent class (`Screen`)
- Use virtual member functions to grab events (`primary_timer_func()`, `mouse_axes_func()`, `joy_button_down_func()`, `key_char_func()`, etc)
- Access assets through global media bins (`Framework::bitmaps["mypic.jpg"]`, `Framework::fonts["Times.ttf 16"]`, etc)

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



UI
---

A new graphical UI has recently been merged into AllegroFlare and the features are still in beta.  To use it, first create a new screen that derives from `UIScreen` (using the UI requires using the `Framework`).  The easiest way to add widgets (buttons, checkboxes, text, etc.) is to declare them inside the constructor.


```cpp
#include <allegro_flare/allegro_flare.h>


class Project : public UIScreen
{
public:
	Project(Display *display) : UIScreen(display)
	{
		new UIText(this, 100, 100, "This is a normal text box.");
		new UIScaledText(this, 100, 150, "This is a scaled text box.  It renders smoothly when in motion.");
		new UICheckbox(this, 100, 200, 20);
		new UIButton(this, 150, 250, 100, 40, "Click Me!");
		new UIVerticalSlider(this, 110, 340, 20, 80);
		new UIVerticalSlider(this, 140, 340, 20, 80);
		new UIVerticalSlider(this, 170, 340, 20, 80);
		new UITextInput(this, 250, 450, 360, 40, "Input some text here");
	}
};


void main()
{
	Framework::initialize();
	Display *display = Framework::create_display(800, 600, NULL);
	Project *project = new Project(display);
	Framework::run_loop();
}
```

### Standard UI Widgets

* UIButton
* UICheckbox
* UIDial
* UIFramedWindow
* UIImage
* UIIntSpinner
* UILabeledCheckbox
* UIListSpinner
* UIMusicNotation
* UIProgressBar
* UIScaledText
* UIScreen
* UIScrollArea
* UIScrollBar
* UISpinner
* UIVerticalSlider
* UIText
* UITextArea
* UITextBox
* UITextInput
* UITextList
* UIToggleButton
* UIXYController
* UIWidget
* UIWindow




