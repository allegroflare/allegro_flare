# Guide to Tile Maps

- *MultiMesh* - MultiMesh allows you to have a large number of rectangular
  objects placed arbitrarily in the world, all with their bitmaps sourced from a single
  *MultiMeshUVAtlas*.  The objects can only be positioned along the vertical and
  horizontal axes, and are not rotated or scaled. MultiMesh is designed to be
  very effecient for graphics rendering, as its underlying data is stored directly on
  the GPU.
- *TileMap* - TileMap is a template that is essentially nothing more than a two
  dimentional array with tiles of type `T`.  TileMap can be resized, and tiles
  can be set arbitrarily.  Since there is no rendering companion for the basic
  TileMap, these can be useful for containing arbtrary data for a tile, for
  example for collision data or an A\* algorithm.

