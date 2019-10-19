# SpriteSheet

## Background

You may have heard the term "sprite sheet" before, but what you probably didn't know is that it comes in different forms, and, depending on how its used can have different advantages and disadvantages.

Regardless of the differences in the way an actual sprite sheet is implemented, they all have the same underlying principal.  That is, given one single big bitmap, you can access and use smaller parts of that bitmap like they were individual bitmaps themselves.

Here's an example of a sprite sheet:

![example sprite sheet](http://kidscancode.org/godot_recipes/img/Adventurer%20Sprite%20Sheet%20v1.1.png)

### Variables:
- background is a key color.  (Early days of Allegro's "magic pink"). 
- background is transparent (png)
- images are evenly tiled in a grid
- images are not evenly tiled
- uneven image grid points are inferred by blank space between sprites
- uneven image grid points are marked with special edge point pixels
- uneven image grid points are referenced through a separate list of coordinates somewhere, like in a file, or an HTML  `<map>`.
- edges from adjacent bitmaps "leak" into other bitmaps
- edges have been padded to prevent seams when rendering
- sprite sheets are "composited" from other sub bitmaps real-time

### Advantages:

- easy to maintain (don't have to have tons of individual image files to manage in your directory)
- huge performance gains for graphics hardware
- sprites can be written to real-time for effects
- sprite sheets, since they actually all exist as a single bitmap, can be tinted as a whole

### Disadvantages:

- can sometimes be difficult to know how to access the individual images
- some tools will disagree about how to refer to indexed images (Tiled indexes at 0)
- some tools (Aesprite) make it easy for you to view sprite sheets as individual files, and save them as sprite sheets without even thinking about it.
- without the right tools, it can be difficult to create sprite sheets and make sure they are aligning well.

### Usages:

- tile sets for tile maps
- frames for animation
- optimizations for rendering

## Bitmap Atlas

You may have also heard the term "bitmap atlas".  It, like a sprite sheet, is one large bitmap that contains multiple bitmaps.  It differs from a sprite sheet in that a bitmap atlas is typically implemented to optimize for graphics performance.

Rather than needing to have each separate image loaded up into the graphics card at separate address spaces, and the graphics card jumping around between memory address spaces each time it needs to draw a graphic, we only need to have a _single address space_ for a single bitmap atlas.  That way, no memory jumping even needs to occur, and we'll get increase in performance.

Bitmap atlases can be created within the computer themselves without any intervention.  In some cases, they are created automatically for you behind the scenes!  But that can vary by hardware so it's generally good to handle bitmap atlases ourselves if that's something we're looking to do.

We won't touch on this topic, since we'll get most of the benefit we're looking for using our `SpriteSheet`.


## Our `SpriteSheet`

OK!  Now that you know about sprite sheets in general, let's talk about our `SpriteSheet`.  To keep things simple, our `SpriteSheet` expects sprite images in equally spaced rows and columns.  Each image can be referenced by its `contiguous_number`, or its `[x, y]` location.

For this reason, it's advisable to keep your sprite sheets at the same number of columns when you edit it. 32 columns, 48 columns, it doesn't matter, but if you decide later on to increase the number of columns in your parent bitmap, you save the file, and then you load it up in your game.  All your previous `[x, y]` values that had previously referenced other images could now be referencing other bitmaps.

There are two other terms I want to talk about here.  "Parent bitmap", and "sub-bitmap".  These two terms refer to a more specific implementation in the Allegro5 library. [tbd]

### Automatic Seam Fixing

When you load a bitmap into a `SpriteSheet`, a completely new bitmap is actually created under the hood.  This bitmap gets processed so that each sub-bitmap is given an extra 1-pixel border around it to prevent seaming artifacts.  Each edge pixel on the original sub-bitmap's frame is extruded out to fill that 1-pixel border.
