![Allegro Flare](bin/data/bitmaps/allegro_flare_logo-04.png?raw=true) AllegroFlare
=============

* Current in-development version - v0.8.11wip on `master`
* Latest release - [v0.8.10 - Diligent Discus](https://github.com/allegroflare/allegro_flare/releases/tag/v0.8.10)


AllegroFlare is set of complementary classes for the [Allegro 5 Game Programming Library](http://liballeg.org) written in C++.

The goal of AllegroFlare is to provide a suite of higher level game programming classes that aren't otherwise a good fit for the Allegro 5 core API.  Hopefully, you may find some AllegroFlare components that make an otherwise complicated game programming task much easier to do.

> Note:
> AllegroFlare is currently in *pre-alpha*.  That is, the overall design is still maturing.  Many years of code are contained in the codebase, work perfectly well, and are well-tested.  Most if not all components work well in isolation and are perfectly usable *at your own risk* in your own software.  However, the build system for the library as a whole is currently locked to core developers. The library in its entirety will not reach alpha until `v0.9`.


## Some Examples

- Bins for media files (`FontBin`, `SampleBin`, `BitmapBin`) that make loading and managing missing assets easier
- Support multiple languages with `Internationalization`
- Manage multiple player-optional inputs (keyboards, joysticks) as a single input event source with `VirtualControls`
- Manage names, attributes, and ids of multiple objects in a scene graph with `Attributes` and `ElementID`
- Convert different datatypes to and from `JSON` for easier loading / saving
- Place and position objects in a scene with `Placement2D` and `Placement3D`
- Manage complex motion graphics effects with `Timeline/*` classes and/or the `Motion` class
- `Frameworks` for managing initialization and screen management (title screen, gameplay screen, etc)
- Build individual game screens into `Screen`s.
- Profile code with `Profiler`
- `TileMaps`
- And more...

Knowledge of Allegro 5 is expected, as you will still have direct access to all of Allegro 5 primitives and operations when using AllegroFlare.  However, you won't have to manage them as much.

## Projected Development Versions

- `v0.8.x` - (current) Product is in pre-alpha. Its build system is local, components are being added and accumulated, and design concepts are being formalized.
- `v0.9.xalpha` - Product is in alpha. Its concepts and intentions are considered mostly complete and it is currently being tested and/or prepared for public release.
- `v0.9.x` - Product is in beta. Build system and documentation is available for public use.
- `v1.0.0` - Product is released to the public, has formalized guidelines, for use and open developer contribution.


## A Simple Example Program

```cpp
#include <AllegroFlare/Framework.hpp>
#include <AllegroFlare/Screen.hpp>
#include <AllegroFlare/ScreenManager.hpp>

class ExampleProgram : public AllegroFlare::Screen
{
public:
   AllegroFlare::FontBin *font_bin;
   ExampleProgram(AllegroFlare::Display *display, AllegroFlare::FontBin *font_bin)
     : AllegroFlare::Screen(display)
     , font_bin(font_bin)
   {}

   void primary_timer_func() override
   {
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});

      ALLEGRO_FONT *font = font_bin->auto_get("Courier.ttf 16");
      al_draw_text(font, ALLEGRO_COLOR{1, 1, 1, 1}, 100, 100, 0, "Hello AllegroFlare!");
   }
};

int main(int argc, char **argv)
{
   // setup the system
   AllegroFlare::ScreenManager screens;
   AllegroFlare::Framework framework(&screens);
   framework.initialize();
   AllegroFlare::Display *display = framework.create_display(1920, 1080);

   // create the screen where our example program exists
   ExampleProgram example_program(display);

   // register the screen to the system
   screens.add(&example_program);

   // run the loop
   framework.run_loop();
}
```

## Components

At its core, `AllegroFlare` is a collection of individual classes, each called a _component_.  Each component has multiple files:

1. Header file (located in `include/` folder)
2. Source file (located in `src/` folder)
3. Documentation file (located in `docs/` folder)
4. Test file (located in `tests/` folder)
4. Example file (located in `examples/` folder)
5. Sometimes, a quintessence file, (located in `quintessence/` folder)


Each component has a filename that corresponds with a file in the same folder structure in each folder.  For example, if the component was `AllegroFlare/Timeline/Actor2D` (corresponding to the namespaced class `AllegroFlare::Timeline::Actor2D`), then the following files should be present:

1. Header file `include/AllegroFlare/Timeline/Actor2D.hpp`
2. Source file `src/AllegroFlare/Timeline/Actor2D.cpp`
3. Documentation file  `docs/AllegroFlare/Timeline/Actor2D.md`
4. Test file `tests/AllegroFlare/Timeline/Actor2DTest.cpp`
4. Example file `examples/AllegroFlare/Timeline/Actor2DExample.cpp`
5. a quintessence file `quintessence/AllegroFlare/Timeline/Actor2D.q.yml`

## In The Repo

```
bin/              <- binary files that have been compiled during build
  data/           <- data files (bitmaps, fonts, samples, etc used for programs)
demos/            <- source files for games made using AllegroFlare
docs/             <- individual `.md` documentation files, each correlating to a specific component
documentation/    <- The documentation, tutorials, etc
examples/         <- example programs, each example only demonstrating one component
include/          <- header `.hpp` files for each component
legacy/           <- folder containing old dead code that might be of interest for future reference
lib/              <- compiled `.lib` files of `allegro_flare-x.x.x` files
quintessence/     <- quintessence file `.q.yml` for each component
src/              <- source `.cpp` file for each component
tmp/
  test_snapshots/ <- screenshots captured during test runs
tests/            <- test file for each component
  fixtures/       <- fixture files for tests
tools/            <- catch-all folder for some helper scripts or random tools
```

## Contributing

- For now, create an issue and mention the changes you'd like to make.
- Otherwise, you might create a fork and then submit a pull request.  Note that a lot of components are generated from the quintessence files so modifying the `hpp` and `cpp` files directly may not be ideal.  Best to ask in an issue first how to proceed at this point.
- Consider the [style guide](https://github.com/allegroflare/allegro_flare/blob/master/documentation/style_guide.md)



