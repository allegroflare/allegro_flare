# Guide to Tile Maps

- *MultiMesh* - MultiMesh allows you to have a large number of rectangular
  objects placed arbitrarily in the world, all with their bitmaps sourced from a single
  *MultiMeshUVAtlas*.  The objects can only be positioned along the vertical and
  horizontal axes, and are not rotated or scaled. MultiMesh is designed to be
  very efficient for graphics rendering, as its underlying data is stored directly on
  the GPU.
- *TileMap* - TileMap is a template that is essentially nothing more than a two
  dimensional array with tiles of type `T`.  TileMap can be resized, and tiles
  can be set arbitrarily.  Since there is no rendering companion for the basic
  TileMap, these can be useful for containing arbtrary data for a tile, for
  example for collision data or an A\* algorithm.

# `AutoTile`

Included under `TileMaps` are a series of classes for processing.  (I'm going to
write this section quickly so that I don't spend too much time on it atm, but
hopefully there's useful info):

- `AllegroFlare::TileMaps::AutoTile::Filters::Base` - Core class that contains
  basic convolution and matrix comparison and stamping logic.

- `AllegroFlare::TileMaps::AutoTile::FilterMatrix` - A basic nxn matrix class
  that holds tile data for processing with `AutoTile::Filters::Base` derived classes.


## Input and Output matrix

Each class derived from `Base` contains an `input_matrix` and `output_matrix`.
The `input_matrix` should be filled with initial data, then you should should call `process`, which will produce
the output results to `output_matrix`.  You can then get the `output_matrix`
with `get_output_matrix` and do whatever you want with it, such as use the data to fill another tilemap.


## Examples of Already Existing Filters

You might look at these as examples of how to setup your autotile filter. Or,
you might be able to use these in your program:

- `AllegroFlare::TileMaps::AutoTile::Filters::SixteenEdges` - A slightly
  unfinished class that represents filtering (`0`= empty, `1`= solid) for a basic tilemap 
  of 16 tiles.
- `AllegroFlare::TileMaps::AutoTile::Filters::FortyEightEdges` - A completed
  class that represents filtering (`0`= empty, `1`= solid) for a more
  complicated tilemap consisting of 48 tiles.

There are a few more classes in `AutoTile/Filters/*`.

Please note that the system is designed to be very extensible, so if the example
filters above don't match your use case, it's likely that your preferred use
case could be accomodated with a different type of filter.  For example, in the
`leacy/tilemap/` folder, there is a class `TileNeighborMatcher` that filters to look for tiles that
are adjacent and identical, then processes from there.

- Note: Should eventually include a callback option for a `match_type`.

## Out of Bounds Match type

An `out_of_bounds_match_type` is used in the `iterate_through_input_and_apply_to_result_if_match` function
to determine how out of bounds tiles should be interpreted.

- `OUT_OF_BOUNDS_MATCH_TYPE_POSITIVE` - If a tile is out of bounds, that tile will
  be matched as a "positive" match.
- `OUT_OF_BOUNDS_MATCH_TYPE_NEGATIVE` - If a tile is out of bounds, that tile will
  be matched as a "negative" match.
- `OUT_OF_BOUNDS_MATCH_TYPE_EXTRUDED_EDGE` (default) - If a tile is out of bounds, that tile will
  be matched as if the `input_matrix` tiles were extruded out from the edge to
  accomodate the match.

Note: May eventually add match types for specific values, for example:
 - `_ALWAYS_SOLID_AS_1`
 - `_ALWAYS_EMPTY_AS_0`
 - `_CALLBACK` (require additional void*) param
 - `_SPECIFIED_VALUE_IS_POSITIVE` (require additional int) param
 - `_SAME_IS_POSITIVE` (or identical `_DIFFERENT_IS_NEGATIVE`)
 - `_DIFFERENT_IS_POSITIVE` from
   [here](https://github.com/allegroflare/allegro_flare/blob/master/legacy/tilemap/include/tilemap/lib/TileNeighborMatcher.hpp#L10-L12)
